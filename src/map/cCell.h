/*
 * cCell.h
 *
 *  Created on: 10-aug-2010
 *      Author: Stefan
 */

#ifndef CCELL_H_
#define CCELL_H_

class tCell {
	public:
		int spiceInCredits;
		int terrainTypeGfxDataIndex;
		int tileIndexToDraw;
		int smudgeTerrainTypeGfxDataIndex;
		int smudgeTileToDraw;
		int hitpoints;
		bool passable;

		// there are 4 'dimensions' of this cell. Each represents the perspective of
		// an entity that is either a unit, structure, the 'worms' dimension and the 'air' dimension.
		int gameObjectId[4]; // ID of
		// 0 = unit
		// 1 = structure
		// 2 = air
		// 3 = worm
};

#endif /* CCELL_H_ */
