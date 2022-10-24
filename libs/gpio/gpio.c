#include "gpio.h"
#include "gpio_config.h"

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

#if ((MCU_CONFIG_PORT1_EXTI_IRQ_EN == ON) || (MCU_CONFIG_PORT2_EXTI_IRQ_EN == ON))
static void GPIO_InterruptRisingEdgeInit_void(GPIO_InitTypeDef *GPIO_Init)
{
    GPIO_Init->Base->PxIE       |= GPIO_Init->Pin;
    GPIO_Init->Base->PxIES      &= ~GPIO_Init->Pin;
    GPIO_Init->Base->PxIFG      &= ~GPIO_Init->Pin;
};

static void GPIO_InterruptFallingEdgeInit_void(GPIO_InitTypeDef *GPIO_Init)
{
    GPIO_Init->Base->PxIE       |= GPIO_Init->Pin;
    GPIO_Init->Base->PxIES      |= GPIO_Init->Pin;
    GPIO_Init->Base->PxIFG      &= ~GPIO_Init->Pin;
};
#endif // ((MCU_CONFIG_PORT1_EXTI_IRQ_EN == ON) || (MCU_CONFIG_PORT2_EXTI_IRQ_EN == ON))

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

#if ((MCU_CONFIG_PORT1_EXTI_IRQ_EN == ON) || (MCU_CONFIG_PORT2_EXTI_IRQ_EN == ON))
        case GPIO_MODE_IT_RISING:
            GPIO_InterruptRisingEdgeInit_void(GPIO_Init);
            GPIO_InputInit_void(GPIO_Init);
            break;

        case GPIO_MODE_IT_FALLING:
            GPIO_InterruptFallingEdgeInit_void(GPIO_Init);
            GPIO_InputInit_void(GPIO_Init);
            break;

#endif // ((MCU_CONFIG_PORT1_EXTI_IRQ_EN == ON) || (MCU_CONFIG_PORT2_EXTI_IRQ_EN == ON))

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

#if ((MCU_CONFIG_PORT1_EXTI_IRQ_EN == ON) || (MCU_CONFIG_PORT2_EXTI_IRQ_EN == ON))
void __attribute__((weak)) GPIO_processingPortIRQ_void()
{
    /* Note: This function should not be modified, when the processing is needed,
     *          the GPIO_processingPortIRQ_void could be implemented in the user file
     */
};
#endif // ((MCU_CONFIG_PORT1_EXTI_IRQ_EN == ON) || (MCU_CONFIG_PORT2_EXTI_IRQ_EN == ON))

#if (MCU_CONFIG_PORT1_EXTI_IRQ_EN == ON)
static bool GPIO_isInterruptPendingOnPort1_bool(GPIO_Pin_u8 GPIO_Pin)
{
    if ((GPIO_1->PxIFG & GPIO_Pin) == GPIO_Pin)
    {
        return true;
    } else
    {
        return false;
    }
};

static void GPIO_port1IRQHandler_void(GPIO_Pin_u8 GPIO_Pin)
{
    if (GPIO_isInterruptPendingOnPort1_bool(GPIO_Pin) == true)
    {
        GPIO_1->PxIFG &= ~GPIO_Pin;
        GPIO_processingPortIRQ_void();
    }
};

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void GPIO_handlingPort1IRQ_void(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) GPIO_handlingPort1IRQ_void (void)
#else
#error Compiler not supported!
#endif // defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
{
    GPIO_port1IRQHandler_void(GPIO_PIN_3);
};
#endif // MCU_CONFIG_PORT1_EXTI_IRQ_EN

#if (MCU_CONFIG_PORT2_EXTI_IRQ_EN == ON)
static bool GPIO_isInterruptPendingOnPort2_bool(GPIO_Pin_u8 GPIO_Pin)
{
    if ((GPIO_2->PxIFG & GPIO_Pin) == GPIO_Pin)
    {
        return true;
    } else
    {
        return false;
    }
};

static void GPIO_port2IRQHandler_void(GPIO_Pin_u8 GPIO_Pin)
{
    if (GPIO_isInterruptPendingOnPort2_bool(GPIO_Pin) == true)
    {
        GPIO_2->PxIFG &= ~GPIO_Pin;
        GPIO_processingPortIRQ_void();
    }
};

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void GPIO_handlingPort2IRQ_void(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT2_VECTOR))) GPIO_handlingPort2IRQ_void (void)
#else
#error Compiler not supported!
#endif //defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
{
    GPIO_port2IRQHandler_void(GPIO_INTERRUPT_PIN);
};
#endif // MCU_CONFIG_PORT2_EXTI_IRQ_EN
