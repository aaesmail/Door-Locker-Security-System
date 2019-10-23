/******************************************************************************
 * Module: Keypad
 *
 * File Name: keypad.h
 *
 * Description: Header File for Keypad (Definitions & Functions Prototypes)
 *
 * Created on: Sep 15, 2019
 *
 * Author: Ali Adel
******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

/******************************************************************************
 * 							Including Files									  *
******************************************************************************/
/* File for standard types */
#include "../general_files/std_types.h"

/* Macros used in module */
#include "../general_files/common_macros.h"

/* Microcontroller specific libraries */
#include "../general_files/micro_config.h"

/******************************************************************************
 * 								Definitions									  *
******************************************************************************/
/* Columns x Rows in used Keypad */

/* Number of Columns in Keypad (Change this to 3(4x3) or 4(4x4) */
#define COLS 4

/* Number of Rows in Keypad	*/
#define ROWS 4

/* Keypad Ports Used	(Uses One Full 8-Bits Port) */

/* Port of Output Pins */
#define KEYPAD_PORT_OUT PORTA

/* Port of Input Pins */
#define KEYPAD_PORT_IN PINA

/* Port Direction */
#define KEYPAD_PORT_DIR DDRA


/* Value first used in port to make only one output */
#define INITIAL_VALUE (0b00010000)

/******************************************************************************
 * 							Functions Prototypes							  *
******************************************************************************/

/***********************************************************************************
 * Function Name: Keypad_getPressedKey
 *
 * Description: Waits for a button to be pressed on Keypad and captures it
 *
 * Args:
 * 		[Void]: Takes No Arguments
 *
 * Return: Returns value of key pressed, if a number is pressed returns its value,
 * 		   if a symbol returns its ASCII Code
***********************************************************************************/
uint8 Keypad_getPressedKey(void);

#endif /* KEYPAD_H_ */
