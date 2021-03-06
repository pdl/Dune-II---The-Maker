/**
 *
 * This is a class, representing a list of icons that can be selected and built.
 *
 * Per list one item can be built at a time. Each list has therefore a timer.
 *
 * A list has also a corresponding icon the user can click on, in order to view the
 * lists contents. (these are the icons left to the building list). Each list has the
 * ID of the unpressed icon picture, and also the coordinates for this icon.
 *
 */

#ifndef CBUILDINGLIST
#define CBUILDINGLIST

#include "../include/definitions.h"

class cBuildingList {
	public:
		cBuildingList(int theId);
		~cBuildingList();

		cBuildingListItem * getItem(int position); // return building list item in array at position.
		cBuildingListItem * getItemToPlace(); // return building list item with placeIt = true.

		// add item to the list
		void addItemToList(cBuildingListItem * item);
		void removeItemFromList(int position);

		bool isOverButton(int x, int y);
		void removeAllItems();
		bool isItemInList(cBuildingListItem * item);

		// get
		bool isUpgrading() {
			return upgrading;
		}
		int getTimer() {
			return TIMER_progress;
		}
		int getLastClickedId() {
			return lastClickedId;
		}
		int getButtonIconIdPressed() {
			return buttonIconIdPressed;
		}
		int getButtonIconIdUnpressed() {
			return buttonIconIdUnpressed;
		}
		int getButtonDrawX() {
			return buttonDrawX;
		}
		int getButtonDrawY() {
			return buttonDrawY;
		}
		int getScrollingOffset() {
			return scrollingOffset;
		}
		bool isAvailable() {
			return available;
		}
		bool isAcceptsOrders() {
			return acceptsOrders;
		}
		bool isBuildingItem();
		bool hasItemType(int itemTypeId);

		void scrollUp();
		void scrollDown();

		// set
		void setTimer(int value) {
			TIMER_progress = value;
		}
		void setTypeOfList(int value) {
			typeOfList = value;
		}
		void setUpgradeLevel(int value) {
			upgradeLevel = value;
		}
		void setUpgrading(bool value) {
			upgrading = value;
		}

		void setButtonIconIdPressed(int iconId) {
			buttonIconIdPressed = iconId;
		}
		void setButtonIconIdUnpressed(int iconId) {
			buttonIconIdUnpressed = iconId;
		}

		void setButtonDrawX(int value) {
			buttonDrawX = value;
		}
		void setButtonDrawY(int value) {
			buttonDrawY = value;
		}
		void setScrollingOffset(int value);
		void setAvailable(bool value) {
			available = value;
		}
		void setLastClickedId(int value) {
			lastClickedId = value;
		}
		void setAcceptsOrders(bool value) {
			acceptsOrders = value;
		}

		int getType() {
			return typeOfList;
		}
		int getUpgradeLevel() {
			return upgradeLevel;
		}
	protected:
		// nothing

	private:
		int TIMER_progress; // timer for upping progress
		bool upgrading; // upgrading this field of technology?
		int lastClickedId; // last clicked item id
		int buttonIconIdPressed; // the button to draw at the left of the list when pressed (selected)
		int buttonIconIdUnpressed; // the button to draw at the left of the list when unpressed
		int buttonDrawX;
		int buttonDrawY;
		int scrollingOffset; // the offset for scrolling through the list.
		bool available; // is this list available?
		bool acceptsOrders; // accepts orders
		int maxItems; // how many items have been set in the list?

		// the list of icons
		cBuildingListItem * items[MAX_ITEMS];

		int getFreeSlot();
		int typeOfList;
		int upgradeLevel;
};

#endif
