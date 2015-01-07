/*
 *  Main.h
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <list>

#include <SFML/Graphics.hpp>

#include "defines.h"
#include "Scene.h"
#include "Scene_Main.h"
#include "Playlists.h"
#include "MediaManager.h"

using namespace std;

class Main
{
	public:
		Main();
		~Main();
		void Run();
		void Init();
		void SetScene(Scene *scene);
		MediaManager *GetMediaManager() { return mediaManager; }
		sf::RenderWindow GetApp() { return App; }
	
	private:
		sf::RenderWindow App;
		bool done;
		Playlists *playlists;
		Playlist *currentPlaylist;
		Scene *currentScene;
		MediaManager *mediaManager;
};

#endif