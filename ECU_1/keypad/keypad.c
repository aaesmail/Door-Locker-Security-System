/******************************************************************************
 * Module: Keypad
 *
 * File Name: keypad.c
 *
 * Description: Source File for Keypad (Functions Definitions)
 *
 * Created on: Sep 15, 2019
 *
 * Author: Ali Adel
******************************************************************************/

/* Including its header file */
#include "keypad.h"

/******************************************************************************
 * 						Private Functions Prototypes						  *
******************************************************************************/

#if (COLS == 3)
/***********************************************************************************
 * Function Name: Keypad_4x3_adjustKeyNumber
 *
 * Description: Edits the number captured by keypad in case of 4x3 (Columns = 3)
 *
 * Args:
 * 		[in]: uint8 button:
 * 					The value of button captured by keypad
 *
 * Return: Returns value if number is pressed or ASCII if symbol is pressed
***********************************************************************************/
static uint8 Keypad_4x3_adjustKeyNumber(uint8 button);
#elif (COLS == 4)
/***********************************************************************************
 * Function Name: Keypad_4x4_adjustKeyNumber
 *
 * Description: Edits the number captured by keypad in case of 4x4 (Columns = 4)
 *
 * Args:
 * 		[in]: uint8 button:
 * 					The value of button captured by keypad
 *
 * Return: Returns value if number is pressed or ASCII if symbol is pressed
***********************************************************************************/
static uint8 Keypad_4x4_adjustKeyNumber(uint8 button);
#endif

/******************************************************************************
 * 							Functions Definitions						  	  *
******************************************************************************/
uint8 Keypad_getPressedKey(void)
{
	uint8 col, row;	/* columns and rows used in looping on keys */
	while (1)	/* Keep looping until a button is pressed */
	{
		for (col = 0; col < COLS; ++col)	/* Loop on Columns first */
		{
			/* Each time only one pin will be output and all rest are input */
			KEYPAD_PORT_DIR = (INITIAL_VALUE << col);

			/* Output 0 on reading Column and 1's on all others to activate internal Pull-Up */
			KEYPAD_PORT_OUT = (~(INITIAL_VALUE << col));

			for (row = 0; row < ROWS; ++row)	/*Loop on all Rows in this Column */
			{
				/* If button is pressed its value is zero is Macro returns true */
				if (BIT_IS_CLEAR(KEYPAD_PORT_IN, row))
				{
					/*
					 * Equation used: (row * TotalColumns) + column + 1
					 * This equation gets the value of key pressed numbered from 1
					 * till the max value
					 */
					#if (COLS == 3)
						return Keypad_4x3_adjustKeyNumber((row * COLS) + col + 1);
					#elif (COLS == 4)
						return Keypad_4x4_adjustKeyNumber((row * COLS) + col + 1);
					#endif
				}
			}
		}
	}
}

#if (COLS == 3)

static uint8 Keypad_4x3_adjustKeyNumber(uint8 button)
{
	/* Switch on the button to get correct reading */
	switch (button)
	{
		case 10:
			return '*';		/* Return ASCII Code of '*' */
			break;
		case 11:
			return 0;		/* Return 0 if Zero key is pressed */
			break;
		case 12:
			return '#';		/* Return ASCII Code of '#' */
			break;
		default:
			return button;	/* Other Buttons positions are correct */
			break;
	}
}

#elif (COLS == 4)

static uint8 Keypad_4x4_adjustKeyNumber(uint8 button)
{
	/* Switch on the button to get correct reading */
	switch (button)
	{
		case 1:
			return 7;	/* Location of 7 on Keypad */
			break;

		case 2:
			return 8;	/* Location of 8 on Keypad */
			break;

		case 3:
			return 9;	/* Location of 9 on Keypad */
			break;

		case 4:
			return '%';	/* Return ASCII Code of '%' */
			break;

		case 5:
			return 4;	/* Location of 4 on Keypad */
			break;

		case 6:
			return 5;	/* Location of 5 on Keypad */
			break;

		case 7:
			return 6;	/* Location of 6 on Keypad */
			break;

		case 8:
			return '*';	/* Return ASCII Code of '*' */
			break;

		case 9:
			return 1;	/* Location of 1 on Keypad */
			break;

		case 10:
			return 2;	/* Location of 2 on Keypad */
			break;

		case 11:
			return 3;	/* Location of 3 on Keypad */
			break;

		case 12:
			return '-';	/* Return ASCII Code of '-' */
			break;

		case 13:
			return 13;	/* Return ASCII Code of 'Enter' */
			break;

		case 14:
			return 0;	/* Location of 0 on Keypad */
			break;

		case 15:
			return '=';	/* Return ASCII Code of '=' */
			break;

		case 16:
			return '+';	/* Return ASCII Code of '+' */
			break;

		default:
			return button; /* Shouldn't happen, Irregular behavior return just the number */
			break;
	}
}

#endif
