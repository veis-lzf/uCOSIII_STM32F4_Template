#include "BSP_DRIVE.h"


/*
*********************************************************************************************************
*	函 数 名: BSP_RTC_Init()
*	功能说明: RTC初始化
*	形    参: 无
*	返 回 值: 1：初始化成功     0：LSE开启失败    2：设置日期失败   3：设置时间失败  
*********************************************************************************************************
*/
uint8_t BSP_RTC_Init()
{
    uint8_t L_Retry;
    RTC_InitTypeDef RTC_InitStruct;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);          //开启电源时钟
    PWR_BackupAccessCmd(ENABLE);	                            //使能后备寄存器访问 
    
    if(RTC_ReadBackupRegister(RTC_BKP_DR0) != 0xA0A0)           //判断是否是初次配置
    {
        RCC_LSEConfig(RCC_LSE_ON);  //开启 LSE
        L_Retry = 5;
        while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)      //检查指定的RCC标志位设置与否,等待低速晶振就绪
        {
            delay_ms(10);
            if(L_Retry-- == 0)return 0;                         //LSE开启失败，返回1
        }
        //LSE开启成功，继续配置
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);                 //选择外部低速时钟作为RTC时钟源
        RCC_RTCCLKCmd(ENABLE);                                  //使能RTC时钟
        
        //RTC异步分频系数(1~0X7F),在此设置为最大0x7f,可以降低功耗
        RTC_InitStruct.RTC_AsynchPrediv =   0x7F; 
        //RTC同步分频系数(0~7FFF),在异步分频系数为0x7f情况下为了得到1Hz时钟，将同步分频系数设置为0xff    
        RTC_InitStruct.RTC_SynchPrediv  =   0xFF;       
        RTC_InitStruct.RTC_HourFormat   =   RTC_HourFormat_24;  //24小时制
        RTC_Init(&RTC_InitStruct);                              //按配置初始化RTC
        if(BSP_RTC_Set_Data(2017,10,11,3) == 0)return 2;        //设置日期，如果失败返回2
        if(BSP_RTC_Set_Time(18,50,0,0x00) == 0) return 3;       //设置时间，如果失败返回3
        RTC_WriteBackupRegister(RTC_BKP_DR0,0xA0A0);	        //标记已经初始化过了
    }
    return 1;                                                   //初始化成功，返回1
}


/*
*********************************************************************************************************
*	函 数 名: BSP_RTC_Set_Data()
*	功能说明: RTC日期设置
*	形    参: 
*           Year    :   年  （合法取值范围：0~65535，但只有十进制下最后两位有效）
*           Month   ：  月  （合法取值范围: 1~12）
*           Data    ：  日  （合法取值范围: 1~31）
*           WeekDay :   星期（合法取值范围: 1~7 ）
*	返 回 值: SUCCESS = 1：日期设置成功    ERROR = 0：日期设置失败   
*********************************************************************************************************
*/
ErrorStatus BSP_RTC_Set_Data(uint16_t Year, uint8_t Month, uint8_t Data, uint8_t WeekDay)
{
    RTC_DateTypeDef L_RTC_DataStruct;
    
    L_RTC_DataStruct.RTC_Year   =   Year % 100;
    L_RTC_DataStruct.RTC_Month  =   Month;
    L_RTC_DataStruct.RTC_Date   =   Data;
    L_RTC_DataStruct.RTC_WeekDay=   WeekDay;
    return (RTC_SetDate(RTC_Format_BIN,&L_RTC_DataStruct));
}

/*
*********************************************************************************************************
*	函 数 名: BSP_RTC_Set_Time()
*	功能说明: RTC时间设置
*	形    参: 
*           Hours  ：   时
*           Minutes:    分
*           Seconds：   秒
*           AM_PM  ：   上下午 （合法取值：RTC_H12_AM(0x00)/RTC_H12_PM(0x40)
*	返 回 值: SUCCESS(1)：时间设置成功    ERROR(0)：时间设置失败   
*********************************************************************************************************
*/
ErrorStatus BSP_RTC_Set_Time(uint8_t Hours, uint8_t Minutes, uint8_t Seconds, uint8_t AM_PM)
{
    RTC_TimeTypeDef L_RTC_TimeStruct;
    
    L_RTC_TimeStruct.RTC_Hours      =   Hours;
    L_RTC_TimeStruct.RTC_Minutes    =   Minutes;
    L_RTC_TimeStruct.RTC_Seconds    =   Seconds;
    L_RTC_TimeStruct.RTC_H12        =   AM_PM;
    return (RTC_SetTime(RTC_Format_BIN,&L_RTC_TimeStruct));
}

/*
*********************************************************************************************************
*	函 数 名: RTC_AlarmA_Set()
*	功能说明: RTC时间设置
*	形    参: 
*           Hours  ：   时
*           Minutes:    分
*           Seconds：   秒
*           Week  ：    星期
*	返 回 值: SUCCESS(1)：时间设置成功    ERROR(0)：时间设置失败   
*********************************************************************************************************
*/
void RTC_AlarmA_Set(uint8_t Week,uint8_t Hours,uint8_t Minutes,uint8_t Seconds)
{
    EXTI_InitTypeDef   EXTI_InitStructure;
    RTC_AlarmTypeDef RTC_AlarmTypeInitStructure;
    RTC_TimeTypeDef RTC_TimeTypeInitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    RTC_AlarmCmd(RTC_Alarm_A,DISABLE);                  //关闭闹钟A 

    RTC_TimeTypeInitStructure.RTC_Hours = Hours;        //小时
    RTC_TimeTypeInitStructure.RTC_Minutes = Minutes;    //分钟
    RTC_TimeTypeInitStructure.RTC_Seconds = Seconds;    //秒
    RTC_TimeTypeInitStructure.RTC_H12 = Week;

    RTC_AlarmTypeInitStructure.RTC_AlarmDateWeekDay = Week;         //星期
    RTC_AlarmTypeInitStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_WeekDay;//按星期闹
    RTC_AlarmTypeInitStructure.RTC_AlarmMask = RTC_AlarmMask_None;  //精确匹配星期，时分秒
    RTC_AlarmTypeInitStructure.RTC_AlarmTime = RTC_TimeTypeInitStructure;
    RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_A,&RTC_AlarmTypeInitStructure);


    RTC_ClearITPendingBit(RTC_IT_ALRA);                 //清除RTC闹钟A的标志
    EXTI_ClearITPendingBit(EXTI_Line17);                //清除LINE17上的中断标志位 

    RTC_ITConfig(RTC_IT_ALRA,ENABLE);                   //开启闹钟A中断
    RTC_AlarmCmd(RTC_Alarm_A,ENABLE);                   //开启闹钟A 

    EXTI_InitStructure.EXTI_Line = EXTI_Line17;         //LINE17
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //中断事件
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //使能LINE17
    EXTI_Init(&EXTI_InitStructure);                     //配置

    NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                     //配置
}

//cnt:自动重装载值.减到0,产生中断.
void RTC_Set_WakeUp(u32 wksel,u16 cnt)
{ 
    EXTI_InitTypeDef   EXTI_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    RTC_WakeUpCmd(DISABLE);                             //关闭WAKE UP

    RTC_WakeUpClockConfig(wksel);                       //唤醒时钟选择

    RTC_SetWakeUpCounter(cnt);                          //设置WAKE UP自动重装载寄存器


    RTC_ClearITPendingBit(RTC_IT_WUT);                  //清除RTC WAKE UP的标志
    EXTI_ClearITPendingBit(EXTI_Line22);                //清除LINE22上的中断标志位 
     
    RTC_ITConfig(RTC_IT_WUT,ENABLE);                    //开启WAKE UP 定时器中断
    RTC_WakeUpCmd( ENABLE);                             //开启WAKE UP 定时器　

    EXTI_InitStructure.EXTI_Line = EXTI_Line22;         //LINE22
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //中断事件
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //使能LINE22
    EXTI_Init(&EXTI_InitStructure);                     //配置


    NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                     //配置
}

//RTC闹钟中断服务函数
void RTC_Alarm_IRQHandler(void)
{    
	if(RTC_GetFlagStatus(RTC_FLAG_ALRAF) == SET)        //ALARM A中断?
	{
		RTC_ClearFlag(RTC_FLAG_ALRAF);                  //清除中断标志
		D_DEBUG_printf("ALARM A!\r\n");
	}   
	EXTI_ClearITPendingBit(EXTI_Line17);	            //清除中断线17的中断标志 											 
}

//RTC WAKE UP中断服务函数
void RTC_WKUP_IRQHandler(void)
{    
	if(RTC_GetFlagStatus(RTC_FLAG_WUTF) == SET)         //WK_UP中断?
	{ 
		RTC_ClearFlag(RTC_FLAG_WUTF);	                //清除中断标志
//		LED1=!LED1; 
	}   
	EXTI_ClearITPendingBit(EXTI_Line22);                //清除中断线22的中断标志 								
}



