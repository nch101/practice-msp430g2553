#include <msp430.h>
#include "gpio.h"


static GPIO_TypeDef        *GPIOx;
static GPIO_InitTypeDef    GPIO_Init;

static void GPIO_OutputInit_void()
{
    GPIOx->PxDIR |= GPIO_Init.Pin;
};

static void GPIO_InputInit_void()
{
    GPIOx->PxDIR &= ~(GPIO_Init.Pin);

    switch (GPIO_Init.Pull)
    {
        case GPIO_PULLUP:
            GPIOx->PxREN |= GPIO_Init.Pin;
            GPIOx->PxOUT |= GPIO_Init.Pin;
            break;

        case GPIO_PULLDOWN:
            GPIOx->PxREN |= GPIO_Init.Pin;
            GPIOx->PxOUT &= ~(GPIO_Init.Pin);
            break;

        case GPIO_NOPULL:
        default:
            break;
    }
};

static void GPIO_InterruptRisingEdgeInit_void()
{
    GPIOx->PxIE     |= GPIO_Init.Pin;
    GPIOx->PxIES    &= ~(GPIO_Init.Pin);
};

static void GPIO_InterruptFallingEdgeInit_void()
{
    GPIOx->PxIE     |= GPIO_Init.Pin;
    GPIOx->PxIES    |= GPIO_Init.Pin;
};

static uint8_t isInterruptPending()
{
    // To do: Check interrupt flag vs Interrupt pin
};

void GPIO(GPIO_TypeDef *_GPIOx, GPIO_InitTypeDef _GPIO_Init)
{
    GPIOx = _GPIOx;
    GPIO_Init = _GPIO_Init;

    switch (GPIO_Init.Mode)
    {
        case GPIO_MODE_INPUT:
            GPIO_InputInit_void();
            break;

        case GPIO_MODE_OUTPUT:
            GPIO_OutputInit_void();
            break;

        case GPIO_MODE_IT_RISING:
            GPIO_InterruptRisingEdgeInit_void();
            GPIO_InputInit_void();
            break;

        case GPIO_MODE_IT_FALLING:
            GPIO_InterruptFallingEdgeInit_void();
            GPIO_InputInit_void();
            break;

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

#pragma vector = PORT1_VECTOR
__interrupt void GPIO_handlingPort1IRQ_void()
{
    // To do: Call process interrupt function
};

void __attribute__((weak)) GPIO_processingPortIRQ_void();

void GPIO_processingPortIRQ_void()
{
    // Add comment
};