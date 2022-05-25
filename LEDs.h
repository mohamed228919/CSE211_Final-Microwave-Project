/**************************************************
*  @file     LEDs.h
*
*  @author   Youssef Eslam Mohamed
*
*  @date     2/5/2022 11:30 AM
*
**************************************************/
#ifndef __LEDs_H__
#define __LEDs_H__
#include "tm4c123gh6pm.h"
#include "SystickTimer.h"
#include "keypad.h"
#include "LCD.h"
void PortFInit(void);											//Intilization of PORTF
unsigned char SW1_Input(void);						//Check if SW1 in TivaC is pressed or not
unsigned char SW2_Input(void);						//Check if SW2 in TivaC is pressed or not
unsigned char SW_Input(void);							//Check if SW1 and SW2 is pressed or not
void RGB_Output(char data);			//Turn ON, Turn OFF, Change Color of LEDS in TivaC
void SW3WithBuzzer_Init(void);								//Intilization of  SW3 and Buzzer
unsigned char SW3_Input(void);						//Check if SW3 is pressed or not
void Buzzer_Output(unsigned char data);		//Turn ON, Turn OFF Buzzer
void Start_Cooking(char time_sec);		//function to start the cooking of microwave
void Start_Timer(short time_sec);				//function to start count down of timer and know number of minutes and seconds
void Write_Timer(short time4, short time3, short time2, short time1);	//function to write timer on lcd
void Enter_kilo(char s);								//function to enter no. of kilo of the beef of chicken
void Cooking_time(void);
#endif
