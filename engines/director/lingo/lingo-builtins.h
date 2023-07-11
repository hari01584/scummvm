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

#ifndef DIRECTOR_LINGO_BUILTINS_H
#define DIRECTOR_LINGO_BUILTINS_H

#include "director/lingo/lingo-utils.h"

namespace Director {

namespace LB {

// builtin functions
DECLAREBUILTIN(b_abs)
DECLAREBUILTIN(b_atan)
DECLAREBUILTIN(b_cos)
DECLAREBUILTIN(b_exp)
DECLAREBUILTIN(b_float)
DECLAREBUILTIN(b_integer)
DECLAREBUILTIN(b_log)
DECLAREBUILTIN(b_pi)
DECLAREBUILTIN(b_power)
DECLAREBUILTIN(b_random)
DECLAREBUILTIN(b_sin)
DECLAREBUILTIN(b_sqrt)
DECLAREBUILTIN(b_tan)

DECLAREBUILTIN(b_chars)
DECLAREBUILTIN(b_charToNum)
DECLAREBUILTIN(b_length)
DECLAREBUILTIN(b_numToChar)
DECLAREBUILTIN(b_offset)
DECLAREBUILTIN(b_string)

DECLAREBUILTIN(b_add)
DECLAREBUILTIN(b_addAt)
DECLAREBUILTIN(b_addProp)
DECLAREBUILTIN(b_append)
DECLAREBUILTIN(b_count)
DECLAREBUILTIN(b_deleteAt)
DECLAREBUILTIN(b_deleteOne)
DECLAREBUILTIN(b_deleteProp)
DECLAREBUILTIN(b_findPos)
DECLAREBUILTIN(b_findPosNear)
DECLAREBUILTIN(b_getaProp)
DECLAREBUILTIN(b_getAt)
DECLAREBUILTIN(b_getLast)
DECLAREBUILTIN(b_getOne)
DECLAREBUILTIN(b_getPos)
DECLAREBUILTIN(b_getProp)
DECLAREBUILTIN(b_getPropAt)
DECLAREBUILTIN(b_list)
DECLAREBUILTIN(b_listP)
DECLAREBUILTIN(b_max)
DECLAREBUILTIN(b_min)
DECLAREBUILTIN(b_setaProp)
DECLAREBUILTIN(b_setAt)
DECLAREBUILTIN(b_setProp)
DECLAREBUILTIN(b_sort)

DECLAREBUILTIN(b_factory)
DECLAREBUILTIN(b_floatP)
DECLAREBUILTIN(b_ilk)
DECLAREBUILTIN(b_integerp)
DECLAREBUILTIN(b_objectp)
DECLAREBUILTIN(b_pictureP)
DECLAREBUILTIN(b_stringp)
DECLAREBUILTIN(b_symbolp)
DECLAREBUILTIN(b_voidP)

DECLAREBUILTIN(b_alert)
DECLAREBUILTIN(b_clearGlobals)
DECLAREBUILTIN(b_cursor)
DECLAREBUILTIN(b_framesToHMS)
DECLAREBUILTIN(b_HMStoFrames)
DECLAREBUILTIN(b_param)
DECLAREBUILTIN(b_printFrom)
DECLAREBUILTIN(b_put)
DECLAREBUILTIN(b_showGlobals)
DECLAREBUILTIN(b_showLocals)
DECLAREBUILTIN(b_value)

DECLAREBUILTIN(b_constrainH)
DECLAREBUILTIN(b_constrainV)
DECLAREBUILTIN(b_copyToClipBoard)
DECLAREBUILTIN(b_duplicate)
DECLAREBUILTIN(b_editableText)
DECLAREBUILTIN(b_erase)
DECLAREBUILTIN(b_findEmpty)
DECLAREBUILTIN(b_importFileInto)
DECLAREBUILTIN(b_installMenu)
DECLAREBUILTIN(b_label)
DECLAREBUILTIN(b_marker)
DECLAREBUILTIN(b_move)
DECLAREBUILTIN(b_moveableSprite)
DECLAREBUILTIN(b_pasteClipBoardInto)
DECLAREBUILTIN(b_puppetPalette)
DECLAREBUILTIN(b_puppetSound)
DECLAREBUILTIN(b_puppetSprite)
DECLAREBUILTIN(b_puppetTempo)
DECLAREBUILTIN(b_puppetTransition)
DECLAREBUILTIN(b_ramNeeded)
DECLAREBUILTIN(b_rollOver)
DECLAREBUILTIN(b_spriteBox)
DECLAREBUILTIN(b_unLoad)
DECLAREBUILTIN(b_unLoadCast)
DECLAREBUILTIN(b_updateStage)
DECLAREBUILTIN(b_zoomBox)
DECLAREBUILTIN(b_immediateSprite)

DECLAREBUILTIN(b_abort)
DECLAREBUILTIN(b_continue)
DECLAREBUILTIN(b_dontPassEvent)
DECLAREBUILTIN(b_delay)
DECLAREBUILTIN(b_do)
DECLAREBUILTIN(b_go)
DECLAREBUILTIN(b_halt)
DECLAREBUILTIN(b_nothing)
DECLAREBUILTIN(b_pass)
DECLAREBUILTIN(b_pause)
DECLAREBUILTIN(b_play)
DECLAREBUILTIN(b_playAccel)
DECLAREBUILTIN(b_preLoad)
DECLAREBUILTIN(b_preLoadCast)
DECLAREBUILTIN(b_quit)
DECLAREBUILTIN(b_restart)
DECLAREBUILTIN(b_shutDown)
DECLAREBUILTIN(b_startTimer)
DECLAREBUILTIN(b_return)

DECLAREBUILTIN(b_closeDA)
DECLAREBUILTIN(b_closeResFile)
DECLAREBUILTIN(b_closeXlib)
DECLAREBUILTIN(b_getNthFileNameInFolder)
DECLAREBUILTIN(b_open)
DECLAREBUILTIN(b_openDA)
DECLAREBUILTIN(b_openResFile)
DECLAREBUILTIN(b_openXlib)
DECLAREBUILTIN(b_setCallBack)
DECLAREBUILTIN(b_saveMovie)
DECLAREBUILTIN(b_showResFile)
DECLAREBUILTIN(b_showXlib)
DECLAREBUILTIN(b_xFactoryList)

DECLAREBUILTIN(b_point)
DECLAREBUILTIN(b_inside)
DECLAREBUILTIN(b_intersect)
DECLAREBUILTIN(b_map)
DECLAREBUILTIN(b_offsetRect)
DECLAREBUILTIN(b_rect)
DECLAREBUILTIN(b_union)

DECLAREBUILTIN(b_window)

DECLAREBUILTIN(b_beep)
DECLAREBUILTIN(b_mci)
DECLAREBUILTIN(b_mciwait)
DECLAREBUILTIN(b_sound)
DECLAREBUILTIN(b_soundBusy)

DECLAREBUILTIN(b_backspace)
DECLAREBUILTIN(b_empty)
DECLAREBUILTIN(b_enter)
DECLAREBUILTIN(b_false)
DECLAREBUILTIN(b_quote)
DECLAREBUILTIN(b_returnconst)
DECLAREBUILTIN(b_tab)
DECLAREBUILTIN(b_true)
DECLAREBUILTIN(b_version)

DECLAREBUILTIN(b_cast)
DECLAREBUILTIN(b_script)

DECLAREBUILTIN(b_numberofchars)
DECLAREBUILTIN(b_numberofitems)
DECLAREBUILTIN(b_numberoflines)
DECLAREBUILTIN(b_numberofwords)

DECLAREBUILTIN(b_scummvmassert)
DECLAREBUILTIN(b_scummvmassertequal)

// XCMD/XFCN (HyperCard), normally exposed
DECLAREBUILTIN(b_getVolumes)

} // End of namespace LB

} // End of namespace Director

#endif
