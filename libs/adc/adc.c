#include "adc.h"
#include "adc_config.h"

static void ADC_resetADCregister_void()
{
    ADC10_CONTROL_REG0->reg = 0;
    ADC10_CONTROL_REG1->reg = 0;
};

static void ADC_defaultInit_void()
{
#if (MCU_CONFIG_ADC_IRQ_EN == ON)
    ADC10_CONTROL_REG0->reg |= ADC_INTERRUPT_ENABLE;
#endif // (MCU_CONFIG_ADC_IRQ_EN == ON)

    ADC10_CONTROL_REG0->reg = ADC_CONTROL0_CONFIGURE;
    ADC10_CONTROL_REG1->reg = ADC_CONTROL1_CONFIGURE;
};

static void ADC_inputPinModeInit_void(ADC_InitTypeDef *ADC_Init)
{
    ADC10_CONTROL_REG0->reg |= ADC_Init->Ref;
    ADC10_CONTROL_REG1->reg |= ADC_Init->Channel;
    ADC10_INPUT_ENABLE_REG  |= ADC_Init->Pin;
};

static void ADC_temperatureSensorModeInit_void()
{
    ADC10_CONTROL_REG0->reg &= ~(SREF_7 | ADC_REF_ON);
    ADC10_CONTROL_REG0->reg |=  SREF_1 + ADC_REF_ON;

    ADC10_CONTROL_REG1->reg &= ~ADC_BIT15_IS_MSB;
    ADC10_CONTROL_REG1->reg |= ADC_CHANNEL_10 + ADC_BIT9_IS_MSB;
};

static void ADC_voltageComparisonModeInit_void(ADC_InitTypeDef *ADC_Init)
{
    ADC10_CONTROL_REG0->reg |= ADC_Init->Channel;
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
            ADC_temperatureSensorModeInit_void();
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
    if (ADC10_CONTROL_REG1->bit.DFORMAT == 0U)
    {
        /* The 10-bit conversion results are right-justified
         * straight-binary format. Bit 9 is the MSB. 15-10 are always 0     */

        return ADC10MEM;
    }
    else
    {
        /* The 10-bit conversion results are left-justified 2scomplement
         * format. Bit 15 is the MSB. Bits 5-0 are always 0.                */

        return (ADC10MEM >> 6);
    }
};

int16_t ADC_getDegreeFarenheit_s16()
{
    // oF = ((A10/1024)*1500mV)-923mV)*1/1.97mV = A10*761/1024 - 468
    uint16_t temp = ADC_getADCValue_u16();
    return ((temp - 630) * 761) / 1024;
};

int16_t ADC_getDegreeCelsius_s16()
{
    // oC = ((A10/1024)*1500mV)-986mV)*1/3.55mV = A10*423/1024 - 278
    uint16_t temp = ADC_getADCValue_u16();
    return ((temp - 673) * 423) / 1024;
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
