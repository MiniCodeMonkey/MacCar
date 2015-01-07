/*
 *  Scene_Music.cpp
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Scene_Music.h"

Scene_Music::Scene_Music()
{
	trackListStartIndex = 0;
	selectedTrackIndex = 0;
}

void Scene_Music::Preload(Main *main)
{
	this->main = main;
	this->screen = main->GetScreen();
	
	menu = IMG_Load("../../Simplistique/Audio_Player_OFF.jpg");
	menu_down = IMG_Load("../../Simplistique/Audio_Player_down.jpg");
	menu_additional = IMG_Load("../../Simplistique/Audio_Player_ON.jpg");
	
	if (menu == NULL || menu_down == NULL || menu_additional == NULL)
	{
		throw new Exception("Could not load image.", EXCEPTION_CRITICAL);
	}
	
	buttons.push_back(new Button(13, 116, 100, 84, BUTTON_PLAY));	// Play
	buttons.push_back(new Button(124, 119, 127, 79, BUTTON_STOP));	// Stop
	buttons.push_back(new Button(13, 210, 101, 84, BUTTON_PREV));	// Previous track
	buttons.push_back(new Button(120, 210, 105, 84, BUTTON_NEXT));	// Next track
	
	buttons.push_back(new Button(631, 504, 87, 98, BUTTON_VOLP));	// Vol+
	buttons.push_back(new Button(545, 502, 88, 95, BUTTON_VOLM));	// Vol-
	buttons.push_back(new Button(715, 502, 91, 95, BUTTON_MUTE));	// Master mute
	
	buttons.push_back(new Button(13, 306, 99, 84, BUTTON_SHFRPT));	// Shuffle/Repeat button
	buttons.push_back(new Button(1, 500, 110, 98, BUTTON_EXIT));	// Exit
	
	buttons.push_back(new Button(738, 368, 59, 54, BUTTON_DOWN));	// Track list down
	buttons.push_back(new Button(737, 158, 60, 55, BUTTON_UP));		// Track list up
	buttons.push_back(new Button(738,317,59,53, BUTTON_PAGE_DOWN));	// Track list page down
	buttons.push_back(new Button(738,212,59,53, BUTTON_PAGE_UP));	// Track list page down
	
	SDL_BlitSurface(menu, NULL, screen, NULL);
	
	// Load fonts
	dotmatrix24 = TTF_OpenFont("../../Simplistique/!FONTS/dotmatrix.ttf", 24);
	arialbd16 = TTF_OpenFont("../../Simplistique/!FONTS/arialbd.ttf", 16);
	arial15 = TTF_OpenFont("../../Simplistique/!FONTS/arial.ttf", 18);
	arial14 = TTF_OpenFont("../../Simplistique/!FONTS/arialbd.ttf", 18);
	drtu18 = TTF_OpenFont("../../Simplistique/!FONTS/Digital_Readout_Thick_Upright.ttf", 20);
	if (dotmatrix24 == NULL || arialbd16 == NULL || drtu18 == NULL || arial15 == NULL || arial14 == NULL)
	{
		throw new Exception("Couldn't open font.", EXCEPTION_CRITICAL);
	}
	TTF_SetFontStyle(arial15, TTF_STYLE_BOLD);
	
	// Scrolling track info text
	strcpy(trackInfo, main->GetMediaManager()->GetCurrentTrack()->GetShortInfo());
	scrollingTrackInfo = new ScrollingText(this, trackInfo, drtu18, (SDL_Color){ 255, 102, 0 }, 10, 45, 396, 35);
	
    trackList = CreateSurface(298, 254);
    if (trackList == NULL)
	{
		throw new Exception("Could not create trackList surface", EXCEPTION_ERROR);
    }
	
	SDL_Flip(screen);
}

void Scene_Music::Draw()
{
	// Write track info
	if (strcmp(trackInfo, main->GetMediaManager()->GetCurrentTrack()->GetShortInfo()) != 0)
	{
		strcpy(trackInfo, main->GetMediaManager()->GetCurrentTrack()->GetShortInfo());
		scrollingTrackInfo->SetText(trackInfo);
	}
	scrollingTrackInfo->Draw();
	
	// Draw time left
	DrawFilledRect((SDL_Color){ 57, 57, 57 }, 421, 46, 74, 35);
	char durationText[20];
	sprintf(durationText, "-%02d:%02d", (int)main->GetMediaManager()->GetTrackDurationLeft() / 60, (int)main->GetMediaManager()->GetTrackDurationLeft() % 60);
	WriteText(durationText, drtu18, (SDL_Color){ 255, 102, 0 }, 421, 46, 74, 35);
	
	// Draw playlist name
	DrawFilledRect((SDL_Color){ 0, 0, 0 }, 435, 115, 360, 20);
	WriteText(main->GetMediaManager()->GetCurrentPlaylist()->GetName(), arial15, (SDL_Color){ 255, 102, 0 }, 435, 115, 360, 20);
	
	// Write date/time
	this->Draw_DateTime();
	
	// Draw volume bars
	float volume = main->GetMediaManager()->GetVolume();
	int bar = ceil((double)(volume * 20.0)); // Max volume is 128
	char imgFile[200];
	
	sprintf(imgFile, "../../Simplistique/volume_slider/volume_%d.jpg", bar);
	SDL_Surface *volumeBar = IMG_Load(imgFile);
	DrawSurface(volumeBar, 303, 520, 215, 45);
	SDL_FreeSurface(volumeBar);
	
	// Draw track list
	this->Draw_TrackList();
	
	// Draw current track position
	DrawFilledRect((SDL_Color){ 57, 57, 57 }, 463 + (265 * (main->GetMediaManager()->GetTrackPercentPlayed())), 445, 265 - (265 * (main->GetMediaManager()->GetTrackPercentPlayed())), 31);
	DrawFilledRect((SDL_Color){ 255, 102, 0 }, 463, 445, 265 * (main->GetMediaManager()->GetTrackPercentPlayed()), 31);
	
	// Draw album cover
	// http://matisen.dk/albumCover.php?s=Album%20name
	
	// Draw shuffle indicator
	DrawFilledRect((SDL_Color){ 0, 0, 0 }, 351, 186, 29, 32);
	if (main->GetMediaManager()->GetShuffleMode())
	{
		SDL_Rect rect;
		rect.x = 351;
		rect.y = 186;
		rect.w = 29;
		rect.h = 32;
		
		DrawFilledRect((SDL_Color){ 57, 57, 57 }, rect.x, rect.y, rect.w, rect.h);
		SDL_BlitSurface(menu_additional, &rect, screen, &rect);
	}
	
	// Draw repeat indicator
	DrawFilledRect((SDL_Color){ 0, 0, 0 }, 312, 186, 33, 34);
	if (main->GetMediaManager()->GetRepeatSongMode())
	{
		SDL_Rect rect;
		rect.x = 312;
		rect.y = 186;
		rect.w = 33;
		rect.h = 34;
		
		DrawFilledRect((SDL_Color){ 57, 57, 57 }, rect.x, rect.y, rect.w, rect.h);
		SDL_BlitSurface(menu_additional, &rect, screen, &rect);
	}
}

void Scene_Music::Draw_TrackList()
{
	// Clear surface
	SDL_FillRect(trackList, NULL, SDL_MapRGB(screen->format, 57, 57, 57));
	
	int y = 0;
	for (int i = trackListStartIndex; i < main->GetMediaManager()->GetCurrentPlaylist()->GetTracksCount() - 1; i++)
	{
		if (selectedTrackIndex == i)
		{
			SDL_Rect rect;
			rect.x = 0;
			rect.y = y;
			rect.w = 298;
			rect.h = 25;
			
			SDL_FillRect(trackList, &rect, SDL_MapRGB(screen->format, 255, 102, 0));
		}
		
		WriteText(main->GetMediaManager()->GetCurrentPlaylist()->GetTrack(i)->GetTrackTitle(), arial14, (SDL_Color) { 255, 255, 255 }, 2, y, 298, 25, 0, trackList);
		y += 25;
		
		if (y > 254)
			break;
	}
	
	DrawSurface(trackList, 435, 164, 298, 254);
}

void Scene_Music::Draw_DateTime()
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime (&rawtime);
	
	char clockInfo[50];
	sprintf(clockInfo, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	DrawFilledRect((SDL_Color){ 0, 0, 0 }, 590, 35, 200, 40); // Clear area first
	WriteText(clockInfo, dotmatrix24, (SDL_Color){ 185, 185, 185 }, 590, 35, 200, 40);
	
	char dateInfo[50];
	sprintf(dateInfo, "%02d/%02d/%02d", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
	DrawFilledRect((SDL_Color){ 0, 0, 0 }, 591, 66, 120, 30); // Clear area first
	WriteText(dateInfo, arialbd16, (SDL_Color){ 185, 185, 185}, 591, 66, 120, 30);
}

void Scene_Music::HandleEvents(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
	{
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK)
		{
			// Mouse button down over track list?
			if (event.motion.x > 435 && event.motion.x < 435 + 298 &&
				event.motion.y > 164 && event.motion.y < 164 + 254)
			{
				selectedTrackIndex = trackListStartIndex + ((event.motion.y - 164) / 25);
			}
		}
	}
	switch (event.type)
	{			
		case SDL_MOUSEBUTTONDOWN:
			for (list<Button*>::iterator button = buttons.begin(); button != buttons.end(); button++)
			{
				SDL_Rect rect = (*button)->GetRect();
				if ((*button)->Intersecting(event.motion.x, event.motion.y))
				{
					SDL_BlitSurface(menu_down, &rect, screen, &rect);
				}
				else
				{
					SDL_BlitSurface(menu, &rect, screen, &rect);
				}
				
			}
			
			break;
			
		case SDL_MOUSEBUTTONUP:
		{
			float currentVolume = main->GetMediaManager()->GetVolume();
			
			for (list<Button*>::iterator button = buttons.begin(); button != buttons.end(); button++)
			{
				if ((*button)->Intersecting(event.motion.x, event.motion.y))
				{
					switch ((*button)->GetButtonId())
					{
						case BUTTON_VOLP:
							main->GetMediaManager()->SetVolume(currentVolume + 0.10);
							break;
							
						case BUTTON_VOLM:
							main->GetMediaManager()->SetVolume(currentVolume - 0.10);
							break;
							
						case BUTTON_MUTE:
							main->GetMediaManager()->SetVolume(0.0);
							break;
							
						case BUTTON_NEXT:
							main->GetMediaManager()->Next();
							break;
							
						case BUTTON_PREV:
							main->GetMediaManager()->Previous();
							break;
							
						case BUTTON_STOP:
							main->GetMediaManager()->Pause();
							break;
							
						case BUTTON_PLAY:
							main->GetMediaManager()->Play(selectedTrackIndex);
							break;
							
						case BUTTON_EXIT:
							main->SetScene(new Scene_Main());
							break;
							
						case BUTTON_DOWN:
							if (trackListStartIndex < main->GetMediaManager()->GetCurrentPlaylist()->GetTracksCount() - 1)
								trackListStartIndex++;
							break;
							
						case BUTTON_UP:
							if (trackListStartIndex > 0)
								trackListStartIndex--;
							break;
							
						case BUTTON_PAGE_DOWN:
							if (trackListStartIndex < main->GetMediaManager()->GetCurrentPlaylist()->GetTracksCount() - 6)
								trackListStartIndex += 5;
							else
								trackListStartIndex = main->GetMediaManager()->GetCurrentPlaylist()->GetTracksCount() -1;
							break;
							
						case BUTTON_PAGE_UP:
							if (trackListStartIndex > 4)
								trackListStartIndex -= 5;
							else
								trackListStartIndex = 0;
							break;
							
						case BUTTON_SHFRPT:
							bool s = main->GetMediaManager()->GetShuffleMode();
							bool r = main->GetMediaManager()->GetRepeatSongMode();
							
							if (!s && !r)
							{
								main->GetMediaManager()->SetShuffleMode(true);
								main->GetMediaManager()->SetShuffleMode(false);
							}
							else if (s && !r)
							{
								main->GetMediaManager()->SetShuffleMode(true);
								main->GetMediaManager()->SetShuffleMode(true);
							}
							else if (s && r)
							{
								main->GetMediaManager()->SetShuffleMode(false);
								main->GetMediaManager()->SetShuffleMode(true);
							}
							else if (!s && r)
							{
								main->GetMediaManager()->SetShuffleMode(false);
								main->GetMediaManager()->SetShuffleMode(false);
							}
							break;
					}
					
					if (trackListStartIndex > main->GetMediaManager()->GetCurrentPlaylist()->GetTracksCount() - 11)
						trackListStartIndex = main->GetMediaManager()->GetCurrentPlaylist()->GetTracksCount() - 11;
				}
				
				SDL_Rect rect = (*button)->GetRect();
				SDL_BlitSurface(menu, &rect, screen, &rect);
			}
			break;
		}
	}
}

Scene_Music::~Scene_Music()
{
	SDL_FreeSurface(menu);
	SDL_FreeSurface(menu_down);
	SDL_FreeSurface(menu_additional);
	SDL_FreeSurface(trackList);
	
	TTF_CloseFont(dotmatrix24); 
	TTF_CloseFont(arialbd16);
	TTF_CloseFont(arial15);
	TTF_CloseFont(arial14);
	TTF_CloseFont(drtu18);
}