#ifndef __MCU_CONFIG_H
#define __MCU_CONFIG_H

#include <stdint.h>

typedef enum
{
    FALSE,
    TRUE,
} __attribute__((packed)) boolean;

#define OFF         0
#define ON          1

#define MCU_CONFIG_PORT1_EXTI_IRQ_EN                OFF
#define MCU_CONFIG_PORT2_EXTI_IRQ_EN                OFF

#endif // __MCU_CONFIG_H
