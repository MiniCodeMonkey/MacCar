/*
 *  Playlists.cpp
 *  MacCar2
 *
 *  Created by Mathias Hansen on 09/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Playlists.h"

void Playlists::find()
{
	DIR *dir;
	struct dirent *entry;
	dir = opendir(MUSIC_DIR);
	
	if (dir == NULL)
	{
		throw new Exception("Music directory doesn't exist!", EXCEPTION_CRITICAL);
		return;
	}
	
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == IS_DIR &&
			strcmp(entry->d_name, ".") != 0 &&
			strcmp(entry->d_name, "..") != 0)
		{
			playlists.push_back(new Playlist(entry->d_name));
		}
	}
}