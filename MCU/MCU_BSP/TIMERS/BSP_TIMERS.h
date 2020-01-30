/*
************************************************************************
*
*   文件名称：BSP_TIMER.h
*   文件说明：该文件包含RTC相关配置
*   版    本：V1.0
*   修改记录：
*       版本号  日期            作者            说明
*       V1.0    2017-10-22      CJ              初次编写
*
*   Copyright  (C):CJ
*
************************************************************************
*/
#ifndef __BSP_TIMRS_H__
#define __BSP_TIMRS_H__

#include "BSP_DRIVE.h"

//基本定时器使能设置
/******************************************定时器6***********************************************/
#define D_TIMER6_EN                 0

#define D_TIMER6_AUTO_RELOAD_VALUE  2000		//定时器6自动重装载值，合法值0~65535
#define D_TIMER6_PRESCALER_VALUE	8399		    //定时器6预分频值，合法值0~65535

#define D_TIMER6_DMA_EN	            1			//定时器6DMA中断使能配置，0禁止，1使能
#define D_TIMER6_UPDATE_INT_EN	    1			//定时器6更新中断使能配置，0禁止，1使能

#define TIMER6_INTERRUPT_FLAG	    (TIM6->SR & 1)	//定时器6发生更新事件标志，发生为1，未发生为0

#define TIMER6_Priority             2

/******************************************定时器7**************************************************/
#define D_TIMER7_EN                 0

#define D_TIMER7_AUTO_RELOAD_VALUE  4000		//定时器7自动重装载值，合法值0~65535
#define D_TIMER7_PRESCALER_VALUE	8399		//定时器7预分频值，合法值0~65535

#define D_TIMER7_DMA_EN	            1			//定时器7DMA中断使能配置，0禁止，1使能
#define D_TIMER7_UPDATE_INT_EN	    1			//定时器7更新中断使能配置，0禁止，1使能

#define TIMER7_INTERRUPT_FLAG	    (TIM7->SR & 1)	//定时器7发生更新事件标志，发生为1，未发生为0

#define TIMER7_Priority             2


//通用定时器使能设置
/******************************************定时器2**************************************************/
#define D_TIMER2_EN                 0

#define D_TIMER2_AUTO_RELOAD_VALUE  2000		//定时器2自动重装载值，合法值0~65535
#define D_TIMER2_PRESCALER_VALUE	8399		//定时器2预分频值，合法值0~65535

#define D_TIMER2_DMA_EN	            1			//定时器2DMA中断使能配置，0禁止，1使能
#define D_TIMER2_UPDATE_INT_EN	    1			//定时器2更新中断使能配置，0禁止，1使能

#define TIMER2_INTERRUPT_FLAG	    (TIM2->SR & 1)	//定时器7发生更新事件标志，发生为1，未发生为0

#define TIMER2_Priority             2

/******************************************定时器3**************************************************/
#define D_TIMER3_EN                 0

#define D_TIMER3_AUTO_RELOAD_VALUE  4000		//定时器7自动重装载值，合法值0~65535
#define D_TIMER3_PRESCALER_VALUE	8399		//定时器7预分频值，合法值0~65535

#define D_TIMER3_DMA_EN	            1			//定时器7DMA中断使能配置，0禁止，1使能
#define D_TIMER3_UPDATE_INT_EN	    1			//定时器7更新中断使能配置，0禁止，1使能

#define TIMER3_INTERRUPT_FLAG	    (TIM3->SR & 1)	//定时器7发生更新事件标志，发生为1，未发生为0

#define TIMER3_Priority             2

/******************************************定时器4**************************************************/
#define D_TIMER4_EN                 0

#define D_TIMER4_AUTO_RELOAD_VALUE  2000		//定时器7自动重装载值，合法值0~65535
#define D_TIMER4_PRESCALER_VALUE	8399		//定时器7预分频值，合法值0~65535

#define D_TIMER4_DMA_EN	            1			//定时器7DMA中断使能配置，0禁止，1使能
#define D_TIMER4_UPDATE_INT_EN	    1			//定时器7更新中断使能配置，0禁止，1使能

#define TIMER4_INTERRUPT_FLAG	    (TIM4->SR & 1)	//定时器7发生更新事件标志，发生为1，未发生为0

#define TIMER4_Priority             2

/******************************************定时器5**************************************************/
#define D_TIMER5_EN                 0

#define D_TIMER5_AUTO_RELOAD_VALUE  4000		//定时器7自动重装载值，合法值0~65535
#define D_TIMER5_PRESCALER_VALUE	8399		//定时器7预分频值，合法值0~65535

#define D_TIMER5_DMA_EN	            1			//定时器7DMA中断使能配置，0禁止，1使能
#define D_TIMER5_UPDATE_INT_EN	    1			//定时器7更新中断使能配置，0禁止，1使能

#define TIMER5_INTERRUPT_FLAG	    (TIM5->SR & 1)	//定时器7发生更新事件标志，发生为1，未发生为0

#define TIMER5_Priority             2

/******************************************定时器9**************************************************/
#define D_TIMER9_EN                 0

#define D_TIMER9_AUTO_RELOAD_VALUE  2000		//定时器7自动重装载值，合法值0~65535
#define D_TIMER9_PRESCALER_VALUE	8399		//定时器7预分频值，合法值0~65535

#define D_TIMER9_DMA_EN	            1			//定时器7DMA中断使能配置，0禁止，1使能
#define D_TIMER9_UPDATE_INT_EN	    1			//定时器7更新中断使能配置，0禁止，1使能

#define TIMER9_INTERRUPT_FLAG	    (TIM9->SR & 1)	//定时器7发生更新事件标志，发生为1，未发生为0

#define TIMER9_Priority             2

/******************************************定时器10*************************************************/
#define D_TIMER10_EN                0

#define D_TIMER10_AUTO_RELOAD_VALUE 4000		//定时器7自动重装载值，合法值0~65535
#define D_TIMER10_PRESCALER_VALUE	8399		//定时器7预分频值，合法值0~65535

#define D_TIMER10_DMA_EN	        1			//定时器7DMA中断使能配置，0禁止，1使能
#define D_TIMER10_UPDATE_INT_EN	    1			//定时器7更新中断使能配置，0禁止，1使能

#define TIMER10_INTERRUPT_FLAG	    (TIM10->SR & 1)	//定时器7发生更新事件标志，发生为1，未发生为0

#define TIMER10_Priority             2

/******************************************定时器11*************************************************/
#define D_TIMER11_EN                0

#define D_TIMER11_AUTO_RELOAD_VALUE 2000		//定时器11自动重装载值，合法值0~65535
#define D_TIMER11_PRESCALER_VALUE	8399		//定时器11预分频值，合法值0~65535

#define D_TIMER11_DMA_EN	        1			//定时器11DMA中断使能配置，0禁止，1使能
#define D_TIMER11_UPDATE_INT_EN	    1			//定时器11更新中断使能配置，0禁止，1使能

#define TIMER11_INTERRUPT_FLAG	   (TIM4->SR & 1)	//定时器11发生更新事件标志，发生为1，未发生为0

#define TIMER11_Priority            2

/******************************************定时器12*************************************************/
#define D_TIMER12_EN                0

#define D_TIMER12_AUTO_RELOAD_VALUE 4000		//定时器7自动重装载值，合法值0~65535
#define D_TIMER12_PRESCALER_VALUE	8399		//定时器7预分频值，合法值0~65535

#define D_TIMER12_DMA_EN	        1			//定时器7DMA中断使能配置，0禁止，1使能
#define D_TIMER12_UPDATE_INT_EN	    1			//定时器7更新中断使能配置，0禁止，1使能

#define TIMER12_INTERRUPT_FLAG	    (TIM12->SR & 1)	//定时器7发生更新事件标志，发生为1，未发生为0

#define TIMER12_Priority             2

/******************************************定时器13*************************************************/
#define D_TIMER13_EN                0

#define D_TIMER13_AUTO_RELOAD_VALUE 2000		//定时器7自动重装载值，合法值0~65535
#define D_TIMER13_PRESCALER_VALUE	8399		//定时器7预分频值，合法值0~65535

#define D_TIMER13_DMA_EN	        1	        //定时器7DMA中断使能配置，0禁止，1使能
#define D_TIMER13_UPDATE_INT_EN	    1			//定时器7更新中断使能配置，0禁止，1使能

#define TIMER13_INTERRUPT_FLAG	   (TIM13->SR & 1)	//定时器7发生更新事件标志，发生为1，未发生为0

#define TIMER13_Priority            2
/******************************************定时器14*************************************************/
#define D_TIMER14_EN                0

#define D_TIMER14_AUTO_RELOAD_VALUE 4000		//定时器7自动重装载值，合法值0~65535
#define D_TIMER14_PRESCALER_VALUE	8399		//定时器7预分频值，合法值0~65535

#define D_TIMER14_DMA_EN	        1			//定时器7DMA中断使能配置，0禁止，1使能
#define D_TIMER14_UPDATE_INT_EN	    1			//定时器7更新中断使能配置，0禁止，1使能

#define TIMER14_INTERRUPT_FLAG	   (TIM14->SR & 1)	//定时器7发生更新事件标志，发生为1，未发生为0

#define TIMER14_Priority            2

//高级控制定时器使能设置
#define D_TIMER1_EN                 1
#define D_TIMER8_EN                 1

#endif


void BSP_Timers_Init(void);

/*************************Copyright:CJ  (END OF FILE)********************/
