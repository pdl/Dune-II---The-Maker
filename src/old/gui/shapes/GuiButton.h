/**
 * A button is a gui shape (rectangle), with a label.
 *
 */
#ifndef CGUIBUTTON_H_
#define CGUIBUTTON_H_

#include <sstream>
#include <string>

#include "allegro.h"

#include "../../drawers/TextDrawer.h"

#include "../../gameobjects/Rectangle.h"
#include "GuiShape.h"
#include "../GuiColors.h"


class GuiButton : public GuiShape {

	public:
		GuiButton(Rectangle * rect, std::string theLabel);
		GuiButton(int x, int y, int width, int height, std::string theLabel);
		GuiButton(GuiButton * other, std::string theLabel);
		~GuiButton();

		void draw();

		std::string getLabel() {
			return label;
		}

		BITMAP * getBitmap() { return bitmap; }
		void setBitmap(BITMAP * value) { bitmap = value; }
		void setHasBorders(bool value) { hasBorders = value; }
		void setPressed(bool value) { pressed = value; }

		bool shouldDrawPressedWhenMouseHovers() { return drawPressedWhenMouseHovers; }
		bool shouldDrawBorders() { return hasBorders; }
		void setDrawPressedWhenMouseHovers(bool value) { drawPressedWhenMouseHovers = value; }
		bool isPressed() { return pressed; }
		bool isEnabled() { return enabled; }
		void setEnabled(bool enabled) { this->enabled = enabled; }

		void adjustHeightOfButtonToFontHeight();
		void moveButtonDownExactlyOneButtonHeight();

		TextDrawer * getTextDrawer() { return textDrawer; }

	private:
		GuiColors guiColors;
		std::string label;
		bool drawPressedWhenMouseHovers;
		bool hasBorders;
		bool pressed;
		bool enabled;
		BITMAP * bitmap;

		void drawBackground();
		void drawLighterBorder();
		void drawDarkerBorder();

		void drawButtonUnpressed();
		void drawButtonPressed();
		void drawButtonHovered();
		void drawDisabled();

		void drawLabel(int color);

		TextDrawer * textDrawer;
};

#endif /* CGUIBUTTON_H_ */
