/*
 *  Exception.h
 *  MacCar2
 *
 *  Created by Mathias Hansen on 10/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>
#include "defines.h"

using namespace std;

class Exception
{
	public:
		Exception(string message, int level)
		{
			this->message = message;//strcpy(this->message, message);
			this->level = level;
			
			printf("** EXCEPTION **\nMessage: %s\n", message.c_str());
			
			if (this->level > 2)
				exit(1);
		}
	
	string getMessage() { return message; }
	int getLevel() { return level; }
	
	private:
	string message;
		int level;
};

#endif