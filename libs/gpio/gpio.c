#include <msp430.h>
#include "gpio.h"


static GPIO_TypeDef        *GPIOx;
static GPIO_InitTypeDef    GPIO_Init;

static void GPIO_OutputInit()
{
    GPIOx->PxDIR |= GPIO_Init.Pin;
};

static void GPIO_InputInit()
{

};

void GPIO(GPIO_TypeDef *_GPIOx, GPIO_InitTypeDef _GPIO_Init)
{
    GPIOx = _GPIOx;
    GPIO_Init = _GPIO_Init;

    switch (GPIO_Init.Mode)
    {
        case GPIO_MODE_INPUT:
            {
                GPIO_InputInit();
                break;
            }

        case GPIO_MODE_OUTPUT:
            {
                GPIO_OutputInit();
                break;
            }

        default:
            break;
    }
};

void GPIO_setOutputSignal_void(GPIO_State_u8 GPIO_State)
{
    GPIOx->PxOUT |= GPIO_State ? GPIO_Init.Pin : !(GPIO_Init.Pin);
};

void GPIO_toggleOutputSignal_void()
{
    GPIOx->PxOUT ^= GPIO_Init.Pin;
};