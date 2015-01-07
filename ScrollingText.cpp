/*
 *  ScrollingText.cpp
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ScrollingText.h"

ScrollingText::ScrollingText(Scene *scene, char *text, TTF_Font *font, SDL_Color color, int x, int y, int w, int h)
{
	this->scene = scene;
	this->font = font;
	this->color = color;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	
	this->SetText(text);
}

void ScrollingText::SetText(char *text)
{
	strcpy(this->text, text);
	
	trackScrollX = 0;
	
	int textWidth, textHeight;
	TTF_SizeText(font, text, &textWidth, &textHeight);
	
	shouldScroll = (textWidth > w);
	direction = DIRECTION_LEFT;
	wait = 0;
}

void ScrollingText::Draw()
{
	int textWidth, textHeight, scrollX;
	if (this->shouldScroll)
	{
		TTF_SizeText(font, text, &textWidth, &textHeight);
	
		int diff;
		
		switch (direction)
		{
			case DIRECTION_LEFT:
				diff = textWidth - this->w;
	
				if (trackScrollX < diff)
				{
					trackScrollX++;
				}
				else
				{
					direction = DIRECTION_STILL;
					nextDirection = DIRECTION_RIGHT;
				}

				break;
				
			case DIRECTION_STILL:
				if (wait < 50)
				{
					wait++;
				}
				else
				{
					wait = 0;
					direction = nextDirection;
				}

				break;
				
			case DIRECTION_RIGHT:
				if (trackScrollX > 0)
				{
					trackScrollX--;
				}
				else
				{
					direction = DIRECTION_STILL;
					nextDirection = DIRECTION_LEFT;
				}

				break;
		}
	
		scrollX = trackScrollX;
	}
	else
	{
		scrollX = 0;
	}
	
	scene->DrawFilledRect((SDL_Color){ 57, 57, 57 }, this->x, this->y, this->w, this->h);
	scene->WriteText(text, font, this->color, this->x, this->y, this->w, this->h, scrollX); 
}