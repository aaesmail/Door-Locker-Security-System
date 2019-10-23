/***************************************************************************
 * Module: EEPROM
 *
 * File Name: eeprom.c
 *
 * Description: Source File for External EEPROM device
 *
 * Created on: Sep 28, 2019
 *
 * Author: Ali Adel
***************************************************************************/

/* Uses I2C in Operation so include driver */
#include "i2c.h"
/* Including its Header File */
#include "eeprom.h"

void EEPROM_init(void)
{
	/* Just initialize I2C Driver (F_CPU is 8MHZ) */
	TWI_Config config = {0x02, PRE_1, OFF, 0x01};
	TWI_init(&config);
}

uint8 EEPROM_writeByte(uint16 address, uint8 data)
{
	/* Send start bit */
	TWI_start();
	if (TWI_getStatus() != TW_START)
	{
		return ERROR;
	}

	/* Send device address and last 3 bits are first 3 bits in memory address and write */
	TWI_write((uint8)(((address & (0x0700)) >> 7) | (0xA0)));
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
	{
		return ERROR;
	}

	/* Send rest of memory address */
	TWI_write((uint8)address);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return ERROR;
	}

	/* Send data to write in location */
	TWI_write(data);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return ERROR;
	}

	/* Send stop bit */
	TWI_stop();

	return SUCCESS;
}

uint8 EEPROM_readByte(uint16 address, uint8* data)
{
	/* Send start bit */
	TWI_start();
	if (TWI_getStatus() != TW_START)
	{
		return ERROR;
	}

	/* Send device address and last 3 bits are first 3 bits in memory address and write */
	TWI_write((uint8)(((address & (0x0700)) >> 7) | (0xA0)));
	if (TWI_getStatus() != TW_MT_SLA_W_ACK)
	{
		return ERROR;
	}

	/* Send rest of memory address */
	TWI_write((uint8)address);
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	{
		return ERROR;
	}

	/* Send repeated start bit */
	TWI_start();
	if (TWI_getStatus() != TW_REP_START)
	{
		return ERROR;
	}

	/* Send device address and last 3 bits are first 3 bits in memory address and read */
	TWI_write((uint8)(((address & (0x0700)) >> 7) | (0xA0) | (1)));
	if (TWI_getStatus() != TW_MT_SLA_R_ACK)
	{
		return ERROR;
	}

	/* Read Byte from location without sending ACK */
	(*data) = TWI_readWithNACK();
	if (TWI_getStatus() != TW_MR_DATA_NACK)
	{
		return ERROR;
	}

	/* Send stop bit */
	TWI_stop();

	return SUCCESS;
}

void EEPROM_deInit(void)
{
	/* Just Disable I2C Driver */
	TWI_deInit();
}
