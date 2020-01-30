/*
************************************************************************
*
*   �ļ����ƣ�BSP_TIMERS.c
*   �ļ�˵������ʱ���������
*   ��    ����V1.0
*   �޸ļ�¼��
*       �汾��  ����            ����            ˵��
*       V1.0    2017-10-22      CJ              ���α�д
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
    
/*************************������ʱ����ʼ��****************************/
#if D_TIMER6_EN
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);                     //������ʱ��6ʱ��
    
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
    
    TIM6 -> DIER &= ~(1<<8);                                                //���DMA�ж�ʹ��λ
    TIM6 -> DIER |= D_TIMER6_DMA_EN;                                        //����DMA�ж�ʹ��λ
    TIM6 -> DIER &= 1;
    TIM6 -> DIER |= D_TIMER6_UPDATE_INT_EN;                                 //�����ж�����
    
    TIM_Cmd(TIM6, ENABLE);
    
#endif
///////////////////////////////////////////////////////////////////////
#if D_TIMER7_EN

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);                     //������ʱ��6ʱ��
    
    TIM_TimeBaseInitStruct.TIM_Period =  D_TIMER7_AUTO_RELOAD_VALUE;
    TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER7_PRESCALER_VALUE; 
    
    TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStruct);
    
#if D_TIMER7_UPDATE_INT_EN    
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER7_Priority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
    
    NVIC_Init(&NVIC_InitStructure);

    TIM7 -> DIER &= ~(1<<8);                                                //���DMA�ж�ʹ��λ
    TIM7 -> DIER |= D_TIMER7_DMA_EN;                                        //����DMA�ж�ʹ��λ
    TIM7 -> DIER &= 1;
    TIM7 -> DIER |= D_TIMER7_UPDATE_INT_EN;                                 //�����ж�����
#endif    

    TIM_Cmd(TIM7, ENABLE);
#endif    
/*******************************************************************/

/************************ͨ�ö�ʱ����ʼ��***************************/
#if D_TIMER2_EN

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                 //ʹ��TIM2ʱ��

    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;             //ʱ�Ӳ���Ƶ
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;         //���ϼ���
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER2_AUTO_RELOAD_VALUE;      //�Զ���װ��ֵ
    TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER3_PRESCALER_VALUE;     //Ԥ��Ƶϵ��

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);                     //���ݽṹ�����ݳ�ʼ����ʱ��ʱ���Ĵ���
    
#if D_TIMER2_UPDATE_INT_EN

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                           //ʹ�ܸ����ж�

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER2_UPDATE_INT_EN;      //��ʱ��2�ж�ʹ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER2_Priority;//��ʱ2���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;                   //�����ȼ�
    
    NVIC_Init(&NVIC_InitStructure);
#endif 
 
    TIM_Cmd(TIM2, ENABLE);

    
#endif
//////////////////////////////////////////////////////////////////////

#if D_TIMER3_EN

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);                     //ʹ��TIM3ʱ��
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER3_AUTO_RELOAD_VALUE; 	    //�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER3_PRESCALER_VALUE;        //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);                         //��ʼ��TIM3
	
#if D_TIMER3_UPDATE_INT_EN   

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                                //����ʱ��3�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER3_Priority;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER3_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif

    TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
    
#endif 
    
#if D_TIMER4_EN

     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);                     //ʹ��TIM4ʱ��
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER4_AUTO_RELOAD_VALUE; 	    //�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER4_PRESCALER_VALUE;        //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);                         //��ʼ��TIM4

#if D_TIMER4_UPDATE_INT_EN 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);                                //����ʱ��4�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER4_Priority;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER3_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif

    TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��3
    
    
#endif
//////////////////////////////////////////////////////////////////////
#if D_TIMER5_EN
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);                     //ʹ��TIM5ʱ��
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER5_AUTO_RELOAD_VALUE; 	    //�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER5_PRESCALER_VALUE;        //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);                         //��ʼ��TIM5
    
#if D_TIMER5_UPDATE_INT_EN 	

	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);                                //����ʱ��5�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; //��ʱ��5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER5_Priority;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER5_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif     
    
    TIM_Cmd(TIM5,ENABLE); //ʹ�ܶ�ʱ��5
    
#endif 
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#if D_TIMER9_EN
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);                     //ʹ��TIM9ʱ��
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER9_AUTO_RELOAD_VALUE; 	    //�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER9_PRESCALER_VALUE;        //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseInitStruct);                         //��ʼ��TIM9

#if D_TIMER9_UPDATE_INT_EN
	TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE);                                //����ʱ��9�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn; //��ʱ��9�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER9_Priority;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER9_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif

    TIM_Cmd(TIM9,ENABLE); //ʹ�ܶ�ʱ��9
    
#endif
//////////////////////////////////////////////////////////////////////
#if D_TIMER10_EN
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);                    //ʹ��TIM10ʱ��
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER10_AUTO_RELOAD_VALUE; 	    //�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER10_PRESCALER_VALUE;       //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM10,&TIM_TimeBaseInitStruct);                         //��ʼ��TIM10

#if D_TIMER10_UPDATE_INT_EN
	TIM_ITConfig(TIM10,TIM_IT_Update,ENABLE);                                //����ʱ��10�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;                //��ʱ��10�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER10_Priority;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                   //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER10_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif    
    
    TIM_Cmd(TIM10,ENABLE);                                                  //ʹ�ܶ�ʱ��10
    
#endif
//////////////////////////////////////////////////////////////////////
#if D_TIMER11_EN
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);                    //ʹ��TIM10ʱ��
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER11_AUTO_RELOAD_VALUE; 	    //�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER11_PRESCALER_VALUE;       //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStruct);                         //��ʼ��TIM11
    
#if D_TIMER11_UPDATE_INT_EN	

	TIM_ITConfig(TIM11,TIM_IT_Update,ENABLE);                                //����ʱ��11�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_TIM11_IRQn;            //��ʱ��11�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER11_Priority;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                   //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER10_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif    
    
    TIM_Cmd(TIM11,ENABLE);                                                  //ʹ�ܶ�ʱ��11
    
#endif 
//////////////////////////////////////////////////////////////////////    
#if D_TIMER12_EN
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);                    //ʹ��TIM12ʱ��
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER12_AUTO_RELOAD_VALUE; 	    //�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER12_PRESCALER_VALUE;       //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseInitStruct);                         //��ʼ��TIM12

#if D_TIMER12_UPDATE_INT_EN

	TIM_ITConfig(TIM12,TIM_IT_Update,ENABLE);                                //����ʱ��12�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_TIM12_IRQn;            //��ʱ��12�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER11_Priority;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                   //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER10_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif    
    
    TIM_Cmd(TIM12,ENABLE);                                                  //ʹ�ܶ�ʱ��12
    
#endif
//////////////////////////////////////////////////////////////////////
#if D_TIMER13_EN

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);                    //ʹ��TIM13ʱ��
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER13_AUTO_RELOAD_VALUE; 	    //�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER13_PRESCALER_VALUE;       //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseInitStruct);                         //��ʼ��TIM13
	
	TIM_ITConfig(TIM13,TIM_IT_Update,ENABLE);                                //����ʱ��13�����ж�

#if D_TIMER13_UPDATE_INT_EN
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_TIM13_IRQn;                //��ʱ��13�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER13_Priority;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                   //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER10_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif    
    
    TIM_Cmd(TIM13,ENABLE);                                                  //ʹ�ܶ�ʱ��13
    
#endif 
/////////////////////////////////////////////////////////////////////    
#if D_TIMER14_EN
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);                    //ʹ��TIM14ʱ��
	
    TIM_TimeBaseInitStruct.TIM_Period = D_TIMER14_AUTO_RELOAD_VALUE; 	    //�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = D_TIMER14_PRESCALER_VALUE;       //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;            //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStruct);                         //��ʼ��TIM14

#if D_TIMER14_UPDATE_INT_EN
	TIM_ITConfig(TIM14,TIM_IT_Update,ENABLE);                                //����ʱ��14�����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM8_TRG_COM_TIM14_IRQn;                //��ʱ��14�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMER14_Priority;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                   //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = D_TIMER10_UPDATE_INT_EN;
	NVIC_Init(&NVIC_InitStructure);
#endif 
 
    TIM_Cmd(TIM14,ENABLE);                                                  //ʹ�ܶ�ʱ��14
    
#endif

/******************************************************************/

/************************�߼���ʱ����ʼ��**************************/
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
*	�� �� ��: TIM6_DAC_IRQHandler
*	����˵��: ��ʱ��6�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
void TIM6_DAC_IRQHandler(void)
{
    TIM_Cmd(TIM6, DISABLE);
	if(TIM_GetITStatus(TIM6,TIM_IT_Update) == SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
        D_DEBUG_printf("TIM6ʱ�䵽��12");
	}
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);  //����жϱ�־λ
    TIM_Cmd(TIM6, ENABLE);
}

#endif

#if D_TIMER7_EN
/*
********************************************************************
*	�� �� ��: TIM7_IRQHandler
*	����˵��: ��ʱ��6�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
void TIM7_IRQHandler(void)
{
    TIM_Cmd(TIM7, DISABLE);
	if(TIM_GetITStatus(TIM7,TIM_IT_Update) == SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
        D_DEBUG_printf("TIM7ʱ�䵽��IRQHandler");
	}
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);  //����жϱ�־λ
    TIM_Cmd(TIM7, ENABLE);
}
#endif

#if D_TIMER2_EN
/*
********************************************************************
*	�� �� ��: TIM2_IRQHandler
*	����˵��: ��ʱ��2�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
        D_DEBUG_printf("TIM2ʱ�䵽��IRQHandler");
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־λ
}
#endif

#if D_TIMER3_EN
/*
********************************************************************
*	�� �� ��: TIM3_IRQHandler
*	����˵��: ��ʱ��3�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
        D_DEBUG_printf("TIM3ʱ�䵽��IRQHandler");
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}
#endif

#if D_TIMER4_EN
/*
********************************************************************
*	�� �� ��: TIM4_IRQHandler
*	����˵��: ��ʱ��4�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
//void TIM4_IRQHandler(void) 
//{
//	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
//	{
//		LED1=!LED1;//DS1��ת
//	}
//	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //����жϱ�־λ
//}

#endif

#if D_TIMER5_EN
/*
********************************************************************
*	�� �� ��: TIM5_IRQHandler
*	����˵��: ��ʱ��5�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
        D_DEBUG_printf("TIM5ʱ�䵽��IRQHandler");
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־λ
}
#endif

#if D_TIMER9_EN
/*
********************************************************************
*	�� �� ��: TIM9_IRQHandler
*	����˵��: ��ʱ��9�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
void TIM1_BRK_TIM9_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM9,TIM_IT_Update)==SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
        D_DEBUG_printf("TIM9ʱ�䵽��IRQHandler");
	}
	TIM_ClearITPendingBit(TIM9,TIM_IT_Update);  //����жϱ�־λ
}
#endif

#if D_TIMER10_EN
/*
********************************************************************
*	�� �� ��: TIM10_IRQHandler
*	����˵��: ��ʱ��10�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
void TIM1_UP_TIM10_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM10,TIM_IT_Update)==SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
        D_DEBUG_printf("TIM10ʱ�䵽��IRQHandler");
	}
	TIM_ClearITPendingBit(TIM10,TIM_IT_Update);  //����жϱ�־λ
}
#endif

#if D_TIMER11_EN
/*
********************************************************************
*	�� �� ��: TIM11_IRQHandler
*	����˵��: ��ʱ��11�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM11,TIM_IT_Update)==SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
        D_DEBUG_printf("TIM11ʱ�䵽��IRQHandler");
	}
	TIM_ClearITPendingBit(TIM11,TIM_IT_Update);  //����жϱ�־λ
}

#endif

#if D_TIMER12_EN
/*
********************************************************************
*	�� �� ��: TIM12_IRQHandler
*	����˵��: ��ʱ��12�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
void TIM8_BRK_TIM12_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM12,TIM_IT_Update)==SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
        D_DEBUG_printf("TIM12ʱ�䵽��IRQHandler");
	}
	TIM_ClearITPendingBit(TIM12,TIM_IT_Update);  //����жϱ�־λ
}
#endif

#if D_TIMER13_EN
/*
********************************************************************
*	�� �� ��: TIM13_IRQHandler
*	����˵��: ��ʱ��13�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
void TIM8_UP_TIM13_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM13,TIM_IT_Update)==SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
        D_DEBUG_printf("TIM13ʱ�䵽��IRQHandler");
	}
	TIM_ClearITPendingBit(TIM13,TIM_IT_Update);  //����жϱ�־λ
}
#endif

#if D_TIMER14_EN
/*
********************************************************************
*	�� �� ��: TIM14_IRQHandler
*	����˵��: ��ʱ��14�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
********************************************************************
*/
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM14,TIM_IT_Update)==SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
        D_DEBUG_printf("TIM14ʱ�䵽��IRQHandler");
	}
	TIM_ClearITPendingBit(TIM14,TIM_IT_Update);  //����жϱ�־λ
}
#endif

/*********************Copyright:CJ  (END OF FILE)******************/
