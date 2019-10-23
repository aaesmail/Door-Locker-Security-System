/***************************************************************************
 * Module: ECU_2 in project
 *
 * File Name: ECU_2_main.c
 *
 * Description: Main file for ECU_2
 *
 * Created on: Oct 3, 2019
 *
 * Author: Ali Adel
***************************************************************************/

#include "dcmotor/dcmotor.h"
#include "eeprom/eeprom.h"
#include "timer1/timer1.h"
#include "usart/usart.h"
#include "prototypes2.h"
#include "definitions.h"

int main(void)
{
	/* First initialize Drivers */
	Drivers_Init();

	/* Read password to initialize system */
	Receive_New_Password();

	while(1)
	{
		/* Wait for Micro 1 to say that button has been pressed */
		USART_receiveByte();
		/* First see if user entered correct password */
		if (Check_Password())
		{
			/* Password entered correctly then check which action to take */
			if (USART_receiveByte() == OPEN_DOOR)
			{
				/* Call function to open door operation */
				Open_Door();
			}
			else
			{
				/* User wants to change password */
				Receive_New_Password();
			}
		}
		else
		{
			/* Activate buzzer and lock system */
			Lock_Down();
		}
	}

	return 0;
}

void Drivers_Init(void)
{
	/* Enable Global Interrupts */
	SET_BIT(SREG, 7);
	DCMOTOR_init();
	EEPROM_init();
	USART_Config config = {BITS_8, DISABLED, BIT_1};
	USART_init(&config);
	/* Make Buzzer Pin output & make sure it's off */
	SET_BIT(DDRD, PD7);
	CLEAR_BIT(PORTD, PD7);
}

void Receive_New_Password(void)
{
	/* Variable to store password */
	uint8 firstTry[PASSWORD_SIZE] = {0};
	while (1)	/* Keep looping till get correct password */
	{
		/* Check if passwords match */
		uint8 status = MATCHED;

		/* Counter for operations */
		uint8 i = 0;
		/* Get first part */
		for (i = 0; i < PASSWORD_SIZE; ++i)
		{
			firstTry[i] = USART_receiveByte();
			/* If user entered enter early */
			if (firstTry[i] == ENTER)
			{
				break;
			}
		}

		/* Transmission was exactly 5 digits so get enter */
		if (i == PASSWORD_SIZE)
		{
			USART_receiveByte();
		}

		/* If after PASSWORD_SIZE digits not ended then bad password */
		if (USART_receiveByte() != FIRST_PART_OVER)
		{
			status = NOT_MATCHED;

			/* Wait till over */
			while (USART_receiveByte() != FIRST_PART_OVER);
		}

		/* Then user didn't enter full 5 digits */
		if (i < PASSWORD_SIZE)
		{
			status = NOT_MATCHED;
		}

		uint8 secondTry[PASSWORD_SIZE] = {0};
		/* Get second part */
		for (i = 0; i < PASSWORD_SIZE; ++i)
		{
			secondTry[i] = USART_receiveByte();

			/* User ended early */
			if (secondTry[i] == ENTER)
			{
				break;
			}
		}

		/* If transmission was exactly 5 digits then get rid of enter */
		if (i == PASSWORD_SIZE)
		{
			USART_receiveByte();
		}

		/* If after 5 digits not ended then bad password */
		if (USART_receiveByte() != SECOND_PART_OVER)
		{
			status = NOT_MATCHED;

			/* Wait till over */
			while (USART_receiveByte() != SECOND_PART_OVER);
		}

		/* Then user didn't enter full 5 digits */
		if (i < PASSWORD_SIZE)
		{
			status = NOT_MATCHED;
		}


		if (status == MATCHED)	/* If user entered both parts as 5-digits then check */
		{
			/* Check if passwords match */
			for (i = 0; i < PASSWORD_SIZE; ++i)
			{
				if (firstTry[i] != secondTry[i])
				{
					status = NOT_MATCHED;
					break;
				}
			}
		}

		/* Send result to Micro 1 */
		USART_sendByte(status);

		if (status == MATCHED)	/* If passwords matched then break out of loop */
		{
			break;
		}
	}

	/* Store Password in EEPROM */
	for (uint8 i = 0; i < PASSWORD_SIZE; ++i)
	{
		EEPROM_writeByte(PASSWORD_LOCATION + i, firstTry[i]);
		/* Delay for EEPROM to write */
		_delay_ms(10);
	}
}

void Activate_Buzzer(void)
{
	SET_BIT(PORTD, PD7);
}

void Stop_Buzzer(void)
{
	CLEAR_BIT(PORTD, PD7);
}

void Switch_Buzzer(void)
{
	TOGGLE_BIT(PORTD, PD7);
}

bool Check_Password(void)
{
	/* Loop for max checks */
	for (uint8 tryTimes = 0; tryTimes < MAX_PASSWORD_CHECKS; ++tryTimes)
	{
		uint8 entry[PASSWORD_SIZE] = {0};
		/* Loop to take password from Micro 1 */
		uint8 counter;
		for (counter = 0; counter < PASSWORD_SIZE; ++counter)
		{
			/* Receive button press from Micro 1 */
			entry[counter] = USART_receiveByte();

			/* If user entered enter then break out */
			if(entry[counter] == ENTER)
			{
				break;
			}
		}

		/* then user entered password exactly 5 digits and next digit is enter */
		if ((counter == PASSWORD_SIZE) && (USART_receiveByte() == ENTER))
		{
			bool goodPass = TRUE;
			/* Check if correct password */
			for (uint8 i = 0; i < PASSWORD_SIZE; ++i)
			{
				uint8 digit;
				/* Read corresponding digit from EEPROM */
				EEPROM_readByte(PASSWORD_LOCATION + i, &digit);
				/* If not matched then set bool to false and break of loop */
				if (digit != entry[i])
				{
					goodPass = FALSE;
					break;
				}
			}

			/* If Passwords match then continue normal operation */
			if (goodPass)
			{
				/* Tell Micro 1 that password was correct */
				USART_sendByte(PASSWORD_CORRECT);
				return TRUE;
			}
		}

		/* If user entered more than 5 digits then keep ignoring till enter */
		if (counter > PASSWORD_SIZE)
		{
			while (USART_receiveByte() != ENTER);
		}

		/* Password was wrong or wrong conditions then tell Micro 1 to ask for password again
		 * and not last loop */
		if (tryTimes != (MAX_PASSWORD_CHECKS - 1))
		{
			USART_sendByte(PASSWORD_AGAIN);
		}
	}

	/* If not entered correctly for max times then return false and tell Micro 1 to intiate lock down */
	USART_sendByte(INITIATE_LOCKDOWN);
	return FALSE;
}

void Open_Door(void)
{
	/* Set timer to counter 1 second */
	TIMER1_Config config = {CTC, CPU_256, 0, {ON, DISCONNECTED, 31250}, {OFF, DISCONNECTED, 0}};
	TIMER1_setCallBackChannelA(Open_Door_Interrupt);
	DCMOTOR_rotateCW();
	TIMER1_init(&config);
}

void Open_Door_Interrupt(void)
{
	/* Counter to know how many times function was called */
	static uint8 counter = 0;

	/* Increment counter each call */
	++counter;

	if (counter == DOOR_OPEN_TIME)
	{
		/* After first second stop motor */
		DCMOTOR_stop();
		/* Tell Micro 1 that first second is over */
		USART_sendByte(OPEN_DOOR);
	}
	else if (counter == (2 * DOOR_OPEN_TIME))
	{
		/* Make it rotate CCW for another 1 second */
		DCMOTOR_rotateCCW();
		/* Tell Micro 1 that second second is over */
		USART_sendByte(OPEN_DOOR);
	}
	else if (counter == (3 * DOOR_OPEN_TIME))
	{
		/* Stop timer operation */
		TIMER1_deInit();
		/* Stop motor */
		DCMOTOR_stop();

		/* Tell Micro 1 that second second is over */
		USART_sendByte(OPEN_DOOR);

		/* zero the counter for next time */
		counter = 0;
	}
}

void Lock_Down(void)
{
	/* Wait for micro 1 to be ready */
	USART_receiveByte();

	TIMER1_Config config = {CTC, CPU_256, 0, {ON, DISCONNECTED, 31250}, {OFF, DISCONNECTED, 0}};
	TIMER1_setCallBackChannelA(Lock_Down_Interrupt);
	TIMER1_init(&config);
}

void Lock_Down_Interrupt(void)
{
	/* Counter for time */
	static uint8 time = LOCK_DOWN_PERIOD;

	/* Send time to Micro 1 */
	USART_sendByte(time);

	/* Activate buzzer and close it ratio of 3:1 */
	if (time % BUZZER_PERIOD)
	{
		Activate_Buzzer();
	}
	else
	{
		Stop_Buzzer();
	}

	/* check if time is 0 */
	if (time == 0)
	{
		/* Time for lock down is over */
		/* Stop timer */
		TIMER1_deInit();
		/* Reinitialize time */
		time = LOCK_DOWN_PERIOD;
		/* Turn off Buzzer */
		Stop_Buzzer();
	}
	else
	{
		/* Decrement time */
		--time;
	}
}
