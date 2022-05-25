/****************************************************
*  @file   Start_Cooking.h
*
*@author   Youssef Eslam Mohamed

*  @date     20/5/2022 10:40PM
*
****************************************************/
#ifndef __START_COOKING_H__
#define __START_COOKING_H__
#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "LEDs.h"
void Start_Cooking(char time_sec);
#define OFF           			0x00
#define BuzzerON            0x04
#define RED 								0x02
#define BLUE 								0x04
#define GREEN 							0x08
#endif