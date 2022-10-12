#include <msp430.h>
#include "gpio.h"

static void GPIO_OutputInit_void(GPIO_InitTypeDef *GPIO_Init)
{
    GPIO_Init->Base->PxDIR |= GPIO_Init->Pin;
};

static void GPIO_InputInit_void(GPIO_InitTypeDef *GPIO_Init)
{
    GPIO_Init->Base->PxDIR &= ~(GPIO_Init->Pin);

    switch (GPIO_Init->Pull)
    {
        case GPIO_PULLUP:
            GPIO_Init->Base->PxREN |= GPIO_Init->Pin;
            GPIO_Init->Base->PxOUT |= GPIO_Init->Pin;
            break;

        case GPIO_PULLDOWN:
            GPIO_Init->Base->PxREN |= GPIO_Init->Pin;
            GPIO_Init->Base->PxOUT &= ~(GPIO_Init->Pin);
            break;

        case GPIO_NOPULL:
        default:
            break;
    }
};

static void GPIO_InterruptRisingEdgeInit_void(GPIO_InitTypeDef *GPIO_Init)
{
    GPIO_Init->Base->PxIE     |= GPIO_Init->Pin;
    GPIO_Init->Base->PxIES    &= ~GPIO_Init->Pin;
};

static void GPIO_InterruptFallingEdgeInit_void(GPIO_InitTypeDef *GPIO_Init)
{
    GPIO_Init->Base->PxIE     |= GPIO_Init->Pin;
    GPIO_Init->Base->PxIES    |= GPIO_Init->Pin;
};

static uint8_t isInterruptPending()
{
    // To do: Check interrupt flag vs Interrupt pin
};

void GPIO_init_void(GPIO_InitTypeDef *GPIO_Init)
{
    switch (GPIO_Init->Mode)
    {
        case GPIO_MODE_INPUT:
            GPIO_InputInit_void(GPIO_Init);
            break;

        case GPIO_MODE_OUTPUT:
            GPIO_OutputInit_void(GPIO_Init);
            break;

        case GPIO_MODE_IT_RISING:
            GPIO_InterruptRisingEdgeInit_void(GPIO_Init);
            GPIO_InputInit_void(GPIO_Init);
            break;

        case GPIO_MODE_IT_FALLING:
            GPIO_InterruptFallingEdgeInit_void(GPIO_Init);
            GPIO_InputInit_void(GPIO_Init);
            break;

        default:
            break;
    }
};

void GPIO_setOutputSignal_void(GPIO_InitTypeDef *GPIO_Init, GPIO_State_u8 GPIO_State)
{
    if (GPIO_State == GPIO_HIGH)
    {
        GPIO_Init->Base->PxOUT |= GPIO_Init->Pin;
    } else
    {
        GPIO_Init->Base->PxOUT &= ~GPIO_Init->Pin;
    }
};

void GPIO_toggleOutputSignal_void(GPIO_InitTypeDef *GPIO_Init)
{
    GPIO_Init->Base->PxOUT ^= GPIO_Init->Pin;
};

GPIO_State_u8 GPIO_getInputSignal_u8(GPIO_InitTypeDef *GPIO_Init)
{
    if ((GPIO_Init->Base->PxIN & GPIO_Init->Pin) != GPIO_Init->Pin)
    {
        return GPIO_HIGH;
    } else
    {
        return GPIO_LOW;
    }
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