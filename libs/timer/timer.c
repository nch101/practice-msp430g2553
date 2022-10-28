#include "timer_a.h"
#include "timer_a_config.h"

static void Timer_resetTimerRegister_void()
{
    TIMER_A_CONTROL_REG->reg        = 0;
    TIMER_A_CC_CONTROL_REG_0->reg   = 0;
    TIMER_A_CC_CONTROL_REG_1->reg   = 0;
    TIMER_A_CC_CONTROL_REG_2->reg   = 0;
};

static void Timer_defaultInit_void()
{
    TIMER_A_CONTROL_REG->reg =  TIMER_CLK_SRC_DEFAULT \
                                | TIMER_INPUT_DIVIDER_DEFAULT \
                                | TIMER_MODE_CONTROL_DEFAULT;

#if (MCU_CONFIG_TIMER_A_IRQ_EN == ON)
    TIMER_A_CONTROL_REG->reg =  TIMER_A_INTERRUPT_ENABLE;
#endif // (MCU_CONFIG_TIMER_A_IRQ_EN == ON)
}