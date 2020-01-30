/*
************************************************************************
*
*   �ļ����ƣ�BSP_RTC.h
*   �ļ�˵�������ļ�����RTC�������
*   ��    ����V1.0
*   �޸ļ�¼��
*       �汾��  ����            ����            ˵��
*       V1.0    2017-10-11      CJ              ���α�д
*
*   Copyright  (C):CJ
*
************************************************************************
*/
#ifndef __BSP_RTC_H__
#define __BSP_RTC_H__
#include "BSP_DRIVE.h"


extern ErrorStatus BSP_RTC_Set_Data(uint16_t Year, uint8_t Month, uint8_t Data, uint8_t WeekDay);
extern ErrorStatus BSP_RTC_Set_Time(uint8_t Hours, uint8_t Minutes, uint8_t Seconds, uint8_t AM_PM);
extern uint8_t BSP_RTC_Init(void);
extern void RTC_AlarmA_Set(uint8_t Week,uint8_t Hours,uint8_t Minutes,uint8_t Seconds);
extern void RTC_Set_WakeUp(u32 wksel,u16 cnt);

#endif



/*************************Copyright:CJ  (END OF FILE)********************/
