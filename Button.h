/*
 *  Button.h
 *  MacCar2
 *
 *  Created by Mathias Hansen on 11/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "defines.h"

class Button {
	public:
		Button(int x, int y, int w, int h, int buttonId = BUTTON_UNDEFINED);
		bool Intersecting(int x, int y);
		//SDL_Rect GetRect();
		int GetButtonId() { return buttonId; }
	
	private:
		int x, y, w, h, buttonId;
};

#endif