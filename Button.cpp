/*
 *  Button.cpp
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "Button.h"

Button::Button(int x, int y, int w, int h, int buttonId)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->buttonId = buttonId;
}

bool Button::Intersecting(int x, int y)
{
	if (x >= this->x && x <= (this->x + this->w) &&
		y >= this->y && y <= (this->y + this->h))
	{
		return true;
	}
	
	return false;
}

SDL_Rect Button::GetRect()
{
	SDL_Rect r;
	r.x = this->x;
	r.y = this->y;
	r.w = this->w;
	r.h = this->h;
	
	return r;
}