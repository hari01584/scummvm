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

#ifndef DIRECTOR_LINGO_XLIBS_BATQT_H
#define DIRECTOR_LINGO_XLIBS_BATQT_H

namespace Director {

class BatQTXObject : public Object<BatQTXObject> {
public:
	BatQTXObject(ObjectType objType);
};

namespace BatQT {

extern const char *xlibName;
extern const char *fileNames[];

void open(int type);
void close(int type);

void m_new(int nargs, bool allowRetVal);
void m_dispose(int nargs, bool allowRetVal);
void m_name(int nargs, bool allowRetVal);
void m_status(int nargs, bool allowRetVal);
void m_error(int nargs, bool allowRetVal);
void m_lastError(int nargs, bool allowRetVal);
void m_open(int nargs, bool allowRetVal);
void m_play(int nargs, bool allowRetVal);
void m_stop(int nargs, bool allowRetVal);
void m_getTimeRange(int nargs, bool allowRetVal);
void m_getMovieBox(int nargs, bool allowRetVal);
void m_getTime(int nargs, bool allowRetVal);
void m_setTime(int nargs, bool allowRetVal);
void m_setVolume(int nargs, bool allowRetVal);
void m_length(int nargs, bool allowRetVal);
void m_setMovieBox(int nargs, bool allowRetVal);
void m_setTimeRange(int nargs, bool allowRetVal);
void m_addCallback(int nargs, bool allowRetVal);
void m_removeCallback(int nargs, bool allowRetVal);
void m_resetCallbacks(int nargs, bool allowRetVal);
void m_setBatch(int nargs, bool allowRetVal);

} // End of namespace BatQT

} // End of namespace Director

#endif
