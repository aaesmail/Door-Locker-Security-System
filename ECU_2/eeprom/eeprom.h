/***************************************************************************
 * Module: EEPROM
 *
 * File Name: eeprom.h
 *
 * Description: Header File for External EEPROM device
 *
 * Created on: Sep 28, 2019
 *
 * Author: Ali Adel
***************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

/******************************************************************************
 * 							Including Files									  *
******************************************************************************/
/* File for standard types */
#include "../general_files/std_types.h"

/******************************************************************************
 * 							Preprocessor Macros								  *
******************************************************************************/
/* Defining status returns */
#define ERROR (0)
#define SUCCESS (1)

/******************************************************************************
 * 							Functions Prototypes							  *
******************************************************************************/
/***************************************************************************
 * Function Name: EEPROM_init
 *
 * Description: Initializes EEPROM Driver
 *
 * Args:
 * 		[void]: Doesn't take arguments
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void EEPROM_init(void);

/***************************************************************************
 * Function Name: EEPROM_writeByte
 *
 * Description: Write byte in desired location
 *
 * Args:
 * 		[in]: uint16 address:
 * 				Address of location in memory to write to
 *
 * 		[in]: uint8 data:
 * 				Data to be written in this address
 *
 * Return Type: [uint8] Returns Status of operation (Success or Fail)
***************************************************************************/
uint8 EEPROM_writeByte(uint16 address, uint8 data);

/***************************************************************************
 * Function Name: EEPROM_readByte
 *
 * Description: read byte in desired location
 *
 * Args:
 * 		[in]: uint16 address:
 * 				Address of location in memory to read from
 *
 * 		[in]: uint8* data:
 * 				puts data read in location by pointer
 *
 * Return Type: [uint8] Returns Status of operation (Success or Fail)
***************************************************************************/
uint8 EEPROM_readByte(uint16 address, uint8* data);

/***************************************************************************
 * Function Name: EEPROM_deInit
 *
 * Description: Disables EEPROM Driver
 *
 * Args:
 * 		[void]: Doesn't take arguments
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void EEPROM_deInit(void);

#endif /* EEPROM_H_ */
