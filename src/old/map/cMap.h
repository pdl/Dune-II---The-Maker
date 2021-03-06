/*

 Dune II - The Maker

 Author : Stefan Hendriks
 Contact: stefanhen83@gmail.com
 Website: http://dune2themaker.fundynamic.com

 2001 - 2011 (c) code by Stefan Hendriks

 */
#ifndef CMAP_H
#define CMAP_H

#include "cMapCell.h"

class cMap {
	public:

		cMap(int theWidth, int theHeight);
		~cMap();

		void init();
		void smooth();
		void draw_bullets();

		void think_minimap();

		bool occupied(int iCell);
		bool occupied(int iCll, int iUnitID);
		bool occupiedInDimension(int iCll, int dimension);
		bool occupiedByType(int iCell);

		void soft();

		void drawAirborneUnitsAndHealthBarAndExperienceOfSelectedUnits();
		void draw_units();

		void smudge_increase(int iType, int iCell);

		int mouse_cell();

		// Drawing
		int mouse_draw_x();
		int mouse_draw_y();

		void thinkInteraction();
		void draw_think();
		void makeAllCellsVisible();
		void makeCircleVisibleForPlayerOfSpecificSize(int c, int size, int player);

		cMapCell cell[MAX_CELLS];

		void remove_id(int iIndex, int iIDType); // removes ID of IDtype (unit/structure), etc

		void increaseScrollTimer() {
			TIMER_scroll++;
		}
		void resetScrollTimer() {
			TIMER_scroll = 0;
		}
		bool isTimeToScroll() {
			return (TIMER_scroll > iScrollSpeed);
		}

		bool isVisible(int iCell, int iPlayer) {
			return iVisible[iCell][iPlayer];
		}

		void setVisible(int iCell, int iPlayer, bool flag) {
			iVisible[iCell][iPlayer] = flag;
		}

		int getHeight() {
			return height;
		}

		int getWidth() {
			return width;
		}

		int getHeightMinusBorder() {
			return (height - 1);
		}

		int getWidthMinusBorder() {
			return (width - 1);
		}

		int getMaxCells() {
			return height * width;
		}

	private:

		bool iVisible[MAX_CELLS][MAX_PLAYERS]; // visibility for <player>

		// Scrolling around map, timer based
		int TIMER_scroll;
		int iScrollSpeed;

		// sizes of the map
		int height, width;

};

#endif
