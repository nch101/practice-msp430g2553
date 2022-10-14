#include <stdint.h>
#include <msp430.h>

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

#define ADC10_CTL0          ((ADC_ADC10CTL0_Reg *) &ADC10CTL0)
#define ADC10_CTL1          ((ADC_ADC10CTL1_Reg *) &ADC10CTL1)
#define ADC10_DTC0          ((ADC_ADC10DTC0_Reg *) &ADC10DTC0)
