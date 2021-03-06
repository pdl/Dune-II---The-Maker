#include "PlayingState.h"

void PlayingState::draw() {
	viewPort->draw(screen, viewPortDrawLocation, viewPortCamera);
	screen->draw(mouse->getBitmap(), mouse->getVector2D());
}

void PlayingState::update() {
	mouse->updateState();

	// manipuleer camera/map
	if (key[KEY_LEFT])	viewPortCamera.substractX(1);
	if (key[KEY_RIGHT])	viewPortCamera.addX(1);
	if (key[KEY_UP]) viewPortCamera.substractY(1);
	if (key[KEY_DOWN]) viewPortCamera.addY(1);
	viewPortCamera.clip(0, 0, map->getWidth(), map->getHeight());


/*	viewPortDrawLocation.set(mouse->getVector2D());*/
// 	
// 	viewPortX = mouse->getX() - (viewPort->getWidth() / 2);
// 	viewPortY = mouse->getY() - (viewPort->getHeight() / 2);


	if (key[KEY_ESC]) {
		this->flagToQuitGame();
	}
}


