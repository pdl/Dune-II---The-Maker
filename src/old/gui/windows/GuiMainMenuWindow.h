/*
 * cGuiMainMenuWindow.h
 *
 *  Created on: 4 okt. 2011
 *      Author: Stefan
 */

#ifndef CGUIMAINMENUWINDOW_H_
#define CGUIMAINMENUWINDOW_H_

#include "GuiWindow.h"
#include "GuiMainMenuWindowInteractionDelegate.h"

#include "../dialogs/MainMenuDialog.h"

class GuiMainMenuWindow : public GuiWindow {
	public:
		GuiMainMenuWindow(GuiMainMenuWindowInteractionDelegate * mainMenuWindowDelegate);
		~GuiMainMenuWindow();

		void draw();

		void setMainMenuDialog(MainMenuDialog * dialog) {
			assert(dialog);
			assert(mainMenuDialog == NULL);
			mainMenuDialog = dialog;
		}

		MainMenuDialog * getMainMenuDialog() {
			return this->mainMenuDialog;
		}

	private:
		MainMenuDialog * mainMenuDialog;

};

#endif /* CGUIMAINMENUWINDOW_H_ */
