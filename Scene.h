/*
 *  Scene.h
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

#include "defines.h"
#include "Button.h"

class Main;

class Scene
{
	public:
		Scene() {}
		virtual void Draw() = 0;
		virtual void HandleEvents(sf::Event event) = 0;
		virtual void Preload(Main *main) = 0;
		/*void WriteText(const char *text, TTF_Font *font, SDL_Color textColor, int x, int y, int w, int h, int srcX = 0, SDL_Surface *dest = NULL);
		void DrawFilledRect(SDL_Color color, int x, int y, int w, int h);
		void DrawSurface(SDL_Surface *surface, int x, int y, int w, int h);
		void DrawScrollingTrackInfo();
		SDL_Surface* CreateSurface(int width, int height);*/
	
		//vector<SDL_Surface> surfaces;
		list<Button*> buttons;
	
		//SDL_Surface *screen;
		Main *main;
};

#endif