/*
 *  ScrollingText.h
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __SCROLLINGTEXT_H___
#define __SCROLLINGTEXT_H___

#include "SDL.h"
#include "SDL_ttf/SDL_ttf.h"

#include "defines.h"
#include "Scene.h"

#define DIRECTION_LEFT	0
#define DIRECTION_STILL	1
#define DIRECTION_RIGHT	2

class ScrollingText
{
	public:
		ScrollingText(Scene *scene, char *text, TTF_Font *font, SDL_Color color, int x, int y, int w, int h);
		void SetText(char *text);
		void Draw();
	
	private:
		Scene *scene;
		int trackScrollX;
		char text[200];
		TTF_Font *font;
		SDL_Color color;
		int x, y, w, h;
		bool shouldScroll;
		int direction, wait, nextDirection;
};

#endif