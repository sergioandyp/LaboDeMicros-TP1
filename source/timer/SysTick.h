/***************************************************************************//**
  @file     SysTick.h
  @brief    SysTick driver
  @author   Nicolas Magliola
 ******************************************************************************/

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define SYSTICK_ISR_FREQUENCY_HZ 500U

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Initialize SysTic driver
 * @param funcallback Function to be call every SysTick
 * @return Initialization and registration succeed
 */
bool SysTick_Init (void (*funcallback)(void));


/*******************************************************************************
 ******************************************************************************/

#endif // _SYSTICK_H_
