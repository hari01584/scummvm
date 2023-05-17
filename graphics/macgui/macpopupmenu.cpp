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

#include "graphics/macgui/macpopupmenu.h"
#include "graphics/macgui/macwindowmanager.h"

namespace Graphics {

MacPopUp::MacPopUp(int id, const Common::Rect &bounds, MacWindowManager *wm, const char *string) : MacMenu(id, bounds, wm) {
	_windowsRect = _windowsRect;
	_menuItemId = addMenuItem(nullptr, "");
	createSubMenuFromString(0, string, 0);
	wm->addMenu(id, this);
	_menuId = id;

}

bool MacPopUp::draw(ManagedSurface *g, bool forceRedraw) {
	// debug("Am i being called to draw? 36");
	_bbox.bottom = 1;

	if (!_isVisible)
		return false;

	if (_dimensionsDirty)
		calcDimensions(_mouseX, _mouseY);

	if (!_contentIsDirty && !forceRedraw)
		return false;
	_contentIsDirty = false;

	_screen.clear(_wm->_colorGreen);
	renderSubmenu(_items[0]->submenu, false);

	if (g)
		g->transBlitFrom(_screen, _wm->_colorGreen);

	if (!(_wm->_mode & kWMModalMenuMode) && g)
		g_system->copyRectToScreen(g->getPixels(), g->pitch, 0, 0, g->w, g->h);

	return true;
}

uint32 MacPopUp::drawAndSelectMenu(int x, int y, int item) {
	// Transform window coordinate to screen coordinates
	// TODO: Performance degradation when using moveTo.. why?
	// This is a workaround and dirty hack around bypassing the _bbox.contains()
	// statement inside mouseClick, required only for first time!
	// _bbox = Common::Rect(x - 1, y - 1, x + 1, y + 1);
	_bbox.bottom = _screen.h;
	// _bbox.moveTo(x, y);
	// _bbox.moveTo(x, 0);
	_mouseX = x;
	_mouseY = y;

	if (!_active)
		_wm->activateMenu();
	setActive(true);
	_isVisible = true;
	_contentIsDirty = true;
	_dimensionsDirty = true;
	_menustack.clear();
	_menustack.push_back(_items[0]->submenu);
	
	// debug("this is called... right?");
	this->draw(_wm->_screen);
	eventLoop();

	closeMenu();
	// _menustack.clear();
	// _activeSubItem = -1;
	// _highlight = -1;
	// mouseClick(x, y);

	int activeSubItem = getLastSelectedSubmenuItem();
	if (activeSubItem == -1)
		return item;

	// Return one indexed item!
	return activeSubItem + 1;
}

Common::String MacPopUp::getItemText(int item) {
	// Convert 1-indexed item to 0 indexed
	item = item - 1;
	MacMenuItem *menu = getMenuItem(_menuItemId);
	MacMenuItem *submenu = getSubMenuItem(menu, item);
	return getName(submenu);
}
} // end of namespace Graphics
