/*
 *  Serial.h
 *  LightControl
 *
 *  Created by Mathias Hansen on 25/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h> 
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>

class Serial
{
public:
	int init(const char* serialport, int baud);
	int writebyte(int fd, uint8_t b);
	int writestr(int fd, const char* str);
	int read_until(int fd, char* buf, char until);
};

#endif
