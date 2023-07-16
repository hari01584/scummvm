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

#ifndef DIRECTOR_FRAME_H
#define DIRECTOR_FRAME_H

namespace Image {
class ImageDecoder;
}

namespace Graphics {
class ManagedSurface;
struct Surface;
}

namespace Common {
class ReadStreamEndian;
class MemoryReadStreamEndian;
}

namespace Director {

class Score;
class Sprite;
class TextCastMember;

enum {
	kMainChannelSizeD2 = 32,
	kSprChannelSizeD2 = 16,

	kMainChannelSizeD4 = 40,
	kSprChannelSizeD4 = 20,

	kMainChannelSizeD5 = 48,
	kSprChannelSizeD5 = 24,

	kMainChannelSizeD6 = 48,
	kSprChannelSizeD6 = 24,
};

struct PaletteInfo {
	CastMemberID paletteId;

	byte firstColor;
	byte lastColor;
	byte flags;
	bool colorCycling;
	bool normal;
	bool fadeToWhite;
	bool fadeToBlack;
	bool autoReverse;
	bool overTime;
	byte speed;
	uint16 frameCount;
	uint16 cycleCount;
	byte fade;
	byte delay;
	byte style;
	byte colorCode;

	PaletteInfo() {
		paletteId = CastMemberID(0, 0);
		firstColor = lastColor = 0;
		flags = 0; colorCycling = false;
		normal = false; fadeToWhite = false;
		fadeToBlack = false; autoReverse = false;
		overTime = false; speed = 0;
		frameCount = cycleCount = 0;
		fade = delay = style = colorCode = 0;
	}
};

struct MainChannels {
	CastMemberID _actionId;
	uint16 _transDuration;
	uint8 _transArea; // 1 - Whole Window, 0 - Changing Area
	uint8 _transChunkSize;
	TransitionType _transType;
	CastMemberID _trans;
	PaletteInfo _palette;
	uint8 _tempo;

	uint8 _scoreCachedTempo;
	CastMemberID _scoreCachedPaletteId;

	CastMemberID _sound1;
	uint8 _soundType1;
	CastMemberID _sound2;
	uint8 _soundType2;

	byte _colorTempo;
	byte _colorSound1;
	byte _colorSound2;
	byte _colorScript;
	byte _colorTrans;

	uint8 _skipFrameFlag;
	uint8 _blend;

	MainChannels() {
		_transDuration = 0;
		_transType = kTransNone;
		_transArea = 0;
		_transChunkSize = 0;
		_tempo = 0;

		_scoreCachedTempo = 0;
		_scoreCachedPaletteId = CastMemberID(0, 0);

		_sound1 = CastMemberID(0, 0);
		_sound2 = CastMemberID(0, 0);
		_soundType1 = 0;
		_soundType2 = 0;

		_actionId = CastMemberID(0, 0);
		_skipFrameFlag = 0;
		_blend = 0;

		_colorTempo = 0;
		_colorSound1 = 0;
		_colorSound2 = 0;
		_colorScript = 0;
		_colorTrans = 0;
	}

	MainChannels(const MainChannels &old) : _actionId(old._actionId), _transDuration(old._transDuration),
											_transArea(old._transArea), _transChunkSize(old._transChunkSize),
											_transType(old._transType), _trans(old._trans),
											_palette(old._palette), _tempo(old._tempo),
											_scoreCachedTempo(old._scoreCachedTempo), _scoreCachedPaletteId(old._scoreCachedPaletteId),
											_sound1(old._sound1), _soundType1(old._soundType1),
											_sound2(old._sound2), _soundType2(old._soundType2),
											_colorTempo(old._colorTempo), _colorSound1(old._colorSound1),
											_colorSound2(old._colorSound2), _colorScript(old._colorScript),
											_colorTrans(old._colorTrans), _skipFrameFlag(old._skipFrameFlag),
											_blend(old._blend) {}

	MainChannels& operator=(const MainChannels& mainChannels) {
		_actionId = mainChannels._actionId;
		_transDuration = mainChannels._transDuration;
		_transArea = mainChannels._transArea;
		_transChunkSize = mainChannels._transChunkSize;
		_transType = mainChannels._transType;
		_trans = mainChannels._trans;
		_palette = mainChannels._palette;
		_tempo = mainChannels._tempo;
		_scoreCachedTempo = mainChannels._scoreCachedTempo;
		_scoreCachedPaletteId = mainChannels._scoreCachedPaletteId;
		_sound1 = mainChannels._sound1;
		_soundType1 = mainChannels._soundType1;
		_sound2 = mainChannels._sound2;
		_soundType2 = mainChannels._soundType2;
		_colorTempo = mainChannels._colorTempo;
		_colorSound1 = mainChannels._colorSound1;
		_colorSound2 = mainChannels._colorSound2;
		_colorScript = mainChannels._colorScript;
		_colorTrans = mainChannels._colorTrans;
		_skipFrameFlag = mainChannels._skipFrameFlag;
		_blend = mainChannels._blend;

		return *this;
	}
};

struct FrameEntity {
	uint16 spriteId;
	Common::Rect rect;
};


class Frame {
public:
	Frame(Score *score, int numChannels);
	Frame(const Frame &frame);
	~Frame();

	void reset();

	Score *getScore() const { return _score; }

	void readChannel(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size, uint16 version);

	void executeImmediateScripts();

	Common::String formatChannelInfo();

private:

	void readChannelD2(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);
	void readSpriteD2(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);
	void readMainChannelsD2(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);

	void readChannelD4(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);
	void readSpriteD4(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);
	void readMainChannelsD4(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);

	void readChannelD5(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);
	void readSpriteD5(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);
	void readMainChannelsD5(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);

	void readChannelD6(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);
	void readSpriteD6(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);
	void readMainChannelsD6(Common::MemoryReadStreamEndian &stream, uint16 offset, uint16 size);

	Image::ImageDecoder *getImageFrom(uint16 spriteId);
	Common::String readTextStream(Common::SeekableReadStreamEndian *textStream, TextCastMember *textCast);


public:
	int _numChannels;
	MainChannels _mainChannels;
	Common::Array<Sprite *> _sprites;
	Score *_score;
	DirectorEngine *_vm;
};

void readSpriteDataD2(Common::SeekableReadStreamEndian &stream, Sprite &sprite, uint32 startPosition, uint32 finishPosition);
void readSpriteDataD4(Common::SeekableReadStreamEndian &stream, Sprite &sprite, uint32 startPosition, uint32 finishPosition);
void readSpriteDataD5(Common::SeekableReadStreamEndian &stream, Sprite &sprite, uint32 startPosition, uint32 finishPosition);
void readSpriteDataD6(Common::SeekableReadStreamEndian &stream, Sprite &sprite, uint32 startPosition, uint32 finishPosition);

} // End of namespace Director

#endif
