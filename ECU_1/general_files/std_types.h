/******************************************************************
 * Module: Standard Types
 *
 * File Name: std_types.h
 *
 * Description: Standard Variable Types used in most projects
 *
 * Created on: Sep 15, 2019
 *
 * Author: Ali Adel
******************************************************************/


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Defining NULL pointer */
#ifndef NULL
#define NULL ((void*)0)
#endif

/* Boolean Data Type */
typedef unsigned char bool;

/* Boolean Value True */
#ifndef TRUE
#define TRUE (1u)
#endif

/* Boolean Value False */
#ifndef FALSE
#define FALSE (0u)
#endif

/* Defining High as 1 */
#ifndef HIGH
#define HIGH (1u)
#endif

/* Defining Low as 0 */
#ifndef LOW
#define LOW (0u)
#endif

/* Defining Integer Types */

/* 0 -> +255														1 Byte */
typedef unsigned char		uint8;

/* -128 -> +127														1 Byte */
typedef signed char			sint8;

/* 0 -> +65,535														2 Bytes */
typedef unsigned short		uint16;

/* -32,768 -> +32,767												2 Bytes*/
typedef signed short		sint16;

/* 0 -> +4,294,967,295												4 Bytes */
typedef unsigned long		uint32;

/* -2,147,483,648 -> +2,147,483,647									4 Bytes */
typedef signed long			sint32;

/* 0 -> +18,446,744,073,709,551,615									8 Bytes */
typedef unsigned long long	uint64;

/* -9,223,372,036,854,775,808 -> +9,223,372,036,854,775,807			8 Bytes */
typedef signed long long	sint64;

/* 1.2E-38 -> 3.4E+38		6 Decimal Places Precision				4 Bytes */
typedef float				float32;

/* 2.3E-308 -> 1.7E+308		15 Decimal Places Precision				8 Bytes */
typedef double				float64;

/* 3.4E-4932 -> 1.1E+4932	19 Decimal Places Precision				10 Bytes */
typedef long double			float80;

#endif /* STD_TYPES_H_ */
