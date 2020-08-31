/*	
    Display
	File: Display.h
	Author: Helton H. Pontes
	Date: August 2020
*/

#ifndef DISPLAY_H
#define DISPLAY_H

//includes
#include "Display.h"
#include "defines.h"
#include <stdio.h>
#include <stdbool.h>

//Defines
#define lcd_type 2 //Type of LCD, 2 = Two Lines Display
#define lcd_seg_lin   0x40 // Second line address

unsigned char const INI_LCD[4] = {0x20 | (lcd_type << 2), 0xf, 1, 6};

void Display_SendNibble(char data);
void Display_SendByte(bool type, char data);
unsigned char Display_ReadByte(void);
void Display_Init(void);
void Display_SetPosition(unsigned char column, unsigned char line);
void Display_SetLine(unsigned char line);
void Display_TurnOnCursor(unsigned char cursor);
void Display_TurnOffCursor(void);
void Display_ClearLine(unsigned char line);
void Display_ClearAll(void);
void Display_TurnOn(void);
void Display_TurnOnBackLight(void);
void Display_TurnOffBackLight(void);

void putch(char p); //required for use with printf function

#endif