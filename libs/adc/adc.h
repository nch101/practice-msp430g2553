#ifndef __ADC_H
#define __ADC_H

#include <stdint.h>
#include <msp430.h>

#include "mcu_config.h"

#define __IO                volatile

/*  */
typedef union
{
    __IO uint16_t           reg;                    /*  */
    struct 
    {
        __IO uint16_t       SC              : 1;    /* [0..0] Start conversion */
        __IO uint16_t       ENCVS           : 1;    /* [1..1] Enable conversion */
        __IO uint16_t       IFG             : 1;    /* [2..2] ADC10 interrupt flag */
        __IO uint16_t       IE              : 1;    /* [3..3] ADC10 interrupt enable */
        __IO uint16_t       ADCON           : 1;    /* [4..4] ADC10 on */
        __IO uint16_t       REFGENON        : 1;    /* [5..5] Reference generator on */
        __IO uint16_t       REFGEN2_5V      : 1;    /* [6..6] Reference generator voltage. REFON must also be set 
                                                     *          0b = 1.5 V
                                                     *          1b = 2.5 V */
        __IO uint16_t       MSPCVS          : 1;    /* [7..7] Multiple sample and conversion
                                                     * Valid only for sequence or repeated modes */
        __IO uint16_t       REFBU           : 1;    /* [8..8] Reference burst
                                                     *          0b = Reference buffer on continuously
                                                     *          1b = Reference buffer on only during sample-and-conversion */
        __IO uint16_t       REFOUTPUT       : 1;    /* [9..9] Reference output */
        __IO uint16_t       SR              : 1;    /* [10..10] ADC10 sampling rate */
        __IO uint16_t       SHTx            : 2;    /* [11..12] ADC10 sample-and-hold time.
                                                     *          00b = 4 ADC10CLK cycles
                                                     *          01b = 8 ADC10CLK cycles
                                                     *          10b = 16 ADC10CLK cycles
                                                     *          11b = 64 ADC10CLK cycles */
        __IO uint16_t       SREFx           : 3;    /* [12..15] Select reference */
    } bit;

} ADC_ADC10CTL0_Reg;


/*  */
typedef union
{
    __IO uint16_t           reg;                    /*  */
    struct
    {
        __IO uint16_t       ADCBUSY         : 1;    /* [0..0] ADC10 busy */
        __IO uint16_t       CONSEQx         : 2;    /* [1..2] Conversion sequence mode select */
        __IO uint16_t       SSELx           : 2;    /* [3..4] ADC10 clock source select */
        __IO uint16_t       DIVx            : 3;    /* [5..7] ADC10 clock divider */
        __IO uint16_t       ISSAH           : 1;    /* [8..8] Invert signal sample-and-hold */
        __IO uint16_t       DFORMAT         : 1;    /* [9..9] ADC10 data format.
                                                     *          0b = Straight binary
                                                     *          1b = 2s complement */
        __IO uint16_t       SHSx            : 2;    /* [10..11] Sample-and-hold source select
                                                     *          00b = ADC10SC bit
                                                     *          01b = Timer_A.OUT1
                                                     *          10b = Timer_A.OUT0
                                                     *          11b = Timer_A.OUT2 */
        __IO uint16_t       INCHx           : 4;    /* [12..15] Input channel select */
    } bit;
    
} ADC_ADC10CTL1_Reg;


/*  */
typedef union
{
    __IO uint8_t            reg;
    struct
    {
        __IO uint8_t        FETCH           : 1;    /* [0..0] This bit should normally be reset. */
        __IO uint8_t        BLOCK1          : 1;    /* [1..1] ADC10 block one
                                                     *          0b = Block 2 is filled
                                                     *          1b = Block 1 is filled */
        __IO uint8_t        CT              : 1;    /* [2..2] ADC10 continuous transfer */
        __IO uint8_t        TWOBLOCK        : 1;    /* [3..3] ADC10 two-block mode */
        __IO uint8_t                        : 4;    /* Reserved */
    } bit;

} ADC_ADC10DTC0_Reg;

#define ADC10_CONTROL_REG0                  ((ADC_ADC10CTL0_Reg *) &ADC10CTL0)
#define ADC10_CONTROL_REG1                  ((ADC_ADC10CTL1_Reg *) &ADC10CTL1)

#define ADC10_DATA_TRANSFER_CONTROL_REG0    ((ADC_ADC10DTC0_Reg *) &ADC10DTC0)
#define ADC10_DATA_TRANSFER_CONTROL_REG1    ADC10DTC1

#define ADC10_INPUT_ENABLE_REG              ADC10AE0

/* ADC Configuration Mode */
typedef enum 
{
    ADC_INPUT_PIN_MODE,             /* Get analog signal from pin */
    ADC_TEMPERATURE_SENSOR_MODE,    /*  */
    ADC_VOLTAGE_COMPARISON_MODE,    /*  */
} __attribute__((__packed__)) ADC_Mode_u8;

/* ADC channels */
#define ADC_CHANNEL_0               INCH_0          /* Selects Channel 0    */
#define ADC_CHANNEL_1               INCH_1          /* Selects Channel 1    */
#define ADC_CHANNEL_2               INCH_2          /* Selects Channel 2    */
#define ADC_CHANNEL_3               INCH_3          /* Selects Channel 3    */
#define ADC_CHANNEL_4               INCH_4          /* Selects Channel 4    */
#define ADC_CHANNEL_5               INCH_5          /* Selects Channel 5    */
#define ADC_CHANNEL_6               INCH_6          /* Selects Channel 6    */
#define ADC_CHANNEL_7               INCH_7          /* Selects Channel 7    */
#define ADC_CHANNEL_8               INCH_8          /* VeREF+               */
#define ADC_CHANNEL_9               INCH_9          /* VREF-/VeREF-         */
#define ADC_CHANNEL_10              INCH_10         /* Temperature sensor   */
#define ADC_CHANNEL_11              INCH_11         /* (VCC – VSS) / 2      */
#define ADC_CHANNEL_12              INCH_12         /* (VCC – VSS) / 2      */
#define ADC_CHANNEL_13              INCH_13         /* (VCC – VSS) / 2      */
#define ADC_CHANNEL_14              INCH_14         /* (VCC – VSS) / 2      */
#define ADC_CHANNEL_15              INCH_15         /* (VCC – VSS) / 2      */

/* ADC pins define */
#define ADC_PIN_0                   ((uint8_t)0x01)     /* Pin 0 selected */
#define ADC_PIN_1                   ((uint8_t)0x02)     /* Pin 1 selected */
#define ADC_PIN_2                   ((uint8_t)0x04)     /* Pin 2 selected */
#define ADC_PIN_3                   ((uint8_t)0x08)     /* Pin 3 selected */
#define ADC_PIN_4                   ((uint8_t)0x10)     /* Pin 4 selected */
#define ADC_PIN_5                   ((uint8_t)0x20)     /* Pin 5 selected */
#define ADC_PIN_6                   ((uint8_t)0x40)     /* Pin 6 selected */
#define ADC_PIN_7                   ((uint8_t)0x80)     /* Pin 7 selected */

/* ADC sampling time */
#define ADC_SAMPLETIME_4CYCLES      ADC10SHT_0          /* 4 x ADC10CLKs  */
#define ADC_SAMPLETIME_8CYCLES      ADC10SHT_1          /* 8 x ADC10CLKs  */
#define ADC_SAMPLETIME_16CYCLES     ADC10SHT_2          /* 16 x ADC10CLKs */
#define ADC_SAMPLETIME_64CYCLES     ADC10SHT_3          /* 64 x ADC10CLKs */

/* ADC sampling rate */
#define ADC_SAMPLERATE_200KSPS      ((uint16_t)0x0000)  /* Reference buffer 200 ksps */
#define ADC_SAMPLERATE_50KSPS       ((uint16_t)0x0400)  /* Reference buffer 50 ksps */

/* ADC reference output */
#define ADC_REFOUTPUT_ON            REFOUT              /* ADC10 Reference on */

/* ADC reference burst */
#define ADC_REFBURST_MODE_ON        REFBURST            /* ADC10 Reference Burst Mode */

/* ADC Multiple Sample Conversion */
#define ADC_MSC                     MSC

/* ADC data format */
#define ADC_BIT9_IS_MSB             ((uint16_t)0x0)
#define ADC_BIT15_IS_MSB            ADC10DF

/* Reference-generator voltage */
#define ADC_REF1_5V                 ((uint16_t)0x0)
#define ADC_REF2_5V                 REF2_5V

/* ADC Reference on */
#define ADC_REF_ON                  REFON               /* ADC10 Reference on */

/* ADC interrupt enable */
#define ADC_INTERRUPT_ENABLE        ADC10IE             /* ADC10 Interrupt Enable */

/* ADC enable conversion */
#define ADC_CONVERSION_ENABLE       ENC                 /* ADC10 Enable Conversion */

/* ADC start conversion */
#define ADC_CONVERSION_START        ADC10SC

/* ADC clock prescaler */
#define ADC_CLOCK_PCLK_DIV1         ADC10DIV_0
#define ADC_CLOCK_PCLK_DIV2         ADC10DIV_1
#define ADC_CLOCK_PCLK_DIV3         ADC10DIV_2
#define ADC_CLOCK_PCLK_DIV4         ADC10DIV_3
#define ADC_CLOCK_PCLK_DIV5         ADC10DIV_4
#define ADC_CLOCK_PCLK_DIV6         ADC10DIV_5
#define ADC_CLOCK_PCLK_DIV7         ADC10DIV_6
#define ADC_CLOCK_PCLK_DIV8         ADC10DIV_7

/* ADC clock source */
#define ADC_OSC                     ADC10SSEL_0         /* Oscillicope              */
#define ADC_ACLK                    ADC10SSEL_1         /* Auxiliary clock          */
#define ADC_MCLK                    ADC10SSEL_2         /* Master clock             */
#define ADC_SMCLK                   ADC10SSEL_3         /* Sub-system master clock  */

/* ADC conversion sequence mode */
#define ADC_CHANNEL_CONVERSION_MODE             CONSEQ_0    /* Single channel single conversion */
#define ADC_SEQUENCE_CHANNEL_MODE               CONSEQ_1    /* Sequence of channels */
#define ADC_REPEAT_SINGLE_CHANNEL_MODE          CONSEQ_2    /* Repeat single channel */
#define ADC_REPEAT_SEQUENCE_CHANNEL_MODE        CONSEQ_3    /* Repeat sequence of channels */

typedef enum
{
    ADC_DISABLE,
    ADC_ENABLE, 
} __attribute__((__packed__)) ADC_Switch_u8;

/* Structure definition of ADC and regular group initialization */
typedef struct
{
    uint16_t        Channel;
    uint16_t        Pin;
    uint16_t        Format;
    ADC_Mode_u8     Mode;
} ADC_InitTypeDef;

// ADC Init
void ADC_init_void(ADC_InitTypeDef *ADC_Init);
void ADC_startSamplingAndConversion_void();
uint16_t ADC_getADCValue_u16();
uint8_t ADC_isADCBusy_u8();

#endif // __ADC_H