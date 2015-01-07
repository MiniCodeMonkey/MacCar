/*
 *  Scene_Music.h
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __SCENE_MUSIC_H__
#define __SCENE_MUSIC_H__

#include "Scene.h"
#include "Main.h"
#include "ScrollingText.h"

#include <math.h>

class Scene_Music : public Scene
{
public:
	Scene_Music();
	~Scene_Music();
	void Draw();
	void Draw_TrackList();
	void Draw_DateTime();
	void HandleEvents(SDL_Event event);
	void Preload(Main *main);
	
private:
	SDL_Surface *menu, *menu_down, *menu_additional;
	TTF_Font *dotmatrix24, *arialbd16, *drtu18, *arial15, *arial14;
	ScrollingText *scrollingTrackInfo;
	char trackInfo[200];
	SDL_Surface *trackList;
	int trackListStartIndex;
	int selectedTrackIndex;
};

#endif