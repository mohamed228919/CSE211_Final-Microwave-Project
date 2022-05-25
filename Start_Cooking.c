/****************************************************
*  @file   Start_Cooking.c
*
* @author   Youssef Eslam Mohamed
*
*  @date     2/5/2022 11:30 AM
*
****************************************************/
#include "Start_Cooking.h"

void LCD_errormsg(void){
	LCD_Write("Err...");
}
//function to start the cooking of microwave
void Start_Cooking(char time_sec){
	int i;
	LCD_command(shiftCursorRight);      //direction of cursor to right
	LCD_command(cursorBlink);         //turn on display mode and cursor blinking
	LCD_command(clearDisplay) ;        //clear whatever is written on display 
	RGB_Output(RED+BLUE+GREEN);		//turn on all leds
	Start_Timer(time_sec);				//start counting down	
	for(i = 0; i < 3; i++)
	{
		Buzzer_Output(BuzzerON);	//turn on buzzer
		RGB_Output(OFF);						//turn off leds
		genericDelay_Wait1ms(1000);					//wait 1 sec
		RGB_Output(RED+BLUE+GREEN);	//turn on all leds
		genericDelay_Wait1ms(1000);					//wait 1 sec
	}
	Buzzer_Output(OFF);					//turn off buzzer
	RGB_Output(OFF);
	}

	


