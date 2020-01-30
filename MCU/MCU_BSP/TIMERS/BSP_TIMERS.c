/*
************************************************************************
*
*   文件名称：BSP_TIMERS.c
*   文件说明：定时器相关驱动
*   版    本：V1.0
*   修改记录：
*       版本号  日期            作者            说明
*       V1.0    2017-10-22      CJ              初次编写
*
*   Copyright  (C):CJ
*
************************************************************************
*/
#include "BSP_TIMERS.h"

void BSP_Timers_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    
/*************************基本定时器初始化****************************/
#if D_TIMER6_EN
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);                     //开启定时器6时钟
    
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER6_AUTO_RELOAD_VALUE;
    TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER6_PRESCALER_VALUE; 
    
    TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);

#if D_TIMER6_UPDATE_INT_EN    
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER6_Priority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
    
    NVIC_Init(&NVIC_InitStructure);
#endif
    
    TIM6 -> DIER &= ~(1<<8);                                                //清除DMA中断使能位
    TIM6 -> DIER |= D_TIMER6_DMA_EN;                                        //设置DMA中断使能位
    TIM6 -> DIER &= 1;
    TIM6 -> DIER |= D_TIMER6_UPDATE_INT_EN;                                 //更新中断设置
    
    TIM_Cmd(TIM6, ENABLE);
    
#endif
///////////////////////////////////////////////////////////////////////
#if D_TIMER7_EN

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);                     //开启定时器6时钟
    
    TIM_TimeBaseInitStruct.TIM_Period =  D_TIMER7_AUTO_RELOAD_VALUE;
    TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER7_PRESCALER_VALUE; 
    
    TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStruct);
    
#if D_TIMER7_UPDATE_INT_EN    
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER7_Priority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
    
    NVIC_Init(&NVIC_InitStructure);

    TIM7 -> DIER &= ~(1<<8);                                                //清除DMA中断使能位
    TIM7 -> DIER |= D_TIMER7_DMA_EN;                                        //设置DMA中断使能位
    TIM7 -> DIER &= 1;
    TIM7 -> DIER |= D_TIMER7_UPDATE_INT_EN;                                 //更新中断设置
#endif    

    TIM_Cmd(TIM7, ENABLE);
#endif    
/*******************************************************************/

/************************通用定时器初始化***************************/
#if D_TIMER2_EN

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                 //使能TIM2时钟

    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;             //时钟不分频
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;         //向上计数
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER2_AUTO_RELOAD_VALUE;      //自动重装载值
    TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER3_PRESCALER_VALUE;     //预分频系数

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);                     //根据结构体数据初始化定时器时基寄存器
    
#if D_TIMER2_UPDATE_INT_EN

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                           //使能更新中断

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER2_UPDATE_INT_EN;      //定时器2中断使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER2_Priority;//定时2优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;                   //子优先级
    
    NVIC_Init(&NVIC_InitStructure);
#endif 
 
    TIM_Cmd(TIM2, ENABLE);

    
#endif
//////////////////////////////////////////////////////////////////////

#if D_TIMER3_EN

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);                     //使能TIM3时钟
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER3_AUTO_RELOAD_VALUE; 	    //自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER3_PRESCALER_VALUE;        //预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);                         //初始化TIM3
	
#if D_TIMER3_UPDATE_INT_EN   

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                                //允许定时器3更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER3_Priority;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER3_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif

    TIM_Cmd(TIM3,ENABLE); //使能定时器3
    
#endif 
    
#if D_TIMER4_EN

     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);                     //使能TIM4时钟
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER4_AUTO_RELOAD_VALUE; 	    //自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER4_PRESCALER_VALUE;        //预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);                         //初始化TIM4

#if D_TIMER4_UPDATE_INT_EN 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);                                //允许定时器4更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER4_Priority;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER3_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif

    TIM_Cmd(TIM4,ENABLE); //使能定时器3
    
    
#endif
//////////////////////////////////////////////////////////////////////
#if D_TIMER5_EN
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);                     //使能TIM5时钟
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER5_AUTO_RELOAD_VALUE; 	    //自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER5_PRESCALER_VALUE;        //预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);                         //初始化TIM5
    
#if D_TIMER5_UPDATE_INT_EN 	

	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);                                //允许定时器5更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; //定时器5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER5_Priority;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER5_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif     
    
    TIM_Cmd(TIM5,ENABLE); //使能定时器5
    
#endif 
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#if D_TIMER9_EN
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);                     //使能TIM9时钟
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER9_AUTO_RELOAD_VALUE; 	    //自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER9_PRESCALER_VALUE;        //预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseInitStruct);                         //初始化TIM9

#if D_TIMER9_UPDATE_INT_EN
	TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE);                                //允许定时器9更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn; //定时器9中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER9_Priority;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER9_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif

    TIM_Cmd(TIM9,ENABLE); //使能定时器9
    
#endif
//////////////////////////////////////////////////////////////////////
#if D_TIMER10_EN
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);                    //使能TIM10时钟
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER10_AUTO_RELOAD_VALUE; 	    //自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER10_PRESCALER_VALUE;       //预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM10,&TIM_TimeBaseInitStruct);                         //初始化TIM10

#if D_TIMER10_UPDATE_INT_EN
	TIM_ITConfig(TIM10,TIM_IT_Update,ENABLE);                                //允许定时器10更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;                //定时器10中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER10_Priority;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                   //子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER10_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif    
    
    TIM_Cmd(TIM10,ENABLE);                                                  //使能定时器10
    
#endif
//////////////////////////////////////////////////////////////////////
#if D_TIMER11_EN
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);                    //使能TIM10时钟
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER11_AUTO_RELOAD_VALUE; 	    //自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER11_PRESCALER_VALUE;       //预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStruct);                         //初始化TIM11
    
#if D_TIMER11_UPDATE_INT_EN	

	TIM_ITConfig(TIM11,TIM_IT_Update,ENABLE);                                //允许定时器11更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn;            //定时器11中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER11_Priority;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                   //子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER10_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif    
    
    TIM_Cmd(TIM11,ENABLE);                                                  //使能定时器11
    
#endif 
//////////////////////////////////////////////////////////////////////    
#if D_TIMER12_EN
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);                    //使能TIM12时钟
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER12_AUTO_RELOAD_VALUE; 	    //自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER12_PRESCALER_VALUE;       //预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseInitStruct);                         //初始化TIM12

#if D_TIMER12_UPDATE_INT_EN

	TIM_ITConfig(TIM12,TIM_IT_Update,ENABLE);                                //允许定时器12更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn;            //定时器12中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER11_Priority;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                   //子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER10_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif    
    
    TIM_Cmd(TIM12,ENABLE);                                                  //使能定时器12
    
#endif
//////////////////////////////////////////////////////////////////////
#if D_TIMER13_EN

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);                    //使能TIM13时钟
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER13_AUTO_RELOAD_VALUE; 	    //自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER13_PRESCALER_VALUE;       //预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseInitStruct);                         //初始化TIM13
	
	TIM_ITConfig(TIM13,TIM_IT_Update,ENABLE);                                //允许定时器13更新中断

#if D_TIMER13_UPDATE_INT_EN
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;                //定时器13中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER13_Priority;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                   //子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER10_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif    
    
    TIM_Cmd(TIM13,ENABLE);                                                  //使能定时器13
    
#endif 
/////////////////////////////////////////////////////////////////////    
#if D_TIMER14_EN
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);                    //使能TIM14时钟
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER14_AUTO_RELOAD_VALUE; 	    //自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER14_PRESCALER_VALUE;       //预分频系数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStruct);                         //初始化TIM14

#if D_TIMER14_UPDATE_INT_EN
	TIM_ITConfig(TIM14,TIM_IT_Update,ENABLE);                                //允许定时器14更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_TRG_COM_TIM14_IRQn;                //定时器14中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER14_Priority;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                   //子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER10_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif 
 
    TIM_Cmd(TIM14,ENABLE);                                                  //使能定时器14
    
#endif

/******************************************************************/

/************************高级定时器初始化**************************/
#if D_TIMER1_EN
    
#endif 
/////////////////////////////////////////////////////////////////////    
#if D_TIMER8_EN
    
#endif
    
/******************************************************************/    
}

#if D_TIMER6_EN
/*
********************************************************************
*	函 数 名: TIM6_DAC_IRQHandler
*	功能说明: 定时器6中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
void TIM6_DAC_IRQHandler(void)
{
    TIM_Cmd(TIM6, DISABLE);
	if(TIM_GetITStatus(TIM6,TIM_IT_Update) == SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
        D_DEBUG_printf("TIM6时间到了12");
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);  //清除中断标志位
    TIM_Cmd(TIM6, ENABLE);
}

#endif

#if D_TIMER7_EN
/*
********************************************************************
*	函 数 名: TIM7_IRQHandler
*	功能说明: 定时器6中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
void TIM7_IRQHandler(void)
{
    TIM_Cmd(TIM7, DISABLE);
	if(TIM_GetITStatus(TIM7,TIM_IT_Update) == SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
        D_DEBUG_printf("TIM7时间到了IRQHandler");
	}
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //清除中断标志位
    TIM_Cmd(TIM7, ENABLE);
}
#endif

#if D_TIMER2_EN
/*
********************************************************************
*	函 数 名: TIM2_IRQHandler
*	功能说明: 定时器2中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
        D_DEBUG_printf("TIM2时间到了IRQHandler");
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}
#endif

#if D_TIMER3_EN
/*
********************************************************************
*	函 数 名: TIM3_IRQHandler
*	功能说明: 定时器3中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
        D_DEBUG_printf("TIM3时间到了IRQHandler");
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}
#endif

#if D_TIMER4_EN
/*
********************************************************************
*	函 数 名: TIM4_IRQHandler
*	功能说明: 定时器4中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
//void TIM4_IRQHandler(void) 
//{
//	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
//	{
//		LED1=!LED1;//DS1翻转
//	}
//	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
//}

#endif

#if D_TIMER5_EN
/*
********************************************************************
*	函 数 名: TIM5_IRQHandler
*	功能说明: 定时器5中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
        D_DEBUG_printf("TIM5时间到了IRQHandler");
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}
#endif

#if D_TIMER9_EN
/*
********************************************************************
*	函 数 名: TIM9_IRQHandler
*	功能说明: 定时器9中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
void TIM1_BRK_TIM9_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM9,TIM_IT_Update)==SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
        D_DEBUG_printf("TIM9时间到了IRQHandler");
	}
	TIM_ClearITPendingBit(TIM9,TIM_IT_Update);  //清除中断标志位
}
#endif

#if D_TIMER10_EN
/*
********************************************************************
*	函 数 名: TIM10_IRQHandler
*	功能说明: 定时器10中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
void TIM1_UP_TIM10_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM10,TIM_IT_Update)==SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
        D_DEBUG_printf("TIM10时间到了IRQHandler");
	}
	TIM_ClearITPendingBit(TIM10,TIM_IT_Update);  //清除中断标志位
}
#endif

#if D_TIMER11_EN
/*
********************************************************************
*	函 数 名: TIM11_IRQHandler
*	功能说明: 定时器11中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM11,TIM_IT_Update)==SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
        D_DEBUG_printf("TIM11时间到了IRQHandler");
	}
	TIM_ClearITPendingBit(TIM11,TIM_IT_Update);  //清除中断标志位
}

#endif

#if D_TIMER12_EN
/*
********************************************************************
*	函 数 名: TIM12_IRQHandler
*	功能说明: 定时器12中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
void TIM8_BRK_TIM12_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM12,TIM_IT_Update)==SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
        D_DEBUG_printf("TIM12时间到了IRQHandler");
	}
	TIM_ClearITPendingBit(TIM12,TIM_IT_Update);  //清除中断标志位
}
#endif

#if D_TIMER13_EN
/*
********************************************************************
*	函 数 名: TIM13_IRQHandler
*	功能说明: 定时器13中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
void TIM8_UP_TIM13_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM13,TIM_IT_Update)==SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
        D_DEBUG_printf("TIM13时间到了IRQHandler");
	}
	TIM_ClearITPendingBit(TIM13,TIM_IT_Update);  //清除中断标志位
}
#endif

#if D_TIMER14_EN
/*
********************************************************************
*	函 数 名: TIM14_IRQHandler
*	功能说明: 定时器14中断服务函数
*	形    参: 无
*	返 回 值: 无
********************************************************************
*/
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM14,TIM_IT_Update)==SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
        D_DEBUG_printf("TIM14时间到了IRQHandler");
	}
	TIM_ClearITPendingBit(TIM14,TIM_IT_Update);  //清除中断标志位
}
#endif

/*********************Copyright:CJ  (END OF FILE)******************/
