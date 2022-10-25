#include "gpio.h"

GPIO_InitTypeDef led10, button13;

int main(void) {   
    // stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    led10.Base  = GPIO_1;
    led10.Pin   = GPIO_PIN_0;
    led10.Mode  = GPIO_MODE_OUTPUT;
    led10.Pull  = GPIO_PULLDOWN;
    GPIO_init_void(&led10);
    GPIO_setOutputSignal_void(&led10, GPIO_HIGH);

    button13.Base   = GPIO_1;
    button13.Pin    = GPIO_PIN_3;
    button13.Mode   = GPIO_MODE_INPUT;
    button13.Pull   = GPIO_PULLUP;
    GPIO_init_void(&button13);

    while(1)
    {
        if (GPIO_getInputSignal_u8(&button13) == GPIO_HIGH)
        {
            GPIO_toggleOutputSignal_void(&led10);
            __delay_cycles(220000);
        }

        __delay_cycles(220000);
    }
}
