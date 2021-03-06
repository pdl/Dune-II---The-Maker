#include "../include/d2tmh.h"

#include <string.h>

using namespace std;

GameDrawer::GameDrawer(cPlayer * thePlayer) {
	logbook("cGameDrawer constructor");
	assert(thePlayer);
	player = thePlayer;
	creditsDrawer = new CreditsDrawer(thePlayer);
	sidebarDrawer = new SideBarDrawer();
	upgradeDrawer = new UpgradeDrawer();
	orderDrawer = new OrderDrawer();
	mapDrawer = new MapDrawer(map, thePlayer, mapCamera);
	miniMapDrawer = new MiniMapDrawer(map, thePlayer, mapCamera);
	particleDrawer = new ParticleDrawer();
	messageBarDrawer = new MessageBarDrawer();
	placeitDrawer = new PlaceItDrawer();
	structureDrawer = new StructureDrawer();
	mouseDrawer = new MouseDrawer(thePlayer, Mouse::getInstance());

// 	MessageBar * messageBar = messageBarDrawer->getMessageBar();
// 	messageBar->setX(0);
// 	messageBar->setY(42);
// 	messageBar->setWidth(/* game.getScreenResolution()->getWidth() */ 800  - 182);
	logbook("cGameDrawer constructor finished");
}

GameDrawer::~GameDrawer() {
	logbook("cGameDrawer : destructor [BEGIN]");
	delete sidebarDrawer;
	sidebarDrawer = NULL;
	delete upgradeDrawer;
	upgradeDrawer = NULL;
	delete orderDrawer;
	orderDrawer = NULL;
	delete creditsDrawer;
	creditsDrawer = NULL;
	delete mapDrawer;
	mapDrawer = NULL;
	delete miniMapDrawer;
	miniMapDrawer = NULL;
	delete particleDrawer;
	particleDrawer = NULL;
	delete placeitDrawer;
	placeitDrawer = NULL;
	delete structureDrawer;
	structureDrawer = NULL;
	delete mouseDrawer;
	mouseDrawer = NULL;
	player = NULL;
	logbook("cGameDrawer : destructor [END]");
}

void GameDrawer::destroy() {
	sidebarDrawer->destroy();
	creditsDrawer->destroy();
}

void GameDrawer::draw() {
//	assert(map);
//	map->draw_think();
//
//	assert(mapDrawer);
//	mapDrawer->drawTerrain();
//
//	// Only draw units/structures, etc, when we do NOT press D
//	// TODO: this should be something like : if (keyboard->isDebuggingStructures())
//	if (!key[KEY_D] || !key[KEY_TAB]) {
//		structureDrawer->drawStructuresFirstLayer();
//	}
//
//	// draw layer 1 (beneath units, on top of terrain
//	particleDrawer->drawLayerBeneathUnits();
//
//	map->draw_units();
//
//	map->draw_bullets();
//
//	structureDrawer->drawStructuresSecondLayer();
//	structureDrawer->drawStructuresHealthBars();
//
//	map->drawAirborneUnitsAndHealthBarAndExperienceOfSelectedUnits();
//
//	particleDrawer->drawHigherLayer();
//	mapDrawer->drawShroud();
//
//	drawRallyPoint();
//
//	// GUI
//	drawSidebar();
//	miniMapDrawer->draw();
//
//	drawStructurePlacing();
//	drawCredits();
//	drawUpgradeButton();
//	drawOrderButton();
//
//	// THE MESSAGE
//	drawMessage();
//
//	// DO COMBAT MOUSE (TODO: remove this eventually, as it updates state and that is not what
//	// this class should be doing)
//	game.combat_mouse();
//
//	// Draw gui things for now
//	// Example code how to use gui Drawer for now
//	// TODO: make it easier to draw entire gui menu's, screens, windows, instead of
//	// seperate components
////	cGuiShapeFactory * factory = new cGuiShapeFactory(game.getScreenResolution());
////	cMainMenuDialog * mainMenuDialog = factory->createMainMenuDialog();
////	guiDrawer->drawShape(mainMenuDialog);
////	delete mainMenuDialog;
////	delete factory;
//
//	// MOUSE
//	drawMouse();
}

void GameDrawer::drawCredits() {
	assert(creditsDrawer);
	creditsDrawer->draw();
}

void GameDrawer::drawRallyPoint() {
	//if (game.selected_structure > -1) {
	//	cAbstractStructure * theStructure = structure[game.selected_structure];
	//	int rallyPointCell = theStructure->getRallyPoint();

	//	// show draw a target on this cell so we know this is the rally point.
	//	if (rallyPointCell > -1) {
	//		// draw this thing ...
	//		set_trans_blender(0, 0, 0, 128);
	//		draw_trans_sprite(bmp_screen, (BITMAP *) gfxdata[MOUSE_MOVE].dat, getDrawXForCell(rallyPointCell), getDrawYForCell(rallyPointCell));

	//		int startX = theStructure->iDrawX() + (theStructure->getS_StructuresType().bmp_width / 2);
	//		int startY = theStructure->iDrawY() + (theStructure->getS_StructuresType().bmp_height / 2);

	//		int endX = getDrawXForCell(rallyPointCell) + 16;
	//		int endY = getDrawYForCell(rallyPointCell) + 16;

	//		line(bmp_screen, startX, startY, endX, endY, player[HUMAN].getMinimapColor());
	//	}
	//}
}

int GameDrawer::getDrawXForCell(int cell) {
	int cellX = iCellGiveX(cell);
	return (cellX * 32) - (mapCamera->getX() * 32);
}

int GameDrawer::getDrawYForCell(int cell) {
	int cellY = iCellGiveY(cell);
	return (cellY * 32) - (mapCamera->getY() * 32) + 42; // + 42 is the top bar (options/upgrade/credits)
}

void GameDrawer::drawOrderButton() {
	// draw the order button
	if (player->getSideBar()->getSelectedListID() == LIST_STARPORT) {
		orderDrawer->drawOrderButton(player);
	}
}

void GameDrawer::drawSidebar() {
	sidebarDrawer->drawSideBar(player);
}

void GameDrawer::drawUpgradeButton() {
	// draw the upgrade button
	int selectedListId = player->getSideBar()->getSelectedListID();
	if (selectedListId > -1) {
		cBuildingList * selectedList = player->getSideBar()->getList(selectedListId);
		upgradeDrawer->drawUpgradeButtonForSelectedListIfNeeded(player, selectedList);
	}
}

void GameDrawer::drawStructurePlacing() {
	//if (game.bPlaceIt) {
	//	// TODO: fix the placeItDrawer, it crashes the game now!
	//	cBuildingListItem *itemToPlace = player->getSideBar()->getList(LIST_CONSTYARD)->getItemToPlace();
	//	if (itemToPlace) {
	//		assert(placeitDrawer);
	//		placeitDrawer->draw(itemToPlace);
	//	}
	//}
}

void GameDrawer::drawMessage() {
	messageBarDrawer->drawMessageBar();
}

void GameDrawer::drawMouse() {
	assert(mouseDrawer);
	mouseDrawer->draw();
	cGameControlsContext *context = player->getGameControlsContext();
	if (context->shouldDrawToolTip()) {
		mouseDrawer->drawToolTip();
	}
}

//int points[] =
//{
//    0,0,
//    100,100,
//    540,100,
//    640,0
//};
//
//spline(bmp_screen, points, makecol(255,255,255));//will draw a nice loopy curve
