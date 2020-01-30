/*
************************************************************************
*
*   �ļ����ƣ�BSP_TIMER.h
*   �ļ�˵�������ļ�����RTC�������
*   ��    ����V1.0
*   �޸ļ�¼��
*       �汾��  ����            ����            ˵��
*       V1.0    2017-10-22      CJ              ���α�д
*
*   Copyright  (C):CJ
*
************************************************************************
*/
#ifndef __BSP_TIMRS_H__
#define __BSP_TIMRS_H__

#include "BSP_DRIVE.h"

//������ʱ��ʹ������
/******************************************��ʱ��6***********************************************/
#define D_TIMER6_EN                 0

#define D_TIMER6_AUTO_RELOAD_VALUE  2000		//��ʱ��6�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER6_PRESCALER_VALUE	8399		    //��ʱ��6Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER6_DMA_EN	            1			//��ʱ��6DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER6_UPDATE_INT_EN	    1			//��ʱ��6�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER6_INTERRUPT_FLAG	    (TIM6->SR & 1)	//��ʱ��6���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER6_Priority             2

/******************************************��ʱ��7**************************************************/
#define D_TIMER7_EN                 0

#define D_TIMER7_AUTO_RELOAD_VALUE  4000		//��ʱ��7�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER7_PRESCALER_VALUE	8399		//��ʱ��7Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER7_DMA_EN	            1			//��ʱ��7DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER7_UPDATE_INT_EN	    1			//��ʱ��7�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER7_INTERRUPT_FLAG	    (TIM7->SR & 1)	//��ʱ��7���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER7_Priority             2


//ͨ�ö�ʱ��ʹ������
/******************************************��ʱ��2**************************************************/
#define D_TIMER2_EN                 0

#define D_TIMER2_AUTO_RELOAD_VALUE  2000		//��ʱ��2�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER2_PRESCALER_VALUE	8399		//��ʱ��2Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER2_DMA_EN	            1			//��ʱ��2DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER2_UPDATE_INT_EN	    1			//��ʱ��2�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER2_INTERRUPT_FLAG	    (TIM2->SR & 1)	//��ʱ��7���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER2_Priority             2

/******************************************��ʱ��3**************************************************/
#define D_TIMER3_EN                 0

#define D_TIMER3_AUTO_RELOAD_VALUE  4000		//��ʱ��7�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER3_PRESCALER_VALUE	8399		//��ʱ��7Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER3_DMA_EN	            1			//��ʱ��7DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER3_UPDATE_INT_EN	    1			//��ʱ��7�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER3_INTERRUPT_FLAG	    (TIM3->SR & 1)	//��ʱ��7���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER3_Priority             2

/******************************************��ʱ��4**************************************************/
#define D_TIMER4_EN                 0

#define D_TIMER4_AUTO_RELOAD_VALUE  2000		//��ʱ��7�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER4_PRESCALER_VALUE	8399		//��ʱ��7Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER4_DMA_EN	            1			//��ʱ��7DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER4_UPDATE_INT_EN	    1			//��ʱ��7�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER4_INTERRUPT_FLAG	    (TIM4->SR & 1)	//��ʱ��7���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER4_Priority             2

/******************************************��ʱ��5**************************************************/
#define D_TIMER5_EN                 0

#define D_TIMER5_AUTO_RELOAD_VALUE  4000		//��ʱ��7�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER5_PRESCALER_VALUE	8399		//��ʱ��7Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER5_DMA_EN	            1			//��ʱ��7DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER5_UPDATE_INT_EN	    1			//��ʱ��7�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER5_INTERRUPT_FLAG	    (TIM5->SR & 1)	//��ʱ��7���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER5_Priority             2

/******************************************��ʱ��9**************************************************/
#define D_TIMER9_EN                 0

#define D_TIMER9_AUTO_RELOAD_VALUE  2000		//��ʱ��7�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER9_PRESCALER_VALUE	8399		//��ʱ��7Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER9_DMA_EN	            1			//��ʱ��7DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER9_UPDATE_INT_EN	    1			//��ʱ��7�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER9_INTERRUPT_FLAG	    (TIM9->SR & 1)	//��ʱ��7���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER9_Priority             2

/******************************************��ʱ��10*************************************************/
#define D_TIMER10_EN                0

#define D_TIMER10_AUTO_RELOAD_VALUE 4000		//��ʱ��7�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER10_PRESCALER_VALUE	8399		//��ʱ��7Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER10_DMA_EN	        1			//��ʱ��7DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER10_UPDATE_INT_EN	    1			//��ʱ��7�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER10_INTERRUPT_FLAG	    (TIM10->SR & 1)	//��ʱ��7���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER10_Priority             2

/******************************************��ʱ��11*************************************************/
#define D_TIMER11_EN                0

#define D_TIMER11_AUTO_RELOAD_VALUE 2000		//��ʱ��11�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER11_PRESCALER_VALUE	8399		//��ʱ��11Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER11_DMA_EN	        1			//��ʱ��11DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER11_UPDATE_INT_EN	    1			//��ʱ��11�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER11_INTERRUPT_FLAG	   (TIM4->SR & 1)	//��ʱ��11���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER11_Priority            2

/******************************************��ʱ��12*************************************************/
#define D_TIMER12_EN                0

#define D_TIMER12_AUTO_RELOAD_VALUE 4000		//��ʱ��7�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER12_PRESCALER_VALUE	8399		//��ʱ��7Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER12_DMA_EN	        1			//��ʱ��7DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER12_UPDATE_INT_EN	    1			//��ʱ��7�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER12_INTERRUPT_FLAG	    (TIM12->SR & 1)	//��ʱ��7���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER12_Priority             2

/******************************************��ʱ��13*************************************************/
#define D_TIMER13_EN                0

#define D_TIMER13_AUTO_RELOAD_VALUE 2000		//��ʱ��7�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER13_PRESCALER_VALUE	8399		//��ʱ��7Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER13_DMA_EN	        1	        //��ʱ��7DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER13_UPDATE_INT_EN	    1			//��ʱ��7�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER13_INTERRUPT_FLAG	   (TIM13->SR & 1)	//��ʱ��7���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER13_Priority            2
/******************************************��ʱ��14*************************************************/
#define D_TIMER14_EN                0

#define D_TIMER14_AUTO_RELOAD_VALUE 4000		//��ʱ��7�Զ���װ��ֵ���Ϸ�ֵ0~65535
#define D_TIMER14_PRESCALER_VALUE	8399		//��ʱ��7Ԥ��Ƶֵ���Ϸ�ֵ0~65535

#define D_TIMER14_DMA_EN	        1			//��ʱ��7DMA�ж�ʹ�����ã�0��ֹ��1ʹ��
#define D_TIMER14_UPDATE_INT_EN	    1			//��ʱ��7�����ж�ʹ�����ã�0��ֹ��1ʹ��

#define TIMER14_INTERRUPT_FLAG	   (TIM14->SR & 1)	//��ʱ��7���������¼���־������Ϊ1��δ����Ϊ0

#define TIMER14_Priority            2

//�߼����ƶ�ʱ��ʹ������
#define D_TIMER1_EN                 1
#define D_TIMER8_EN                 1

#endif


void BSP_Timers_Init(void);

/*************************Copyright:CJ  (END OF FILE)********************/
