//  file: exti.c
//  brief: EXTI Driver for STM32F407
//----------------------------------------------------------------------

#include "exti.h"

#include "stm32f4xx.h"

//----------------------------------------------------------------------

//----------------------------------------------------------------------

void exti_configLine(GPIO_TypeDef* port, uint32_t pin)
{
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    uint32_t exti_config = 0;
    if (port == GPIOA) exti_config = 0x00;
    else if (port == GPIOB) exti_config = 0x01;
    else if (port == GPIOC) exti_config = 0x02;
    else if (port == GPIOD) exti_config = 0x03;
    else if (port == GPIOE) exti_config = 0x04;

    uint32_t tempreg = 0x0FuL << (4u * (pin & 0x03u));
    SYSCFG->EXTICR[pin >> 2u] &= ~tempreg;
    SYSCFG->EXTICR[pin >> 2u] |= exti_config << (4u * (pin & 0x03u));
}

void exti_configTrigger(uint32_t pin, EXTI_Edge_e trigger)
{
    uint32_t tempreg = 0x00;

    if (trigger & EXTI_Edge_Falling)
    {
        tempreg = EXTI->FTSR;
        tempreg &= ~(0x01 << pin);
        tempreg |= (0x01 << pin);
        EXTI->FTSR = tempreg;
    }

    if (trigger & EXTI_Edge_Rising)
    {
        tempreg = EXTI->RTSR;
        tempreg &= ~(0x01 << pin);
        tempreg |= (0x01 << pin);
        EXTI->RTSR = tempreg;
    }
}

void exti_setIrqEventMask(uint32_t pin, EXTI_Mode_e mode)
{
    uint32_t tempreg = 0x00;

    if (mode & EXTI_Mode_IRQ)
    {
        tempreg = EXTI->IMR;
        tempreg &= ~(0x01 << pin);
        tempreg |= (0x01 << pin);
        EXTI->IMR = tempreg;
    }
    else
    {
        tempreg = EXTI->EMR;
        tempreg &= ~(0x01 << pin);
        tempreg |= (0x01 << pin);
        EXTI->EMR = tempreg;
    }
}

void exti_setSoftwareIrq(uint32_t pin)
{
    EXTI->SWIER |= (0x01 << pin);
}

void exti_clearPendigIrq(uint32_t pin)
{
    EXTI->PR |= (0x01 << pin);
}

//----------------------------------------------------------------------