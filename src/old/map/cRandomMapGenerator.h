/*
 * cRandomMapGenerator.h
 *
 *  Created on: 16 nov. 2010
 *      Author: Stefan
 */

#ifndef CRANDOMMAPGENERATOR_H_
#define CRANDOMMAPGENERATOR_H_

class cRandomMapGenerator {
	public:
		cRandomMapGenerator(cMap * theMap);
		virtual ~cRandomMapGenerator();

		void generateRandomMap();

	private:
		cMap * map;

};

#endif /* CRANDOMMAPGENERATOR_H_ */
