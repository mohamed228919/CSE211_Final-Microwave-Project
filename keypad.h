/**************************************************
*  @file     Keypad.h
*
*  @author   Group Mido & Nahas
*
*  @date    2/5/2022 11:30 AM
**************************************************/
#ifndef __KEYPAD_H__
#define __KEYPAD_H__
#include "tm4c123gh6pm.h"
#include "SystickTimer.h"
#define  padRows  4
#define  padCols  4

void keypad_Init       (void);
char keypad_getkey     (void);

#endif
