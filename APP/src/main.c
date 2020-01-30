#include "BSP_DRIVE.h"
#include "includes.h"
#include "os_app_hooks.h"

/*��ʼ����*/
//�������ȼ�
#define START_TASK_PRIO		3
//�����ջ��С
#define START_STK_SIZE 		512
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);


/*LED0��������*/
//�������ȼ�
#define LED0_TASK_PRIO		4
//�����ջ��С
#define LED0_STK_SIZE 		128
//������ƿ�
OS_TCB Led0TaskTCB;
//�����ջ
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
void led0_task(void *p_arg);


/*LED1��������*/
//�������ȼ�
#define LED1_TASK_PRIO		5
//�����ջ��С
#define LED1_STK_SIZE 		128
//������ƿ�
OS_TCB Led1TaskTCB;
//�����ջ
CPU_STK LED1_TASK_STK[LED1_STK_SIZE];
//������
void led1_task(void *p_arg);


/*��������ӡ����*/
//�������ȼ�
#define FLOAT_TASK_PRIO		6
//�����ջ��С
#define FLOAT_STK_SIZE		128
//������ƿ�
OS_TCB	FloatTaskTCB;
//�����ջ
__align(8) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];
//������
void float_task(void *p_arg);


/*LCD��ʾ����*/
//�������ȼ�
#define LCD_TASK_PRIO		7
//�����ջ��С
#define LCD_STK_SIZE		128
//������ƿ�
OS_TCB	LcdTaskTCB;
//�����ջ
__align(8) CPU_STK	LCD_TASK_STK[LCD_STK_SIZE];
//������
void lcd_task(void *p_arg);



/*�����������*/
//�������ȼ�
#define KEYSCAN_TASK_PRIO		8
//�����ջ��С
#define KEYSCAN_STK_SIZE		128
//������ƿ�
OS_TCB	KeyscanTaskTCB;
//�����ջ
__align(8) CPU_STK	KEYSCAN_TASK_STK[KEYSCAN_STK_SIZE];
//������
void keyscan_task(void *p_arg);



int main(void)
{
    OS_ERR err;
    CPU_SR_ALLOC();

    delay_init(168);  	                           //ʱ�ӳ�ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������
    BSP_USARTS_Init();                             //���ڳ�ʼ��
    BSP_LED_Init();                                //LED��ʼ��
    BSP_KEY_Init();                                //������ʼ��
    BSP_Lcd_Init();                                //LCD��ʼ��

    printf("start OS\r\n");
    CPU_Init();
    OSInit(&err);		                           //��ʼ��UCOSIII
    OS_CRITICAL_ENTER();                           //�����ٽ���
    
    //������ʼ����
    OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
                 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE / 10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
    OS_CRITICAL_EXIT();	//�˳��ٽ���
    OSStart(&err);      //����UCOSIII
    printf("OS statr over\r\n");
    while(1);
}

//��ʼ������
void start_task(void *p_arg)
{
    OS_ERR err;
    CPU_SR_ALLOC();
    p_arg = p_arg;

    CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);  	//ͳ������
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
    //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
    OSSchedRoundRobinCfg(DEF_ENABLED, 1, &err);
#endif


    OS_CRITICAL_ENTER();	//�����ٽ���
    
    //����LED0����
    OSTaskCreate((OS_TCB 	* )&Led0TaskTCB,
                 (CPU_CHAR	* )"led0 task",
                 (OS_TASK_PTR )led0_task,
                 (void		* )0,
                 (OS_PRIO	  )LED0_TASK_PRIO,
                 (CPU_STK   * )&LED0_TASK_STK[0],
                 (CPU_STK_SIZE)LED0_STK_SIZE / 10,
                 (CPU_STK_SIZE)LED0_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK	  )0,
                 (void   	* )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);

    //����LED1����
    OSTaskCreate((OS_TCB 	* )&Led1TaskTCB,
                 (CPU_CHAR	* )"led1 task",
                 (OS_TASK_PTR )led1_task,
                 (void		* )0,
                 (OS_PRIO	  )LED1_TASK_PRIO,
                 (CPU_STK   * )&LED1_TASK_STK[0],
                 (CPU_STK_SIZE)LED1_STK_SIZE / 10,
                 (CPU_STK_SIZE)LED1_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK	  )0,
                 (void   	* )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);


    //���������������
    OSTaskCreate((OS_TCB 	* )&FloatTaskTCB,
                 (CPU_CHAR	* )"float test task",
                 (OS_TASK_PTR )float_task,
                 (void		* )0,
                 (OS_PRIO	  )FLOAT_TASK_PRIO,
                 (CPU_STK   * )&FLOAT_TASK_STK[0],
                 (CPU_STK_SIZE)FLOAT_STK_SIZE / 10,
                 (CPU_STK_SIZE)FLOAT_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK	  )0,
                 (void   	* )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);
    
    //���������������
    OSTaskCreate((OS_TCB 	* )&KeyscanTaskTCB,
                 (CPU_CHAR	* )"key scan task",
                 (OS_TASK_PTR )keyscan_task,
                 (void		* )0,
                 (OS_PRIO	  )KEYSCAN_TASK_PRIO,
                 (CPU_STK   * )&KEYSCAN_TASK_STK[0],
                 (CPU_STK_SIZE)KEYSCAN_STK_SIZE / 10,
                 (CPU_STK_SIZE)KEYSCAN_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK	  )0,
                 (void   	* )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);
           
    //����LCD��ʾ����
    OSTaskCreate((OS_TCB 	* )&LcdTaskTCB,
                 (CPU_CHAR	* )"key scan task",
                 (OS_TASK_PTR )lcd_task,
                 (void		* )0,
                 (OS_PRIO	  )LCD_TASK_PRIO,
                 (CPU_STK   * )&LCD_TASK_STK[0],
                 (CPU_STK_SIZE)LCD_STK_SIZE / 10,
                 (CPU_STK_SIZE)LCD_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK	  )0,
                 (void   	* )0,
                 (OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);
                 
    OS_TaskSuspend((OS_TCB*)&StartTaskTCB, &err);		//����ʼ����
    OS_CRITICAL_EXIT();	                                //�˳��ٽ���
}

//led0������
void led0_task(void *p_arg)
{
    OS_ERR err;
    p_arg = p_arg;
    while(1)
    {
        LED0 = ~LED0;
        printf("led0_task\r\n");
        OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err); //��ʱ500ms
    }
}

//led1������
void led1_task(void *p_arg)
{
    OS_ERR err;
    p_arg = p_arg;
    while(1)
    {
        LED1 = ~LED1;
        printf("led1_task\r\n");
        delay_ms(500);
//        OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err); //��ʱ500ms
        
    }
}

//�����������
void float_task(void *p_arg)
{
    CPU_SR_ALLOC();
    static float float_num = 0.01;
    while(1)
    {
        float_num += 0.01f;
        OS_CRITICAL_ENTER();	//�����ٽ���
        printf("float_num��ֵΪ: %.4f\r\n", float_num);
        OS_CRITICAL_EXIT();		//�˳��ٽ���
        delay_ms(500);			//��ʱ500ms
    }
}

//�����������
void keyscan_task(void *p_arg)
{
    CPU_SR_ALLOC();
    static u8 key_res = 0;
    
    while(1)
    {
        OS_CRITICAL_ENTER();	//�����ٽ���
        key_res = KEY_Scan(0);
        if(0 != key_res) printf("key_res: %d\r\n", key_res);
        OS_CRITICAL_EXIT();		//�˳��ٽ���
    }
}

//LCD��ʾ����
void lcd_task(void *p_arg)
{
    CPU_SR_ALLOC();
    static u8 x = 0;
    
    while(1)
    {
        OS_CRITICAL_ENTER();	//�����ٽ���
        printf("LCD Task Start!\r\n");
        switch(x++)
		{
			case 0:LCD_Clear(White);    break;
			case 1:LCD_Clear(Black);    break;
			case 2:LCD_Clear(Blue);     break;
			case 3:LCD_Clear(Red);      break;
			case 4:LCD_Clear(Magenta);  break;
			case 5:LCD_Clear(Green);    break;
			case 6:LCD_Clear(Cyan);     break; 
			case 7:LCD_Clear(Yellow);   break;
		}

        if(7 == x) x = 0;
        delay_ms(1000);
        OS_CRITICAL_EXIT();	   //�˳��ٽ���
    }
}
