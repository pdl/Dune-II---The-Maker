#include "../include/d2tmh.h"

cCombatInteractionManager::cCombatInteractionManager(cPlayer * thePlayer) : cInteractionManager(thePlayer) {
	sidebar = player->getSideBar();
	assert(sidebar);
}

cCombatInteractionManager::~cCombatInteractionManager() {
}

void cCombatInteractionManager::interactWithMouse() {
	interactWithSidebar();
}

void cCombatInteractionManager::interactWithKeyboard() {
	cInteractionManager::interactWithKeyboard();
}

void cCombatInteractionManager::interactWithSidebar() {
	assert(sidebar);
	sidebar->thinkInteraction();
	MiniMapDrawer * miniMapDrawer = gameDrawer->getMiniMapDrawer();
	assert(miniMapDrawer);
	miniMapDrawer->interact();
}
