#include "adc.h"
#include "adc_config.h"

static void ADC_resetADCregister_void()
{
    ADC10_CONTROL_REG0->reg = 0;
    ADC10_CONTROL_REG1->reg = 0;
};

static void ADC_defaultInit_void()
{
    ADC10_CONTROL_REG0->reg = ADC_SAMPLING_TIME_DEFAULT | ADC_SAMPLING_RATE_DEFAULT;
    ADC10_CONTROL_REG1->reg = ADC_CLOCK_SOURCE_DEFAULT | ADC_CLOCK_PRESCALER_DEFAULT;
};

static void ADC_inputPinModeInit_void(ADC_InitTypeDef *ADC_Init)
{
#if (MCU_CONFIG_ADC_IRQ_EN == ON)
    ADC10_CONTROL_REG0->reg |= ADC_INTERRUPT_ENABLE;
#endif // (MCU_CONFIG_ADC_IRQ_EN == ON)
    ADC10_CONTROL_REG0->reg |= ADC10ON;
    ADC10_CONTROL_REG1->reg |= ADC_Init->Channel + ADC_Init->Format;

    ADC10_INPUT_ENABLE_REG  |= ADC_Init->Pin;
};

static void ADC_temperatureSensorModeInit_void(ADC_InitTypeDef *ADC_Init)
{
    // Todo: 
};

static void ADC_voltageComparisonModeInit_void(ADC_InitTypeDef *ADC_Init)
{
    // Todo: 
};

void ADC_init_void(ADC_InitTypeDef *ADC_Init)
{
    ADC_resetADCregister_void();
    ADC_defaultInit_void();

    switch (ADC_Init->Mode)
    {
        case ADC_INPUT_PIN_MODE:
            ADC_inputPinModeInit_void(ADC_Init);
            break;

        case ADC_TEMPERATURE_SENSOR_MODE:
            ADC_temperatureSensorModeInit_void(ADC_Init);
            break;

        case ADC_VOLTAGE_COMPARISON_MODE:
            ADC_voltageComparisonModeInit_void(ADC_Init);
            break;

        default:
            break;
    }
};

void ADC_startSamplingAndConversion_void()
{
    ADC10_CONTROL_REG0->reg = ADC_CONVERSION_ENABLE | ADC_CONVERSION_START;
};

uint16_t ADC_getADCValue_u16()
{
    return ADC10MEM;
};

uint8_t ADC_isADC10Busy_u8()
{
    return (uint8_t)(ADC10_CONTROL_REG1->bit.ADCBUSY);
};

#if (MCU_CONFIG_ADC_IRQ_EN == ON)
void __attribute__((weak)) ADC_processingADC_void()
{
    /* Note: This function should not be modified, when the processing is needed,
     *          the ADC_processingADC_void could be implemented in the user file
     */
};

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC_handlingADC10IQR_void(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC_handlingADC10IQR_void (void)
#else
#error Compiler not supported!
#endif // defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
{
    __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
    ADC_processingADC_void();
}
#endif // (MCU_CONFIG_ADC_IRQ_EN == ON)
