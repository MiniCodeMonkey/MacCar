/*
 *  Scene_Main.h
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __SCENE_MAIN_H__
#define __SCENE_MAIN_H__

#include "Scene.h"
#include "Scene_Music.h"
#include "Main.h"
#include "ScrollingText.h"

#include <math.h>

class Scene_Main : public Scene
{
	public:
		Scene_Main();
		~Scene_Main();
		void Draw();
		void Draw_DateTime();
		void HandleEvents(sf::Event event);
		void Preload(Main *main);
	
	private:
		sf::Sprite menu, menu_down;
		TTF_Font *dotmatrix24, *arialbd16, *drtu18;
		ScrollingText *scrollingTrackInfo;
		char trackInfo[200];
};

#endif