/*
 *  MediaManager.h
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __MEDIAMANAGER_H__
#define __MEDIAMANAGER_H__

#include <math.h>

#include "Playlists.h"
#include <SFML/Graphics.hpp>
#include "bass.h"
#include "Serial.h"

class MediaManager
{
	public:
		MediaManager();
		~MediaManager();
		void Tick();
		void Next();
		void Previous();
		void Pause();
		bool GetPaused() { return paused; }
		void Play(int index = -1);
		Playlist *GetCurrentPlaylist() { return currentPlaylist; }
		Track *GetCurrentTrack() { return currentPlaylist->GetTrack(currentTrackIndex); };
		double GetTrackDurationLeft();
		double GetTrackPercentPlayed();
		bool GetShuffleMode() { return shuffleMode; }
		void SetShuffleMode(bool val) { shuffleMode = val; } // TODO: Actually implement this
		bool GetRepeatSongMode() { return repeatSongMode; }
		void SetRepeatSongMode(bool val) { repeatSongMode = val; } // TODO: Actually implement this
		float GetVolume() { return BASS_GetVolume(); }
		void SetVolume(float volume) { if (volume > 1.0) volume = 1.0; else if (volume < 0.0) volume = 0.0; BASS_SetVolume(volume); }
	
	private:
		Playlists *playlists;
		Playlist *currentPlaylist;
		DWORD channel;
		long lastSpecCheck;
		int currentTrackIndex;
		bool shuffleMode;
		bool repeatSongMode;
		bool firstStream;
		bool paused;
		int serialId;
		Serial *serial;
		int light;
		int color;
		int colorNum;
		sf::Clock Clock;
};

#endif