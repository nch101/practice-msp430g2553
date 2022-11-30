#ifndef __ADC_CONFIG_H
#define __ADC_CONFIG_H

#include "adc.h"

/**
 * @brief ADC10 Control 0 Register Default Value
 * 
 * 
 */
#define ADC_SAMPLING_TIME_DEFAULT       ADC_SAMPLETIME_16CYCLES
#define ADC_SAMPLING_RATE_DEFAULT       ADC_SAMPLERATE_50KSPS
#define ADC_REFERENCE_OUTPUT_DEFAULT    ADC_REFOUTPUT_OFF
#define ADC_REFERENCE_BURST_DEFAULT     ADC_REFBURST_MODE_OFF
#define ADC_MULTI_SAMPLE_CONVERSION     ADC_MSC_OFF
#define ADC_REF_GENERATOR_VOLTAGE       ADC_REF2_5V
#define ADC_REF_GENERATOR_DEFAULT       ADC_REF_ON

#define ADC_CONTROL0_CONFIGURE          (ADC_SAMPLING_TIME_DEFAULT \
                                        | ADC_SAMPLING_RATE_DEFAULT \
                                        | ADC_REFERENCE_OUTPUT_DEFAULT \
                                        | ADC_REFERENCE_BURST_DEFAULT \
                                        | ADC_MULTI_SAMPLE_CONVERSION \
                                        | ADC_REF_GENERATOR_VOLTAGE \
                                        | ADC_REF_GENERATOR_DEFAULT)

/**
 * @brief ADC10 Control 1 Register Default Value
 * 
 * 
 */
#define ADC_SAMPLE_HOLD_SRC_DEFAULT     SHS_0
#define ADC_DATA_FORMAT_DEFAULT         ADC_BIT9_IS_MSB
#define ADC_INVERT_SIGNAL_DEFAULT       ADC_NOT_INVERTED
#define ADC_CLOCK_PRESCALER_DEFAULT     ADC_CLOCK_PCLK_DIV2
#define ADC_CLOCK_SOURCE_DEFAULT        ADC_ACLK
#define ADC_CONVERSION_MODE_DEFAULT     ADC_SEQUENCE_CHANNEL_MODE

#define ADC_CONTROL1_CONFIGURE          (ADC_SAMPLE_HOLD_SRC_DEFAULT \
                                        | ADC_DATA_FORMAT_DEFAULT \
                                        | ADC_INVERT_SIGNAL_DEFAULT \
                                        | ADC_CLOCK_PRESCALER_DEFAULT \
                                        | ADC_CLOCK_SOURCE_DEFAULT \
                                        | ADC_CONVERSION_MODE_DEFAULT)

#endif // __ADC_CONFIG_H
