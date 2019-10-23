/***********************************************************************************
 * Module: Timer 1 Normal & CTC
 *
 * File Name: timer1.h
 *
 * Description: Source file for Atmega16/32 Timer1 Driver (Normal & CTC)
 *
 * Created on: Sep 30, 2019
 *
 * Author: Ali Adel
***********************************************************************************/

/* Including its header file */
#include "timer1.h"

/* Global Variable for storing address of call back function */
static void (*volatile g_normalCallBack)(void) = NULL;
static void (*volatile g_channelACallBack)(void) = NULL;
static void (*volatile g_channelBCallBack)(void) = NULL;

/********************************************************************
 * 								ISRs								*
********************************************************************/
ISR(TIMER1_OVF_vect)
{
	/* Check if user did indicate a function for call back */
	if (g_normalCallBack != NULL)
	{
		/* Call users call back function */
		(*g_normalCallBack)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	/* Check if user did indicate a function for call back */
	if (g_channelACallBack != NULL)
	{
		/* Call users call back function */
		(*g_channelACallBack)();
	}
}

ISR(TIMER1_COMPB_vect)
{
	/* Check if user did indicate a function for call back */
	if (g_channelBCallBack != NULL)
	{
		/* Call users call back function */
		(*g_channelBCallBack)();
	}
}

/********************************************************************
 * 						Functions Prototypes						*
********************************************************************/
void TIMER1_init(const TIMER1_Config* config)
{
	/* Put initial value */
	TCNT1 = config->INITIAL_VALUE;

	if (config->MODE == NORMAL)
	{
		/* Select Normal Mode, these bits specify a non pwm mode */
		TCCR1A = (1 << FOC1A) | (1 << FOC1B);

		/* Clear this register for normal mode */
		TCCR1B = 0;

		/* Activate normal mode interrupt */
		SET_BIT(TIMSK, TOIE1);
	}
	else
	{
		/* Insert OCR1A & OCR1B Modes into register && FOC1X are always high when specify a non-pwm */
		TCCR1A = (((uint8)((config->CHANNELA).TIMER1_CHANNEL_OCR1)) << 6) |
				 (((uint8)((config->CHANNELB).TIMER1_CHANNEL_OCR1)) << 4) |
				 (1 << FOC1A) | (1 << FOC1B);

		/* If OCR1A is not disconnected make it output pin */
		if ((config->CHANNELA).TIMER1_CHANNEL_OCR1 != DISCONNECTED)
		{
			SET_BIT(DDRD, PD5);
		}
		/* If OCR1B is not disconnected make it output pin */
		if ((config->CHANNELB).TIMER1_CHANNEL_OCR1 != DISCONNECTED)
		{
			SET_BIT(DDRD, PD4);
		}

		/* Choose CTC Mode where top is in OCR1 Register */
		TCCR1B = (1 << WGM12);

		/* Insert compare value into OCR1 */
		OCR1A = (config->CHANNELA).COMPARE_VALUE;
		OCR1B = (config->CHANNELB).COMPARE_VALUE;

		/* Activate interrupt for channel A if ON */
		if ((config->CHANNELA).TIMER1_INTERRUPT == ON)
		{
			SET_BIT(TIMSK, OCIE1A);
		}

		/* Activate interrupt for channel B if ON */
		if ((config->CHANNELB).TIMER1_INTERRUPT == ON)
		{
			SET_BIT(TIMSK, OCIE1B);
		}
	}

	/* Insert clock settings to start timer */
	TCCR1B |= (config->PRESCALAR);
}

void TIMER1_setCallBackNormal(void(*callBack)(void))
{
	g_normalCallBack = callBack;
}

void TIMER1_setCallBackChannelA(void(*callBack)(void))
{
	g_channelACallBack = callBack;
}

void TIMER1_setCallBackChannelB(void(*callBack)(void))
{
	g_channelBCallBack = callBack;
}

void TIMER1_stop(void)
{
	/* Stop Timer by disabling clock */
	TCCR1B &= 0xF8;
}

void TIMER1_restart(TIMER1_PRESCALAR clk)
{
	/* Make sure clock bits are off */
	TCCR1B &= 0xF8;

	/* Insert clk user wants */
	TCCR1B |= clk;
}

void TIMER1_deInit(void)
{
	/* Just clear all registers & disable clock */
	TCCR1A = 0;
	/* to keep values of ICU */
	TCCR1B &= 0xC0;
	TCNT1 = 0;
	OCR1A = 0;
	OCR1B = 0;

	/* Disable all interrupts */
	CLEAR_BIT(TIMSK, OCIE1A);
	CLEAR_BIT(TIMSK, OCIE1B);
	CLEAR_BIT(TIMSK, TOIE1);

	/* Set pointers to their default values */
	g_normalCallBack = NULL;
	g_channelACallBack = NULL;
	g_channelBCallBack = NULL;
}
