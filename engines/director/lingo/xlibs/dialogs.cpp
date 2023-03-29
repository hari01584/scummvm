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

-- Extended
set VidFileFULLPATH to gDialogsObj(mPutFile, "Save your Total Distortion Video File!", "TDVideo", "TDV")
me(MakeACorrectFileName, VidFileFULLPATH, ".TDV")
set fileV to FileIO(mnew, "Write", VidFileFULLPATH)

set VidFileFULLPATH to gDialogsObj(mGetFile, "Find your Total Distortion Video File!", "*.TDV", "TDV")
set fileV to FileIO(mnew, "Read", VidFileFULLPATH)

method MakeACorrectFileName UserFullPath, WindowsSuffix
  set normitemDelimiter to the itemDelimiter
  set the itemDelimiter to "\"
  set TotalItemsInPath to the number of items in UserFullPath
  set filenam to item TotalItemsInPath of UserFullPath
  set LastCharN to the number of chars in filenam
  repeat with x = LastCharN down to 1
    set c to char x of filenam
    if c = "." then
      set breakOffCharN to x - 1
      exit repeat
    end if
  end repeat
  set VidFileNAME to chars(filenam, 1, breakOffCharN) & WindowsSuffix
  set VidFileFULLPATH to item 1 to TotalItemsInPath - 1 of UserFullPath & "\" & VidFileNAME
  set the itemDelimiter to normitemDelimiter

 *************************************
 *
 * USED IN:
 * Total Distortion
 *
 *************************************/

#include "gui/saveload.h"
#include "common/savefile.h"

#include "director/director.h"
#include "director/lingo/lingo.h"
#include "director/lingo/lingo-object.h"
#include "director/lingo/xlibs/dialogs.h"


namespace Director {

class DialogsSaveMetaEngine : public MetaEngine {
	Common::String _title;
	Common::String _name;
	Common::String _extension;
private:
	Common::String findFileByGameId(const Common::String &gameId) const;
public:
	DialogsSaveMetaEngine(Common::String title, Common::String name, Common::String extn);

	const char *getName() const override {
		return "DialogsSaveMetaEngine";
	}

	bool hasFeature(MetaEngineFeature f) const override;
	Common::Error createInstance(OSystem *syst, Engine **engine) override;

	SaveStateList listSaves(const char *target) const override;
	int getMaximumSaveSlot() const override;
};

DialogsSaveMetaEngine::DialogsSaveMetaEngine(Common::String title, Common::String name, Common::String extn) {
	_title = title;
	_name = name;
	_extension = extn;
}

bool DialogsSaveMetaEngine::hasFeature(MetaEngineFeature f) const {
	return f == kSupportsListSaves; // Only supporting saves
}

Common::Error DialogsSaveMetaEngine::createInstance(OSystem *syst, Engine **engine) {
	return Common::kNoError; // Dummy engine
}

SaveStateList DialogsSaveMetaEngine::DialogsSaveMetaEngine::listSaves(const char *target) const {
	Common::SaveFileManager *saveFileMan = g_system->getSavefileManager();
	SaveStateList saveList;

	// Bruteforce each slot and check if a matching file exist! If yes then adds to saveslotlist
	for (int slot = 0; slot < getMaximumSaveSlot(); slot++) {
		Common::String filen = Common::String::format("%s-%02d\\.%s.txt", target, slot, _extension.c_str());
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

/* --------------- Dummy Meta Engine Ends --------------- */

Common::String getFileName(Common::String title, Common::String defaultName, Common::String extension, bool isSave) {
	Common::String label = isSave ? "Save" : "Load";
	Common::String buttonLabel = Common::String::format("%s %s file!", label.c_str(), extension.c_str());
	
	DialogsSaveMetaEngine *dummyEngine = new DialogsSaveMetaEngine(title, defaultName, extension); // Create dummy engine for saves!
	GUI::SaveLoadChooser *dialog = new GUI::SaveLoadChooser(title, buttonLabel, true);
	int saveSlot = dialog->runModalWithMetaEngineAndTarget(dummyEngine, g_director->getTargetName()); // Get slot!
	delete dialog;
	delete dummyEngine;

	// If slots < 0, ie invalid, then use default one (ie slot 0)
	if (saveSlot <= 0) {
		saveSlot = 0;
	}

	// Create filename from slot, here if slot is 4, then filename will simply be 04!
	Common::String fileName = Common::String::format("%02d", saveSlot);

	return fileName;
}

/* --------------- Helper Function Ends --------------- */

const char *DialogsXObj::xlibNames[] = {
	"DialogS",
	nullptr
};

const char *DialogsXObj::fileNames[] = {
	"DialogS",
	"shaREQUE", // TD loads this up using openXLib("@:shaREQUE.DLL")
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
	Datum d3 = g_lingo->pop();
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	Common::String title = d1.asString();
	Common::String name = d2.asString();
	Common::String extn = d3.asString();

	Common::String fileName = getFileName(title, name, extn, true);
	g_lingo->push(Datum(fileName));
}

void DialogsXObj::m_getFile(int nargs) {
	Datum d3 = g_lingo->pop();
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	Common::String title = d1.asString();
	Common::String name = d2.asString();
	Common::String extn = d3.asString();

	Common::String fileName = getFileName(title, name, extn, true);
	// Format filename to returning format filename\.{extension} string, ie for slot 04 and extn TDG, filename will be "04\.TDG"
	// this is done because in m_putFile, the returned path is corrected internally lingo script using MakeACorrectFileName handler(in comments top)
	// which is then fed to FileIO for saving, all this creates filename to be in this format!
	fileName = Common::String::format("%s\\.%s", fileName.c_str(), extn.c_str());

	g_lingo->push(Datum(fileName));
}

} // End of namespace Director
