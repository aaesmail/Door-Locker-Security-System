/***************************************************************************
 * Module: I2C (TWI)
 *
 * File Name: i2c.h
 *
 * Description: Header File for I2C (TWI) AVR Driver
 *
 * Created on: Sep 28, 2019
 *
 * Author: Ali Adel
***************************************************************************/

#ifndef I2C_H_
#define I2C_H_

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
 * 							Configuration Types								  *
******************************************************************************/
/* Value of Bit Rate Prescalar */
typedef enum
{
	PRE_1 = 0,
	PRE_4 = 1,
	PRE_16 = 2,
	PRE_64 = 3
}TWI_PRESCALAR;

/* if turned on recognizes to general calls */
typedef enum
{
	OFF = 0,
	ON = 1
}TWI_GENERALCALL;

/* Configuration values of Module */
typedef struct
{
	/* Inserts this value into TWBR Register to get required bit rate
	 * See equation to get correct value */
	uint8 BIT_RATE;

	/* Set the bitrate prescalar (Again see equation to get correct value) */
	TWI_PRESCALAR PRESCALAR;

	/* Turn on/off general call recognition */
	TWI_GENERALCALL GENERAL_CALL;

	/* Device's slave address */
	uint8 SLAVE_ADDRESS;
}TWI_Config;

/******************************************************************************
 * 							Preprocessor Macros								  *
******************************************************************************/
/* Defining Status Values */
/* Start bit sent successfully */
#define TW_START (0x08)
/* Repeated Start bit sent successfully */
#define TW_REP_START (0x10)
/* Master transmits sent successfully (slave address + write + ACK received) */
#define TW_MT_SLA_W_ACK (0x18)
/* Master transmits sent successfully (slave address + read + ACK received) */
#define TW_MT_SLA_R_ACK (0x40)
/* Master transmits data and received ACK from slave */
#define TW_MT_DATA_ACK (0x28)
/* Master received data from slave and sent ACK */
#define TW_MR_DATA_ACK (0x50)
/* Master received data from slave but doesn't sent ACK */
#define TW_MR_DATA_NACK (0x58)

/******************************************************************************
 * 							Functions Prototypes							  *
******************************************************************************/
/***************************************************************************
 * Function Name: TWI_init
 *
 * Description: Initializes I2C Driver
 *
 * Args:
 * 		[in]: const TWI_Config* config:
 * 				Values to initialize driver with options chosen
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void TWI_init(const TWI_Config* config);

/***************************************************************************
 * Function Name: TWI_start
 *
 * Description: Sends the start bit
 *
 * Args:
 * 		[void]: Doesn't take arguments
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void TWI_start(void);

/***************************************************************************
 * Function Name: TWI_stop
 *
 * Description: Sends the stop bit
 *
 * Args:
 * 		[void]: Doesn't take arguments
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void TWI_stop(void);

/***************************************************************************
 * Function Name: TWI_write
 *
 * Description: Sends the data on bus
 *
 * Args:
 * 		[in]: uint8 data:
 * 				Contains data user wants to send
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void TWI_write(uint8 data);

/***************************************************************************
 * Function Name: TWI_readWithACK
 *
 * Description: Receives data and sends ACK to sender
 *
 * Args:
 * 		[void]: Doesn't take arguments
 *
 * Return Type: [uint8] Returns data received
***************************************************************************/
uint8 TWI_readWithACK(void);

/***************************************************************************
 * Function Name: TWI_readWithNACK
 *
 * Description: Receives data and doesn't send ACK to sender
 *
 * Args:
 * 		[void]: Doesn't take arguments
 *
 * Return Type: [uint8] Returns data received
***************************************************************************/
uint8 TWI_readWithNACK(void);

/***************************************************************************
 * Function Name: TWI_getStatus
 *
 * Description: Reads the status register and returns its value
 *
 * Args:
 * 		[void]: Doesn't take arguments
 *
 * Return Type: [uint8] Returns status of last operation
***************************************************************************/
uint8 TWI_getStatus(void);

/***************************************************************************
 * Function Name: TWI_deInit
 *
 * Description: Stops I2C Driver
 *
 * Args:
 * 		[void]: Doesn't take arguments
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void TWI_deInit(void);

#endif /* I2C_H_ */
