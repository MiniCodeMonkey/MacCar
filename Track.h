/*
 *  Track.h
 *  MacCar2
 *
 *  Created by Mathias Hansen on 09/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __TRACK_H__
#define __TRACK_H__

#include <iostream>
#include <fstream>
#include <string>
#include "defines.h"
#include "TagLib/tag.h"
#include "TagLib/fileref.h"

using namespace std;

class Track
{
	public:
		Track(char *file);
		char *GetFilename() { return file; }
		char *GetTrackTitle() { return trackTitle; }
		char *GetTrackArtist() { return trackArtist; }
		char *GetShortInfo() { return trackShortInfo; }
		int GetTrackDuration() { return trackDuration; }
		int GetTrackBitrate() { return trackBitrate; }
	
	private:
		char file[200];
		char trackTitle[70];
		char trackArtist[70];
		char trackAlbum[70];
		char trackShortInfo[100];
		int trackDuration, trackBitrate;
};

#endif