#ifndef _EXTI_DRIVER_H_
#define _EXTI_DRIVER_H_

#include <stdint.h>

#include "stm32f4xx.h"

//----------------------------------------------------------------------

typedef enum
{
    EXTI_Mode_IRQ = 0x01,
    EXTI_Mode_Event,
} EXTI_Mode_e;

typedef enum
{
    EXTI_Edge_Rising = 0x01,
    EXTI_Edge_Falling,
    EXTI_Edge_Rising_Falling,
} EXTI_Edge_e;


//----------------------------------------------------------------------

/**
 * \brief Configure external interrupt line in SYSCFG
 */
void exti_configLine(GPIO_TypeDef* port, uint32_t pin);

/**
 * \brief Set Rising, Falling or both Rising-Falling edge of trigger
 * for interrupt
 */
void exti_configTrigger(uint32_t pin, EXTI_Edge_e trigger);

/**
 * \brief Set Event or Interrupt mask
 */
void exti_setIrqEventMask(uint32_t pin, EXTI_Mode_e mode);

/**
 * \brief Get IRQ by software
 */
void exti_setSoftwareIrq(uint32_t pin);

/**
 * \brief Clear pending interrupt
 */
void exti_clearPendigIrq(uint32_t pin);

//----------------------------------------------------------------------

#endif // _EXTI_DRIVER_H_