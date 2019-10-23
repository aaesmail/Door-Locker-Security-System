/***************************************************************************
 * Module: ECU_1 in project
 *
 * File Name: ECU_1_main.c
 *
 * Description: Main file for ECU_1
 *
 * Created on: Oct 3, 2019
 *
 * Author: Ali Adel
***************************************************************************/

#include "timer1/timer1.h"
#include "keypad/keypad.h"
#include "lcd/lcd.h"
#include "usart/usart.h"
#include "prototypes.h"
#include "../ECU_2/definitions.h"

int main(void)
{
	/* Initialize All Drivers */
	Drivers_Init();

	/* Communicate with ECU_2 to set new Password */
	Receive_New_Password();

	/* Variable to hold key press */
	uint8 keyPressed;

	while(1)
	{
		/* Get key press on main screen */
		keyPressed = Keypad_getPressedKey();

		/* Tell Micro 2 that a button was pressed */
		USART_sendByte(ENTER);

		if (keyPressed == '+')
		{
			Open_Door();
		}
		else if (keyPressed == '-')
		{
			Change_Password();
		}

		/* Delay to wait till nextKey Press */
		_delay_ms(DISPLAY_DELAY);
	}

	return 0;
}

void Drivers_Init(void)
{
	/* Enable Global Interrupts */
	SET_BIT(SREG, 7);
	LCD_init();
	USART_Config config = {BITS_8, DISABLED, BIT_1};
	USART_init(&config);
}

void Receive_New_Password(void)
{
	while (1)	/* Keep looping till get correct password */
	{

		/* Make sure screen is cleared first */
		LCD_clearScreen();

		/* Tell user to enter password */
		LCD_displayString("Please Enter New");
		LCD_goToRowColumn(1, 0);
		LCD_integerToString(PASSWORD_SIZE);
		LCD_displayString("-Digits");
		LCD_goToRowColumn(2, 0);
		LCD_displayString("Password:");
		LCD_goToRowColumn(3, 0);

		/* Variables being used */
		uint8 keyPress = 0;

		/* First get first part */
		while (keyPress != ENTER)
		{
			/* Ask user for new password */
			keyPress = Keypad_getPressedKey();
			/* Display '*' on LCD except if it is an enter */
			if (keyPress != ENTER)
			{
				LCD_displayCharacter('*');
			}
			/* Delay to not repeat button presses */
			_delay_ms(DISPLAY_DELAY);

			/* Send Key Press to ECU_2 */
			USART_sendByte(keyPress);
		}

		/* Tell Micro 2 that part 1 is done and ignore any presses beyond 5 digits */
		USART_sendByte(FIRST_PART_OVER);

		/* Make sure screen is cleared first */
		LCD_clearScreen();

		/* Tell user to enter password */
		LCD_displayString("Please re-enter");
		LCD_goToRowColumn(1, 0);
		LCD_displayString("Same Password:");
		LCD_goToRowColumn(2, 0);

		/* Reset keyPress to enter loop */
		keyPress = 0;
		/* then get second part of pass */
		while (keyPress != ENTER)
		{
			/* Ask user for new password */
			keyPress = Keypad_getPressedKey();
			/* Display '*' on LCD except if it is an enter */
			if (keyPress != ENTER)
			{
				LCD_displayCharacter('*');
			}
			/* Delay to not repeat button presses */
			_delay_ms(DISPLAY_DELAY);

			/* Send Key Press to ECU_2 */
			USART_sendByte(keyPress);
		}

		/* Tell Micro 2 that part 2 is done and ignore any presses beyond 5 digits */
		USART_sendByte(SECOND_PART_OVER);

		/* Wait for Micro 2 to confirm passwords */
		if (USART_receiveByte() == MATCHED)	/* If passwords match then end function */
		{
			/* Clean Screen before going out */
			LCD_clearScreen();
			/* Display Success Message before exit */
			LCD_displayString("Password Set");
			LCD_goToRowColumn(1, 0);
			LCD_displayString("Successfully!");
			_delay_ms(DISPLAY_DELAY_LONG);
			LCD_clearScreen();
			break;
		}

		/* Else start over again */
	}

	/* Display Main Screen */
	Display_Main_Screen();
}

void Display_Main_Screen(void)
{
	/* Clear LCD in case something is written */
	LCD_clearScreen();

	/* Write First Option */
	LCD_displayString(" + : Open Door");

	/* Go to Third Line */
	LCD_goToRowColumn(2, 0);

	/* Write Second Option */
	LCD_displayString(" - : Change");

	/* Go to Fourth Line */
	LCD_goToRowColumn(3, 5);

	/* Write Rest of Second Option */
	LCD_displayString("Password");
}

void Open_Door(void)
{
	/* First check to see if password matches */
	if (!Check_Password())
	{
		/* If it doesn't match then go to lock down */
		Lock_Down();
		return;
	}

	/* Tell Micro 2 to open Door */
	USART_sendByte(OPEN_DOOR);

	/* Display Door is unlocking on LCD */
	LCD_clearScreen();
	LCD_displayString("    Door is");
	LCD_goToRowColumn(2, 3);
	LCD_displayString("Unlocking!");

	/* Wait till door is Unlocked */
	USART_receiveByte();
	LCD_clearScreen();
	LCD_displayString("      Door");
	LCD_goToRowColumn(2, 0);
	LCD_displayString("    Unlocked!");

	/* Wait till door starts closing */
	USART_receiveByte();
	LCD_clearScreen();
	LCD_displayString("    Door is");
	LCD_goToRowColumn(2, 0);
	LCD_displayString("    Locking!");

	/* Wait till Door is locked */
	USART_receiveByte();
	LCD_clearScreen();
	/* Tell user door is locked */
	LCD_goToRowColumn(1, 0);
	LCD_displayString("  Door Locked!");

	/* Let user see it for half second */
	_delay_ms(1000);
	/* Display Main Screen Again */
	Display_Main_Screen();
}

void Change_Password(void)
{
	/* First check to see if password matches */
	if (!Check_Password())
	{
		/* If it doesn't match then go to lock down */
		Lock_Down();
		return;
	}

	/* Tell Micro 2 to change password */
	USART_sendByte(CHANGE_PASSWORD);
	/* Delay to wait for micro 2 and negate any keyPressed before receving */
	_delay_ms(500);
	/* Start change password operation */
	Receive_New_Password();
}

bool Check_Password(void)
{
	while (1)
	{
		/* Tell user to enter password */
		LCD_clearScreen();
		LCD_displayString("Enter Password:");
		LCD_goToRowColumn(1, 0);

		/* Delay to wait for pressed key to be released */
		_delay_ms(DISPLAY_DELAY);

		/* Variable to hold key presses */
		uint8 keyPress = 0;
		/* Loop till user presses enter */
		while (keyPress != ENTER)
		{
			/* Wait for user to enter */
			keyPress = Keypad_getPressedKey();
			if (keyPress != ENTER)
			{
				/* If keypressed wasn't enter then display * */
				LCD_displayCharacter('*');
			}
			/* Send Micro 2 what was pressed */
			USART_sendByte(keyPress);
			/* Delay to not get several presses on same button */
			_delay_ms(DISPLAY_DELAY);
		}

		/* Wait for status check from Micro 2 */
		uint8 status = USART_receiveByte();

		/* If user entered valid data and correct password */
		if (status == PASSWORD_CORRECT)
		{
			return TRUE;
		}
		/* If Micro 2 decides it's lockdown time */
		else if (status == INITIATE_LOCKDOWN)
		{
			break;
		}

		/* Tell user wrong password and try again */
		LCD_clearScreen();
		LCD_displayString("Wrong Password!");
		_delay_ms(DISPLAY_DELAY);
	}
	/* return false to start lock down and display that to user */
	LCD_clearScreen();
	LCD_displayString("   Initiating");
	LCD_goToRowColumn(2, 3);
	LCD_displayString("Lock Down!");
	_delay_ms(DISPLAY_DELAY_LONG);
	return FALSE;
}

void Lock_Down(void)
{
	/* Display on screen wrong password and lock down system */
	LCD_clearScreen();
	LCD_displayString(" System Locked!");

	/* Tell Micro 2 that i'm ready */
	USART_sendByte(ENTER);

	/* Time left till lock down is over */
	uint8 time = LOCK_DOWN_PERIOD;

	while (time != 0)
	{
		/* Get time from Micro 2 and display it */
		time = USART_receiveByte();
		LCD_goToRowColumn(2, 7);
		LCD_integerToString(time);
		LCD_displayString("   ");
	}

	/* Display 0 for 1 second */
	_delay_ms(DISPLAY_DELAY_LONG);
	/* Go Back to main Screen */
	Display_Main_Screen();
}
