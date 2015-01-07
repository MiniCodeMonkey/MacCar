/*
 *  MediaManager.cpp
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "MediaManager.h"
#include "Serial.h"

MediaManager::MediaManager()
{	
	// Load playlists
	playlists = new Playlists();
	playlists->find();
	currentPlaylist = playlists->GetPlaylist(1);
	currentTrackIndex = 0;
	shuffleMode = false;
	repeatSongMode = false;
	paused = false;
	firstStream = true;
	channel = NULL;
	
	if (!BASS_Init(-1, 44100, 0, NULL, NULL))
	{
		throw new Exception("Could not init BASS Library.", EXCEPTION_CRITICAL);
	}
	
	//SetVolume(0.2);
	lastSpecCheck = 0;
	light = 0;
	colorNum = 0;
	
	serial = new Serial();
	serialId = serial->init("/dev/tty.usbserial-A9007OS2", 115200);
}

double MediaManager::GetTrackDurationLeft()
{	
	QWORD len = BASS_ChannelGetLength(channel, BASS_POS_BYTE);
	double lenTime = BASS_ChannelBytes2Seconds(channel, len);
	
	QWORD pos = BASS_ChannelGetPosition(channel, BASS_POS_BYTE);
	double posTime = BASS_ChannelBytes2Seconds(channel, pos);
	
	return lenTime - posTime;
}

double MediaManager::GetTrackPercentPlayed()
{
	QWORD len = BASS_ChannelGetLength(channel, BASS_POS_BYTE);
	double lenTime = BASS_ChannelBytes2Seconds(channel, len);
	
	QWORD pos = BASS_ChannelGetPosition(channel, BASS_POS_BYTE);
	double posTime = BASS_ChannelBytes2Seconds(channel, pos);
	
	return posTime / lenTime;	
}

void MediaManager::Tick()
{	
	if (!GetPaused() && GetTrackDurationLeft() <= 0.0)
	{
		this->Next();
	}
	
	
	//serial->writestr(serialId, "r0e");
	if ((int)Clock.GetElapsedTime() - lastSpecCheck >= 0)
	{
	int x,y;
	float fft[1024]; // get the FFT data
	BASS_ChannelGetData(channel,fft,BASS_DATA_FFT2048);
		
	int b0=0;
	//memset(specbuf,0,sizeof(specbuf));
#define BANDS 28
#define SPECHEIGHT 255
	for (x=0;x<BANDS;x++) {
		float sum=0;
		int sc,b1=pow(2,x*10.0/(BANDS-1));
		if (b1>1023) b1=1023;
		if (b1<=b0) b1=b0+1; // make sure it uses at least 1 FFT bin
		sc=10+b1-b0;
		for (;b0<b1;b0++) sum+=fft[1+b0];
		y=(sqrt(sum/log10(sc))*1.7*SPECHEIGHT)-4; // scale it
		if (y>SPECHEIGHT) y=SPECHEIGHT; // cap it
		//if (x > 7 && x < 12)
		//	printf("Band: %d, level: %d\n", x, y);
		
		if (x == 0 && y > 50)
		{
			//if (colorNum >= 5)
			{
				colorNum = 0;
				color++;
			
				if (color > 2)
				{
					color = 0;
				}
			}
			colorNum++;
		}
		
		if (x == 24)
		{
			if (y > 150)
			{
				light = y;
			}
			else
			{
				light -= 10;
				
				if (light < 0)
					light = 0;
			}

			char buf[10];
			char colorChar;
			
			if (color == 0)
			{
				colorChar = 'r';
			}
			else if (color == 1)
			{
				colorChar = 'g';
			}
			else {
				colorChar = 'b';
			}
			
			sprintf(buf, "%c%de", colorChar, light);
			serial->writestr(serialId, buf);
			
			char colorTemp1, colorTemp2 = ' ';
			
			if (colorChar == 'r')
			{
				colorTemp1 = 'g';
				colorTemp2 = 'b';
			}
			
			if (colorChar == 'g')
			{
				colorTemp1 = 'r';
				colorTemp2 = 'b';
			}
			
			if (colorChar == 'b')
			{
				colorTemp1 = 'r';
				colorTemp2 = 'g';
			}
			
			
			sprintf(buf, "%c%de", colorTemp1, 0);
			serial->writestr(serialId, buf);
			
			sprintf(buf, "%c%de", colorTemp2, 0);
			serial->writestr(serialId, buf);
		}
		
#if 0
		if (x == 4)//14)
		{
			char color1, color2, color3;
			char buf[10];
			if (y > 180)
			{
				color1 = 'g';
				color2 = 'b';
				color3 = 'r';
			}
			else if (y > 100)
			{
				color1 = 'b';
				color2 = 'r';
				color3 = 'g';
			}
			else
			{
				color1 = 'r';
				color2 = 'b';
				color3 = 'g';
			}
			
			sprintf(buf, "%c%de", color1, y);
			serial->writestr(serialId, buf);
			
			sprintf(buf, "%c%de", color2, 0);
			serial->writestr(serialId, buf);
			
			sprintf(buf, "%c%de", color3, 0);
			serial->writestr(serialId, buf);
			break;
		}
#endif		
		/*char buf[20];
		if (x == 2)
		{
			sprintf(buf, "%c%de", 'r', y);
			serial->writestr(serialId, buf);
		}
		
		if (x == 10)
		{
			sprintf(buf, "%c%de", 'g', y / 4);
			serial->writestr(serialId, buf);
		}
		
		if (x == 24)
		{
			sprintf(buf, "%c%de", 'b', y / 4);
			serial->writestr(serialId, buf);
		}*/
		
		/*while (--y>=0)
		 for (y1=0;y1<SPECWIDTH/BANDS-2;y1++)
		 specbuf[(SPECHEIGHT-1-y)*SPECWIDTH+x*(SPECWIDTH/BANDS)+y1]=palette[y+1]; // draw bar*/
	}
	//printf("-------------------------\n\n");
		lastSpecCheck = SDL_GetTicks();
	}
}

void MediaManager::Next()
{
	currentTrackIndex++;
	
	int trackIndexMax = GetCurrentPlaylist()->GetTracksCount() - 1;
	
	if (currentTrackIndex > trackIndexMax)
		currentTrackIndex = trackIndexMax;
	
	Play();
}

void MediaManager::Previous()
{
	currentTrackIndex--;
	
	if (currentTrackIndex < 0)
		currentTrackIndex = 0;
	
	Play();
}

void MediaManager::Pause()
{
	paused = true;
	BASS_ChannelPause(channel);
}

void MediaManager::Play(int index)
{	
	if (index > 0 && index < currentPlaylist->GetTracksCount() -1)
		currentTrackIndex = index;
	
	paused = false;
	
	Track *track = currentPlaylist->GetTrack(currentTrackIndex);
	
	if (firstStream)
	{
		BASS_StreamFree(channel);
	}
	
	if (channel = BASS_StreamCreateFile(FALSE, track->GetFilename(), 0, 0, 0))
	{
		BASS_ChannelPlay(channel, FALSE);
	}
	else
	{
		//printf(track->GetFilename());
		throw new Exception("Could not play file.", EXCEPTION_ERROR);
	}
}

MediaManager::~MediaManager()
{
	BASS_Free();
}