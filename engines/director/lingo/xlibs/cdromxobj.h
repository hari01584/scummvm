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

#ifndef DIRECTOR_LINGO_XLIBS_CDROMXOBJ_H
#define DIRECTOR_LINGO_XLIBS_CDROMXOBJ_H

#include "backends/audiocd/audiocd.h"

namespace Director {

class CDROMXObject : public Object<CDROMXObject> {
public:
	CDROMXObject(ObjectType objType);
    AudioCDManager::Status _cdda_status;
};

namespace CDROMXObj {

extern const char *xlibName;
extern const char *fileNames[];

void open(int type);
void close(int type);

void m_new(int nargs, bool allowRetVal);
void m_name(int nargs, bool allowRetVal);
void m_play(int nargs, bool allowRetVal);
void m_playTrack(int nargs, bool allowRetVal);
void m_playName(int nargs, bool allowRetVal);
void m_playAbsTime(int nargs, bool allowRetVal);
void m_playSegment(int nargs, bool allowRetVal);
void m_askPlay(int nargs, bool allowRetVal);
void m_stepFwd(int nargs, bool allowRetVal);
void m_stepBwd(int nargs, bool allowRetVal);
void m_pause(int nargs, bool allowRetVal);
void m_continue(int nargs, bool allowRetVal);
void m_stop(int nargs, bool allowRetVal);
void m_stopTrack(int nargs, bool allowRetVal);
void m_stopAbsTime(int nargs, bool allowRetVal);
void m_removeStop(int nargs, bool allowRetVal);
void m_eject(int nargs, bool allowRetVal);
void m_status(int nargs, bool allowRetVal);
void m_playMode(int nargs, bool allowRetVal);
void m_currentFormat(int nargs, bool allowRetVal);
void m_currentTrack(int nargs, bool allowRetVal);
void m_currentTime(int nargs, bool allowRetVal);
void m_firstTrack(int nargs, bool allowRetVal);
void m_lastTrack(int nargs, bool allowRetVal);
void m_totalTime(int nargs, bool allowRetVal);
void m_scanFwd(int nargs, bool allowRetVal);
void m_scanBwd(int nargs, bool allowRetVal);
void m_stopScan(int nargs, bool allowRetVal);

} // End of namespace CDROMXObj

} // End of namespace Director

#endif
