/***********************************************************************************
 * Module: Timer 1 Normal & CTC
 *
 * File Name: timer1.h
 *
 * Description: Header file for Atmega16/32 Timer1 Driver (Normal & CTC)
 *
 * Created on: Sep 30, 2019
 *
 * Author: Ali Adel
***********************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

/********************************************************************
 * 							Including Files							*
********************************************************************/
/* File for Standard Types */
#include "../general_files/std_types.h"

/* File for Most used Macros */
#include "../general_files/common_macros.h"

/* File for MCU Specific Configurations */
#include "../general_files/micro_config.h"

/********************************************************************
 * 							Configuration Types						*
********************************************************************/
/* Choose Operating Mode */
typedef enum
{
	NORMAL = 0,
	CTC = 1
}TIMER1_MODE;

/* Choose Channel behavior */
typedef struct
{
	enum	/* Enable interrupt or not */
	{
		OFF = 0,
		ON = 1
	}TIMER1_INTERRUPT;

	enum	/* Mode of OCR1X */
	{
		DISCONNECTED = 0,
		TOGGLE = 1,
		CLEAR = 2,
		SET = 3
	}TIMER1_CHANNEL_OCR1;

	uint16 COMPARE_VALUE;	/* Value for compare register */
}TIMER1_CHANNEL;

/* Choose Clock Prescalar */
typedef enum
{
	CPU_1 = 1,
	CPU_8 = 2,
	CPU_64 = 3,
	CPU_256 = 4,
	CPU_1024 = 5
}TIMER1_PRESCALAR;

/* Choose Timer1 Configurations */
typedef struct
{
	TIMER1_MODE MODE;	/* Choose operating mode */
	TIMER1_PRESCALAR PRESCALAR;	/* Choose operation prescalar */
	uint16 INITIAL_VALUE;	/* Put start value for timer1 */
	TIMER1_CHANNEL CHANNELA;		/* Configurations for ChannelA behavior
	 	 	 	 	 	 	 	 	   1- choose enable interrupt or not (ON/OFF)
	 	 	 	 	 	 	 	 	   2- Mode of OCR1A (DISCONNECTED/TOGGLE/CLEAR/SET)
	 	 	 	 	 	 	 	 	   3- Compare value to insert into register (uint16) */
	TIMER1_CHANNEL CHANNELB;		/* Configurations for ChannelB behavior
	 	 	 	 	 	 	 	 	   1- choose enable interrupt or not (ON/OFF)
	 	 	 	 	 	 	 	 	   2- Mode of OCR1B (DISCONNECTED/TOGGLE/CLEAR/SET)
	 	 	 	 	 	 	 	 	   3- Compare value to insert into register (uint16) */
}TIMER1_Config;
/********************************************************************
 * 							Functions Prototypes					*
********************************************************************/
/***************************************************************
 * Function Name: TIMER1_init
 *
 * Description: Starts Timer1 With given configurations
 *
 * Args:
 * 		[in]: const TIMER1_Config* config:
 * 					Pointer to used chosen configurations to start module with
 *
 * Return Type: [void] Doesn't return anything
***************************************************************/
void TIMER1_init(const TIMER1_Config* config);

/***************************************************************
 * Function Name: TIMER1_setCallBackNormal
 *
 * Description: Sets callback function for normal mode
 *
 * Args:
 * 		[in]: void (*callBack)(void):
 * 					Pointer to callback function to call when interrupt happens
 *
 * Return Type: [void] Doesn't return anything
***************************************************************/
void TIMER1_setCallBackNormal(void(*callBack)(void));

/***************************************************************
 * Function Name: TIMER1_setCallBackChannelA
 *
 * Description: Sets callback function for CTC channelA mode
 *
 * Args:
 * 		[in]: void (*callBack)(void):
 * 					Pointer to callback function to call when interrupt happens
 *
 * Return Type: [void] Doesn't return anything
***************************************************************/
void TIMER1_setCallBackChannelA(void(*callBack)(void));

/***************************************************************
 * Function Name: TIMER1_setCallBackChannelB
 *
 * Description: Sets callback function for CTC channelB mode
 *
 * Args:
 * 		[in]: void (*callBack)(void):
 * 					Pointer to callback function to call when interrupt happens
 *
 * Return Type: [void] Doesn't return anything
***************************************************************/
void TIMER1_setCallBackChannelB(void(*callBack)(void));

/********************************************************
 * Function Name: Timer1_stop
 *
 * Description: Stops the Timer1 by disabling clock
 *
 * Args:
 * 		[void]: Doesn't take Arguments
 *
 * 	Return: [void] Doesn't return anything
********************************************************/
void TIMER1_stop(void);

/********************************************************
 * Function Name: Timer1_restart
 *
 * Description: Restarts the Timer1
 *
 * Args:
 * 		[in]: TIMER1_PRESCALAR clk:
 * 						Restart Timer by Clock user selects
 *
 * 	Return: [void] Doesn't return anything
********************************************************/
void TIMER1_restart(TIMER1_PRESCALAR clk);

/***************************************************************
 * Function Name: TIMER1_deInit
 *
 * Description: Stops operation of Timer1
 *
 * Args:
 * 		[void]: Doesn't take any arguments
 *
 * Return Type: [void] Doesn't return anything
***************************************************************/
void TIMER1_deInit(void);

#endif /* TIMER1_H_ */
