#ifndef TEXTDRAWER_H_
#define TEXTDRAWER_H_

#include <alfont.h>

#include "../gui/GuiColors.h"

class TextDrawer {
	public:
		TextDrawer();
		TextDrawer(ALFONT_FONT *theFont);
		~TextDrawer();
		void drawTextWithOneInteger(int x, int y, const char * msg, int var);
		void drawTextWithTwoIntegers(int x, int y, const char * msg, int var1, int var2);
		void drawText(int x, int y, const char * msg);
		void drawText(int x, int y, const char * msg, int color);

		void drawTextCentered(const char * msg, int y);
		void drawTextCentered(const char * msg, int y, int color);

		void drawTextBottomRight(const char * msg);
		void drawTextBottomLeft(const char * msg);

		void setApplyShaddow(bool value) {
			applyShadow = value;
		}

		void setTextColor(int value) {
			textColor = value;
		}

		void setShadowColor(int value) {
			shadowColor = value;
		}

		int getYCoordinateForBottomRight();
		int getXCoordinateForBottomRight(const char * msg);

		int getHeightInPixelsForFont();
		int getLenghtInPixelsForChar(const char * msg);

	protected:

	private:
		GuiColors guiColors;
		bool applyShadow;

		int textColor;
		int shadowColor;

		ALFONT_FONT * font;
};

#endif /* TEXTDRAWER_H_ */
