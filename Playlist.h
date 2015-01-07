/*
 *  Playlist.h
 *  MacCar2
 *
 *  Created by Mathias Hansen on 09/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

#include <iostream>
#include <dirent.h>
#include <vector>
#include "defines.h"
#include "Track.h"

using namespace std;

class Playlist {
	public:
		Playlist(char *folder);
		Track *GetTrack(int index) { return tracks.at(index); };
		int GetTracksCount() { return tracks.size(); }
		char *GetName() { return (char *)name.c_str(); }
	
	private:
		char folder[200];
		string name;
		vector<Track*> tracks;
		int currentTrackIndex;
};

#endif
