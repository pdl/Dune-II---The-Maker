#include "../include/d2tmh.h"

#include "CellCalculator.h"

cStructureUtils::cStructureUtils() {
}

cStructureUtils::~cStructureUtils() {
}

int cStructureUtils::getHeightOfStructureTypeInCells(int structureType) {
	assert(structureType >= 0);
	assert(structureType < MAX_STRUCTURETYPES);
	return structures[structureType].bmp_height / TILESIZE_HEIGHT_PIXELS;
}

int cStructureUtils::getWidthOfStructureTypeInCells(int structureType) {
	assert(structureType >= 0);
	assert(structureType < MAX_STRUCTURETYPES);
	return structures[structureType].bmp_width / TILESIZE_WIDTH_PIXELS;
}

/**
 * This is almost the same as the findStructureToDeployUnit
 *
 * However, whenever the player has not set any primary building. Try to find a structure that has some free cell around it.
 */
int cStructureUtils::findStarportToDeployUnit(cPlayer * player) {
	assert(player);
	int playerId = player->getId();

	// check primary building first if set
	int primaryBuildingOfStructureType = player->iPrimaryBuilding[STARPORT];

	if (primaryBuildingOfStructureType > -1) {
		cAbstractStructure * theStructure = structure[primaryBuildingOfStructureType];
		if (theStructure && theStructure->iFreeAround() > -1) {
			return primaryBuildingOfStructureType;
		}
	}

	// find a starport that has space around it.
	int starportId = -1;
	int firstFoundStarportId = -1;
	bool foundStarportWithFreeAround = false;
	for (int i = 0; i < MAX_STRUCTURES; i++) {
		cAbstractStructure * theStructure = structure[i];
		if (theStructure && theStructure->getOwner() == playerId) {
			if (theStructure->getType() == STARPORT) {
				// when no id set, always set one id
				if (starportId < 0) {
					starportId = i;
				}

				if (firstFoundStarportId < 0) {
					firstFoundStarportId = i;
				}

				if (theStructure->iFreeAround() > -1) {
					// when free around structure, override id and break out of loop
					starportId = i;
					foundStarportWithFreeAround = true;
					break;
				}
			}
		}
	}

	if (!foundStarportWithFreeAround) {
		if (primaryBuildingOfStructureType > -1) {
			return primaryBuildingOfStructureType;
		}
		if (firstFoundStarportId > -1) {
			return firstFoundStarportId;
		}
	}
	return starportId;

}

/**
 * Finds a building to deploy a unit from. Returns the structure ID of the found structure.
 *
 * Will use primary building set by player first, before looking for alternatives.
 *
 */
int cStructureUtils::findStructureToDeployUnit(cPlayer * player, int structureType) {
	assert(player);
	assert(structureType > -1);

	int playerId = player->getId();

	if (DEBUGGING) {
		char msg[255];
		sprintf(msg, "Looking for primary building (type %d, name %s, player %d)", structureType, structures[structureType].name, playerId);
		logbook(msg);
	}

	// check primary building first if set
	int primaryBuildingOfStructureType = player->iPrimaryBuilding[structureType];

	if (primaryBuildingOfStructureType > -1) {
		cAbstractStructure * theStructure = structure[primaryBuildingOfStructureType];
		if (theStructure && theStructure->iFreeAround() > -1) {
			return primaryBuildingOfStructureType;
		}
	}

	int structureIdFound = -1;
	// check other structures now
	for (int i = 0; i < MAX_STRUCTURES; i++) {
		cAbstractStructure * theStructure = structure[i];
		if (theStructure && theStructure->getOwner() == playerId) {
			if (theStructure->getType() == structureType) {
				if (theStructure->iFreeAround() > -1) {
					structureIdFound = i; // return this structure
				}
			}
		}
	}

	// assign as primary building
	if (structureIdFound > -1) {
		player->iPrimaryBuilding[structureType] = structureIdFound;
	}

	return structureIdFound;
}

/**
 * Depending on list type, return a structure type.
 */
int cStructureUtils::findStructureTypeByTypeOfList(cBuildingList *list, cBuildingListItem *item) {
	assert(list);
	assert(item);
	assert(item->getBuildType() == UNIT);

	int listTypeId = list->getType();
	char msg[255];
	sprintf(msg, "going to find list with listTypeId [%d]", listTypeId);
	Logger::getInstance()->logCommentLine(msg);
	switch (listTypeId) {
		case LIST_CONSTYARD:
			// a unit, and then built from a constyard list
			assert(false);
			return CONSTYARD;
		case LIST_HEAVYFC:
			return HEAVYFACTORY;
		case LIST_INFANTRY:
			if (item->getBuildId() == INFANTRY || item->getBuildId() == SOLDIER) {
				return BARRACKS;
			}
			return WOR;
		case LIST_LIGHTFC:
			return LIGHTFACTORY;
		case LIST_ORNI:
			return HIGHTECH;
		case LIST_PALACE:
			return PALACE;
		case LIST_NONE:
			assert(false);
			return -1;
		case LIST_STARPORT:
			return STARPORT;
		default:
			assert(false);
			return -1;
	}
	return -1;
}

int cStructureUtils::findClosestStructureTypeToCell(int cell, int structureType, cPlayer * player) {
	assert(player);
	assert(structureType > -1);
	assert(cell >= 0 || cell < MAX_CELLS);

	int foundStructureId = -1; // found structure id
	long shortestDistance = 9999; // max distance to search in

	int playerId = player->getId();

	CellCalculator * cellCalculator = new CellCalculator(map);
	for (int i = 0; i < MAX_STRUCTURES; i++) {
		if (structure[i]) { // exists (pointer)
			if (structure[i]->getOwner() == playerId) { // same player
				if (structure[i]->getType() == structureType) { // type equals parameter
					if (structure[i]->iUnitID < 0) { // no other unit is heading to this structure
						long distance = cellCalculator->distance(cell, structure[i]->getCell());

						// if distance is lower than last found distance, it is the closest for now.
						if (distance < shortestDistance) {
							foundStructureId = i;
							shortestDistance = distance;
						}
					}
				}
			}
		}
	}

	delete cellCalculator;
	return foundStructureId;
}

void cStructureUtils::putStructureOnDimension(int dimensionId, cAbstractStructure * theStructure) {
	assert(theStructure);

	int cellOfStructure = theStructure->getCell();

	assert(cellOfStructure > -1);

	CellCalculator * cellCalculator = new CellCalculator(map);
	for (int w = 0; w < theStructure->getWidth(); w++) {
		for (int h = 0; h < theStructure->getHeight(); h++) {
			int xOfStructureCell = cellCalculator->getX(cellOfStructure);
			int yOfStructureCell = cellCalculator->getY(cellOfStructure);

			int iCell = cellCalculator->getCell(xOfStructureCell + w, yOfStructureCell + h);

			map->cell[iCell].gameObjectId[dimensionId] = theStructure->getStructureId();
		}
	}
	delete cellCalculator;
}

bool cStructureUtils::isStructureOnScreen(cAbstractStructure *structure) {
	assert(structure);
	int drawX = structure->iDrawX();
	int drawY = structure->iDrawY();
	int width = structure->getWidthInPixels();
	int height = structure->getHeightInPixels();

	return ((drawX + width) > 0 && drawX < /* game.getScreenResolution()->getWidth() */ 800 ) && ((drawY + height) > 0 && drawY < /* game.getScreenResolution()->getHeight */ 600 );
}

bool cStructureUtils::isMouseOverStructure(Mouse *mouse, cAbstractStructure *structure) {
	assert(structure);
	assert(mouse);

	Rectangle * rectangle = structure->getRectangle();
	return mouse->isOverRectangle(rectangle);
}

int cStructureUtils::getTotalPowerUsageForPlayer(cPlayer * player) {
	assert(player);
	int totalPowerUsage = 0;

	for (int i = 0; i < MAX_STRUCTURES; i++) {
		cAbstractStructure * theStructure = structure[i];
		if (theStructure) {
			if (theStructure->getPlayer()->getId() == player->getId()) {
				int powerUsageOfStructure = theStructure->getPowerUsage();
				totalPowerUsage += powerUsageOfStructure;
			} else if (theStructure->getType() == CONSTYARD) {
				totalPowerUsage += 4;
			}
		}
	}

	return totalPowerUsage;
}

int cStructureUtils::getTotalSpiceCapacityForPlayer(cPlayer * player) {
	int totalCapacity = 0;
	for (int i = 0; i < MAX_STRUCTURES; i++) {
		cAbstractStructure * theStructure = structure[i];
		if (theStructure) {
			if (theStructure->getPlayer()->getId() == player->getId()) {
				int capacity = 0;
				if (theStructure->getType() == SILO) {
					cSpiceSilo * spiceSilo = dynamic_cast<cSpiceSilo*> (theStructure);
					capacity = spiceSilo->getSpiceSiloCapacity();
				} else if (theStructure->getType() == REFINERY) {
					cRefinery * refinery = dynamic_cast<cRefinery*> (theStructure);
					capacity = refinery->getSpiceSiloCapacity();
				} else if (theStructure->getType() == CONSTYARD) {
					capacity = 5;
				}
				totalCapacity += capacity;
			}
		}
	}
	return totalCapacity;
}

int cStructureUtils::getTotalPowerOutForPlayer(cPlayer * player) {
	assert(player);
	int totalPowerOut = 0;
	for (int i = 0; i < MAX_STRUCTURES; i++) {
		cAbstractStructure * theStructure = structure[i];
		if (theStructure) {
			if (theStructure->getPlayer()->getId() == player->getId()) {
				if (theStructure->getType() == WINDTRAP) {
					cWindTrap * windTrap = dynamic_cast<cWindTrap*> (theStructure);
					int powerOutOfStructure = windTrap->getPowerOut();
					totalPowerOut += powerOutOfStructure;
				} else if (theStructure->getType() == CONSTYARD) {
					totalPowerOut += 5;
				}
			}
		}
	}
	return totalPowerOut;
}
