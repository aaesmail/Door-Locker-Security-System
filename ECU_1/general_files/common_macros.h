/************************************************************
 * Module: Common Macros
 *
 * File Name: common_macros.h
 *
 * Description: Commonly used macros in most projects
 *
 * Created on: Sep 15, 2019
 *
 * Author: Ali Adel
************************************************************/


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Sets the given bit to 1 in the given register */
#define SET_BIT(REG,BIT_NUM) ((REG) = (REG) | ((1u) << (BIT_NUM)))

/* Clears the given bit to 0 in the given register */
#define CLEAR_BIT(REG,BIT_NUM) ((REG) = (REG) & (~((1u) << (BIT_NUM))))

/* Toggles the given bit in the given register */
#define TOGGLE_BIT(REG,BIT_NUM) ((REG) = (REG) ^ ((1u) << (BIT_NUM)))

/* Checks if the bit is set to 1 returns true (1) */
#define BIT_IS_SET(REG,BIT_NUM) (((REG) & ((1u) << (BIT_NUM))) == ((1u) << (BIT_NUM)))

/* Checks if the bit is cleared return true (1) */
#define BIT_IS_CLEAR(REG,BIT_NUM) (!((REG) & ((1u) << (BIT_NUM))))

/*****************************************************************
 * Rotates the 8-bits register RIGHT with number of rotates given
 * (Works only with 8-bits registers)
 ****************************************************************/
#define ROR(REG,NUM) (REG) = (((REG) >> (NUM)) | ((REG) << ((8u) - (NUM))))

/*****************************************************************
 * Rotates the 8-bits register LEFT with number of rotates given
 * (Works only with 8-bits registers)
 ****************************************************************/
#define ROL(REG,NUM) (REG) = (((REG) << (NUM)) | ((REG) >> ((8u) - (NUM))))

#endif /* COMMON_MACROS_H_ */
