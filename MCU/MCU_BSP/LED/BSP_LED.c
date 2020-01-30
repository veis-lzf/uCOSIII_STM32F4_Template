#include "BSP_LED.h"

void BSP_LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);                //使能GPIOD时钟
    
    GPIO_InitStruct.GPIO_Mode   =   GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType  =   GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin    =   GPIO_Pin_12 |GPIO_Pin_13;
    GPIO_InitStruct.GPIO_PuPd   =   GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed  =   GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOD, &GPIO_InitStruct);
    /*初始化LED灯为熄灭状态*/
    GPIO_SetBits(GPIOD, GPIO_Pin_12);
    GPIO_ResetBits(GPIOD, GPIO_Pin_13);
}
