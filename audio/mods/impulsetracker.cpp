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
#include "audio/decoders/ac3.h"
#include "audio/decoders/raw.h"

#include "impulsetracker.h"

extern "C" {
#include <mikmod.h>
}

namespace Audio {

class ImpulseTrackerMod : public AudioStream {
public:
	ImpulseTrackerMod(Common::SeekableReadStream *stream){}
	~ImpulseTrackerMod(){}


	// AudioStream API
	int readBuffer(int16 *buffer, const int numSamples) override {
        // int8 *buf8 = (int8*)malloc(numSamples*sizeof(int8));

        VC_WriteBytes((SBYTE*)buffer, numSamples*2);

        // // Now convert to buffer!
        // for(int i=0; i<numSamples; i++){
        //     *buffer = (int16) (*buf8 - 0x80) << 8;
        //     buffer++;
        //     buf8++;
        // }

        // free(buf8);
        
        return numSamples;
    }

	bool isStereo() const override { return true; }
	int getRate() const override { return 44100; }
	bool endOfData() const override { return false; }
	bool endOfStream() const override { return endOfData(); }
};

AudioStream *makeImpulseStream(Common::SeekableReadStream *stream, DisposeAfterUse::Flag disposeAfterUse) {
    ImpulseTrackerMod *itm = new ImpulseTrackerMod(stream);

    return itm;
}

} // End of namespace Audio