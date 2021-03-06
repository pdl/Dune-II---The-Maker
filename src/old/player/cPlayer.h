/*

 Dune II - The Maker

 Author : Stefan Hendriks
 Contact: stefanhen83@gmail.com
 Website: http://dune2themaker.fundynamic.com

 2001 - 2011 (c) code by Stefan Hendriks

 A player has a sidebar. The sidebar contains lists of items that can be built. These
 items can be structures/units but also special weapons, etc.

 In order to build items, a player has an itemBuilder.

 A player can upgrade the sidebar lists. Therefore a cBuildingListUpgrader is used.
 The state of upgrades is held by a cPlayerUpgradeState object.

 */
#ifndef PLAYER_H
#define PLAYER_H

#ifndef CGAMECONTROLSCONTEXT_H_
class cGameControlsContext;
#endif

#include "allegro.h"

#include "cPlayerDifficultySettings.h"

#include "../include/definitions.h"

#include "../building/cItemBuilder.h"
#include "../sidebar/cSideBar.h"
#include "../upgrade/cBuildingListUpdater.h"
#include "../upgrade/cUpgradeBuilder.h"

#include "../gameobjects/structures/cStructurePlacer.h"
#include "../gameobjects/structures/cOrderProcesser.h"

class cPlayer {

	public:
		cPlayer();
		~cPlayer();

		PALETTE pal; // each player has its own 256 color scheme (used for coloring units)

		void init();

		int iTeam;

		int use_power;
		int has_power;

		float credits; // the credits this player has
		float max_credits; // max credits a player can have (influenced by silo's)

		int focus_cell; // this is the cell that will be showed in the game centralized upon map loading

		int iPrimaryBuilding[MAX_STRUCTURETYPES]; // remember the primary ID (structure id) of each structure type
		int iStructures[MAX_STRUCTURETYPES]; // remember what is built for each type of structure

		bool bEnoughPower();

		int TIMER_think; // timer for thinking itself (calling main routine)
		int TIMER_attack; // -1 = determine if its ok to attack, > 0 is , decrease timer, 0 = attack

		// set
		void setItemBuilder(cItemBuilder *theItemBuilder);
		void setSideBar(cSideBar *theSideBar);
		void setBuildingListUpdater(cBuildingListUpdater *theBuildingListUpgrader);
		void setTechLevel(int theTechLevel) {
			techLevel = theTechLevel;
		}
		void setHouse(int iHouse);
		void setId(int theId);
		void setStructurePlacer(cStructurePlacer *theStructurePlacer);
		void setUpgradeBuilder(cUpgradeBuilder *theUpgradeBuilder);
		void setOrderProcesser(cOrderProcesser *theOrderProcesser);
		void setGameControlsContext(cGameControlsContext *theGameControlsContext);
		void setCredits(float value) {
			credits = value;
		}
		void setTeam(int value) {
			iTeam = value;
		}
		// get
		cBuildingListUpdater *getBuildingListUpdater() {
			return buildingListUpdater;
		}
		cPlayerDifficultySettings *getDifficultySettings() {
			return difficultySettings;
		}
		cItemBuilder *getItemBuilder() {
			return itemBuilder;
		}
		cSideBar *getSideBar() {
			return sidebar;
		}
		int getHouse() {
			return house;
		}
		int getTechLevel() {
			return techLevel;
		}
		int getId() {
			return id;
		}
		cStructurePlacer * getStructurePlacer() {
			return structurePlacer;
		}
		cUpgradeBuilder * getUpgradeBuilder() {
			return upgradeBuilder;
		}
		cOrderProcesser * getOrderProcesser() {
			return orderProcesser;
		}
		cGameControlsContext * getGameControlsContext() {
			return gameControlsContext;
		}
		int getMinimapColor() {
			return minimapColor;
		}

		int getAmountOfStructuresForType(int structureType);

		void deleteSideBar() {
			delete sidebar;
			sidebar = NULL;
		}

	private:
		int getRGBColorForHouse(int houseId);

		// TODO: in the end this should be redundant.. perhaps remove it now/soon anyway?
		// TODO: redundant? OBSELETE. Since we're getting more properties for units and thereby
		// can/should create units specific for houses.
		cPlayerDifficultySettings *difficultySettings;

		// these have all state, and need to be recreated for each mission.
		cSideBar * sidebar; // each player has a sidebar (lists of what it can build)
		cItemBuilder * itemBuilder; // each player can build items
		cUpgradeBuilder * upgradeBuilder; // each player can upgrade lists

		cBuildingListUpdater * buildingListUpdater; // modifies list of sidebar on upgrades
		cStructurePlacer * structurePlacer; // used to place structures and handle updates in sidebar accordingly
		cOrderProcesser * orderProcesser; // process orders for starport

		cGameControlsContext * gameControlsContext;

		int id; // this id is the reference to the player array
		int techLevel; // technology level
		int house;
		int minimapColor; // color of this team on minimap;
};

#endif
