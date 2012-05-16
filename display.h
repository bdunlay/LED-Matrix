#ifndef __DISPLAY_H
#define __DISPLAY_H

/*
 * display.h
 *
 * Created: 5/16/2012 10:40:41 AM
 *  Author: Brian
 */ 

#define DISPLAY_WIDTH	8

#include "common.h"

void refresh(void);
void printd(byte[]);
void test_display(void);

#endif