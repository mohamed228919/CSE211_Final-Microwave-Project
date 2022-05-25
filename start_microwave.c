#include "stdint.h"
#include "stdlib.h"
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "LEDs.h"
#include "Start_Cooking.h"


//function to start count down of timer and know number of minutes and seconds
volatile unsigned int flag = 1;
void flag_stop(void)
	{
	
		flag =0;

	}

short time_4;
short time_3;
short time_2;
short time_1;
//function to start count down of timer and know number of minutes and seconds
void Start_Timer(short time_sec){
	flag =1;
	//short time_4;
	time_4 = (time_sec/60)/10;									//(0)0:00
	//short time_3;
	time_3 = (time_sec/60)-(time_4 *10);	//0(0):00
	//short time_2;
	time_2 = (time_sec/10)-6*(time_3+time_4*10);		//00:(0)0
	//short time_1;
	time_1 = time_sec-(time_2*10+(time_4*10+time_3)*60);	//00:0(0)
	Write_Timer(time_4 ,time_3 ,time_2 ,time_1);
	genericDelay_Wait1ms(1000);	
	while(time_4 | time_3 | time_2 | time_1 ){
		if(time_1!=0){
				time_1 = time_1 -1;
				Write_Timer(time_4,time_3,time_2,time_1);		
				genericDelay_Wait1ms(1000);	
			}
		else if (time_2 !=0 && time_1 ==0){
				time_2 = time_2 - 1;
				time_1 = 9;
				Write_Timer(time_4,time_3,time_2,time_1);		
				genericDelay_Wait1ms(1000);	
			}
		else if (time_3!=0 && time_2 ==0 && time_1 ==0){
		
				time_3 = time_3-1;
				time_2=5;
				time_1=9;		
				Write_Timer(time_4,time_3,time_2,time_1);		
				genericDelay_Wait1ms(1000);	
			}
		else if (time_4!=0 && time_3==0 && time_2 ==0 && time_1 ==0){
				time_4 = time_4 -1;
				time_3 = 9;
				time_2=5;
				time_1=9;		
				Write_Timer(time_4,time_3,time_2,time_1);		
				genericDelay_Wait1ms(1000);	
			}
		else if (flag == 0)
		{
			time_4 = 0;
			time_3 = 0;
			time_2 = 0;
			time_1 = 0;
			
		
		}
		
	}
}
//function to write timer on lcd
void Write_Timer(short time4, short time3, short time2, short time1)
{
	LCD_command(shiftCursorRight);      //direction of cursor to right
	LCD_command(clearDisplay);        //clear whatever is written on display
	LCD_data(time4 + '0');					//(0)0:00
	LCD_data(time3 + '0');					//0(0):00
	LCD_data(':');								//00(:)00
	LCD_data(time2 + '0');					//00:(0)0
	LCD_data(time1 + '0');					//00:0(0)
}

//function to enter no. of kilo of the beef of chicken
void Enter_kilo(char s)
{
	short c;						//variable to represent symbol pressed on keypad
	short check = 1;		//variable used to check and exit while loop
	//while loop to enter no. of kilo and check if number entered is valid or not
	while (check)
	{
		c = 0;
		if (s == 'B')								//check if the food entered is beef
			LCD_Write("Beef Weight?");	//write "Beef Weight? on lcd
		else if (s == 'C')					//check if the food entered is chicken
			LCD_Write("Chicken Weight?");		//write "Chicken Weight? on lcd
		//wait for the user to enter the number if kilo
		while (c == 0)
		{
			c = keypad_getkey();	//c => symbol pressed
		}
		//check if the symbol entered is a number between 1 to 9 or not
		if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == '#' || c == '0' || c == '*')
		{
			LCD_Write("Err..");			//write "Err.." on lcd
			genericDelay_Wait1ms(2000);			//wait 2 sec
		}
		//check if the symbol entered is a number between 1 to 9 or not
		else if(c > 0)
		{
			if (s == 'B')						//check if the food entered is beef
				Start_Cooking(30 * c); //Beef is defrosted at a rate of 0.5 minutes per kilo.
			else if (s == 'C')			//check if the food entered is chicken
				Start_Cooking(12 * c); //Chicken is defrosted at a rate of 0.2 minutes per kilo.
			check = 0;							//exit while loop
		}
	}
}

void Cooking_time(void)
{
	short i;	//variable for outer loop
	short j;	//variable for inner loop
	short time_sec;	//total time in sec
	short c = 0;	//variable to represent symbol pressed on keypad
	short flag1 = 1;	//a flag to check if time entered is valid or not
	short flag2 = 1;	//a flag to check is SW2 is pressed or not
	short times[4] = {0,0,0,0};	//an array representing time in 00:00
	short size = sizeof(times) / sizeof(short);	//a variable to determine size of array
	while(flag1)
	{
		flag2 = 1;		//set flag2 to 1
		//a loop to set time to zero
		for(i=0;i<size;i++)
		{
			times[i] = 0;
		}
		Write_Timer(times[3], times[2], times[1], times[0]); //write timer on lcd
		genericDelay_Wait1ms(500);	//wait

		//a loop to let user enter time
		for(i=0; i<size && flag2; i++)
		{
			c = 0;
			//wait for the user to enter the number
			while(c == 0)
			{
				c = keypad_getkey();	//c => symbol pressed
				//check if the symbol entered is a number or not
				if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == '#' || c == '*')
				{
					LCD_Write("Err..");			//write "Err.." on lcd
					genericDelay_Wait1ms(2000);			//wait 2 sec
					c = 0;
					Write_Timer(times[3], times[2], times[1], times[0]); //write timer on lcd
					genericDelay_Wait1ms(500);	//wait
				}
				//check if the user pressed start button or not
				if (!SW2_Input())
				{
					flag2 = 0;	//user pressed start button
					break;			//exit from loop
				}
			}
			//check if the user pressed start button or not
			if (flag2)
			{
				//if user pressed c is set to '0' not 0, so if user pressed '0' in this case let c => 0
				if (c == '0')
					c = 0;
				//a  loop to set timer values
				for(j=(size-1);j>=0;j--)
				{
					if(j==0)
						times[j] = c;
					else
						times[j] = times[j-1];
				}
				Write_Timer(times[3], times[2], times[1], times[0]); //write timer on lcd
				genericDelay_Wait1ms(500);	//wait
			}
		}
		time_sec = ((times[3]*10) + times[2])*60 + ((times[1]*10) + times[0]);	//calculate total no. of seconds
		// if time is more than 30 minutes
		if (time_sec > 1800)
		{
			LCD_Write("Max Time is 30");	//write "Max Time is 30" on lcd
			genericDelay_Wait1ms(2000);						//wait 2 sec
		}
		//if time is 00
		else if(time_sec == 0)
		{
			LCD_Write("Time is 0???");	//write	"Time is 0???" on lcd
			genericDelay_Wait1ms(2000);					//wait 2 sec
		}
		else
		{
			while (SW2_Input()){}		//wait for user to press start button
			Start_Cooking(time_sec);	//start cooking
			flag1 = 0;	//exit loop
		}
	}
}
