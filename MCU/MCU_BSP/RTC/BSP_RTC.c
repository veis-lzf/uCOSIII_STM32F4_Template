#include "BSP_DRIVE.h"


/*
*********************************************************************************************************
*	�� �� ��: BSP_RTC_Init()
*	����˵��: RTC��ʼ��
*	��    ��: ��
*	�� �� ֵ: 1����ʼ���ɹ�     0��LSE����ʧ��    2����������ʧ��   3������ʱ��ʧ��  
*********************************************************************************************************
*/
uint8_t BSP_RTC_Init()
{
    uint8_t L_Retry;
    RTC_InitTypeDef RTC_InitStruct;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);          //������Դʱ��
    PWR_BackupAccessCmd(ENABLE);	                            //ʹ�ܺ󱸼Ĵ������� 
    
    if(RTC_ReadBackupRegister(RTC_BKP_DR0) != 0xA0A0)           //�ж��Ƿ��ǳ�������
    {
        RCC_LSEConfig(RCC_LSE_ON);  //���� LSE
        L_Retry = 5;
        while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)      //���ָ����RCC��־λ�������,�ȴ����پ������
        {
            delay_ms(10);
            if(L_Retry-- == 0)return 0;                         //LSE����ʧ�ܣ�����1
        }
        //LSE�����ɹ�����������
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);                 //ѡ���ⲿ����ʱ����ΪRTCʱ��Դ
        RCC_RTCCLKCmd(ENABLE);                                  //ʹ��RTCʱ��
        
        //RTC�첽��Ƶϵ��(1~0X7F),�ڴ�����Ϊ���0x7f,���Խ��͹���
        RTC_InitStruct.RTC_AsynchPrediv =   0x7F; 
        //RTCͬ����Ƶϵ��(0~7FFF),���첽��Ƶϵ��Ϊ0x7f�����Ϊ�˵õ�1Hzʱ�ӣ���ͬ����Ƶϵ������Ϊ0xff    
        RTC_InitStruct.RTC_SynchPrediv  =   0xFF;       
        RTC_InitStruct.RTC_HourFormat   =   RTC_HourFormat_24;  //24Сʱ��
        RTC_Init(&RTC_InitStruct);                              //�����ó�ʼ��RTC
        if(BSP_RTC_Set_Data(2017,10,11,3) == 0)return 2;        //�������ڣ����ʧ�ܷ���2
        if(BSP_RTC_Set_Time(18,50,0,0x00) == 0) return 3;       //����ʱ�䣬���ʧ�ܷ���3
        RTC_WriteBackupRegister(RTC_BKP_DR0,0xA0A0);	        //����Ѿ���ʼ������
    }
    return 1;                                                   //��ʼ���ɹ�������1
}


/*
*********************************************************************************************************
*	�� �� ��: BSP_RTC_Set_Data()
*	����˵��: RTC��������
*	��    ��: 
*           Year    :   ��  ���Ϸ�ȡֵ��Χ��0~65535����ֻ��ʮ�����������λ��Ч��
*           Month   ��  ��  ���Ϸ�ȡֵ��Χ: 1~12��
*           Data    ��  ��  ���Ϸ�ȡֵ��Χ: 1~31��
*           WeekDay :   ���ڣ��Ϸ�ȡֵ��Χ: 1~7 ��
*	�� �� ֵ: SUCCESS = 1���������óɹ�    ERROR = 0����������ʧ��   
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
*	�� �� ��: BSP_RTC_Set_Time()
*	����˵��: RTCʱ������
*	��    ��: 
*           Hours  ��   ʱ
*           Minutes:    ��
*           Seconds��   ��
*           AM_PM  ��   ������ ���Ϸ�ȡֵ��RTC_H12_AM(0x00)/RTC_H12_PM(0x40)
*	�� �� ֵ: SUCCESS(1)��ʱ�����óɹ�    ERROR(0)��ʱ������ʧ��   
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
*	�� �� ��: RTC_AlarmA_Set()
*	����˵��: RTCʱ������
*	��    ��: 
*           Hours  ��   ʱ
*           Minutes:    ��
*           Seconds��   ��
*           Week  ��    ����
*	�� �� ֵ: SUCCESS(1)��ʱ�����óɹ�    ERROR(0)��ʱ������ʧ��   
*********************************************************************************************************
*/
void RTC_AlarmA_Set(uint8_t Week,uint8_t Hours,uint8_t Minutes,uint8_t Seconds)
{
    EXTI_InitTypeDef   EXTI_InitStructure;
    RTC_AlarmTypeDef RTC_AlarmTypeInitStructure;
    RTC_TimeTypeDef RTC_TimeTypeInitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    RTC_AlarmCmd(RTC_Alarm_A,DISABLE);                  //�ر�����A 

    RTC_TimeTypeInitStructure.RTC_Hours = Hours;        //Сʱ
    RTC_TimeTypeInitStructure.RTC_Minutes = Minutes;    //����
    RTC_TimeTypeInitStructure.RTC_Seconds = Seconds;    //��
    RTC_TimeTypeInitStructure.RTC_H12 = Week;

    RTC_AlarmTypeInitStructure.RTC_AlarmDateWeekDay = Week;         //����
    RTC_AlarmTypeInitStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_WeekDay;//��������
    RTC_AlarmTypeInitStructure.RTC_AlarmMask = RTC_AlarmMask_None;  //��ȷƥ�����ڣ�ʱ����
    RTC_AlarmTypeInitStructure.RTC_AlarmTime = RTC_TimeTypeInitStructure;
    RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_A,&RTC_AlarmTypeInitStructure);


    RTC_ClearITPendingBit(RTC_IT_ALRA);                 //���RTC����A�ı�־
    EXTI_ClearITPendingBit(EXTI_Line17);                //���LINE17�ϵ��жϱ�־λ 

    RTC_ITConfig(RTC_IT_ALRA,ENABLE);                   //��������A�ж�
    RTC_AlarmCmd(RTC_Alarm_A,ENABLE);                   //��������A 

    EXTI_InitStructure.EXTI_Line = EXTI_Line17;         //LINE17
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //�ж��¼�
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //ʹ��LINE17
    EXTI_Init(&EXTI_InitStructure);                     //����

    NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);                     //����
}

//cnt:�Զ���װ��ֵ.����0,�����ж�.
void RTC_Set_WakeUp(u32 wksel,u16 cnt)
{ 
    EXTI_InitTypeDef   EXTI_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    RTC_WakeUpCmd(DISABLE);                             //�ر�WAKE UP

    RTC_WakeUpClockConfig(wksel);                       //����ʱ��ѡ��

    RTC_SetWakeUpCounter(cnt);                          //����WAKE UP�Զ���װ�ؼĴ���


    RTC_ClearITPendingBit(RTC_IT_WUT);                  //���RTC WAKE UP�ı�־
    EXTI_ClearITPendingBit(EXTI_Line22);                //���LINE22�ϵ��жϱ�־λ 
     
    RTC_ITConfig(RTC_IT_WUT,ENABLE);                    //����WAKE UP ��ʱ���ж�
    RTC_WakeUpCmd( ENABLE);                             //����WAKE UP ��ʱ����

    EXTI_InitStructure.EXTI_Line = EXTI_Line22;         //LINE22
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //�ж��¼�
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //ʹ��LINE22
    EXTI_Init(&EXTI_InitStructure);                     //����


    NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);                     //����
}

//RTC�����жϷ�����
void RTC_Alarm_IRQHandler(void)
{    
	if(RTC_GetFlagStatus(RTC_FLAG_ALRAF) == SET)        //ALARM A�ж�?
	{
		RTC_ClearFlag(RTC_FLAG_ALRAF);                  //����жϱ�־
		D_DEBUG_printf("ALARM A!\r\n");
	}   
	EXTI_ClearITPendingBit(EXTI_Line17);	            //����ж���17���жϱ�־ 											 
}

//RTC WAKE UP�жϷ�����
void RTC_WKUP_IRQHandler(void)
{    
	if(RTC_GetFlagStatus(RTC_FLAG_WUTF) == SET)         //WK_UP�ж�?
	{ 
		RTC_ClearFlag(RTC_FLAG_WUTF);	                //����жϱ�־
//		LED1=!LED1; 
	}   
	EXTI_ClearITPendingBit(EXTI_Line22);                //����ж���22���жϱ�־ 								
}



