/*	
    Display
	File: Display.c
	Author: Helton H. Pontes
	Date: August 2020
*/

#include "defines.h"
#include "visor_comp.h"
#include <stdio.h>
#include <stdbool.h>

void Display_SendNibble(char data){//Sends a nibble to the display
   
	DISPLAY_RW = 0; //Sets to write mode
	DISPLAY_D4 = !!(dado & 1); //puts data bits on data pin
	DISPLAY_D5 = !!(dado & 2); //puts data bits on data pin
	DISPLAY_D6 = !!(dado & 4); //puts data bits on data pin
	DISPLAY_D7 = !!(dado & 8); //puts data bits on data pin

    DISPLAY_ENABLE = 1;
	__delay_us(1);
	DISPLAY_ENABLE = 0;
	
}

void Display_SendByte(bool type, char data){
	
	DISPLAY_RW = 0; //Sets to write mode
	DISPLAY_RS = type;//Sets data/instruction mode
	
	__delay_us(40);
	
	DISPLAY_ENABLE = 0; 
	
	Display_SendNibble(dado >> 4);//Sends Most Significant Nibble
	Display_SendNibble(dado & 0x0f);//Sends Least Significant Nibble
}


void Display_Init(void)
{
   unsigned char i; //byte conta;
   
   DISPLAY_RW = 0; //Sets to write mode
   
   DISPLAY_D4 = 0; //Puts 0 on data pin
   DISPLAY_D5 = 0; //Puts 0 on data pin
   DISPLAY_D6 = 0; //Puts 0 on data pin
   DISPLAY_D7 = 0; //Puts 0 on data pin
   
   DISPLAY_RS = 0; //Sets to instruction mode
   
   DISPLAY_ENABLE = 0; 
   
   __delay_ms(50);
   
   for(i=1;i<=3;++i){
      Display_SendNibble(3);
      __delay_ms(50);
   }
   
   Display_SendNibble(2);
   
   for(i=0;i<=3;++i){
      Display_SendByte(0,INI_LCD[i]);
   }
   __delay_ms(10);
}

void Display_SetPosition(unsigned char column, unsigned char line) {
	
	unsigned char address = 0;
   
	if(line==1) address = 0;
	else if(line==2) address = lcd_seg_lin;
   
	address += column-1; //calc address
   
	Display_SendByte(0,0x80|address);
	
}

void Display_SetLine(unsigned char line){
	
	if(line==1) Display_SetPosition(1,1);
	else if(line==2) Display_SetPosition(1,2);
	
}

void Display_TurnOnCursor(unsigned char cursor){
   
   Display_SendByte(0,cursor);
   __delay_ms(50);
}

void Display_TurnOffCursor(void){
	
   Display_SendByte(0,12);
   __delay_ms(50);
   
}

void Display_ClearLine(unsigned char line){
   
   Display_SetLine(lin);
   printf("                    ");
   
}

void Display_ClearAll(void){
  
	Display_ClearLine(1);
	Display_ClearLine(2);
	
}

void Display_TurnOn(void){
	
   Display_SendByte(0,12);
   __delay_ms(50);
   
}

void liga_back_light(void){
   DISPLAY_BACKLIGHT = 1;
}
void desliga_back_light(void){
   DISPLAY_BACKLIGHT = 0;
}

unsigned char Display_ReadByte(void){ //Read a Byte from Display
   
	unsigned char data = 0;
   
	DISPLAY_RS = 1;//Sets data mode
	DISPLAY_ENABLE = 1;
   
	//Sets data pins as input
	TRISFbits.TRISF2 = 1;
	TRISFbits.TRISF3 = 1;
	TRISFbits.TRISF4 = 1;
	TRISFbits.TRISF6 = 1;

	DISPLAY_RW = 1; //Sets to read mode
   
	DISPLAY_ENABLE = 1;//Display Enable
   
	__delay_us(50);
   

	// Reads 4 most significant bits
	if(DISPLAY_D7) data |= 0x80;//if (input(lcd_d7)) bit_set(dado,7);
	if(DISPLAY_D6) data |= 0x40;//if (input(lcd_d6)) bit_set(dado,6);
	if(DISPLAY_D5) data |= 0x20;//if (input(lcd_d5)) bit_set(dado,5);
	if(DISPLAY_D4) data |= 0x10;//if (input(lcd_d4)) bit_set(dado,4);
   
	//Pulse enable pin
	DISPLAY_ENABLE = 0;
	__delay_us(1);
	DISPLAY_ENABLE = 1;
	__delay_us(50);
   
	// Reads 4 least significant bits
	if(DISPLAY_D7) dado |= 0x08;//if (input(lcd_d7)) bit_set(dado,3);
	if(DISPLAY_D6) dado |= 0x04;//if (input(lcd_d6)) bit_set(dado,2);
	if(DISPLAY_D5) dado |= 0x02;//if (input(lcd_d5)) bit_set(dado,1);
	if(DISPLAY_D4) dado |= 0x01;//if (input(lcd_d4)) bit_set(dado,0);
	
	DISPLAY_ENABLE = 0;
   
	//Sets data pins as input
	TRISFbits.TRISF2 = 0;
    TRISFbits.TRISF3 = 0;
    TRISFbits.TRISF4 = 0;
    TRISFbits.TRISF6 = 0;
   
	return data;   // retorna o byte lido
}


void putch(char p){
	
	switch (p){
		case '\f':   
			Display_SendByte(0,1);
			__delay_ms(50);
			break;
		case '\n':
		case '\r':   
			Display_SetPosition(1,2);
			break;
		case '\b':
			Display_SendByte(0,0x10);
			break;
		case '°':
			Display_SendByte(1,0xDF);
			break;
		default:   
			Display_SendByte(1,p);
		break;
	}
}
