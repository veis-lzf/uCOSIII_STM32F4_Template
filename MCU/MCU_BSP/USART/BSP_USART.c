/*
************************************************************************
*
*   �ļ����ƣ�BSP_USART.c
*   �ļ�˵����������ص�����
*   ��    ����V1.0
*   �޸ļ�¼��
*       �汾��  ����            ����            ˵��
*       V1.0    2017-03-20      CJ              ���α�д
*
*   Copyright  (C):CJ
*
************************************************************************
*/

#include "BSP_DRIVE.h"
#include <string.h>

/*
*********************************************************************************************************
*	�� �� ��: BSP_USARTS_Init()
*	����˵��: ��ʼ������
*	��    ��:
*           P_USARTS_Struct      : ���ڲ����ʽṹ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_USARTS_Init()
{

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

#if D_USART1_EN	                                                //����USART1

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);      //ʹ��USART1ʱ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                //���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	        //�ٶ�100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;              //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                //����

    if(D_USART1_GPIO == GPIOA)                                  //USART1ʹ������PA9/PA10
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   //ʹ��GPIOAʱ��
        //����1��Ӧ���Ÿ���ӳ��
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); //GPIOA9����ΪUSART1
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //GPIOA10����ΪUSART1

        //USART1�˿�����
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
        GPIO_Init(GPIOA, &GPIO_InitStructure);                  //��ʼ��PA9��PA10
    }
    if(D_USART1_GPIO == GPIOB)                                 //USART1ʹ������PB6/PB7
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   //ʹ��GPIOBʱ��
        //����1��Ӧ���Ÿ���ӳ��
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1); //GPIOB6����ΪUSART1
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1); //GPIOB7����ΪUSART1

        //USART1�˿�����
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  //GPIOA9��GPIOA10
        GPIO_Init(GPIOB, &GPIO_InitStructure);                  //��ʼ��PB6��PB7
    }

    //USART1 ��ʼ������
    USART_InitStructure.USART_BaudRate = D_USART1_BAND;         //����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;         //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure);                   //��ʼ������1

    USART_Cmd(USART1, ENABLE);                                  //ʹ�ܴ���1

    USART_ClearFlag(USART1, USART_FLAG_TC);

#if D_EN_USART1_RX
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);              //��������ж�

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;           //����1�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = D_USART1_Priority; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		   //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	                            //����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif      //#if D_EN_USART1_RX

#endif      //#if D_USART1_EN

#if D_USART2_EN	                                                //����USART2

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);      //ʹ��USART2ʱ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                //���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	        //�ٶ�100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;              //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                //����

    if(D_USART2_GPIO == GPIOA)                                  //USART2ʹ������PA2/PA3
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   //ʹ��GPIOAʱ��
        //����2��Ӧ���Ÿ���ӳ��
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //GPIOA2����ΪUSART2
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //GPIOA3����ΪUSART2

        //USART2�˿�����
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;  //GPIOA2��GPIOA3
        GPIO_Init(GPIOA, &GPIO_InitStructure);                  //��ʼ��PA2��PA3
    }
    if(D_USART2_GPIO == GPIOD)                                  //USART2ʹ������PD5/PD6
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);   //ʹ��GPIODʱ��
        //����2��Ӧ���Ÿ���ӳ��
        GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2); //GPIOD5����ΪUSART2
        GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2); //GPIOD6����ΪUSART2

        //USART1�˿�����
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;  //GPIOD5��GPIOD6
        GPIO_Init(GPIOD, &GPIO_InitStructure);                  //��ʼ��PD5��PD6
    }

    //USART2 ��ʼ������
    USART_InitStructure.USART_BaudRate = D_USART2_BAND;         //����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;         //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure);                   //��ʼ������2

    USART_Cmd(USART2, ENABLE);                                  //ʹ�ܴ���2

    USART_ClearFlag(USART2, USART_FLAG_TC);

#if D_EN_USART2_RX
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);              //��������ж�

    //Usart2 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;           //����2�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = D_USART2_Priority; //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		   //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	                            //����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif      //#if D_EN_USART2_RX
#endif      //#if D_USART2_EN

#if D_USART3_EN	                                                //����USART3

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);      //ʹ��USART3ʱ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                //���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	        //�ٶ�100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;              //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                //����

    if(D_USART3_GPIO == GPIOB)                                  //USART3ʹ������PB10/PB11
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   //ʹ��GPIOBʱ��
        //����3��Ӧ���Ÿ���ӳ��
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3); //GPIOB10����ΪUSART3
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3); //GPIOB11����ΪUSART3

        //USART3�˿�����
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//GPIOB10��GPIOB11
        GPIO_Init(GPIOB, &GPIO_InitStructure);                  //��ʼ��PB10��PB11
    }
    if(D_USART3_GPIO == GPIOC)                                  //USART3ʹ������PC10/PC11
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);   //ʹ��GPIODʱ��
        //����3��Ӧ���Ÿ���ӳ��
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3); //GPIOC10����ΪUSART3
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3); //GPIOC11����ΪUSART3

        //USART3�˿�����
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//GPIOC10��GPIOC11
        GPIO_Init(GPIOC, &GPIO_InitStructure);                  //��ʼ��PC10��PC11
    }

    //USART3 ��ʼ������
    USART_InitStructure.USART_BaudRate = D_USART3_BAND;         //����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;         //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART3, &USART_InitStructure);                   //��ʼ������3

    USART_Cmd(USART3, ENABLE);                                  //ʹ�ܴ���3

    USART_ClearFlag(USART3, USART_FLAG_TC);

#if D_EN_USART3_RX
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);              //��������ж�

    //Usart3 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;           //����3�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = D_USART3_Priority; //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		   //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	                            //����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif      //#if D_EN_USART3_RX
#endif      //#if D_USART3_EN

#if D_UART4_EN	                                                //����USART3

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);       //ʹ��USART3ʱ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                //���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	        //�ٶ�100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;              //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                //����

    if(D_UART4_GPIO == GPIOA)                                   //UART4ʹ������PA0/PA1
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   //ʹ��GPIOAʱ��
        //����2��Ӧ���Ÿ���ӳ��
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4); //GPIOA0����ΪUART4
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4); //GPIOA1����ΪUART4

        //USART3�˿�����
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;  //GPIOA0��GPIOA1
        GPIO_Init(GPIOA, &GPIO_InitStructure);                  //��ʼ��PA0��PA1
    }
    if(D_UART4_GPIO == GPIOC)                                   //UART4ʹ������PC10/PC11
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);   //ʹ��GPIOCʱ��
        //����4��Ӧ���Ÿ���ӳ��
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4); //GPIOC10����ΪUART4
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4); //GPIOC11����ΪUART4

        //UART4�˿�����
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//GPIOC10��GPIOC11
        GPIO_Init(GPIOC, &GPIO_InitStructure);                  //��ʼ��PC10��PC11
    }

    //USART3 ��ʼ������
    USART_InitStructure.USART_BaudRate = D_UART4_BAND;          //����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;         //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(UART4, &USART_InitStructure);                    //��ʼ������4

    USART_Cmd(UART4, ENABLE);                                   //ʹ�ܴ���4

    USART_ClearFlag(UART4, USART_FLAG_TC);

#if D_EN_UART4_RX
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);               //��������ж�

    //Usart3 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;            //����4�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = D_UART4_Priority; //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		   //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	                            //����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif      //#if D_EN_UART4_RX
#endif      //#if D_UART4_EN

}


/*
*******************************************************************************************************
*   �ڱ�׼�����ض��� printf ��������Ҫ���ӵĴ��룬ʹ�� MicroLIB �ɲ����ⲿ�ִ���
*/
#pragma import(__use_no_semihosting)
//��׼����Ҫ��֧�ֺ���
struct __FILE
{
    int handle;

};

FILE __stdout;
//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
    x = x;
}

/*
********************************************************************************************************
*/

/*
*********************************************************************************************************
*	�� �� ��: fputc
*	����˵��: �ض��������ض�������ʹ��printf �����򴮿ڷ�������
*	��    ��:
*	�� �� ֵ:
*********************************************************************************************************
*/
USART_TypeDef *G_USARTx_printf = USART1;        //�����������ý� printf �����ض����ĸ����ڣ�Ĭ��ΪUSART1
int fputc(int ch, FILE *f)
{
    while((G_USARTx_printf->SR & 0X40) == 0);   //ѭ������,ֱ���������
    G_USARTx_printf->DR = (u8) ch;
    return ch;
}

USARTS_RX_Typedef USARTS_RX_Struct =            //���ڽ��ܵ������ݻ������Ͷ�дָ��
{
#if D_USART1_EN
    {0},
    '\0',                                       //��ʼ��Ϊ������
    0,                                          //֡���ȳ�ʼ��Ϊ0
    0,                                          //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    USARTS_RX_Struct.Usart1_Rx_Buff,            //д��USART_BUFFָ�룬
    USARTS_RX_Struct.Usart1_Rx_Buff,            //����USART_BUFFָ��
    USARTS_RX_Struct.Usart1_Rx_Buff + D_USART1_BUFF_LEN - 1,//���ջ���������ַ
#endif

#if D_USART2_EN
    {0},
    '\0',                                       //��ʼ��Ϊ������
    0,                                          //֡���ȳ�ʼ��Ϊ0
    0,                                          //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    USARTS_RX_Struct.Usart2_Rx_Buff,            //д��USART_BUFFָ�룬
    USARTS_RX_Struct.Usart2_Rx_Buff,            //����USART_BUFFָ��
    USARTS_RX_Struct.Usart2_Rx_Buff + D_USART1_BUFF_LEN - 1,//���ջ���������ַ
#endif

#if D_USART3_EN
    {0},
    '\0',                                       //��ʼ��Ϊ������
    0,                                          //֡���ȳ�ʼ��Ϊ0
    0,                                          //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    USARTS_RX_Struct.Usart3_Rx_Buff,            //д��USART_BUFFָ�룬
    USARTS_RX_Struct.Usart3_Rx_Buff,            //����USART_BUFFָ��
    USARTS_RX_Struct.Usart3_Rx_Buff + D_USART1_BUFF_LEN - 1,//���ջ���������ַ
#endif

#if D_UART4_EN
    {0},
    '\0',                                       //��ʼ��Ϊ������
    0,                                          //֡���ȳ�ʼ��Ϊ0
    0,                                          //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    USARTS_RX_Struct.Uart4_Rx_Buff,             //д��USART_BUFFָ�룬
    USARTS_RX_Struct.Uart4_Rx_Buff,             //����USART_BUFFָ��
    USARTS_RX_Struct.Uart4_Rx_Buff + D_USART1_BUFF_LEN - 1,//���ջ���������ַ
#endif

#if D_UART5_EN
    {0},
    '\0',                                       //��ʼ��Ϊ������
    0,                                          //֡���ȳ�ʼ��Ϊ0
    0,                                          //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    USARTS_RX_Struct.Uart5_Rx_Buff,             //д��USART_BUFFָ�룬
    USARTS_RX_Struct.Uart5_Rx_Buff,             //����USART_BUFFָ��
    USARTS_RX_Struct.Uart5_Rx_Buff + D_USART1_BUFF_LEN - 1,//���ջ���������ַ
#endif
};
/*
*********************************************************************************************************
*	�� �� ��: USARTx_Revice_Data
*	����˵��: ͨ�����ڷ����ַ���
*	��    ��:
*           P_USARTx    : �������ݵĴ���
*	�� �� ֵ: 1����֡���ճɹ���   0�����ֽڽ��ճɹ�����֡����δ��ɣ�  -1�����������
*********************************************************************************************************
*/
int8_t USARTx_Revice_Data(USART_TypeDef* P_USARTx)
{
    uint8_t *USARTx_Rev_Buff;                       //ָ�򴮿ڻ�������ָ��
    uint8_t *USARTx_Frame_Len;                      //ָ��֡����¼�ֽڵ�ָ��
    uint8_t *USARTx_Total_Frame;                    //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    uint8_t **USARTx_WRITE_POINT;                   //ָ��д��USART_BUFFָ���ָ��
    uint8_t **USARTx_READ_POINT;                    //ָ�����USART_BUFFָ���ָ��
    uint8_t *USARTx_BUFF_MAX_ADDR;                  //���ڼ�¼���ڽ��ջ���������ֵַ

    switch((uint32_t)P_USARTx)
    {
#if D_USART1_EN
    case (uint32_t)USART1 :
    {
        USARTx_Rev_Buff    = USARTS_RX_Struct.Usart1_Rx_Buff;
        USARTx_Frame_Len   = &USARTS_RX_Struct.Usart1_Frame_Len;
        USARTx_Total_Frame = &USARTS_RX_Struct.Usart1_Total_Frame;
        USARTx_WRITE_POINT = &USARTS_RX_Struct.Usart1_WRITE_POINT;
        USARTx_READ_POINT  = &USARTS_RX_Struct.Usart1_READ_POINT;
        USARTx_BUFF_MAX_ADDR = USARTS_RX_Struct.Usart1_Rx_Buff_MAX_ADDR;
    }
    break;
#endif

#if D_USART2_EN
    case (uint32_t)USART2 :
    {
        USARTx_Rev_Buff    = USARTS_RX_Struct.Usart2_Rx_Buff;
        USARTx_Frame_Len   = &USARTS_RX_Struct.Usart2_Frame_Len;
        USARTx_Total_Frame = &USARTS_RX_Struct.Usart2_Total_Frame;
        USARTx_WRITE_POINT = &USARTS_RX_Struct.Usart2_WRITE_POINT;
        USARTx_READ_POINT  = &USARTS_RX_Struct.Usart2_READ_POINT;
        USARTx_BUFF_MAX_ADDR = USARTS_RX_Struct.Usart2_Rx_Buff_MAX_ADDR;
    }
    break;
#endif

#if D_USART3_EN
    case (uint32_t)USART3 :
    {
        USARTx_Rev_Buff    = USARTS_RX_Struct.Usart3_Rx_Buff;
        USARTx_Frame_Len   = &USARTS_RX_Struct.Usart3_Frame_Len;
        USARTx_Total_Frame = &USARTS_RX_Struct.Usart3_Total_Frame;
        USARTx_WRITE_POINT = &USARTS_RX_Struct.Usart3_WRITE_POINT;
        USARTx_READ_POINT  = &USARTS_RX_Struct.Usart3_READ_POINT;
        USARTx_BUFF_MAX_ADDR = USARTS_RX_Struct.Usart3_Rx_Buff_MAX_ADDR;
    }
    break;
#endif

#if D_UART4_EN
    case (uint32_t)UART4  :
    {
        USARTx_Rev_Buff    = USARTS_RX_Struct.Uart4_Rx_Buff;
        USARTx_Frame_Len   = &USARTS_RX_Struct.Uart4_Frame_Len;
        USARTx_Total_Frame = &USARTS_RX_Struct.Uart4_Total_Frame;
        USARTx_WRITE_POINT = &USARTS_RX_Struct.Uart4_WRITE_POINT;
        USARTx_READ_POINT  = &USARTS_RX_Struct.Uart4_READ_POINT;
        USARTx_BUFF_MAX_ADDR = USARTS_RX_Struct.Uart4_Rx_Buff_MAX_ADDR;
    }
    break;
#endif

#if D_UART5_EN
    case (uint32_t)UART5  :
    {
        USARTx_Rev_Buff    = USARTS_RX_Struct.Uart5_Rx_Buff;
        USARTx_Frame_Len   = &USARTS_RX_Struct.Uart5_Frame_Len;
        USARTx_Total_Frame = &USARTS_RX_Struct.Uart5_Total_Frame;
        USARTx_WRITE_POINT = &USARTS_RX_Struct.Uart5_WRITE_POINT;
        USARTx_READ_POINT  = &USARTS_RX_Struct.Uart5_READ_POINT;
        USARTx_BUFF_MAX_ADDR = USARTS_RX_Struct.Uart5_Rx_Buff_MAX_ADDR;
    }
    break;
#endif
    default :
    {
        D_DEBUG_printf("��ѡ����δʹ�ܻ�ʹ��ʧ�ܣ�");
//            D_DEBUG_printf("%x",(uint32_t)P_USARTx);
//            while(1);
    }
    }
    if(USARTx_WRITE_POINT == USARTx_READ_POINT)
    {
        return -1;                                              //����������������-1
    }
    (*USARTx_WRITE_POINT) ++;                                   //дָ������ָ�����д������ݵĵ�ַ
    if((*USARTx_WRITE_POINT) > (USARTx_BUFF_MAX_ADDR))          //дָ����ڻ�����������ֵַ
    {
        *USARTx_WRITE_POINT = USARTx_Rev_Buff;                  //��дָ��ָ�򻺳����׵�ַ,ѭ���洢
    }
    *(*USARTx_WRITE_POINT) = P_USARTx -> DR & (uint16_t)0x01FF; //����������
    (*USARTx_Frame_Len) ++ ;                                    //֡�����Լ�1
    if(**USARTx_WRITE_POINT == 0x0a)                            //�ж��½��յ������Ƿ���0x0a
    {
        if((*(*USARTx_WRITE_POINT - 1)) == 0x0d)                //��������ж��ϴν��յ��Ƿ���0x0d,�����ʾ���ν������
        {
            (*USARTx_WRITE_POINT)--;                            //дָ�����Ƶ�0x0dλ�ã�Ϊ�����λ�����롮\0����׼��
            *(*USARTx_WRITE_POINT) = '\0';
            (*USARTx_Total_Frame)++;                            //��֡�������,֡����һ
//            (*USARTx_Frame_Len) -= 2;                         //���ݳ��ȼ�ȥ������0x0d��ռ�ĳ��ȵõ���ʵ���ݳ���

            if((*USARTx_WRITE_POINT - (*USARTx_Frame_Len) + 1) < USARTx_Rev_Buff)//ָ���ܳ���������Χ��˵���ѽ����¸�����ѭ
            {
                //����֡���ȵ�֡ͷ����2�Ǽ�ȥ0x0d��0x0a
                //֡�����ڵ�ַ = ������ĩ��ַ - �������׵�ַ + д��ַ - ��֡��������0x0a��0x0d��
                *((USARTx_BUFF_MAX_ADDR - USARTx_Rev_Buff + (*USARTx_WRITE_POINT) - ((*USARTx_Frame_Len) - 2))) = *USARTx_Frame_Len - 2;
            }
            else
            {
                *(*USARTx_WRITE_POINT - (*USARTx_Frame_Len) + 1) = *USARTx_Frame_Len - 2;//����֡���ȵ�֡ͷ����2�Ǽ�ȥ0x0d��0x0a
            }

            (*USARTx_Frame_Len) = 0;                            //֡�������㣬Ϊ�´μ���׼��
            (*USARTx_WRITE_POINT) ++;                           //д����ָ�����ƣ�Ԥ��һ���ֽ���д��һ֡����

            if((*USARTx_WRITE_POINT) > (USARTx_BUFF_MAX_ADDR))  //дָ����ڻ�����������ֵַ
            {
                *USARTx_WRITE_POINT = USARTx_Rev_Buff;          //��дָ��ָ�򻺳����׵�ַ,ѭ���洢
            }

            return 1;                                           //��֡������ϣ��˳�����,����1

        }
    }

    return 0;
}


/*
*********************************************************************************************************
*	�� �� ��: USART1_IRQHandler
*	����˵��: ����1�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#if D_USART1_EN
void USART1_IRQHandler(void)
{
    int8_t  res;
    if(USART_GetFlagStatus(USART1, USART_IT_RXNE))              //���յ������ж�
    {
        res = USARTx_Revice_Data(USART1);                       //���ô��ڽ������ݺ����ѽ��յ�������
        //����ŵ���Ӧ�����ݻ�����
        if(res == 1)                                            //���յ�������֡
        {
            D_DEBUG_printf("USART1���յ�������֡��");
        }
        else if(res == -1)
        {
            D_DEBUG_printf("USART1���ջ�����������");
        }
    }
}
#endif
/*
*********************************************************************************************************
*	�� �� ��: USART2_IRQHandler
*	����˵��: ����2�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#if D_USART2_EN
void USART2_IRQHandler(void)
{
    int8_t res;
    if(USART_GetFlagStatus(USART2, USART_IT_RXNE))              //���յ������ж�
    {
        res = USARTx_Revice_Data(USART2);                       //���ô��ڽ������ݺ����ѽ��յ�������
        //����ŵ���Ӧ�����ݻ�����
        if(res == 1)                                            //���յ�������֡
        {
            D_DEBUG_printf("USART2���յ�������֡��");
        }
        else if(res == -1)
        {
            D_DEBUG_printf("USART2���ջ�����������");
        }
    }
}
#endif
/*
*********************************************************************************************************
*	�� �� ��: USART3_IRQHandler
*	����˵��: ����3�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#if D_USART3_EN
void USART3_IRQHandler(void)
{
    int8_t res;
    if(USART_GetFlagStatus(USART3, USART_IT_RXNE))              //���յ������ж�
    {
        res = USARTx_Revice_Data(USART3);                       //���ô��ڽ������ݺ����ѽ��յ�������
        //����ŵ���Ӧ�����ݻ�����
        if(res == 1)                                            //���յ�������֡
        {
            D_DEBUG_printf("USART3���յ�������֡��");
        }
        else if(res == -1)
        {
            D_DEBUG_printf("USART3���ջ�����������");
        }
    }
}
#endif
/*
*********************************************************************************************************
*	�� �� ��: UART4_IRQHandler
*	����˵��: ����4�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#if D_UART4_EN
void UART4_IRQHandler(void)
{
    int8_t res;
    if(USART_GetFlagStatus(UART4, USART_IT_RXNE))               //���յ������ж�
    {
        res = USARTx_Revice_Data(UART4);                        //���ô��ڽ������ݺ����ѽ��յ�������
        //����ŵ���Ӧ�����ݻ�����
        if(res == 1)                                            //���յ�������֡
        {
            D_DEBUG_printf("UART4���յ�������֡��");
        }
        else if(res == -1)
        {
            D_DEBUG_printf("UART4���ջ�����������");
        }
    }
}
#endif
/*
*********************************************************************************************************
*	�� �� ��: UART5_IRQHandler
*	����˵��: ����5�жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
#if D_UART5_EN
void UART5_IRQHandler(void)
{
    int8_t res;
    if(USART_GetFlagStatus(UART5, USART_IT_RXNE))               //���յ������ж�
    {
        res = USARTx_Revice_Data(UART5);                         //���ô��ڽ������ݺ����ѽ��յ�������
        //����ŵ���Ӧ�����ݻ�����
        if(res == 1)                                            //���յ�������֡
        {
            D_DEBUG_printf("UART5���յ�������֡��");
        }
        else if(res == -1)
        {
            D_DEBUG_printf("UART5���ջ�����������");
        }
    }
}
#endif

/*
*************************************************************************************************************
*	�� �� ��: USARTx_Read()
*	����˵��: ���ڶ�ȡ���ݺ���
*	��    ��: USART_TypeDef* P_USARTx : ���ĸ������ж�����
*	�� �� ֵ: 1����ȡ�ɹ�  0��û�д���ȡ������֡  -1������ʹ��ʧ�ܻ�����ԭ���µĶ�ȡʧ��
*************************************************************************************************************
*/
int8_t G_USARTx_Read_Buff[D_USARTx_READ_BUFF_LEN];   //�Ӵ��ڽ��ջ��������������ݽ������ڸ�������
int8_t USARTx_Read(USART_TypeDef* P_USARTx)
{
    uint8_t *USARTx_Rev_Buff;                       //ָ�򴮿ڻ�������ָ��
    uint8_t *USARTx_Total_Frame;                    //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    uint8_t **USARTx_READ_POINT;                    //ָ�����USART_BUFFָ���ָ��
    uint8_t *USARTx_BUFF_MAX_ADDR;                  //ָ����ջ���������ַ
    uint8_t *temp;

    /********************************���ڵ�ѡ��************************************/
    switch((uint32_t)P_USARTx)
    {
#if D_USART1_EN
    case (uint32_t)USART1 :
    {
        USARTx_Rev_Buff    = USARTS_RX_Struct.Usart1_Rx_Buff;
        USARTx_Total_Frame = &USARTS_RX_Struct.Usart1_Total_Frame;
        USARTx_READ_POINT  = &USARTS_RX_Struct.Usart1_READ_POINT;
        USARTx_BUFF_MAX_ADDR = USARTS_RX_Struct.Usart1_Rx_Buff_MAX_ADDR;
    }
    break;
#endif

#if D_USART2_EN
    case (uint32_t)USART2 :
    {
        USARTx_Rev_Buff    = USARTS_RX_Struct.Usart2_Rx_Buff;
        USARTx_Total_Frame = &USARTS_RX_Struct.Usart2_Total_Frame;
        USARTx_READ_POINT  = &USARTS_RX_Struct.Usart2_READ_POINT;
        USARTx_BUFF_MAX_ADDR = USARTS_RX_Struct.Usart2_Rx_Buff_MAX_ADDR;
    }
    break;
#endif

#if D_USART3_EN
    case (uint32_t)USART3 :
    {
        USARTx_Rev_Buff    = USARTS_RX_Struct.Usart3_Rx_Buff;
        USARTx_Total_Frame = &USARTS_RX_Struct.Usart3_Total_Frame;
        USARTx_READ_POINT  = &USARTS_RX_Struct.Usart3_READ_POINT;
        USARTx_BUFF_MAX_ADDR = USARTS_RX_Struct.Usart3_Rx_Buff_MAX_ADDR;
    }
    break;
#endif

#if D_UART4_EN
    case (uint32_t)UART4  :
    {
        USARTx_Rev_Buff    = USARTS_RX_Struct.Uart4_Rx_Buff;
        USARTx_Total_Frame = &USARTS_RX_Struct.Uart4_Total_Frame;
        USARTx_READ_POINT  = &USARTS_RX_Struct.Uart4_READ_POINT;
        USARTx_BUFF_MAX_ADDR = USARTS_RX_Struct.Uart4_Rx_Buff_MAX_ADDR;
    }
    break;
#endif

#if D_UART5_EN
    case (uint32_t)UART5  :
    {
        USARTx_Rev_Buff    = USARTS_RX_Struct.Uart5_Rx_Buff;
        USARTx_Total_Frame = &USARTS_RX_Struct.Uart5_Total_Frame;
        USARTx_READ_POINT  = &USARTS_RX_Struct.Uart5_READ_POINT;
        USARTx_BUFF_MAX_ADDR = USARTS_RX_Struct.Uart5_Rx_Buff_MAX_ADDR;
    }
    break;
#endif
    default :
    {
        D_DEBUG_printf("��ѡ����δʹ�ܻ�ʹ��ʧ�ܣ�");
//            D_DEBUG_printf("%x",(uint32_t)P_USARTx);
//            while(1);
    }
    }

    /**********************************************************************************************************/

    /***********************************��ѡ�еĴ��ڽ��ջ��������ж�ȡ*****************************************/

    if((*USARTx_Total_Frame) > 0)                                              //���ջ��������д���ȡ������֡
    {
        (*USARTx_Total_Frame) --;
        //*USARTx_READ_POINTΪ��ָ���ַ��*(*USARTx_READ_POINT)Ϊ��֡�ľ�֡����
        temp = (*USARTx_READ_POINT) + (*(*USARTx_READ_POINT));
        if(temp < USARTx_BUFF_MAX_ADDR)                                         //��֡���ݰ���ַ�����洢������������ͬһ��ѭ����
        {
            memcpy(G_USARTx_Read_Buff, *USARTx_READ_POINT, (*(*USARTx_READ_POINT)) + 2); //+1��Ϊ�˰ѽ�����'\0'Ҳ���ƽ�ȥ
            *USARTx_READ_POINT = temp + 2;
        }
        else
        {
            //������һ������ѭ���дӶ�ָ��λ�õ����ջ����������ݵ���������
            memcpy(G_USARTx_Read_Buff, *USARTx_READ_POINT, (uint32_t)USARTx_BUFF_MAX_ADDR - (uint32_t)(*USARTx_READ_POINT) + 1);

            //�ӻ������׵�ַ��ʼ�������Ʊ�֡ʣ�����ݵ���������
            memcpy(G_USARTx_Read_Buff + (uint32_t)USARTx_BUFF_MAX_ADDR - (uint32_t)(*USARTx_READ_POINT) + 1,
                   USARTx_Rev_Buff, (*(*USARTx_READ_POINT) + (uint32_t)(*USARTx_READ_POINT) + 1 - (uint32_t)USARTx_BUFF_MAX_ADDR));

            //������һ֡���ݵĿ�ʼ = ��ָ���ַ + ��֡�� + 1 + �������׵�ַ - ������ĩ��ַ
            *USARTx_READ_POINT = temp + 1 + (uint32_t)USARTx_Rev_Buff - (uint32_t)USARTx_BUFF_MAX_ADDR;
        }
        return 1;
    }
    else
    {
        return 0;                                       //����0
    }

}

/**************��һ���ڶ�����*************************/
void USART1_circulation()
{
    uint8_t *temp;
    if(USARTS_RX_Struct.Usart1_Total_Frame > 0 )
    {

        temp = USARTS_RX_Struct.Usart1_READ_POINT + (*USARTS_RX_Struct.Usart1_READ_POINT);
        //��Ϊ֡�׵�һ���ֽ����ڴ洢֡�������Զ�ȡ��ʵ��Ϣʱ��ָ��Ҫ��1���ֽ�
        D_DEBUG_printf("%s", USARTS_RX_Struct.Usart1_READ_POINT + 1);
        if(temp < (&USARTS_RX_Struct.Usart1_Rx_Buff[99]))    //��֡���ݰ���ַ�����洢
        {
            //������ָ���֡�����ֽ�,ͬʱ��2������'\0'ָ����һ֡��֡��
            USARTS_RX_Struct.Usart1_READ_POINT = temp + 2;
        }
        else
        {

            //�ӻ������׵�ַ��ʼ������ȡ��֡ʣ����Ϣ��������֡�����Ľ������������ζ�ȡ
            D_DEBUG_printf("%s", USARTS_RX_Struct.Usart1_Rx_Buff);

            //������һ֡���ݵĿ�ʼ
            USARTS_RX_Struct.Usart1_READ_POINT = temp + 1 - D_USART1_BUFF_LEN + 1;

        }


        USARTS_RX_Struct.Usart1_Total_Frame--;

    }
}

/*************************Copyright:CJ  (END OF FILE)********************/