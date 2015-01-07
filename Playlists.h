/*
 *  Playlists.h
 *  MacCar2
 *
 *  Created by Mathias Hansen on 09/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __PLAYLISTS_H__
#define __PLAYLISTS_H__

#include <iostream>
#include <dirent.h>
#include <vector>
#include "defines.h"
#include "Playlist.h"

using namespace std;

class Playlists
{
	private:
		vector<Playlist*> playlists;
	
	public:
		Playlists() {}
		void find();
		Playlist *GetPlaylist(int index) { return playlists.at(index); }
};

#endif