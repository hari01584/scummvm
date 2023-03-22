/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#define FORBIDDEN_SYMBOL_EXCEPTION_FILE

#include "common/inttypes.h"
#include "common/ptr.h"
#include "common/stream.h"
#include "common/textconsole.h"
#include "common/util.h"

#include "audio/audiostream.h"
#include "audio/decoders/raw.h"

#include "impulsetracker.h"

extern "C" {
#include <mikmod.h>
}

// Start memory wrapper
// Extras, mikmod mreader struct to wrap readstream
typedef struct _MY_MEMREADER {
	MREADER core;
	const void *buffer;
	Common::SeekableReadStream *base;
	long len;
	long pos;
} MY_MEMREADER;

static BOOL My_MemReader_Eof(MREADER *reader);
static BOOL My_MemReader_Read(MREADER *reader, void *ptr, size_t size);
static int  My_MemReader_Get(MREADER *reader);
static int  My_MemReader_Seek(MREADER *reader, long offset, int whence);
static long My_MemReader_Tell(MREADER *reader);

MREADER *my_new_mem_reader(Common::SeekableReadStream *base);
void my_delete_mem_reader(MREADER *reader);

void my_delete_mem_reader(MREADER *reader) {
	if (reader) free(reader);
}

MREADER *my_new_mem_reader(Common::SeekableReadStream *base) {
	MY_MEMREADER *reader = (MY_MEMREADER *) calloc(1, sizeof(MY_MEMREADER));
	if (reader) {
		reader->core.Eof = &My_MemReader_Eof;
		reader->core.Read = &My_MemReader_Read;
		reader->core.Get = &My_MemReader_Get;
		reader->core.Seek = &My_MemReader_Seek;
		reader->core.Tell = &My_MemReader_Tell;
		reader->base = base;
	}
	return (MREADER *)reader;
}

static BOOL My_MemReader_Eof(MREADER *reader) {
	MY_MEMREADER *mr = (MY_MEMREADER *) reader;
	if (!mr) return 1;
	if (mr->base && mr->base->eos() == true) return 1;
	return 0;
}

static BOOL My_MemReader_Read(MREADER *reader, void *ptr, size_t size) {
	MY_MEMREADER *mr;
	mr = (MY_MEMREADER *) reader;

	if (!mr && !mr->base) return 0;

	uint32 si = mr->base->read(ptr, size);

	if (si < size) return 0; // not enough remaining bytes (or error)
	return 1;
}

static int My_MemReader_Get(MREADER *reader) {
	MY_MEMREADER *mr;

	mr = (MY_MEMREADER *) reader;
	if (!mr->base) return -1;
	return mr->base->readByte();;
}

static int My_MemReader_Seek(MREADER *reader, long offset, int whence) {
	MY_MEMREADER *mr;

	if (!reader) return -1;
	mr = (MY_MEMREADER *) reader;
	if (!mr->base) return -1;

	return mr->base->seek(offset, whence);
}

static long My_MemReader_Tell(MREADER *reader) {
	if (reader) {
		return ((MY_MEMREADER *)reader)->base->pos();
	}
	return 0;
}

// End memory wrappper


namespace Audio {
class ImpulseTrackerMod : public AudioStream {
public:
	ImpulseTrackerMod(Common::SeekableReadStream *stream, DisposeAfterUse::Flag disposeAfterUse);
	~ImpulseTrackerMod();

	// AudioStream API
	int readBuffer(int16 *buffer, const int numSamples) override {
		VC_WriteBytes((SBYTE *)buffer, numSamples * 2);
		return numSamples;
	}

	bool isStereo() const override {
		return true;
	}
	int getRate() const override {
		return 44100;
	}
	bool endOfData() const override {
		return !Player_Active();
	}
	bool endOfStream() const override {
		return endOfData();
	}

private:
	DisposeAfterUse::Flag dispose;

	bool mikmod_load_successful = true;
	// Private for class use vars
	Common::SeekableReadStream *s;
	MREADER *reader;
	MODULE *mod;

	bool initMikMod();
	void freeMikMod();
};

bool ImpulseTrackerMod::initMikMod() {
	MikMod_InitThreads();

	// No sound driver as we will be routing through scrumm mixer!
	MikMod_RegisterDriver(&drv_nos);

	// See flags
	md_mode |= DMODE_SOFT_MUSIC | DMODE_NOISEREDUCTION;

	md_mixfreq = 44100;
	if (MikMod_Init("")) {
		mikmod_load_successful = false;
		warning("Could not initialize sound, reason: %s\n",
		        MikMod_strerror(MikMod_errno));
		return false;
	}

	// Loading only impulse tracker loader!
	MikMod_RegisterLoader(&load_it);
	return true;
}

void ImpulseTrackerMod::freeMikMod() {
	MikMod_Exit();
}

ImpulseTrackerMod::ImpulseTrackerMod(Common::SeekableReadStream *stream, DisposeAfterUse::Flag disposeAfterUse) {
	if (!stream) {
		mikmod_load_successful = false;
		warning("Bad impulse tracker stream");
		return;
	}

	s = stream;
	dispose = disposeAfterUse;

	if (!initMikMod()) return;

	// Load mod using custom loader class!
	reader = my_new_mem_reader(s);
	mod = Player_LoadGeneric(reader, 64, 0);
	if (!mod) {
		mikmod_load_successful = false;
		warning("mod file problem %s", MikMod_strerror(MikMod_errno));
		return;
	}
	// warning("Playing %s", mod->songname);

	// Start mikmod playing, ie fill VC_Driver buffer with data
	if (mod) Player_Start(mod);
}

ImpulseTrackerMod::~ImpulseTrackerMod() {
	freeMikMod();

	Player_Stop();
	if (mod) Player_Free(mod);
	if (reader) my_delete_mem_reader(reader);

	// Delete stream pointer or free it?
	// if (s) delete s;
}

AudioStream *makeImpulseStream(Common::SeekableReadStream *stream, DisposeAfterUse::Flag disposeAfterUse) {
	ImpulseTrackerMod *itm = new ImpulseTrackerMod(stream, disposeAfterUse);
	return itm;
}

} // End of namespace Audio