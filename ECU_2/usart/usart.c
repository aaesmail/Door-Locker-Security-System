/******************************************************************************
 * Module: USART
 *
 * File Name: usart.c
 *
 * Description: Source File for Atmega16/32 USART Driver
 *
 * Created on: Sep 24, 2019
 *
 * Author: Ali Adel
******************************************************************************/

/* Including its header file */
#include "usart.h"

/*****************************************************************************
 * 								Definitions									 *
*****************************************************************************/
/* Equation used to calculate value put in register to get desired BaudRate */
#define BAUD_PRESCALE (((F_CPU) / ((USART_BAUDRATE) * (8UL))) - (1UL))

/*****************************************************************************
 * 								Functions Definitions						 *
*****************************************************************************/
void USART_init(const USART_Config* config)
{
	/* Double Transmisson Speed */
	UCSRA = (1 << U2X);

	/* Enable Receiver and Transmitter Modes */
	UCSRB = (1 << RXEN) | (1 << TXEN);

	/* Choosing Data Bits Size */
	if (config->data == BITS_5)
	{
		/* Just leave bits as Zero */
		UCSRC = (1 << URSEL);
	}
	else if (config->data == BITS_6)
	{
		/* Insert 1 in UCSZ0 */
		UCSRC = (1 << URSEL) | (1 << UCSZ0);
	}
	else if (config->data == BITS_7)
	{
		/* Insert 1 in UCSZ1 */
		UCSRC = (1 << URSEL) | (1 << UCSZ1);
	}
	else if (config->data == BITS_8)
	{
		/* Choose UCSZ0 & UCSZ1 */
		UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	}

	/* Choosing Parity Mode */
	if (config->parity == EVEN)
	{
		/* Enable Even Parity */
		UCSRC |= (1 << URSEL) | (1 << UPM1);
	}
	else if (config->parity == ODD)
	{
		/* Enable Odd Parity */
		UCSRC |= (1 << URSEL) | (1 << UPM1) | (1 << UPM0);
	}

	/* Choosing Number of Stop Bits */
	if (config->stop == BIT_2)
	{
		/* Enable 2 Stop Bits */
		UCSRC |= (1 << URSEL) | (1 << USBS);
	}

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = BAUD_PRESCALE >> 8;
	UBRRL = BAUD_PRESCALE;
}

void USART_sendByte(const uint8 data)
{
	/* If there is a previous send operation keep polling till it's done first */
	while (BIT_IS_CLEAR(UCSRA, UDRE));

	/* Put Required data into UDR it also clears UDRE flag as it's not empty now */
	UDR = data;
}

uint8 USART_receiveByte(void)
{
	/* Wait till RXC flag is set which means received new data */
	while (BIT_IS_CLEAR(UCSRA, RXC));

	/*
	 * Read Received data and RXC flag will be cleared automatically when this register
	 * is read
	 */
	return UDR;
}

bool USART_getParityFlag(void)
{
	/* Return status of Parity flag of byte to be read next */
	if (BIT_IS_SET(UCSRA, PE))
	{
		/* If flag is set (Error occured in last transfer) */
		return TRUE;
	}
	else
	{
		/* If Operation went successful then return false */
		return FALSE;
	}
}

void USART_sendString(const uint8* str)
{
	/* Loop until before NULL character */
	while ((*str) != '\0')
	{
		/* Send Character By Character */
		USART_sendByte(*str);
		/* Increment Pointer to get Next Character */
		++str;
	}
}

void USART_receiveString(uint8* str)
{
	/* Receive first character first to start loop */
	(*str) = USART_receiveByte();

	/* Loop Until a terminating character ex.'#' */
	while ((*str) != '#')
	{
		/* Increment to Next Place in array */
		++str;

		/* Put Data in Array */
		(*str) = USART_receiveByte();
	}

	/*
	 * Put a NULL character instead of used terminating character
	 * to make it a normal C String
	*/
	(*str) = '\0';
}

void USART_deInit(void)
{
	/* Turn off bit for double speed */
	CLEAR_BIT(UCSRA, U2X);

	/* Disable Enables */
	CLEAR_BIT(UCSRB, RXEN);
	CLEAR_BIT(UCSRB, TXEN);

	/* Clear UCRSEC Register */
	UCSRC = (1 << URSEL);

	/* Clear BAUD_PRESCALE */
	UBRRH = 0;
	UBRRL = 0;
}
