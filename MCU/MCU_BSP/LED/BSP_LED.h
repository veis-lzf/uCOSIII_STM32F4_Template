#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "sys.h"

#define LED0    PDout(12)
#define LED1    PDout(13)

void BSP_LED_Init(void);

#endif
