#include <msp430.h>
#include "gpio.h"

int main(void) {
    volatile int i;
    
    // stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    GPIO_InitTypeDef GPIO_Temp;

    GPIO_Temp.Pin = GPIO_PIN_0;
    GPIO_Temp.Mode = GPIO_MODE_OUTPUT;
    GPIO_Temp.Pull = GPIO_PULLDOWN;
    GPIO(GPIO_1, GPIO_Temp);

    GPIO_setOutputSignal_void(GPIO_HIGH);

    while(1)
    {
        GPIO_toggleOutputSignal_void();
        for (i = 0; i < 0x6000; i++);
    }
}
