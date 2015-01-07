/*
 *  Scene_Main.cpp
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Scene_Main.h"

Scene_Main::Scene_Main()
{
}

void Scene_Main::Preload(Main *main)
{
	this->main = main;
	//this->App = main->GetScreen();
	
	
	menu = IMG_Load("../../Simplistique/menu_OFF.jpg");
	menu_down = IMG_Load("../../Simplistique/menu_down.jpg");
	
	if (menu == NULL || menu_down == NULL)
	{
		throw new Exception("Could not load image", EXCEPTION_CRITICAL);
	}
	
	buttons.push_back(new Button(0, 116, 290, 80, BUTTON_MUSIC));	// Music
	buttons.push_back(new Button(0, 212, 270, 80, 99));					// Radio
	buttons.push_back(new Button(0, 307, 270, 80));					// Video
	buttons.push_back(new Button(0, 402, 348, 80));					// DVD
	
	buttons.push_back(new Button(520, 117, 360, 82));				// TV
	buttons.push_back(new Button(540, 212, 300, 80));				// GPS
	buttons.push_back(new Button(530, 307, 275, 80));				// Internet
	buttons.push_back(new Button(455, 402, 350, 80));				// Utilities
	
	buttons.push_back(new Button(632, 512, 86, 87, BUTTON_VOLP));	// Vol+
	buttons.push_back(new Button(547, 512, 87, 87, BUTTON_VOLM));	// Vol-
	
	buttons.push_back(new Button(121, 503, 108, 104));				// Exit
	buttons.push_back(new Button(715, 512, 90, 87, BUTTON_MUTE));	// Master mute
	
	SDL_BlitSurface(menu, NULL, screen, NULL);
	
	// Load fonts
	dotmatrix24 = TTF_OpenFont("../../Simplistique/!FONTS/dotmatrix.ttf", 24);
	arialbd16 = TTF_OpenFont("../../Simplistique/!FONTS/arialbd.ttf", 16);
	drtu18 = TTF_OpenFont("../../Simplistique/!FONTS/Digital_Readout_Thick_Upright.ttf", 20);
	if (dotmatrix24 == NULL || arialbd16 == NULL || drtu18 == NULL)
	{
		throw new Exception("Couldn't open font.", EXCEPTION_CRITICAL);
	}
	//TTF_SetFontStyle(drtu18, TTF_STYLE_BOLD);
	
	// Scrolling track info text
	strcpy(trackInfo, main->GetMediaManager()->GetCurrentTrack()->GetShortInfo());
	scrollingTrackInfo = new ScrollingText(this, trackInfo, drtu18, (SDL_Color){ 255, 102, 0 }, 10, 45, 396, 35);
	
	SDL_Flip(screen);
}

void Scene_Main::Draw()
{	
	// Write track info
	if (strcmp(trackInfo, main->GetMediaManager()->GetCurrentTrack()->GetShortInfo()) != 0)
	{
		strcpy(trackInfo, main->GetMediaManager()->GetCurrentTrack()->GetShortInfo());
		scrollingTrackInfo->SetText(main->GetMediaManager()->GetCurrentTrack()->GetShortInfo());
	}
	scrollingTrackInfo->Draw();
	
	DrawFilledRect((SDL_Color){ 57, 57, 57 }, 421, 46, 74, 35);
	char durationText[20];
	sprintf(durationText, "-%02d:%02d", (int)main->GetMediaManager()->GetTrackDurationLeft() / 60, (int)main->GetMediaManager()->GetTrackDurationLeft() % 60);
	WriteText(durationText, drtu18, (SDL_Color){ 255, 102, 0 }, 421, 46, 74, 35);
	
	// Write date/time
	Draw_DateTime();
	
	// Draw volume bars
	float volume = main->GetMediaManager()->GetVolume();
	int bar = ceil(volume * 20.0);
	char imgFile[200];
	
	sprintf(imgFile, "../../Simplistique/volume_slider/volume_%d.jpg", bar);
	SDL_Surface *volumeBar = IMG_Load(imgFile);
	DrawSurface(volumeBar, 303, 520, 215, 45);
	SDL_FreeSurface(volumeBar);
}

void Scene_Main::Draw_DateTime()
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime (&rawtime);
	
	char clockInfo[50];
	sprintf(clockInfo, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	DrawFilledRect((SDL_Color){ 0, 0, 0 }, 590, 35, 200, 40); // Clear area first
	WriteText(clockInfo, dotmatrix24, (SDL_Color){ 255, 255, 255 }, 590, 35, 200, 40);
	
	char dateInfo[50];
	sprintf(dateInfo, "%02d/%02d/%02d", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
	DrawFilledRect((SDL_Color){ 0, 0, 0 }, 591, 66, 120, 30); // Clear area first
	WriteText(dateInfo, arialbd16, (SDL_Color){ 255, 255, 255}, 591, 66, 120, 30);
}

void Scene_Main::HandleEvents(SDL_Event event)
{
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
						case 99:
							SDL_Quit();
							break;
							
						case BUTTON_VOLP:
							main->GetMediaManager()->SetVolume(currentVolume + 0.10);
							break;
							
						case BUTTON_VOLM:
							if (currentVolume - 0.10 < 0.0)
							{
								main->GetMediaManager()->SetVolume(0.0);
							}
							else
							{
								main->GetMediaManager()->SetVolume(currentVolume - 0.10);
							}
							break;
							
						case BUTTON_MUTE:
							main->GetMediaManager()->SetVolume(0.0);
							break;
							
						case BUTTON_MUSIC:
							main->SetScene(new Scene_Music());
							return;
							break;
					}
				}
				
				SDL_Rect rect = (*button)->GetRect();
				SDL_BlitSurface(menu, &rect, screen, &rect);
			}
			break;
		}
	}
}

Scene_Main::~Scene_Main()
{
	SDL_FreeSurface(menu);
	SDL_FreeSurface(menu_down);
	
	TTF_CloseFont(dotmatrix24); 
	TTF_CloseFont(arialbd16);
	TTF_CloseFont(drtu18);
}