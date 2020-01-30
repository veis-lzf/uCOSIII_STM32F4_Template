/*
************************************************************************
*
*   文件名称：BSP_RTC.h
*   文件说明：该文件包含RTC相关配置
*   版    本：V1.0
*   修改记录：
*       版本号  日期            作者            说明
*       V1.0    2017-10-11      CJ              初次编写
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
