/*************************************************************************
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: LCD Driver Header File (Functions Prototypes)
 *
 * Created on: Sep 15, 2019
 *
 * Author: Ali Adel
*************************************************************************/

#ifndef LCD_H_
#define LCD_H_

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
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 8

/* Use higher 4 bits in port Undefine if want to use Lower Pins in Port
 * To Redefine it, Add the Following:
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif
*/
#if (DATA_BITS_MODE == 4)
	#define UPPER_PORT_PINS
#endif

						/* LCD HW Pins */

/* RS Pin: Register Select (Selects Command or Data Register) */
#define RS PB0

/* RW Pin: Read or Write Pin */
#define RW PB1

/* E Pin: Enable */
#define E PB2

/* Control Pins Port */
#define LCD_CTRL_PORT PORTB

/* Control Pins Port Direction */
#define LCD_CTRL_PORT_DIR DDRB

/* Data Pins Port */
#define LCD_DATA_PORT PORTC

/* Data Pins Port Direction */
#define LCD_DATA_PORT_DIR DDRC

/* to make the delays in commands with Milli-Seconds, else
 *  it's gonna delay using Micro-Seconds
 *  Define MS for Milli-Seconds, Add following line:
 *  #define MS
 *  Remove it for Micro-Seconds
 *  */
#define MS

/* Delay Used in LCD Commands */
#define LCD_DELAY 1

			/* Start Addresses of Lines on LCD Screen */

/* First Line Start Address */
#define FIRST_LINE_ADDRESS 0

/* Second Line Start Address */
#define SECOND_LINE_ADDRESS 0x40

/* Third Line Start Address */
#define THIRD_LINE_ADDRESS 0x10

/* Fourth Line Start Address */
#define FOURTH_LINE_ADDRESS 0x50

				/* LCD Commands */
#define CLEAR_COMMAND (0x01)
#define FOUR_BITS_DATA_MODE (0x02)
#define TWO_LINE_LCD_FOUR_BIT_MODE (0x28)
#define TWO_LINE_LCD_EIGHT_BIT_MODE (0x38)
#define CURSOR_OFF (0x0C)
#define CURSOR_ON (0x0E)
#define SET_CURSOR_LOCATION (0x80)

/****************************************************************************************
 * 								Functions Prototypes					   			    *
****************************************************************************************/

/***********************************************************************************
 * Function Name: LCD_init
 *
 * Description:	Sets the LCD up to be ready
 *
 * Args:
 *		[void]: Takes no Arguments
 *
 * Return:	[void] doesn't return anything
***********************************************************************************/
void LCD_init(void);

/***********************************************************************************
 * Function Name: LCD_sendCommand
 *
 * Description: Sends Command to LCD to execute
 *
 * Args:
 * 		[in]:	uint8 command:
 * 						The command Code that the LCD will execute
 *
 * Return: [void] doesn't return anything
***********************************************************************************/
void LCD_sendCommand(uint8 command);

/***********************************************************************************
 * Function Name: LCD_displayCharacter
 *
 * Description: Sends Character to LCD to display on screen
 *
 * Args:
 *		[in]:	uint8 data:
 *						The ASCII for the character to display on LCD screen
 *
 * Return:  [void] doesn't return anything
***********************************************************************************/
void LCD_displayCharacter(uint8 data);

/***********************************************************************************
 * Function Name: LCD_displayString
 *
 * Description: Sends string to LCD to display on screen at once
 *
 * Args:
 *		[in]:	const char* str:
 *						pointer to first character in string to display
 *
 * Return:  [void] doesn't return anything
***********************************************************************************/
void LCD_displayString(const char* str);

/***********************************************************************************
 * Function Name: LCD_goToRowColumn
 *
 * Description: Makes Cursor go to row and column sent
 *
 * Args:
 *		[in]:	uint8 row:
 *						Row which the cursor will go to
 *
 *		[in]:	uint8 col:
 *						Column which the cursor will go to
 *
 * Return:  [void] doesn't return anything
***********************************************************************************/
void LCD_goToRowColumn(uint8 row, uint8 col);

/***********************************************************************************
 * Function Name: LCD_clearScreen
 *
 * Description: Clears LCD screen and sets cursor to beginning
 *
 * Args:
 *		[void]: Takes no Arguments
 *
 * Return:  [void] doesn't return anything
***********************************************************************************/
void LCD_clearScreen(void);

/***********************************************************************************
 * Function Name: LCD_displayStringRowColumn
 *
 * Description: Displays string on LCD screen on location sent by row & column
 *
 * Args:
 *		[in]:	uint8 row:
 *						Row which the cursor will go to and display string
 *
 *		[in]:	uint8 col:
 *						Column which the cursor will go to and display string
 *
 *		[in]:	const char* str:
 *						pointer to first character in string to display
 *
 * Return:  [void] doesn't return anything
***********************************************************************************/
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char* str);

/***********************************************************************************
 * Function Name: LCD_integerToString
 *
 * Description: Sends Number to LCD to display on screen at once
 *
 * Args:
 *		[in]:	int data:
 *						Number which the LCD will Display
 *
 * Return:  [void] doesn't return anything
***********************************************************************************/
void LCD_integerToString(int data);

#endif /* LCD_H_ */
