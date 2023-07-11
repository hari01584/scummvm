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

#ifndef DIRECTOR_LINGO_XLIBS_ORTHOPLAYXOBJ_H
#define DIRECTOR_LINGO_XLIBS_ORTHOPLAYXOBJ_H

namespace Director {

class OrthoPlayXObject : public Object<OrthoPlayXObject> {
public:
	OrthoPlayXObject(ObjectType objType);
};

namespace OrthoPlayXObj {

extern const char *xlibName;
extern const char *fileNames[];

void open(int type);
void close(int type);

void m_new(int nargs, bool allowRetVal);
void m_setSerialPort(int nargs, bool allowRetVal);
void m_setInitViaDlog(int nargs, bool allowRetVal);
void m_getInitInfo(int nargs, bool allowRetVal);
void m_setInitInfo(int nargs, bool allowRetVal);
void m_getMaxDevices(int nargs, bool allowRetVal);
void m_getDeviceTitle(int nargs, bool allowRetVal);
void m_setDevice(int nargs, bool allowRetVal);
void m_selectDevice(int nargs, bool allowRetVal);
void m_getDevice(int nargs, bool allowRetVal);
void m_service(int nargs, bool allowRetVal);
void m_getValue(int nargs, bool allowRetVal);
void m_cancel(int nargs, bool allowRetVal);
void m_explain(int nargs, bool allowRetVal);
void m_idle(int nargs, bool allowRetVal);
void m_readStatus(int nargs, bool allowRetVal);
void m_readPos(int nargs, bool allowRetVal);
void m_searchTo(int nargs, bool allowRetVal);
void m_play(int nargs, bool allowRetVal);
void m_still(int nargs, bool allowRetVal);
void m_stop(int nargs, bool allowRetVal);
void m_scanForward(int nargs, bool allowRetVal);
void m_scanReverse(int nargs, bool allowRetVal);
void m_playReverse(int nargs, bool allowRetVal);
void m_fastForward(int nargs, bool allowRetVal);
void m_rewind(int nargs, bool allowRetVal);
void m_stepForward(int nargs, bool allowRetVal);
void m_stepReverse(int nargs, bool allowRetVal);
void m_shuttle(int nargs, bool allowRetVal);
void m_record(int nargs, bool allowRetVal);
void m_eject(int nargs, bool allowRetVal);
void m_prepareMedium(int nargs, bool allowRetVal);
void m_getFirstTrack(int nargs, bool allowRetVal);
void m_getLastTrack(int nargs, bool allowRetVal);
void m_getFirstFrame(int nargs, bool allowRetVal);
void m_getLastFrame(int nargs, bool allowRetVal);
void m_getTrack(int nargs, bool allowRetVal);
void m_resetCounter(int nargs, bool allowRetVal);
void m_audioEnable(int nargs, bool allowRetVal);
void m_audioMute(int nargs, bool allowRetVal);
void m_videoEnable(int nargs, bool allowRetVal);
void m_showFrame(int nargs, bool allowRetVal);
void m_getFrameResolution(int nargs, bool allowRetVal);
void m_setFrameResolution(int nargs, bool allowRetVal);
void m_hasDropFrames(int nargs, bool allowRetVal);
void m_sendRaw(int nargs, bool allowRetVal);
void m_readRaw(int nargs, bool allowRetVal);
void m_setInPoint(int nargs, bool allowRetVal);
void m_setOutPoint(int nargs, bool allowRetVal);
void m_setDuration(int nargs, bool allowRetVal);
void m_getMinDuration(int nargs, bool allowRetVal);
void m_setPreroll(int nargs, bool allowRetVal);
void m_getPreroll(int nargs, bool allowRetVal);
void m_setPostroll(int nargs, bool allowRetVal);
void m_getPostroll(int nargs, bool allowRetVal);
void m_setFieldDominance(int nargs, bool allowRetVal);
void m_playCue(int nargs, bool allowRetVal);
void m_playSegment(int nargs, bool allowRetVal);
void m_recordCue(int nargs, bool allowRetVal);
void m_recordSegment(int nargs, bool allowRetVal);
void m_recordVideoEnable(int nargs, bool allowRetVal);
void m_recordAudioEnable(int nargs, bool allowRetVal);
void m_assembleRecord(int nargs, bool allowRetVal);
void m_previewRecord(int nargs, bool allowRetVal);
void m_gotoInPoint(int nargs, bool allowRetVal);
void m_gotoOutPoint(int nargs, bool allowRetVal);
void m_gotoPrerollPoint(int nargs, bool allowRetVal);
void m_gotoPostrollPoint(int nargs, bool allowRetVal);

} // End of namespace OrthoPlayXObj

} // End of namespace Director

#endif
