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

/*
-- Dialogs XObject. Written by Scott Kildall. Copyright (c) Red Eye Software, December 11th, 1994.
Compuserve:72703,451 AOL:KILDALL  APPLELINK:S.KILDALL
Internet:72703.451@compuserve.com
Licensed for the MediaBook CD for Director
Published by gray matter design (415) 243-0394
Dialogs
X        mNew          --Creates a new instance of the XObject
SSSS     mPutFile, Dialog Title, Default Name, Default Extension       --Displays a save dialog box
SSSS     mGetFile, Dialog Title, Default Name, Default Extension       --Displays an open dialog box

-- How it is called:
set GameFileFULLPATH to gDialogsObj(mPutFile, "Save your Total Distortion Game File!", "TDGame", "TDG")
set GameFileFULLPATH to gDialogsObj(mGetFile, "Find your Total Distortion Game File!", "*.TDG", "TDG")

 *************************************
 *
 * USED IN:
 * Total Distortion
 *
 *************************************/

#include "gui/saveload.h"
#include <common/savefile.h>
#include "common/translation.h"
#include "common/config-manager.h"

#include "director/director.h"
#include "director/lingo/lingo.h"
#include "director/lingo/lingo-object.h"
#include "director/lingo/xlibs/dialogs.h"


namespace Director {
Common::String getSaveStateName(int slot) {
	return Common::String::format("%02d", slot);
}

class DialogsSaveMetaEngine : public MetaEngine {
private:
	Common::String findFileByGameId(const Common::String &gameId) const;
public:
	const char *getName() const override {
		return "DialogsSaveMetaEngine";
	}

	bool hasFeature(MetaEngineFeature f) const override;
	Common::Error createInstance(OSystem *syst, Engine **engine) override;

	SaveStateList listSaves(const char *target) const override;
	int getMaximumSaveSlot() const override;
};

bool DialogsSaveMetaEngine::hasFeature(MetaEngineFeature f) const {
	return f == kSupportsListSaves;
}

Common::Error DialogsSaveMetaEngine::createInstance(OSystem *syst, Engine **engine) {
	return Common::kNoError; // Dummy engine
}

SaveStateList DialogsSaveMetaEngine::DialogsSaveMetaEngine::listSaves(const char *target) const {
	Common::SaveFileManager *saveFileMan = g_system->getSavefileManager();
	SaveStateList saveList;

	for (int slot = 0; slot < getMaximumSaveSlot(); slot++) {
		Common::String filen = Common::String::format("%s-%02d\\.TDG.txt", target, slot);
		Common::InSaveFile *in = saveFileMan->openForLoading(filen);
		if (in) {
			Common::String desc = Common::String::format("%s.%02d", target, slot);
			saveList.push_back(SaveStateDescriptor(this, slot, desc));
			delete in;
		}
	}

	// Sort saves based on slot number.
	Common::sort(saveList.begin(), saveList.end(), SaveStateDescriptorSlotComparator());
	return saveList;
}

int DialogsSaveMetaEngine::DialogsSaveMetaEngine::getMaximumSaveSlot() const {
	return 99;
}

const char *DialogsXObj::xlibNames[] = {
	"DialogS",
	nullptr
};

const char *DialogsXObj::fileNames[] = {
	"DialogS",
	"@:shaREQUE", // TD loads this up using openXLib("@:shaREQUE.DLL")
	nullptr
};

static MethodProto xlibMethods[] = {
	{ "new",               DialogsXObj::m_new,              0, 0,  400 },  // D4
	{ "GetFile",           DialogsXObj::m_getFile,          3, 3,  400 },  // D4
	{ "PutFile",           DialogsXObj::m_putFile,          3, 3,  400 },  // D4
	{ nullptr, nullptr, 0, 0, 0 }
};

void DialogsXObj::open(int type) {
	if (type == kXObj) {
		DialogsXObject::initMethods(xlibMethods);
		DialogsXObject *xobj = new DialogsXObject(kXObj);
		for (uint i = 0; xlibNames[i]; i++) {
			g_lingo->exposeXObject(xlibNames[i], xobj);
		}
	}
}

void DialogsXObj::close(int type) {
	if (type == kXObj) {
		DialogsXObject::cleanupMethods();
		for (uint i = 0; xlibNames[i]; i++) {
			g_lingo->_globalvars[xlibNames[i]] = Datum();
		}
	}
}


DialogsXObject::DialogsXObject(ObjectType ObjectType) : Object<DialogsXObject>("DialogS") {
	_objType = ObjectType;
}

void DialogsXObj::m_new(int nargs) {
	g_lingo->push(g_lingo->_state->me);
}

void DialogsXObj::m_putFile(int nargs) {
	// g_lingo->printSTUBWithArglist("DialogsXObj::m_getFile", nargs);
	g_lingo->dropStack(nargs);

	DialogsSaveMetaEngine *dummyEngine = new DialogsSaveMetaEngine();
	GUI::SaveLoadChooser *dialog = new GUI::SaveLoadChooser(_("Save game:"), _("Save"), true);
	int saveSlot = dialog->runModalWithMetaEngineAndTarget(dummyEngine, g_director->getTargetName());
	delete dialog;
	delete dummyEngine;

	Common::String fileName = getSaveStateName(saveSlot);
	g_lingo->push(Datum(fileName));
}

void DialogsXObj::m_getFile(int nargs) {
	// g_lingo->printSTUBWithArglist("DialogsXObj::m_getFile", nargs);
	g_lingo->dropStack(nargs);

	DialogsSaveMetaEngine *dummyEngine = new DialogsSaveMetaEngine();
	GUI::SaveLoadChooser *dialog = new GUI::SaveLoadChooser(_("Restore game:"), _("Restore"), false);
	int saveSlot = dialog->runModalWithMetaEngineAndTarget(dummyEngine, g_director->getTargetName());
	delete dialog;
	delete dummyEngine;

	Common::String fileName = getSaveStateName(saveSlot) + "\\.TDG";

	g_lingo->push(Datum(fileName));
}

} // End of namespace Director
