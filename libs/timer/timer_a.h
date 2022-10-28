#ifndef __TIMER_A_H
#define __TIMER_A_H

#include <stdint.h>
#include <msp430.h>

#include "mcu_config.h"


/**
 * @brief Timer_A Control Register
 * 
 */
typedef union 
{
    __IO uint16_t reg;
    struct
    {
        __IO uint16_t IFG       : 1; /* [0..0] Timer_A interrupt flag. */
        __IO uint16_t IE        : 1; /* [1..1] Timer_A interrupt enable. */
        __IO uint16_t CLR       : 1; /* [2..2] Timer_A clear.
                                      * Setting this bit resets TAR, the clock divider,
                                      * and the count direction. The TACLR bit is 
                                      * automatically reset and always reads as zero. */
        __IO uint16_t           : 1;
        __IO uint16_t MCx       : 2; /* [4..5] Mode control. */
        __IO uint16_t IDx       : 2; /* [6..7] Input divider. */
        __IO uint16_t SSELx     : 2; /* [8..9] Timer_A clock source select */
        __IO uint16_t           : 6;
    } bit;

} Timer_TACTL_Reg;


/**
 * @brief Timer_A Capture/Compare Control x Register
 * 
 */
typedef union
{
    __IO uint16_t reg;
    struct
    {
        __IO uint16_t IFG       : 1; /* [0..0] Capture/compare interrupt flag. */
        __IO uint16_t OV        : 1; /* [1..1] Capture overflow. This bit indicates a capture
                                      * overflow occurred. */
        __IO uint16_t OUTPUT    : 1; /* [2..2] Output. For output mode 0, this bit directly controls 
                                      * the state of the output. */
        __IO uint16_t INPUT     : 1; /* [3..3] Capture/compare input. The selected input signal 
                                      * can be read by this bit. */
        __IO uint16_t IE        : 1; /* [4..4] Capture/compare interrupt enable. This bit enables
                                      * the interrupt request of the corresponding CCIFG flag. */
        __IO uint16_t OUTMODx   : 3; /* [5..7] Output mode. Modes 2, 3, 6, and 7 are not useful for 
                                      * TACCR0, because EQUx = EQU0.
                                      * 000b = OUT bit value
                                      * 001b = Set
                                      * 010b = Toggle/reset
                                      * 011b = Set/reset
                                      * 100b = Toggle
                                      * 101b = Reset
                                      * 110b = Toggle/set
                                      * 111b = Reset/set */
        __IO uint16_t MODE      : 1; /* [8..8] Compare/Capture mode */
        __IO uint16_t           : 1;
        __IO uint16_t SYNC_INPUT: 1; /* [10..10] Synchronized capture/compare input. The selected CCI input signal
                                      * is latched with the EQUx signal and can be read via this bit */
        __IO uint16_t SYNC_SRC  : 1; /* [11..11] Synchronize capture source. This bit is used to synchronize the
                                      * capture input signal with the timer clock. */
        __IO uint16_t INPUT_SEL : 2; /* [12..13] Capture/compare input select. These bits select the TACCRx
                                      * input signal. See the device-specific data sheet for specific signal
                                      * connections.*/
        __IO uint16_t CAP_MODE  : 2; /* [14..15] Capture mode 
                                      * 00b = No capture
                                      * 01b = Capture on rising edge
                                      * 10b = Capture on falling edge
                                      * 11b = Capture on both rising and falling edges */
    } bit;

} Timer_TACCTLx_Reg;

#define TIMER_A_CONTROL_REG                 ((Timer_TACTL_Reg *) &TACTL)
#define TIMER_A_CC_CONTROL_REG_0            ((Timer_TACCTLx_Reg *) &TACCTL0)
#define TIMER_A_CC_CONTROL_REG_1            ((Timer_TACCTLx_Reg *) &TACCTL1)
#define TIMER_A_CC_CONTROL_REG_2            ((Timer_TACCTLx_Reg *) &TACCTL2)


#define TIMER_A_INTERRUPT_ENABLE            TAIE

/**
 * @brief Timer A clock source select
 * 
 */
#define TIMER_TACLK_CLOCK_SOURCE        TASSEL_0
#define TIMER_ACLK_CLOCK_SOURCE         TASSEL_1
#define TIMER_SMCLK_CLOCK_SOURCE        TASSEL_2
#define TIMER_INCLK_CLOCK_SOURCE        TASSEL_3

/**
 * @brief Timer A input divider
 * 
 */
#define TIMER_INPUT_DIV1                ID_0 /* Timer A input divider: 0 - /1 */
#define TIMER_INPUT_DIV2                ID_1 /* Timer A input divider: 1 - /2 */
#define TIMER_INPUT_DIV4                ID_2 /* Timer A input divider: 2 - /4 */
#define TIMER_INPUT_DIV8                ID_3 /* Timer A input divider: 3 - /8 */

/**
 * @brief Timer Mode Control
 * 
 */
#define TIMER_STOP_MODE                 MC_0 /* The timer is halted. */
#define TIMER_UP_MODE                   MC_1 /* The timer repeatedly counts from zero to the value of TACCR0. */
#define TIMER_CONTINUOUS_MODE           MC_2 /* The timer repeatedly counts from zero to 0FFFFh. */
#define TIMER_UP_DOWN_MODE              MC_3 /* The timer repeatedly counts from zero up to the value of TACCR0 and back down to zero. */

/**
 * @brief PWM output mode
 * 
 */
#define TIMER_OUTPUT_MODE               OUTMOD_0 /*  */
#define TIMER_SET_MODE                  OUTMOD_1 /*  */
#define TIMER_TOGGLE_RESET_MODE         OUTMOD_2 /*  */
#define TIMER_SET_RESET_MODE            OUTMOD_3 /*  */
#define TIMER_TOGGLE_MODE               OUTMOD_4 /*  */
#define TIMER_RESET_MODE                OUTMOD_5 /*  */
#define TIMER_TOGGLE_SET_MODE           OUTMOD_6 /*  */
#define TIMER_RESET_SET_MODE            OUTMOD_7 /*  */

/**
 * @brief 
 * 
 */
typedef struct
{

} Timer_InitTypeDef;


#endif // __TIMER_A_H
