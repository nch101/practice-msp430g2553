#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>
#include <msp430.h>

#include "mcu_config.h"

/** @defgroup GPIO_pins_define GPIO pins define
  * @{
  */
#define GPIO_PIN_0          ((uint8_t)0x01)     /* Pin 0 selected */
#define GPIO_PIN_1          ((uint8_t)0x02)     /* Pin 1 selected */
#define GPIO_PIN_2          ((uint8_t)0x04)     /* Pin 2 selected */
#define GPIO_PIN_3          ((uint8_t)0x08)     /* Pin 3 selected */
#define GPIO_PIN_4          ((uint8_t)0x10)     /* Pin 4 selected */
#define GPIO_PIN_5          ((uint8_t)0x20)     /* Pin 5 selected */
#define GPIO_PIN_6          ((uint8_t)0x40)     /* Pin 6 selected */
#define GPIO_PIN_7          ((uint8_t)0x80)     /* Pin 7 selected */
/**
  * @}
  */

#define GPIO_BASE_1         0x0020
#define GPIO_BASE_2         0x0028
#define GPIO_BASE_3         0x0018

#define __IO                volatile

/** 
  * @brief General Purpose I/O
  */
typedef struct 
{
    __IO uint8_t            PxIN;         /* Input Register       */
    __IO uint8_t            PxOUT;        /* Output Register      */
    __IO uint8_t            PxDIR;        /* Direction Register   */
    __IO uint8_t            PxIFG;        /* Interrupt Flag Registers */
    __IO uint8_t            PxIES;        /* Interrupt Edge Select Registers  */
    __IO uint8_t            PxIE;         /* Interrupt Enable         */
    __IO uint8_t            PxSEL;        /* Function Select Registers        */
    __IO uint8_t            PxREN;        /* Pullup or Pulldown Resistor Enable Register */
} GPIO_TypeDef;

#define GPIO_1              ((GPIO_TypeDef *) GPIO_BASE_1)
#define GPIO_2              ((GPIO_TypeDef *) GPIO_BASE_2)


/** @defgroup GPIO_Mode_define GPIO mode define
  * @brief GPIO Configuration Mode
  * @{
  */
typedef enum
{
    GPIO_MODE_INPUT,        /* Input Mode       */
    GPIO_MODE_OUTPUT,       /* Output Mode      */

#if ((MCU_CONFIG_PORT1_EXTI_IRQ_EN == ON) || (MCU_CONFIG_PORT2_EXTI_IRQ_EN == ON))
    GPIO_MODE_IT_RISING,    /* External Interrupt Mode with Rising edge trigger detection       */
    GPIO_MODE_IT_FALLING,   /* External Interrupt Mode with Falling edge trigger detection      */
#endif // ((MCU_CONFIG_PORT1_EXTI_IRQ_EN == ON) || (MCU_CONFIG_PORT2_EXTI_IRQ_EN == ON))
} __attribute__((__packed__)) GPIO_Mode_u8;
/**
  * @}  
  */

/** 
  * @brief GPIO Pull-Up or Pull-Down Activation
  */
typedef enum
{
    GPIO_NOPULL,            /* No Pull-up or Pull-down Activation   */
    GPIO_PULLUP,            /* Pull-up Activation                   */
    GPIO_PULLDOWN           /* Pull-down Activation                 */
} __attribute__((__packed__)) GPIO_Pull_u8;
/**
  * @}  
  */

typedef     uint8_t         GPIO_Pin_u8;

typedef enum
{
    GPIO_LOW,
    GPIO_HIGH
} __attribute__((__packed__)) GPIO_State_u8;

typedef struct
{
    GPIO_TypeDef    *Base;
    GPIO_Pin_u8     Pin;
    GPIO_Mode_u8    Mode;
    GPIO_Pull_u8    Pull;
} GPIO_InitTypeDef;

// GPIO Init
void GPIO_init_void(GPIO_InitTypeDef *GPIO_Init);

// Output
void GPIO_setOutputSignal_void(GPIO_InitTypeDef *GPIO_Init, GPIO_State_u8 GPIO_State);
void GPIO_toggleOutputSignal_void(GPIO_InitTypeDef *GPIO_Init);

// Input
GPIO_State_u8 GPIO_getInputSignal_u8(GPIO_InitTypeDef *GPIO_Init);

#endif // __GPIO_H