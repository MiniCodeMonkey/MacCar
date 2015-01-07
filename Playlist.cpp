/*
 *  Playlist.cpp
 *  MacCar2
 *
 *  Created by Mathias Hansen on 09/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Playlist.h"

Playlist::Playlist(char *folder)
{
	// Initialize variables
	currentTrackIndex = 4;
	
	// Save folder name
	strcpy(this->folder, folder);
	
	// Search playlist folder for music tracks
	DIR *dir;
	struct dirent *entry;
	char playlistDir[200];
	sprintf(playlistDir, "%s/%s", MUSIC_DIR, folder);
	
	dir = opendir(playlistDir);
	
	// Check if directory could be opened
	if (dir == NULL)
	{
		printf("Could not open playlist dir: %s\n", playlistDir);
	}
	
	// Loop through files
	char fullDir[200];
	while (entry = readdir(dir))
	{
		if (entry->d_type == IS_FILE && entry->d_name[0] != '.')
		{
			sprintf(fullDir, "%s/%s/%s", MUSIC_DIR, folder, entry->d_name);
			tracks.push_back(new Track(fullDir));
		}
	}
	
	// Save name
	string dirloc = (string)folder;
	size_t found = dirloc.find_last_of("/\\");
	dirloc = dirloc.substr(found + 1);
	
	name = dirloc;
}