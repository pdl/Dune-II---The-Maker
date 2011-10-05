/**
 * A button is a gui shape (rectangle), with a label.
 *
 */
#ifndef CGUIBUTTON_H_
#define CGUIBUTTON_H_

#include <sstream>
#include <string>

#include "../../gameobjects/cRectangle.h"
#include "GuiShape.h"

class GuiButton : public GuiShape {

	public:
		GuiButton(cRectangle * rect, std::string theLabel);
		GuiButton(int x, int y, int width, int height, std::string theLabel);
		virtual ~GuiButton();

		std::string * getLabel() {
			return label;
		}

		BITMAP * getBitmap() { return bitmap; }
		void setBitmap(BITMAP * value) { bitmap = value; }
		void setHasBorders(bool value) { hasBorders = value; }

		bool shouldDrawPressedWhenMouseHovers() { return drawPressedWhenMouseHovers; }
		bool shouldDrawBorders() { return hasBorders; }
		void setDrawPressedWhenMouseHovers(bool value) { drawPressedWhenMouseHovers = value; }

	private:
		std::string * label;
		bool drawPressedWhenMouseHovers;
		bool hasBorders;
		BITMAP * bitmap;
};

#endif /* CGUIBUTTON_H_ */