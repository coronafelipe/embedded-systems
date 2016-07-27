/*
 * CS145Lab2.c
 *
 * Created: 4/21/2016 3:54:15 PM
 * Author : toran
 */ 

#include <avr/io.h>
#include "lcd.h"
#include "avr.h"
#include "stdio.h"
#include "string.h"
unsigned int speed = 1;

struct note
{
	unsigned int freq;
	unsigned int dur;
	unsigned int delay;
};


struct note mySong[41];
struct note mySong1[42];



void playNote(struct note theNote)
{
	for(unsigned long i = 0; i < theNote.dur; i++)
	{
		SET_BIT(PORTB, 3);
		wait_avr2(theNote.freq);
		CLR_BIT(PORTB, 3);
		wait_avr2(theNote.freq);
	}
	wait_avr((theNote.delay / speed));
}

unsigned int convertKeypad(unsigned int input)
{
	unsigned int output = input;
	if(input == 5 || input == 6 || input == 7)
	{
		output = input - 1;
	}
	else if(input == 9 ||input == 10 || input == 11)
	{
		output = input - 2;
	}
	else if(input == 14)
	{
		output = 0;
	}
	
	
	return output;
	
}

struct D 
{
	int day;
	int mo;
	unsigned int yr;
};

struct T
{
	int sec;
	int min;
	int hr;	
};

unsigned char pressed(unsigned char r, unsigned char c)
{
	DDRC = 0;
	PORTC = 0;
	SET_BIT(DDRC, c + 4);
	SET_BIT(PORTC, r);
	CLR_BIT(PORTC, c + 4);
	//CLR_BIT(PORTC, r << 4);
	
	wait_avr(1);
	
	if(!(GET_BIT(PINC, r)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned char get_key()
{
	unsigned char r;
	unsigned char c;
	//char inputLine[32];
	//PORTC = 0x0b00001111;
	//SET_BIT(PORTC, 4);
	//SET_BIT(PORTC, 5);
	//SET_BIT(PORTC, 6);
	//SET_BIT(PORTC, 7);
	
	for(r = 0; r < 4; ++r)
	{
		for(c = 0; c < 4; ++c)
		{
			
			if (pressed(r, c))
			{
				
				return (r * 4) + (c + 1);
			}
		}
	}
	return 0;
}


int checkDate(struct D date)
{
	int monthLen[13] = {29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (date.mo > 12)
	{
		return 0;
	}
	if (date.yr % 4 == 0)
	{
		monthLen[2] = 29;
	}
	if (date.day > monthLen[date.mo])
	{
		return 0;
	}
	return 1;
}

int checkTime(struct T time)
{
	if (time.hr > 24)
	{
		return 0;
	}
	if (time.min >= 60)
	{
		return 0;
	}
	if (time.sec >= 60)
	{
		return 0;
	}
	return 1;
}

int main(void)
{
    
	SET_BIT(DDRB, 3);
	
	mySong[0].freq = 76;
	mySong[0].dur = 100;
	mySong[0].delay = 150;
	
	mySong[1].freq = 76;
	mySong[1].dur = 100;
	mySong[1].delay = 300;
	
	mySong[2].freq = 76;
	mySong[2].dur = 100;
	mySong[2].delay = 300;
	
	mySong[3].freq = 95;
	mySong[3].dur = 100;
	mySong[3].delay = 100;
	
	mySong[4].freq = 76;
	mySong[4].dur = 100;
	mySong[4].delay = 300;
	
	mySong[5].freq = 63;
	mySong[5].dur = 100;
	mySong[5].delay = 550;
	
	mySong[6].freq = 131;
	mySong[6].dur = 100;
	mySong[6].delay = 575;
	
	mySong[7].freq = 98;
	mySong[7].dur = 100;
	mySong[7].delay = 450;

	mySong[8].freq = 131;
	mySong[8].dur = 100;
	mySong[8].delay = 400;

	mySong[9].freq = 156;
	mySong[9].dur = 100;
	mySong[9].delay = 500;

	mySong[10].freq = 113;
	mySong[10].dur = 100;
	mySong[10].delay = 300;

	mySong[11].freq = 104;
	mySong[11].dur = 80;
	mySong[11].delay = 330;

	mySong[12].freq = 111;
	mySong[12].dur = 100;
	mySong[12].delay = 150;

	mySong[13].freq = 116;
	mySong[13].dur = 100;
	mySong[13].delay = 300;

	mySong[14].freq = 131;
	mySong[14].dur = 100;
	mySong[14].delay = 200;

	mySong[15].freq = 76;
	mySong[15].dur = 80;
	mySong[15].delay = 200;

	mySong[16].freq = 66;
	mySong[16].dur = 50;
	mySong[16].delay = 150;

	mySong[17].freq = 58;
	mySong[17].dur = 100;
	mySong[17].delay = 300;

	mySong[18].freq = 71;
	mySong[18].dur = 80;
	mySong[18].delay = 150;

	mySong[19].freq = 66;
	mySong[19].dur = 50;
	mySong[19].delay = 350;

	mySong[20].freq = 76;
	mySong[20].dur = 80;
	mySong[20].delay = 300;

	mySong[21].freq = 96;
	mySong[21].dur = 80;
	mySong[21].delay = 150;

	mySong[22].freq = 86;
	mySong[22].dur = 80;
	mySong[22].delay = 150;

	mySong[23].freq = 104;
	mySong[23].dur = 80;
	mySong[23].delay = 500;
	
	mySong[24].freq = 98;
	mySong[24].dur = 100;
	mySong[24].delay = 450;

	mySong[25].freq = 131;
	mySong[25].dur = 100;
	mySong[25].delay = 400;

	mySong[26].freq = 156;
	mySong[26].dur = 100;
	mySong[26].delay = 500;

	mySong[27].freq = 113;
	mySong[27].dur = 100;
	mySong[27].delay = 300;

	mySong[28].freq = 104;
	mySong[28].dur = 80;
	mySong[28].delay = 330;

	mySong[29].freq = 111;
	mySong[29].dur = 100;
	mySong[29].delay = 150;

	mySong[30].freq = 116;
	mySong[30].dur = 100;
	mySong[30].delay = 300;

	mySong[31].freq = 131;
	mySong[31].dur = 100;
	mySong[31].delay = 200;

	mySong[32].freq = 76;
	mySong[32].dur = 80;
	mySong[32].delay = 200;

	mySong[33].freq = 66;
	mySong[33].dur = 50;
	mySong[33].delay = 150;

	mySong[34].freq = 58;
	mySong[34].dur = 100;
	mySong[34].delay = 300;

	mySong[35].freq = 71;
	mySong[35].dur = 80;
	mySong[35].delay = 150;

	mySong[36].freq = 66;
	mySong[36].dur = 50;
	mySong[36].delay = 350;

	mySong[37].freq = 76;
	mySong[37].dur = 80;
	mySong[37].delay = 300;

	mySong[38].freq = 96;
	mySong[38].dur = 80;
	mySong[38].delay = 150;

	mySong[39].freq = 86;
	mySong[39].dur = 80;
	mySong[39].delay = 150;

	mySong[40].freq = 104;
	mySong[40].dur = 80;
	mySong[40].delay = 500;
	
	mySong1[0].freq = 85;
	mySong1[0].dur = 100;
	mySong1[0].delay = 80;

	mySong1[1].freq = 72;
	mySong1[1].dur = 100;
	mySong1[1].delay = 80;

	mySong1[2].freq = 43;
	mySong1[2].dur = 200;
	mySong1[2].delay = 250;

	mySong1[3].freq = 85;
	mySong1[3].dur = 100;
	mySong1[3].delay = 80;

	mySong1[4].freq = 72;
	mySong1[4].dur = 100;
	mySong1[4].delay = 80;

	mySong1[5].freq = 43;
	mySong1[5].dur = 200;
	mySong1[5].delay = 250;

	mySong1[6].freq = 37;
	mySong1[6].dur = 200;
	mySong1[6].delay = 200;

	mySong1[7].freq = 36;
	mySong1[7].dur = 100;
	mySong1[7].delay = 100;

	mySong1[8].freq = 37;
	mySong1[8].dur = 100;
	mySong1[8].delay = 80;

	mySong1[9].freq = 36;
	mySong1[9].dur = 100;
	mySong1[9].delay = 80;

	mySong1[10].freq = 37;
	mySong1[10].dur = 100;
	mySong1[10].delay = 80;

	mySong1[11].freq = 48;
	mySong1[11].dur = 100;
	mySong1[11].delay = 80;

	mySong1[12].freq = 57;
	mySong1[12].dur = 100;
	mySong1[12].delay = 300;

	mySong1[13].freq = 57;
	mySong1[13].dur = 200;
	mySong1[13].delay = 100;

	mySong1[13].freq = 85;
	mySong1[13].dur = 200;
	mySong1[13].delay = 100;

	mySong1[14].freq = 72;
	mySong1[14].dur = 100;
	mySong1[14].delay = 100;

	mySong1[15].freq = 64;
	mySong1[15].dur = 100;
	mySong1[15].delay = 100;

	mySong1[16].freq = 57;
	mySong1[16].dur = 100;
	mySong1[16].delay = 500;

	mySong1[17].freq = 57;
	mySong1[17].dur = 200;
	mySong1[17].delay = 100;

	mySong1[18].freq = 85;
	mySong1[18].dur = 200;
	mySong1[18].delay = 100;

	mySong1[19].freq = 72;
	mySong1[19].dur = 100;
	mySong1[19].delay = 100;

	mySong1[20].freq = 64;
	mySong1[20].dur = 100;
	mySong1[20].delay = 100;

	mySong1[21].freq = 76;
	mySong1[21].dur = 100;
	mySong1[21].delay = 500;


	mySong1[22].freq = 85;
	mySong1[22].dur = 100;
	mySong1[22].delay = 80;

	mySong1[23].freq = 72;
	mySong1[23].dur = 100;
	mySong1[23].delay = 80;

	mySong1[24].freq = 43;
	mySong1[24].dur = 200;
	mySong1[24].delay = 250;

	mySong1[25].freq = 85;
	mySong1[25].dur = 100;
	mySong1[25].delay = 80;

	mySong1[26].freq = 72;
	mySong1[26].dur = 100;
	mySong1[26].delay = 80;

	mySong1[27].freq = 43;
	mySong1[27].dur = 200;
	mySong1[27].delay = 250;

	mySong1[28].freq = 37;
	mySong1[28].dur = 200;
	mySong1[28].delay = 200;

	mySong1[29].freq = 36;
	mySong1[29].dur = 100;
	mySong1[29].delay = 100;

	mySong1[30].freq = 37;
	mySong1[30].dur = 100;
	mySong1[30].delay = 80;

	mySong1[31].freq = 36;
	mySong1[31].dur = 100;
	mySong1[31].delay = 80;

	mySong1[32].freq = 37;
	mySong1[32].dur = 100;
	mySong1[32].delay = 80;

	mySong1[33].freq = 48;
	mySong1[33].dur = 100;
	mySong1[33].delay = 80;

	mySong1[34].freq = 57;
	mySong1[34].dur = 100;
	mySong1[34].delay = 300;

	mySong1[35].freq = 57;
	mySong1[35].dur = 200;
	mySong1[35].delay = 100;

	mySong1[36].freq = 85;
	mySong1[36].dur = 200;
	mySong1[36].delay = 100;

	mySong1[37].freq = 72;
	mySong1[37].dur = 100;
	mySong1[37].delay = 100;

	mySong1[38].freq = 64;
	mySong1[38].dur = 100;
	mySong1[38].delay = 100;

	mySong1[39].freq = 57;
	mySong1[39].dur = 300;
	mySong1[39].delay = 100;

	mySong1[40].freq = 57;
	mySong1[40].dur = 200;
	mySong1[40].delay = 100;

	mySong1[41].freq = 85;
	mySong1[41].dur = 300;
	mySong1[41].delay = 2000;
	
	for (int i = 0; i < 41; i++){
		mySong[i].delay = (mySong[i].delay / 2);
	}
	
	ini_lcd();
    //while (1) 
    //{
		int running = 1;
		unsigned int keypressed = 0;
		int stop = 0;
		char line1[32];
		char line2[32];
		char alarmOutput[32];
		char timeOutput[32];
		char inputLine1[32];
		char inputLine2[32];
		struct D date;
		date.day = 28;
		date.mo = 2;
		date.yr = 2016;
		
		struct T time;
		struct T alarm;
		time.sec = 55;
		time.min = 59;
		time.hr = 23;
		alarm.sec = 0;
		alarm.min = 0;
		alarm.hr = 0;
		while(running)
		{
			pos_lcd(0,0);
			
			sprintf(line1, "%02d/%02d/%04d", date.mo, date.day, date.yr);
			puts_lcd2(line1);
			
			
			pos_lcd(1,0);
			sprintf(line2, "%02d:%02d:%02d", time.hr, time.min, time.sec);
			puts_lcd2(line2);
			if(!(keypressed = get_key()))
			{
				if(time.hr == alarm.hr && time.min == alarm.min && stop == 0 )
				{
					
					clr_lcd();
					puts_lcd2(line1);
					pos_lcd(1,0);
					sprintf(line2,"%s", "Wake Up!");
					puts_lcd2(line2);
					int counter = 0;
					int count = 0;
					
					while(counter < 42)
					{
						if(!(keypressed = get_key()))
						{
							
						}
						else
						{
							if(keypressed == 16)
							{
								stop = 1;
							}
							if (keypressed == 15)
							{
								if (count == 0)
								{
									alarm.min++;
									count++;
								}
								
							}
						}

						playNote(mySong1[counter]);
						counter++;
					}
					for (int i = 0; i < 14; i++)
					{
						time.sec++;
						if (time.sec == 60)
						{
							time.sec = 0;
							time.min++;
						}
						if (time.min == 60)
						{
							time.min = 0;
							time.hr++;
						}
						if (time.hr == 24)
						{
							time.hr = 0;
							date.day++;
						}
						if (date.mo == 1 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 2) // if its feb
						{
							if (date.yr % 4 == 0) // if leap year
							{
								if (date.day == 30)
								{
									date.day = 1;
									date.mo++;
								}
							}
							else  // not a leap year
							{
								if (date.day == 29)
								{
									date.day = 1;
									date.mo++;
								}
							}
						}
						else if (date.mo == 3 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 4 && date.day == 31)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 5 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 6 && date.day == 31)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 7 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 8 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 9 && date.day == 31)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 10 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 11 && date.day == 31)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 12 && date.day == 32)
						{
							date.day = 1;
							date.mo = 1;
							date.yr++;
						}
					}
				}
				
				time.sec++;
				if (time.sec == 60)
				{
					time.sec = 0;
					time.min++;
				}
				if (time.min == 60)
				{
					time.min = 0;
					time.hr++;
				}
				if (time.hr == 24)
				{
					time.hr = 0;
					date.day++;
				}
				if (date.mo == 1 && date.day == 32)
				{
					date.day = 1;
					date.mo++;
				}
				else if (date.mo == 2) // if its feb
				{
					if (date.yr % 4 == 0) // if leap year
					{
						if (date.day == 30)
						{
							date.day = 1;
							date.mo++;
						}
					}
					else  // not a leap year
					{
						if (date.day == 29)
						{
							date.day = 1;
							date.mo++;
						}
					}
				}
				else if (date.mo == 3 && date.day == 32)
				{
					date.day = 1;
					date.mo++;
				}
				else if (date.mo == 4 && date.day == 31)
				{
					date.day = 1;
					date.mo++;
				}
				else if (date.mo == 5 && date.day == 32)
				{
					date.day = 1;
					date.mo++;
				}
				else if (date.mo == 6 && date.day == 31)
				{
					date.day = 1;
					date.mo++;
				}
				else if (date.mo == 7 && date.day == 32)
				{
					date.day = 1;
					date.mo++;
				}
				else if (date.mo == 8 && date.day == 32)
				{
					date.day = 1;
					date.mo++;
				}
				else if (date.mo == 9 && date.day == 31)
				{
					date.day = 1;
					date.mo++;
				}
				else if (date.mo == 10 && date.day == 32)
				{
					date.day = 1;
					date.mo++;
				}
				else if (date.mo == 11 && date.day == 31)
				{
					date.day = 1;
					date.mo++;
				}
				else if (date.mo == 12 && date.day == 32)
				{
					date.day = 1;
					date.mo = 1;
					date.yr++;
				}
				
				// Check Alarm
				
			}
			else 
			{
				//If Reset Date
				if(keypressed == 4)
				{
					int count = 0;
					int counts = 0;
					
					pos_lcd(0,0);
					//Start Reset
					while(((keypressed = get_key()) != 8 ) && count < 8)
					{
						
						//Decrease
						if(keypressed == 13)
						{
							count--;
							if(count < 0)
							{
								count = 0;
							}
						}
						//Increase
						if(keypressed == 15)
						{
							count++;
						}
						//Convert Input and Error Check
						if(count == 0 && (keypressed == 1 || keypressed == 14))
						{
							keypressed = convertKeypad(keypressed);
							if(keypressed == 1)
							{
								date.mo = (date.mo % 10) + 10;
								//count++;
								pos_lcd(0,0);
								clr_lcd();
								sprintf(inputLine1, "%02d/%02d/%04d", date.mo, date.day, date.yr);
								puts_lcd2(inputLine1);
								wait_avr(50);
							}
							if(keypressed == 0)
							{
								date.mo %= 10;
								pos_lcd(0,0);
								clr_lcd();
								sprintf(inputLine1, "%02d/%02d/%04d", date.mo, date.day, date.yr);
								puts_lcd2(inputLine1);
								wait_avr(50);
							}
							
						}
						if (count == 1 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
						{
							if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
							{
									keypressed = convertKeypad(keypressed);
									date.mo = ((date.mo / 10) *  10) + keypressed;
									pos_lcd(0,0);
									clr_lcd();
									sprintf(inputLine1, "%02d/%02d/%04d", date.mo, date.day, date.yr);
									puts_lcd2(inputLine1);
									wait_avr(50);
							}
						}
						if (count == 2 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
						{
							keypressed = convertKeypad(keypressed);
							if(keypressed == 1 || keypressed == 2 || keypressed == 3  || keypressed == 0)
							{
									//keypressed = convertKeypad(keypressed);
									date.day = ((date.day % 10) +  (10 * keypressed));
									pos_lcd(0,0);
									clr_lcd();
									//sprintf(line1, "%d%d/%d%d/%d%d%d%d", mon0, mon1, d0, d1, y0, y1, y2, y3);
									sprintf(inputLine1, "%02d/%02d/%04d", date.mo, date.day, date.yr);
									puts_lcd2(inputLine1);
									wait_avr(50);
							}
					
						}
						if (count == 3 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
						{
							//keypressed = convertKeypad(keypressed);
							
								if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
								{
									keypressed = convertKeypad(keypressed);
									date.day = ((date.day / 10) *  10) + keypressed;
									pos_lcd(0,0);
									clr_lcd();
									sprintf(inputLine1, "%02d/%02d/%04d", date.mo, date.day, date.yr);
									puts_lcd2(inputLine1);
									wait_avr(50);
								}
						}
						if (count == 4 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
						{
							//keypressed = convertKeypad(keypressed);
							
							if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
							{
								keypressed = convertKeypad(keypressed);
								date.yr = ((date.yr % 1000) + (keypressed * 1000));
								pos_lcd(0,0);
								clr_lcd();
								//sprintf(line1, "%d%d/%d%d/%d%d%d%d", mon0, mon1, d0, d1, y0, y1, y2, y3);
								sprintf(inputLine1, "%02d/%02d/%04d", date.mo, date.day, date.yr);
								puts_lcd2(inputLine1);
								wait_avr(50);
							}
						}
						if (count == 5 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
						{
							//keypressed = convertKeypad(keypressed);
							
							if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
							{
								keypressed = convertKeypad(keypressed);
								date.yr = (((date.yr / 1000) * 1000) + (date.yr % 100) + (keypressed * 100));
								pos_lcd(0,0);
								clr_lcd();
								//sprintf(line1, "%d%d/%d%d/%d%d%d%d", mon0, mon1, d0, d1, y0, y1, y2, y3);
								sprintf(inputLine1, "%02d/%02d/%04d", date.mo, date.day, date.yr);
								puts_lcd2(inputLine1);
								wait_avr(50);
							}
						}
						if (count == 6 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
						{
							
							
							if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
							{
								keypressed = convertKeypad(keypressed);
								date.yr = (((date.yr / 1000) * 1000) + (((date.yr / 100) % 10) * 100) + (date.yr % 10) + (keypressed * 10));
								pos_lcd(0,0);
								clr_lcd();
								
								sprintf(inputLine1, "%02d/%02d/%04d", date.mo, date.day, date.yr);
								puts_lcd2(inputLine1);
								wait_avr(50);
							}
						}
						if (count == 7 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
						{
							
							
							if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
							{
								keypressed = convertKeypad(keypressed);
								date.yr = (((date.yr / 1000) * 1000) + (((date.yr / 100) % 10) * 100) + (((date.yr / 10) % 10) * 10) + (keypressed));
								pos_lcd(0,0);
								clr_lcd();

								sprintf(inputLine1, "%02d/%02d/%04d", date.mo, date.day, date.yr);
								puts_lcd2(inputLine1);
								wait_avr(50);
							}
						}

						wait_avr(175);
						counts++;
						
					}
					int increment = (counts * 175) / 1000;
					
					for (int i = 0; i < increment; i++)
					{
						time.sec++;
						if (time.sec == 60)
						{
							time.sec = 0;
							time.min++;
						}
						if (time.min == 60)
						{
							time.min = 0;
							time.hr++;
						}
						if (time.hr == 24)
						{
							time.hr = 0;
							date.day++;
						}
						if (date.mo == 1 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 2) // if its feb
						{
							if (date.yr % 4 == 0) // if leap year
							{
								if (date.day == 30)
								{
									date.day = 1;
									date.mo++;
								}
							}
							else  // not a leap year
							{
								if (date.day == 29)
								{
									date.day = 1;
									date.mo++;
								}
							}
						}
						else if (date.mo == 3 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 4 && date.day == 31)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 5 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 6 && date.day == 31)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 7 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 8 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 9 && date.day == 31)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 10 && date.day == 32)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 11 && date.day == 31)
						{
							date.day = 1;
							date.mo++;
						}
						else if (date.mo == 12 && date.day == 32)
						{
							date.day = 1;
							date.mo = 1;
							date.yr++;
						}
					}
					
					clr_lcd();
					if(checkDate(date) == 1)
					{
						
						sprintf(inputLine2, "%s", "Set");
						puts_lcd2(inputLine2);
					}
					else
					{
						sprintf(inputLine2, "%s", "Invalid Date");
						puts_lcd2(inputLine2);
						wait_avr(2000);
						date.day = 0;
						date.mo = 0;
						date.yr = 0;
					}
					
					wait_avr(175);
						
				}
				else
				{
					//Set Time
					if(keypressed == 8)
					{
						int count = 0;
						pos_lcd(1,0);
						int counts = 0;
					
						while(((keypressed = get_key()) != 16 ) && count < 6)
						{
							//pos_lcd(0,count);

							if(keypressed == 13)
							{
								count--;
								if(count < 0)
								{
									count = 0;
								}
							}
							if(keypressed == 15)
							{
								count++;
							}
						
							if (count == 0 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										time.hr = (time.hr % 10) + (keypressed * 10);
										//pos_lcd(1,0);
										clr_lcd();
										pos_lcd(1,0);
										//sprintf(line2, "%d%d:%d%d:%d%d", h0, h1, m0, m1, s0, s1);
										sprintf(timeOutput, "%02d:%02d:%02d", time.hr, time.min, time.sec);
										puts_lcd2(timeOutput);
										wait_avr(50);
								}
								
							}
							if (count == 1 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										time.hr = ((time.hr / 10) * 10) + (keypressed);
										pos_lcd(1,0);
										clr_lcd();
										//sprintf(line1, "%d%d/%d%d/%d%d%d%d", mon0, mon1, d0, d1, y0, y1, y2, y3);
										pos_lcd(1,0);
										//sprintf(line2, "%d%d:%d%d:%d%d", h0, h1, m0, m1, s0, s1);
										sprintf(timeOutput, "%02d:%02d:%02d", time.hr, time.min, time.sec);
										puts_lcd2(timeOutput);
										wait_avr(50);
								}
								
							}
							if (count == 2 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||  keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										time.min = (time.min % 10) + (keypressed * 10);
										//pos_lcd(1,0);
										clr_lcd();
										pos_lcd(1,0);
										//sprintf(line2, "%d%d:%d%d:%d%d", h0, h1, m0, m1, s0, s1);
										sprintf(timeOutput, "%02d:%02d:%02d", time.hr, time.min, time.sec);
										puts_lcd2(timeOutput);
										wait_avr(50);
								}
								
							}
							if (count == 3 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										time.min = ((time.min / 10) * 10) + (keypressed);
										pos_lcd(1,0);
										clr_lcd();
										//sprintf(line1, "%d%d/%d%d/%d%d%d%d", mon0, mon1, d0, d1, y0, y1, y2, y3);
										pos_lcd(1,0);
										//sprintf(line2, "%d%d:%d%d:%d%d", h0, h1, m0, m1, s0, s1);
										sprintf(timeOutput, "%02d:%02d:%02d", time.hr, time.min, time.sec);
										puts_lcd2(timeOutput);
										wait_avr(50);
								}
							
							}
							if (count == 4 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||  keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										time.sec = (time.sec % 10) + (keypressed * 10);
										//pos_lcd(1,0);
										clr_lcd();
										pos_lcd(1,0);
										//sprintf(line2, "%d%d:%d%d:%d%d", h0, h1, m0, m1, s0, s1);
										sprintf(timeOutput, "%02d:%02d:%02d", time.hr, time.min, time.sec);
										puts_lcd2(timeOutput);
										wait_avr(50);
								}
								
							}
							if (count == 5 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										time.sec = ((time.sec / 10) * 10) + (keypressed);
										pos_lcd(1,0);
										clr_lcd();
										pos_lcd(1,0);
										sprintf(timeOutput, "%02d:%02d:%02d", time.hr, time.min, time.sec);
										puts_lcd2(timeOutput);
										wait_avr(50);
								}
							}
						
						
							wait_avr(175);
							counts++;
						
						}
						int increment = (counts * 175) / 1000;
						
						for (int i = 0; i < increment; i++)
						{
							time.sec++;
							if (time.sec == 60)
							{
								time.sec = 0;
								time.min++;
							}
							if (time.min == 60)
							{
								time.min = 0;
								time.hr++;
							}
							if (time.hr == 24)
							{
								time.hr = 0;
								date.day++;
							}
							if (date.mo == 1 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 2) // if its feb
							{
								if (date.yr % 4 == 0) // if leap year
								{
									if (date.day == 30)
									{
										date.day = 1;
										date.mo++;
									}
								}
								else  // not a leap year
								{
									if (date.day == 29)
									{
										date.day = 1;
										date.mo++;
									}
								}
							}
							else if (date.mo == 3 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 4 && date.day == 31)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 5 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 6 && date.day == 31)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 7 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 8 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 9 && date.day == 31)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 10 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 11 && date.day == 31)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 12 && date.day == 32)
							{
								date.day = 1;
								date.mo = 1;
								date.yr++;
							}
						}
					
						clr_lcd();
						if(checkTime(time) == 1)
						{
						
							sprintf(inputLine2, "%s", "Set");
							puts_lcd2(inputLine2);
						}
						else
						{
							sprintf(inputLine2, "%s", "Invalid Time");
							puts_lcd2(inputLine2);
							wait_avr(2000);
							time.hr = 0;
							time.min = 0;
							time.sec = 0;
						}
					
						//running = 0;
						wait_avr(175);
						
					}
					else
					{
						if(keypressed == 12)
						{
							clr_lcd();
							pos_lcd(0,0);
							sprintf(line1, "%s", "Alarm");
							puts_lcd2(line1);
							int count = 0;
							int counts = 0;
							
						pos_lcd(1,0);
						sprintf(alarmOutput, "%02d:%02d:%02d", alarm.hr, alarm.min, alarm.sec);
						puts_lcd2(alarmOutput);
					
						while(((keypressed = get_key()) != 16 ) && count < 6)
						{
							//pos_lcd(0,count);

							if(keypressed == 13)
							{
								count--;
								if(count < 0)
								{
									count = 0;
								}
							}
							if(keypressed == 15)
							{
								count++;
							}
						
							if (count == 0 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										alarm.hr = (alarm.hr % 10) + (keypressed * 10);
										//pos_lcd(1,0);
										clr_lcd();
										pos_lcd(1,0);
										//sprintf(line2, "%d%d:%d%d:%d%d", h0, h1, m0, m1, s0, s1);
										sprintf(alarmOutput, "%02d:%02d:%02d", alarm.hr, alarm.min, alarm.sec);
										puts_lcd2(alarmOutput);
										wait_avr(50);
								}
								
							}
							if (count == 1 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										alarm.hr = ((alarm.hr / 10) * 10) + (keypressed);
										pos_lcd(1,0);
										clr_lcd();
										//sprintf(line1, "%d%d/%d%d/%d%d%d%d", mon0, mon1, d0, d1, y0, y1, y2, y3);
										pos_lcd(1,0);
										//sprintf(line2, "%d%d:%d%d:%d%d", h0, h1, m0, m1, s0, s1);
										sprintf(alarmOutput, "%02d:%02d:%02d", alarm.hr, alarm.min, alarm.sec);
										puts_lcd2(alarmOutput);
										wait_avr(50);
								}
								
							}
							if (count == 2 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||  keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										alarm.min = (alarm.min % 10) + (keypressed * 10);
										//pos_lcd(1,0);
										clr_lcd();
										pos_lcd(1,0);
										//sprintf(line2, "%d%d:%d%d:%d%d", h0, h1, m0, m1, s0, s1);
										sprintf(alarmOutput, "%02d:%02d:%02d", alarm.hr, alarm.min, alarm.sec);
										puts_lcd2(alarmOutput);
										wait_avr(50);
								}
							
							}
							if (count == 3 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										alarm.min = ((alarm.min / 10) * 10) + (keypressed);
										pos_lcd(1,0);
										clr_lcd();
										//sprintf(line1, "%d%d/%d%d/%d%d%d%d", mon0, mon1, d0, d1, y0, y1, y2, y3);
										pos_lcd(1,0);
										//sprintf(line2, "%d%d:%d%d:%d%d", h0, h1, m0, m1, s0, s1);
										sprintf(alarmOutput, "%02d:%02d:%02d", alarm.hr, alarm.min, alarm.sec);
										puts_lcd2(alarmOutput);
										wait_avr(50);
								}
								
							}
							if (count == 4 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||  keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										alarm.sec = (alarm.sec % 10) + (keypressed * 10);
										//pos_lcd(1,0);
										clr_lcd();
										pos_lcd(1,0);
										//sprintf(line2, "%d%d:%d%d:%d%d", h0, h1, m0, m1, s0, s1);
										sprintf(alarmOutput, "%02d:%02d:%02d", alarm.hr, alarm.min, alarm.sec);
										puts_lcd2(alarmOutput);
										wait_avr(50);
								}
							
							}
							if (count == 5 && (keypressed % 4 != 0) && (keypressed != 13) && keypressed != 15 && (keypressed !=0))
							{
								//keypressed = convertKeypad(keypressed);
								if(keypressed == 1 || keypressed == 2 || keypressed == 3 || keypressed == 5 || keypressed == 6 ||keypressed == 7 || keypressed == 9 || keypressed == 10 || keypressed == 11 || keypressed == 14)
								{
										keypressed = convertKeypad(keypressed);
										alarm.sec = ((alarm.sec / 10) * 10) + (keypressed);
										pos_lcd(1,0);
										clr_lcd();
										pos_lcd(1,0);
										sprintf(alarmOutput, "%02d:%02d:%02d", alarm.hr, alarm.min, alarm.sec);
										puts_lcd2(alarmOutput);
										wait_avr(50);
								}
							}
						
						
							wait_avr(175);
							counts++;
						}
						int increment = (counts * 175) / 1000;
						
						for (int i = 0; i < increment; i++)
						{
							time.sec++;
							if (time.sec == 60)
							{
								time.sec = 0;
								time.min++;
							}
							if (time.min == 60)
							{
								time.min = 0;
								time.hr++;
							}
							if (time.hr == 24)
							{
								time.hr = 0;
								date.day++;
							}
							if (date.mo == 1 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 2) // if its feb
							{
								if (date.yr % 4 == 0) // if leap year
								{
									if (date.day == 30)
									{
										date.day = 1;
										date.mo++;
									}
								}
								else  // not a leap year
								{
									if (date.day == 29)
									{
										date.day = 1;
										date.mo++;
									}
								}
							}
							else if (date.mo == 3 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 4 && date.day == 31)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 5 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 6 && date.day == 31)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 7 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 8 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 9 && date.day == 31)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 10 && date.day == 32)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 11 && date.day == 31)
							{
								date.day = 1;
								date.mo++;
							}
							else if (date.mo == 12 && date.day == 32)
							{
								date.day = 1;
								date.mo = 1;
								date.yr++;
							}
						}
					
						clr_lcd();
						if(checkTime(alarm) == 1)
						{
						
							sprintf(inputLine2, "%s", "Set");
							puts_lcd2(inputLine2);
						}
						else
						{
							sprintf(inputLine2, "%s", "Invalid Time");
							puts_lcd2(inputLine2);
							wait_avr(2000);
							alarm.hr = 0;
							alarm.min = 0;
							alarm.sec = 0;
						}
					
						//running = 0;
						wait_avr(175);
						}
						
						
							
						
						
						
					}
					
					
				}
				
				
				
			}					
			wait_avr(1000);
			clr_lcd();
	}
}

/*
#include "avr.h"
unsigned int speed = 1;
unsigned int convertKeypad(unsigned int input)
{
	unsigned int output = input;
	if(input == 5 || input == 6 || input == 7)
	{
		output = input - 1;
	}
	else if(input == 9 ||input == 10 || input == 11)
	{
		output = input - 2;
	}
	else if(input == 14)
	{
		output = 0;
	}
	
	
	return output;
	
}

unsigned char pressed(unsigned char r, unsigned char c)
{
	DDRC = 0;
	PORTC = 0;
	SET_BIT(DDRC, c + 4);
	SET_BIT(PORTC, r);
	CLR_BIT(PORTC, c + 4);
	//CLR_BIT(PORTC, r << 4);
	
	wait_avr2(1);
	
	if(!(GET_BIT(PINC, r)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned char get_key()
{
	unsigned char r;
	unsigned char c;
	//char inputLine[32];
	//PORTC = 0x0b00001111;
	//SET_BIT(PORTC, 4);
	//SET_BIT(PORTC, 5);
	//SET_BIT(PORTC, 6);
	//SET_BIT(PORTC, 7);
	
	for(r = 0; r < 4; ++r)
	{
		for(c = 0; c < 4; ++c)
		{
			
			if (pressed(r, c))
			{
				
				return (r * 4) + (c + 1);
			}
		}
	}
	return 0;
}


struct note
{
	unsigned int freq;
	unsigned int dur;
	unsigned int delay;
};


struct note mySong[41];
struct note mySong1[42];


						
void playNote(struct note theNote)
{
	for(unsigned long i = 0; i < theNote.dur; i++)
	{
		SET_BIT(PORTB, 3);
		wait_avr2(theNote.freq);
		CLR_BIT(PORTB, 3);
		wait_avr2(theNote.freq);
	}
	wait_avr((theNote.delay / speed));
}
 
 int main (void)
 {
	 //map<unsigned int, unsigned int> song;
	 //song
	SET_BIT(DDRB, 3);
	
	mySong[0].freq = 76;
	mySong[0].dur = 100;
	mySong[0].delay = 150;
	
	mySong[1].freq = 76;
	mySong[1].dur = 100;
	mySong[1].delay = 300;
	
	mySong[2].freq = 76;
	mySong[2].dur = 100;
	mySong[2].delay = 300;
	
	mySong[3].freq = 95;
	mySong[3].dur = 100;
	mySong[3].delay = 100;
	
	mySong[4].freq = 76;
	mySong[4].dur = 100;
	mySong[4].delay = 300;
	
	mySong[5].freq = 63;
	mySong[5].dur = 100;
	mySong[5].delay = 550;
		
	mySong[6].freq = 131;
	mySong[6].dur = 100;
	mySong[6].delay = 575;
			
	mySong[7].freq = 98;
	mySong[7].dur = 100;
	mySong[7].delay = 450;

	mySong[8].freq = 131;
	mySong[8].dur = 100;
	mySong[8].delay = 400;

	mySong[9].freq = 156;
	mySong[9].dur = 100;
	mySong[9].delay = 500;

	mySong[10].freq = 113;
	mySong[10].dur = 100;
	mySong[10].delay = 300;

	mySong[11].freq = 104;
	mySong[11].dur = 80;
	mySong[11].delay = 330;

	mySong[12].freq = 111;
	mySong[12].dur = 100;
	mySong[12].delay = 150;

	mySong[13].freq = 116;
	mySong[13].dur = 100;
	mySong[13].delay = 300;

	mySong[14].freq = 131;
	mySong[14].dur = 100;
	mySong[14].delay = 200;

	mySong[15].freq = 76;
	mySong[15].dur = 80;
	mySong[15].delay = 200;

	mySong[16].freq = 66;
	mySong[16].dur = 50;
	mySong[16].delay = 150;

	mySong[17].freq = 58;
	mySong[17].dur = 100;
	mySong[17].delay = 300;

	mySong[18].freq = 71;
	mySong[18].dur = 80;
	mySong[18].delay = 150;

	mySong[19].freq = 66;
	mySong[19].dur = 50;
	mySong[19].delay = 350;

	mySong[20].freq = 76;
	mySong[20].dur = 80;
	mySong[20].delay = 300;

	mySong[21].freq = 96;
	mySong[21].dur = 80;
	mySong[21].delay = 150;

	mySong[22].freq = 86;
	mySong[22].dur = 80;
	mySong[22].delay = 150;

	mySong[23].freq = 104;
	mySong[23].dur = 80;
	mySong[23].delay = 500;
	
	mySong[24].freq = 98;
	mySong[24].dur = 100;
	mySong[24].delay = 450;

	mySong[25].freq = 131;
	mySong[25].dur = 100;
	mySong[25].delay = 400;

	mySong[26].freq = 156;
	mySong[26].dur = 100;
	mySong[26].delay = 500;

	mySong[27].freq = 113;
	mySong[27].dur = 100;
	mySong[27].delay = 300;

	mySong[28].freq = 104;
	mySong[28].dur = 80;
	mySong[28].delay = 330;

	mySong[29].freq = 111;
	mySong[29].dur = 100;
	mySong[29].delay = 150;

	mySong[30].freq = 116;
	mySong[30].dur = 100;
	mySong[30].delay = 300;

	mySong[31].freq = 131;
	mySong[31].dur = 100;
	mySong[31].delay = 200;

	mySong[32].freq = 76;
	mySong[32].dur = 80;
	mySong[32].delay = 200;

	mySong[33].freq = 66;
	mySong[33].dur = 50;
	mySong[33].delay = 150;

	mySong[34].freq = 58;
	mySong[34].dur = 100;
	mySong[34].delay = 300;

	mySong[35].freq = 71;
	mySong[35].dur = 80;
	mySong[35].delay = 150;

	mySong[36].freq = 66;
	mySong[36].dur = 50;
	mySong[36].delay = 350;

	mySong[37].freq = 76;
	mySong[37].dur = 80;
	mySong[37].delay = 300;

	mySong[38].freq = 96;
	mySong[38].dur = 80;
	mySong[38].delay = 150;

	mySong[39].freq = 86;
	mySong[39].dur = 80;
	mySong[39].delay = 150;

	mySong[40].freq = 104;
	mySong[40].dur = 80;
	mySong[40].delay = 500;
	
	mySong1[0].freq = 85;
	mySong1[0].dur = 100;
	mySong1[0].delay = 80;

	mySong1[1].freq = 72;
	mySong1[1].dur = 100;
	mySong1[1].delay = 80;

	mySong1[2].freq = 43;
	mySong1[2].dur = 200;
	mySong1[2].delay = 250;

	mySong1[3].freq = 85;
	mySong1[3].dur = 100;
	mySong1[3].delay = 80;

	mySong1[4].freq = 72;
	mySong1[4].dur = 100;
	mySong1[4].delay = 80;

	mySong1[5].freq = 43;
	mySong1[5].dur = 200;
	mySong1[5].delay = 250;

	mySong1[6].freq = 37;
	mySong1[6].dur = 200;
	mySong1[6].delay = 200;

	mySong1[7].freq = 36;
	mySong1[7].dur = 100;
	mySong1[7].delay = 100;

	mySong1[8].freq = 37;
	mySong1[8].dur = 100;
	mySong1[8].delay = 80;

	mySong1[9].freq = 36;
	mySong1[9].dur = 100;
	mySong1[9].delay = 80;

	mySong1[10].freq = 37;
	mySong1[10].dur = 100;
	mySong1[10].delay = 80;

	mySong1[11].freq = 48;
	mySong1[11].dur = 100;
	mySong1[11].delay = 80;

	mySong1[12].freq = 57;
	mySong1[12].dur = 100;
	mySong1[12].delay = 300;

	mySong1[13].freq = 57;
	mySong1[13].dur = 200;
	mySong1[13].delay = 100;

	mySong1[13].freq = 85;
	mySong1[13].dur = 200;
	mySong1[13].delay = 100;

	mySong1[14].freq = 72;
	mySong1[14].dur = 100;
	mySong1[14].delay = 100;

	mySong1[15].freq = 64;
	mySong1[15].dur = 100;
	mySong1[15].delay = 100;

	mySong1[16].freq = 57;
	mySong1[16].dur = 100;
	mySong1[16].delay = 500;

	mySong1[17].freq = 57;
	mySong1[17].dur = 200;
	mySong1[17].delay = 100;

	mySong1[18].freq = 85;
	mySong1[18].dur = 200;
	mySong1[18].delay = 100;

	mySong1[19].freq = 72;
	mySong1[19].dur = 100;
	mySong1[19].delay = 100;

	mySong1[20].freq = 64;
	mySong1[20].dur = 100;
	mySong1[20].delay = 100;

	mySong1[21].freq = 76;
	mySong1[21].dur = 100;
	mySong1[21].delay = 500;


	mySong1[22].freq = 85;
	mySong1[22].dur = 100;
	mySong1[22].delay = 80;

	mySong1[23].freq = 72;
	mySong1[23].dur = 100;
	mySong1[23].delay = 80;

	mySong1[24].freq = 43;
	mySong1[24].dur = 200;
	mySong1[24].delay = 250;

	mySong1[25].freq = 85;
	mySong1[25].dur = 100;
	mySong1[25].delay = 80;

	mySong1[26].freq = 72;
	mySong1[26].dur = 100;
	mySong1[26].delay = 80;

	mySong1[27].freq = 43;
	mySong1[27].dur = 200;
	mySong1[27].delay = 250;

	mySong1[28].freq = 37;
	mySong1[28].dur = 200;
	mySong1[28].delay = 200;

	mySong1[29].freq = 36;
	mySong1[29].dur = 100;
	mySong1[29].delay = 100;

	mySong1[30].freq = 37;
	mySong1[30].dur = 100;
	mySong1[30].delay = 80;

	mySong1[31].freq = 36;
	mySong1[31].dur = 100;
	mySong1[31].delay = 80;

	mySong1[32].freq = 37;
	mySong1[32].dur = 100;
	mySong1[32].delay = 80;

	mySong1[33].freq = 48;
	mySong1[33].dur = 100;
	mySong1[33].delay = 80;

	mySong1[34].freq = 57;
	mySong1[34].dur = 100;
	mySong1[34].delay = 300;

	mySong1[35].freq = 57;
	mySong1[35].dur = 200;
	mySong1[35].delay = 100;

	mySong1[36].freq = 85;
	mySong1[36].dur = 200;
	mySong1[36].delay = 100;

	mySong1[37].freq = 72;
	mySong1[37].dur = 100;
	mySong1[37].delay = 100;

	mySong1[38].freq = 64;
	mySong1[38].dur = 100;
	mySong1[38].delay = 100;

	mySong1[39].freq = 57;
	mySong1[39].dur = 300;
	mySong1[39].delay = 100;

	mySong1[40].freq = 57;
	mySong1[40].dur = 200;
	mySong1[40].delay = 100;

	mySong1[41].freq = 85;
	mySong1[41].dur = 300;
	mySong1[41].delay = 2000;
	
	for (int i = 0; i < 41; i++){
		mySong[i].delay = (mySong[i].delay / 2);
	}
	
	ini_lcd();
	int running = 1;
	unsigned int keypressed = 0;
	char line1[32];
	char line2[32];
	pos_lcd(0,0);
	clr_lcd();
	sprintf(line1, "%d: %s" ,1, "Super Mario Theme");
	puts_lcd2(line1);
	pos_lcd(1,0);
	sprintf(line2, "%d: %s" , 2, "Zelda - Song of Storms");
	puts_lcd2(line2);
	
	while(running)
	{
		if(!(keypressed = get_key()))
		{
				
		}
		else
		{
			if(convertKeypad(keypressed) == 1)
			{
				
				for(int i = 0; i < 41; i++)
				{
					playNote(mySong[i]);
				}
			}
			else if(convertKeypad(keypressed) == 2)
			{
				for(int i = 0; i < 42; i++)
				{
					playNote(mySong1[i]);
				}
			}
			else if(convertKeypad(keypressed) == 7)
			{
				speed--;
				if(speed < 1)
				{
					speed = 1;
				}
			}
			else if(convertKeypad(keypressed) == 8)
			{
				speed++;
				if(speed > 4)
				{
					speed = 4;
				}
				
			}
			
			
		}
	}
				
	 
	 return 0;
 }

*/