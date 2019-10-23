/******************************************************************************
 * Module: USART
 *
 * File Name: usart.h
 *
 * Description: Header File for Atmega16/32 USART Driver
 *
 * Created on: Sep 24, 2019
 *
 * Author: Ali Adel
******************************************************************************/

#ifndef USART_H_
#define USART_H_


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
 * 							Configuration Definitions						  *
******************************************************************************/
/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600

/******************************************************************************
 * 							Configuration Modes								  *
******************************************************************************/
/* Choose Number of bits in data in frame */
typedef enum
{
	BITS_5 = 0,
	BITS_6 = 1,
	BITS_7 = 2,
	BITS_8 = 3
}USART_DATA_BITS;

/* Choose Mode of Parity */
typedef enum
{
	DISABLED = 0,
	EVEN = 2,
	ODD = 3
}USART_PARITY;

/* Choose Number of Stop Bits at Frame end */
typedef enum
{
	BIT_1 = 0,
	BIT_2 = 1
}USART_STOP_BITS;

/* Choose Configuration to Start UART */
typedef struct
{
	USART_DATA_BITS data;	/* Choose Number of bits in data in frame */
	USART_PARITY parity;	/* Choose Mode of Parity */
	USART_STOP_BITS stop;	/* Choose Number of Stop Bits at Frame end */
}USART_Config;

/******************************************************************************
 * 							Functions Prototypes							  *
******************************************************************************/
/***************************************************************************
 * Function Name: UART_init
 *
 * Description: Initializes the UART Driver to be ready for operations
 *
 * Args:
 * 		[in]: const USART_Config* config:
 * 					Contains Configuration data to initialize USART Driver
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void USART_init(const USART_Config* config);

/***************************************************************************
 * Function Name: USART_sendByte
 *
 * Description: Sends data given using number of bits on initialization
 *
 * Args:
 * 		[in]: const uint8 data:
 * 					Data to be sent
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void USART_sendByte(const uint8 data);

/***************************************************************************
 * Function Name: USART_receiveByte
 *
 * Description: Receives Data found in register
 *
 * Args:
 * 		[void]: Doesn't take arguments
 *
 * Return Type: [uint8] Returns Byte Received
***************************************************************************/
uint8 USART_receiveByte(void);

/***************************************************************************
 * Function Name: USART_getParityFlag
 *
 * Description: Gets Parity Flag Status on last operation
 * 				Must be read before operation because it clears automatically
 * 				after UDR is read
 *
 * Args:
 * 		[void]: Doesn't take arguments
 *
 * Return Type: [bool] Returns TRUE if Set (Error occured in data transfer) and FALSE if not
***************************************************************************/
bool USART_getParityFlag(void);

/***************************************************************************
 * Function Name: USART_sendString
 *
 * Description: Sends string given using number of bits on initialization
 * 				But Doesn't send NULL character at end
 * 				(Should try to put own terminating character int string ex.'#')
 *
 *
 * Args:
 * 		[in]: const uint8* str:
 * 					string to be sent
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void USART_sendString(const uint8* str);

/***************************************************************************
 * Function Name: USART_receiveString
 *
 * Description: Receives a string until the '#' character
 *
 * Args:
 * 		[out]: uint8* str:
 * 					array to put string in
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void USART_receiveString(uint8* str);

/***************************************************************************
 * Function Name: USART_deInit
 *
 * Description: Stops the USART Driver
 *
 * Args:
 * 		[void]: Doesn't take arguments
 *
 * Return Type: [void] Doesn't Return anything
***************************************************************************/
void USART_deInit(void);

#endif /* USART_H_ */
