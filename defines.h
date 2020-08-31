/*	
	File: defines.h
	Author: Helton H. Pontes
	Date: August 2020
*/

#ifndef DEFINES_H
#define DEFINES_H

#define _XTAL_FREQ 10000000 //40000000 //8000000

	#include <stdio.h>
	#include <stdbool.h>

	//defines for pins
	#define DISPLAY_ENABLE     RF0//Enable pin -> Chip Select pin -> 1 Enable, 0 Disable
	#define DISPLAY_RS         RF1//RS Pin -> 0 for data, 1 for Instruction
	#define DISPLAY_RW         RE7//Read/Write Pin -> 1 for Read, 0 for Write
	#define DISPLAY_D4         RF2//Data pin
	#define DISPLAY_D5         RF3//Data pin
	#define DISPLAY_D6         RF4//Data pin
	#define DISPLAY_D7         RF6//Data pin  
	#define H_DISPLAY      RF7//Back light control pin

#endif