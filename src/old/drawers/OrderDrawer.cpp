#include "../include/d2tmh.h"

OrderDrawer::OrderDrawer() {
}

OrderDrawer::~OrderDrawer() {
}

bool OrderDrawer::isMouseOverOrderButton(int mouseX, int mouseY) {
	if ((mouseX > 29 && mouseX < 187) && (mouseY > 2 && mouseY < 31)) {
		return true;
	}
	return false;
}

void OrderDrawer::drawOrderPlaced(cPlayer * thePlayer) {
	BITMAP *bmp_trans = create_bitmap(((BITMAP *) gfxinter[BTN_ORDER].dat)->w, ((BITMAP *) gfxinter[BTN_ORDER].dat)->h);
	clear_to_color(bmp_trans, makecol(255, 0, 255));

	// copy
	draw_sprite(bmp_trans, (BITMAP *) gfxinter[BTN_ORDER].dat, 0, 0);

	// make black
	rectfill(bmp_screen, 29, 0, 187, 29, makecol(0, 0, 0));

	// trans
	fblend_trans(bmp_trans, bmp_screen, 29, 0, 128);

	destroy_bitmap(bmp_trans);
}

void OrderDrawer::drawOrderButton(cPlayer * thePlayer) {
	assert(thePlayer);

	cOrderProcesser * orderProcesser = thePlayer->getOrderProcesser();

	assert(orderProcesser);
	if (orderProcesser->isOrderPlaced()) {
		drawOrderPlaced(thePlayer);
	} else {
		draw_sprite(bmp_screen, (BITMAP *) gfxinter[BTN_ORDER].dat, 29, 0);
	}
}
