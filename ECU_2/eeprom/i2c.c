/***************************************************************************
 * Module: I2C (TWI)
 *
 * File Name: i2c.c
 *
 * Description: Source File for I2C (TWI) AVR Driver
 *
 * Created on: Sep 28, 2019
 *
 * Author: Ali Adel
***************************************************************************/

/* Including its header file */
#include "i2c.h"

void TWI_init(const TWI_Config* config)
{
	/* Set Bit Rate Register */
	TWBR = config->BIT_RATE;

	/* Enter prescalar values */
	TWSR = config->PRESCALAR;

	/* Insert Slave address and set general recognition */
	TWAR = ((config->SLAVE_ADDRESS) << 1) | (config->GENERAL_CALL);

	/* Enable I2C */
	TWCR = (1 << TWEN);
}

void TWI_start(void)
{
	/*
	 * Clear Interrupt Flag (TWINT) before sending start bit (Cleared by writing 1)
	 * Send start bit (TWSTA = 1)
	 * Enable device
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait till start bit is sent successfully */
	while (BIT_IS_CLEAR(TWCR, TWINT));
}

void TWI_stop(void)
{
	/*
	 * Clear Interrupt Flag (TWINT) before sending stop bit (Cleared by writing 1)
	 * Sent Stop bit (TWSTO = 1)
	 * Enable device
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8 data)
{
	/* Put data in register */
	TWDR = data;

	/*
	 * Clear Interrupt Flag (TWINT) before writing data (Cleared by writing 1)
	 * Enable device
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);

	/* Wait till data is sent successfully */
	while (BIT_IS_CLEAR(TWCR, TWINT));
}

uint8 TWI_readWithACK(void)
{
	/*
	 * Clear Interrupt Flag (TWINT) before reading data (Cleared by writing 1)
	 * Enable ACK bit to send ACK on reading
	 * Enable device
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

	/* Wait till data is received */
	while (BIT_IS_CLEAR(TWCR, TWINT));

	/* Read and return data */
	return TWDR;
}

uint8 TWI_readWithNACK(void)
{
	/*
	 * Clear Interrupt Flag (TWINT) before reading data (Cleared by writing 1)
	 * Disable ACK bit to send NACK on reading
	 * Enable device
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);

	/* Wait till data is received */
	while (BIT_IS_CLEAR(TWCR, TWINT));

	/* Read and return data */
	return TWDR;
}

uint8 TWI_getStatus(void)
{
	/* Mask first 3 bits and return status which is left 5 bits (Doesn't need shifting) */
	return (TWSR & (0xF8));
}

void TWI_deInit(void)
{
	/* Clear registers and turn off enable */
	TWBR = 0;
	TWCR = 0;
	TWSR = 0;
	TWAR = 0;
}
