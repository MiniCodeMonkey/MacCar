/*
 *  Track.cpp
 *  MacCar2
 *
 *  Created by Mathias Hansen on 09/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Track.h"

Track::Track(char *file)
{
	strcpy(this->file, file);
	
	TagLib::FileRef *tagLib_fileRef = new TagLib::FileRef(this->file);
	TagLib::Tag *tagLib_tag;
	
	if (!tagLib_fileRef->isNull() && tagLib_fileRef->tag())
		tagLib_tag = tagLib_fileRef->tag();
	else
		return;
	
	// Track title
	if (tagLib_tag->title().length() > 0)
	{
		strcpy(trackTitle, (char*)tagLib_tag->title().toCString());
	}
	else
	{
		// Guess from file name.
		string filename = (string)this->GetFilename();
		size_t found = filename.find_last_of("/\\");
		filename = filename.substr(found + 1);
		
		found = filename.find_last_of(".");
		filename = filename.substr(0, found);
		
		found = filename.find_last_of("-");
		filename = filename.substr(found + 1);
		
		// Trim Both leading and trailing spaces
		size_t startpos = filename.find_first_not_of(" \t"); // Find the first character position after excluding leading blank spaces
		size_t endpos = filename.find_last_not_of(" \t"); // Find the first character position from reverse af
		
		// If all spaces or empty return an empty string
		if (string::npos == startpos || string::npos == endpos)
		{
			filename = "Unknown track";
		}
		else
			filename = filename.substr(startpos, endpos-startpos+1);
		
		strcpy(trackTitle, (char*)filename.c_str());
	}
	
	// Track artist
	if (tagLib_tag->artist().length() > 0)
	{
		strcpy(trackArtist, (char*)tagLib_tag->artist().toCString());
	}
	else
	{
		strcpy(trackArtist, "");
	}
	
	// Track album
	if (tagLib_tag->album().length() > 0)
	{
		strcpy(trackAlbum, (char*)tagLib_tag->album().toCString());
	}
	else
	{
		strcpy(trackAlbum, "");
	}
	
	// Short info
	if (tagLib_tag->title().length() > 0 && tagLib_tag->artist().length() > 0)
	{
		//char *shortInfo = (char*)malloc(100); // I think i made myself a little memory leak here -.-
		sprintf(trackShortInfo, "%s - %s", tagLib_tag->artist().toCString(), tagLib_tag->title().toCString());
	}
	else if (tagLib_tag->title().length() > 0)
	{
		strcpy(trackShortInfo, (char*)tagLib_tag->title().toCString());
	}
	else
	{
		// Guess from file name.
		string filename = (string)this->GetFilename();
		size_t found = filename.find_last_of("/\\");
		filename = filename.substr(found + 1);
		
		found = filename.find_last_of(".");
		filename = filename.substr(0, found);
		
		strcpy(trackShortInfo, (char*)filename.c_str());
	}
	
	trackDuration = tagLib_fileRef->audioProperties()->length();
	trackBitrate = tagLib_fileRef->audioProperties()->bitrate();
}