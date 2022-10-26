#ifndef __GENERAL_DEFINES_H
#define __GENERAL_DEFINES_H

#include <stdint.h>

#define OFF         0
#define ON          1

typedef enum
{
    FALSE,
    TRUE,
} __attribute__((packed)) boolean;

#define __IO                volatile


#endif // __GENERAL_DEFINES_H
