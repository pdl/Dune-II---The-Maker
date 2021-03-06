/*

 Dune II - The Maker

 Author : Stefan Hendriks
 Contact: stefanhen83@gmail.com
 Website: http://dune2themaker.fundynamic.com

 2001 - 2011 (c) code by Stefan Hendriks

 */

#ifndef STRUCTURE_FACTORY
#define STRUCTURE_FACTORY

class cStructureFactory {

	private:
		static cStructureFactory *instance;

	protected:
		cStructureFactory();
		~cStructureFactory();

	public:

		static cStructureFactory *getInstance();

		void deleteStructureInstance(cAbstractStructure *structure);

		cAbstractStructure *createStructureInstance(int type);

		cAbstractStructure *createStructure(int iCell, int iStructureType, int iPlayer, int iPercent);
		cAbstractStructure *createStructure(int iCell, int iStructureType, int iPlayer);

		int getFreeSlot();

		void clearAllStructures();

		void clearFogForStructureType(int iCell, cAbstractStructure *str);
		void clearFogForStructureType(int iCell, int iStructureType, int iSight, int iPlayer);

		void createSlabForStructureType(int iCell, int iStructureType);

		void placeStructure(int iCell, int iStructureType, int iPlayer);

		int getSlabStatus(int iCell, int iStructureType, int iUnitIDToIgnore);

		void powerUp(int iStructureType, int iPlayer);
		void powerDown(int iStructureType, int iPlayer);

};
#endif
