#pragma once
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Screen.h"
#include "Map.h"

class Viewport {

	public:
		Viewport(int width, int height, Map * map) {
			if (map == NULL) throw NullArgumentException;
			this->map = map;
			this->width = width;
			this->height = height;
			this->bitmap = new Bitmap(width, height);
		}
	
		void draw(Screen * screen, int x, int y);

		int getWidth() { return width; }
		int getHeight() { return height; }

	private:
		int width, height;

		Bitmap * bitmap;
		Map * map;
};

#endif
