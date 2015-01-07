/*
 *  Scene.cpp
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Scene.h"

void Scene::WriteText(const char *text, TTF_Font *font, SDL_Color textColor, int x, int y, int w, int h, int srcX, SDL_Surface *dest)
{
	SDL_Surface *s = TTF_RenderText_Blended(font, text, textColor);
	
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	
	SDL_Rect rectSource;
	rectSource.x = srcX;
	rectSource.y = 0;
	rectSource.w = w;
	rectSource.h = h;
	
	SDL_BlitSurface(s, &rectSource, (dest == NULL) ? screen : dest, &rect);	
}

void Scene::DrawFilledRect(SDL_Color color, int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	
	SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, color.r, color.g, color.b));
}

void Scene::DrawSurface(SDL_Surface *surface, int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	
	SDL_BlitSurface(surface, NULL, screen, &rect);
}

SDL_Surface* Scene::CreateSurface(int width, int height)
{	
	const SDL_PixelFormat& fmt = *(screen->format);
	return SDL_CreateRGBSurface(SDL_HWSURFACE, width, height,
								fmt.BitsPerPixel,
								fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask );
}