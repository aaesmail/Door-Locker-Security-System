/*************************************************************************
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: LCD Driver Source File (Functions Definitions)
 *
 * Created on: Sep 15, 2019
 *
 * Author: Ali Adel
*************************************************************************/

/* Including its header file */
#include "lcd.h"

/******************************************************************************
 * 							Functions Definitions						  	  *
******************************************************************************/

void LCD_init(void)
{
	/* Set Control Port Direction as output to Control LCD */
	SET_BIT(LCD_CTRL_PORT_DIR, E);
	SET_BIT(LCD_CTRL_PORT_DIR, RS);
	SET_BIT(LCD_CTRL_PORT_DIR, RW);

	#if (DATA_BITS_MODE == 4)	/* 4-bits data mode defined */
		#ifdef UPPER_PORT_PINS	/* Using higher pins from 8-bits port */
			LCD_DATA_PORT_DIR |= 0xF0;	/* Set the 4 higher pins as output */
		#else							/* Using lower pins from 8-bits port */
			LCD_DATA_PORT_DIR |= 0x0F;	/* Set the 4 lower pins as output */
		#endif
		LCD_sendCommand(FOUR_BITS_DATA_MODE);	/* Start using 4 bits data mode */
		LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);	/* Initialize two lines lcd 4-bits */
	#elif (DATA_BITS_MODE == 8)		/* 8-bits data mode defined */
		LCD_DATA_PORT_DIR = 0xFF;	/* Set the 8-bits register as output */
		LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE);	/* Initialize 2 lines 8-bits mode */
	#endif

	LCD_sendCommand(CURSOR_OFF);	/* Turn off Cursor */
	LCD_sendCommand(CLEAR_COMMAND);	/* Clear LCD at begining */
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT, RS);	/* Instructions Mode RS = 0 */
	CLEAR_BIT(LCD_CTRL_PORT, RW);	/* Write data so write mode RW = 0 */

	#ifdef MS	/* Delay for Processing Tas = 50ns */
		_delay_ms(LCD_DELAY);
	#else
		_delay_us(LCD_DELAY);
	#endif

	SET_BIT(LCD_CTRL_PORT, E);	/* Set LCD Enable = 1 */

	#ifdef MS	/* Delay for Processing Tpw - Tdws = 190ns */
		_delay_ms(LCD_DELAY);
	#else
		_delay_us(LCD_DELAY);
	#endif

	#if (DATA_BITS_MODE == 4)

		#ifdef UPPER_PORT_PINS	/* Output the Most Significant 4-Bits of Command */
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
		#endif

		#ifdef MS	/* Delay for Processing Tdsw = 100ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

		CLEAR_BIT(LCD_CTRL_PORT, E);	/* Disable LCD Enable = 0 */

		#ifdef MS	/* Delay for Processing Th = 13ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

		SET_BIT(LCD_CTRL_PORT, E);		/* Set LCD Enable = 1 */

		#ifdef MS	/* Delay for Processing Tpw - Tdws = 190ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

		#ifdef UPPER_PORT_PINS	/* Output the Least Significant 4-Bits of Command */
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
		#endif

		#ifdef MS	/* Delay for Processing Tdsw = 100ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

		CLEAR_BIT(LCD_CTRL_PORT, E);	/* Disable LCD Enable = 0 */

		#ifdef MS	/* Delay for Processing Th = 13ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

	#elif (DATA_BITS_MODE == 8)

		LCD_DATA_PORT = command;	/* Output whole command to 8-Bits Port */

		#ifdef MS	/* Delay for Processing Tdsw = 100ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

		CLEAR_BIT(LCD_CTRL_PORT, E);	/* Disable LCD Enable = 0 */

		#ifdef MS	/* Delay for Processing Th = 13ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

	#endif
}

void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT, RS);	/* Data Mode RS = 1 */
	CLEAR_BIT(LCD_CTRL_PORT, RW);	/* Write data so write mode RW = 0 */

	#ifdef MS	/* Delay for Processing Tas = 50ns */
		_delay_ms(LCD_DELAY);
	#else
		_delay_us(LCD_DELAY);
	#endif

	SET_BIT(LCD_CTRL_PORT, E);	/* Set LCD Enable = 1 */

	#ifdef MS	/* Delay for Processing Tpw - Tdws = 190ns */
		_delay_ms(LCD_DELAY);
	#else
		_delay_us(LCD_DELAY);
	#endif

	#if (DATA_BITS_MODE == 4)

		#ifdef UPPER_PORT_PINS	/* Output the Most Significant 4-Bits of Data */
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
		#endif

		#ifdef MS	/* Delay for Processing Tdsw = 100ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

		CLEAR_BIT(LCD_CTRL_PORT, E);	/* Disable LCD Enable = 0 */

		#ifdef MS	/* Delay for Processing Th = 13ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

		SET_BIT(LCD_CTRL_PORT, E);		/* Set LCD Enable = 1 */

		#ifdef MS	/* Delay for Processing Tpw - Tdws = 190ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

		#ifdef UPPER_PORT_PINS	/* Output the Least Significant 4-Bits of Data */
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
		#endif

		#ifdef MS	/* Delay for Processing Tdsw = 100ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

		CLEAR_BIT(LCD_CTRL_PORT, E);	/* Disable LCD Enable = 0 */

		#ifdef MS	/* Delay for Processing Th = 13ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

	#elif (DATA_BITS_MODE == 8)

		LCD_DATA_PORT = data;	/* Output whole Data to 8-Bits Port */

		#ifdef MS	/* Delay for Processing Tdsw = 100ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

		CLEAR_BIT(LCD_CTRL_PORT, E);	/* Disable LCD Enable = 0 */

		#ifdef MS	/* Delay for Processing Th = 13ns */
			_delay_ms(LCD_DELAY);
		#else
			_delay_us(LCD_DELAY);
		#endif

	#endif
}

void LCD_displayString(const char* str)
{
	/* Loop on string till Null Character */
	while ((*str) != '\0')
	{
		LCD_displayCharacter(*str);	/* Send Character by Character to Display Character */
		++str;						/* Increment pointer to next Character for Display */
	}
}

void LCD_goToRowColumn(uint8 row, uint8 col)
{
	uint8 Address;	/* Variable to calculate command for cursor location change */

	switch (row)	/* First Calculate Required Address */
	{
		case 0:
			/* Address on first line is first Line Start Address + Column */
			Address = col + FIRST_LINE_ADDRESS;
			break;
		case 1:
			/* Address on second line is Second Line Start Address + Column */
			Address = col + SECOND_LINE_ADDRESS;
			break;
		case 2:
			/* Address on third line is third Line Start Address + Column */
			Address = col + THIRD_LINE_ADDRESS;
			break;
		case 3:
			/* Address on fourth line is fourth Line Start Address + Column */
			Address = col + FOURTH_LINE_ADDRESS;
			break;
		default:
			/* In Case of Invalid Row just print on First row */
			Address = col;
			break;
	}
	/* To Write to specific Address send the next command: (0x80 + Address) */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_clearScreen(void)
{
	/* Send the Clear Screen Command and it automatically returns to home Position */
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_displayStringRowColumn(uint8 row, uint8 col, const char* str)
{
	/* First Go to required Position */
	LCD_goToRowColumn(row, col);
	/* Start Displaying the String */
	LCD_displayString(str);
}

void LCD_integerToString(int data)
{
	/* String to hold ASCII Code of Digits */
	char buff[16];
	/* Function to convert Digits to string & put 10 for decimal based result */
	itoa(data, buff, 10);
	/* Send String for Display */
	LCD_displayString(buff);
}
