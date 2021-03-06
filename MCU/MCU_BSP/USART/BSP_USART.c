/*
************************************************************************
*
*   文件名称：BSP_USART.c
*   文件说明：串口相关的驱动
*   版    本：V1.0
*   修改记录：
*       版本号  日期            作者            说明
*       V1.0    2017-03-20      CJ              初次编写
*
*   Copyright  (C):CJ
*
************************************************************************
*/

#include "BSP_DRIVE.h"
#include <string.h>

/*
*********************************************************************************************************
*	函 数 名: BSP_USARTS_Init()
*	功能说明: 初始化串口
*	形    参:
*           P_USARTS_Struct      : 串口波特率结构体
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_USARTS_Init()
{

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

#if D_USART1_EN	                                                //开启USART1

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);      //使能USART1时钟
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	        //速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;              //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                //上拉

    if(D_USART1_GPIO == GPIOA)                                  //USART1使用引脚PA9/PA10
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   //使能GPIOA时钟
        //串口1对应引脚复用映射
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); //GPIOA9复用为USART1
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //GPIOA10复用为USART1

        //USART1端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
        GPIO_Init(GPIOA, &GPIO_InitStructure);                  //初始化PA9，PA10
    }
    if(D_USART1_GPIO == GPIOB)                                 //USART1使用引脚PB6/PB7
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   //使能GPIOB时钟
        //串口1对应引脚复用映射
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1); //GPIOB6复用为USART1
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1); //GPIOB7复用为USART1

        //USART1端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  //GPIOA9与GPIOA10
        GPIO_Init(GPIOB, &GPIO_InitStructure);                  //初始化PB6，PB7
    }

    //USART1 初始化设置
    USART_InitStructure.USART_BaudRate = D_USART1_BAND;         //波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;         //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure);                   //初始化串口1

    USART_Cmd(USART1, ENABLE);                                  //使能串口1

    USART_ClearFlag(USART1, USART_FLAG_TC);

#if D_EN_USART1_RX
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);              //开启相关中断

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;           //串口1中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = D_USART1_Priority; //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		   //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	                            //根据指定的参数初始化VIC寄存器、

#endif      //#if D_EN_USART1_RX

#endif      //#if D_USART1_EN

#if D_USART2_EN	                                                //开启USART2

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);      //使能USART2时钟
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	        //速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;              //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                //上拉

    if(D_USART2_GPIO == GPIOA)                                  //USART2使用引脚PA2/PA3
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   //使能GPIOA时钟
        //串口2对应引脚复用映射
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //GPIOA2复用为USART2
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //GPIOA3复用为USART2

        //USART2端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;  //GPIOA2与GPIOA3
        GPIO_Init(GPIOA, &GPIO_InitStructure);                  //初始化PA2，PA3
    }
    if(D_USART2_GPIO == GPIOD)                                  //USART2使用引脚PD5/PD6
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);   //使能GPIOD时钟
        //串口2对应引脚复用映射
        GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2); //GPIOD5复用为USART2
        GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2); //GPIOD6复用为USART2

        //USART1端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;  //GPIOD5与GPIOD6
        GPIO_Init(GPIOD, &GPIO_InitStructure);                  //初始化PD5，PD6
    }

    //USART2 初始化设置
    USART_InitStructure.USART_BaudRate = D_USART2_BAND;         //波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;         //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART2, &USART_InitStructure);                   //初始化串口2

    USART_Cmd(USART2, ENABLE);                                  //使能串口2

    USART_ClearFlag(USART2, USART_FLAG_TC);

#if D_EN_USART2_RX
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);              //开启相关中断

    //Usart2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;           //串口2中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = D_USART2_Priority; //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		   //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	                            //根据指定的参数初始化VIC寄存器、

#endif      //#if D_EN_USART2_RX
#endif      //#if D_USART2_EN

#if D_USART3_EN	                                                //开启USART3

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);      //使能USART3时钟
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	        //速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;              //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                //上拉

    if(D_USART3_GPIO == GPIOB)                                  //USART3使用引脚PB10/PB11
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   //使能GPIOB时钟
        //串口3对应引脚复用映射
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3); //GPIOB10复用为USART3
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3); //GPIOB11复用为USART3

        //USART3端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//GPIOB10与GPIOB11
        GPIO_Init(GPIOB, &GPIO_InitStructure);                  //初始化PB10，PB11
    }
    if(D_USART3_GPIO == GPIOC)                                  //USART3使用引脚PC10/PC11
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);   //使能GPIOD时钟
        //串口3对应引脚复用映射
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3); //GPIOC10复用为USART3
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3); //GPIOC11复用为USART3

        //USART3端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//GPIOC10与GPIOC11
        GPIO_Init(GPIOC, &GPIO_InitStructure);                  //初始化PC10，PC11
    }

    //USART3 初始化设置
    USART_InitStructure.USART_BaudRate = D_USART3_BAND;         //波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;         //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART3, &USART_InitStructure);                   //初始化串口3

    USART_Cmd(USART3, ENABLE);                                  //使能串口3

    USART_ClearFlag(USART3, USART_FLAG_TC);

#if D_EN_USART3_RX
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);              //开启相关中断

    //Usart3 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;           //串口3中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = D_USART3_Priority; //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		   //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	                            //根据指定的参数初始化VIC寄存器、

#endif      //#if D_EN_USART3_RX
#endif      //#if D_USART3_EN

#if D_UART4_EN	                                                //开启USART3

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);       //使能USART3时钟
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	        //速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;              //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                //上拉

    if(D_UART4_GPIO == GPIOA)                                   //UART4使用引脚PA0/PA1
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   //使能GPIOA时钟
        //串口2对应引脚复用映射
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4); //GPIOA0复用为UART4
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4); //GPIOA1复用为UART4

        //USART3端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;  //GPIOA0与GPIOA1
        GPIO_Init(GPIOA, &GPIO_InitStructure);                  //初始化PA0，PA1
    }
    if(D_UART4_GPIO == GPIOC)                                   //UART4使用引脚PC10/PC11
    {
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);   //使能GPIOC时钟
        //串口4对应引脚复用映射
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4); //GPIOC10复用为UART4
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4); //GPIOC11复用为UART4

        //UART4端口配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//GPIOC10与GPIOC11
        GPIO_Init(GPIOC, &GPIO_InitStructure);                  //初始化PC10，PC11
    }

    //USART3 初始化设置
    USART_InitStructure.USART_BaudRate = D_UART4_BAND;          //波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;         //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(UART4, &USART_InitStructure);                    //初始化串口4

    USART_Cmd(UART4, ENABLE);                                   //使能串口4

    USART_ClearFlag(UART4, USART_FLAG_TC);

#if D_EN_UART4_RX
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);               //开启相关中断

    //Usart3 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;            //串口4中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = D_UART4_Priority; //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		   //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			    //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	                            //根据指定的参数初始化VIC寄存器、

#endif      //#if D_EN_UART4_RX
#endif      //#if D_UART4_EN

}


/*
*******************************************************************************************************
*   在标准库下重定向 printf 到串口需要增加的代码，使用 MicroLIB 可不用这部分代码
*/
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
    int handle;

};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
    x = x;
}

/*
********************************************************************************************************
*/

/*
*********************************************************************************************************
*	函 数 名: fputc
*	功能说明: 重定向函数，重定向后可以使用printf 函数向串口发送数据
*	形    参:
*	返 回 值:
*********************************************************************************************************
*/
USART_TypeDef *G_USARTx_printf = USART1;        //变量用于设置将 printf 函数重定向到哪个串口，默认为USART1
int fputc(int ch, FILE *f)
{
    while((G_USARTx_printf->SR & 0X40) == 0);   //循环发送,直到发送完毕
    G_USARTx_printf->DR = (u8) ch;
    return ch;
}

USARTS_RX_Typedef USARTS_RX_Struct =            //串口接受到的数据缓冲区和读写指针
{
#if D_USART1_EN
    {0},
    '\0',                                       //初始化为结束符
    0,                                          //帧长度初始化为0
    0,                                          //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    USARTS_RX_Struct.Usart1_Rx_Buff,            //写入USART_BUFF指针，
    USARTS_RX_Struct.Usart1_Rx_Buff,            //读出USART_BUFF指针
    USARTS_RX_Struct.Usart1_Rx_Buff + D_USART1_BUFF_LEN - 1,//接收缓冲区最大地址
#endif

#if D_USART2_EN
    {0},
    '\0',                                       //初始化为结束符
    0,                                          //帧长度初始化为0
    0,                                          //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    USARTS_RX_Struct.Usart2_Rx_Buff,            //写入USART_BUFF指针，
    USARTS_RX_Struct.Usart2_Rx_Buff,            //读出USART_BUFF指针
    USARTS_RX_Struct.Usart2_Rx_Buff + D_USART1_BUFF_LEN - 1,//接收缓冲区最大地址
#endif

#if D_USART3_EN
    {0},
    '\0',                                       //初始化为结束符
    0,                                          //帧长度初始化为0
    0,                                          //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    USARTS_RX_Struct.Usart3_Rx_Buff,            //写入USART_BUFF指针，
    USARTS_RX_Struct.Usart3_Rx_Buff,            //读出USART_BUFF指针
    USARTS_RX_Struct.Usart3_Rx_Buff + D_USART1_BUFF_LEN - 1,//接收缓冲区最大地址
#endif

#if D_UART4_EN
    {0},
    '\0',                                       //初始化为结束符
    0,                                          //帧长度初始化为0
    0,                                          //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    USARTS_RX_Struct.Uart4_Rx_Buff,             //写入USART_BUFF指针，
    USARTS_RX_Struct.Uart4_Rx_Buff,             //读出USART_BUFF指针
    USARTS_RX_Struct.Uart4_Rx_Buff + D_USART1_BUFF_LEN - 1,//接收缓冲区最大地址
#endif

#if D_UART5_EN
    {0},
    '\0',                                       //初始化为结束符
    0,                                          //帧长度初始化为0
    0,                                          //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    USARTS_RX_Struct.Uart5_Rx_Buff,             //写入USART_BUFF指针，
    USARTS_RX_Struct.Uart5_Rx_Buff,             //读出USART_BUFF指针
    USARTS_RX_Struct.Uart5_Rx_Buff + D_USART1_BUFF_LEN - 1,//接收缓冲区最大地址
#endif
};
/*
*********************************************************************************************************
*	函 数 名: USARTx_Revice_Data
*	功能说明: 通过串口发送字符串
*	形    参:
*           P_USARTx    : 接收数据的串口
*	返 回 值: 1：本帧接收成功，   0：本字节接收成功但本帧接收未完成，  -1：缓冲区溢出
*********************************************************************************************************
*/
int8_t USARTx_Revice_Data(USART_TypeDef* P_USARTx)
{
    uint8_t *USARTx_Rev_Buff;                       //指向串口缓冲区的指针
    uint8_t *USARTx_Frame_Len;                      //指向帧长记录字节的指针
    uint8_t *USARTx_Total_Frame;                    //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    uint8_t **USARTx_WRITE_POINT;                   //指向写入USART_BUFF指针的指针
    uint8_t **USARTx_READ_POINT;                    //指向读出USART_BUFF指针的指针
    uint8_t *USARTx_BUFF_MAX_ADDR;                  //用于记录串口接收缓冲区最大地址值

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
        D_DEBUG_printf("所选串口未使能或使能失败！");
//            D_DEBUG_printf("%x",(uint32_t)P_USARTx);
//            while(1);
    }
    }
    if(USARTx_WRITE_POINT == USARTx_READ_POINT)
    {
        return -1;                                              //缓冲区已满，返回-1
    }
    (*USARTx_WRITE_POINT) ++;                                   //写指针总是指向最后写入的数据的地址
    if((*USARTx_WRITE_POINT) > (USARTx_BUFF_MAX_ADDR))          //写指针大于缓冲区的最大地址值
    {
        *USARTx_WRITE_POINT = USARTx_Rev_Buff;                  //将写指针指向缓冲区首地址,循环存储
    }
    *(*USARTx_WRITE_POINT) = P_USARTx -> DR & (uint16_t)0x01FF; //接收新数据
    (*USARTx_Frame_Len) ++ ;                                    //帧长度自加1
    if(**USARTx_WRITE_POINT == 0x0a)                            //判断新接收的数据是否是0x0a
    {
        if((*(*USARTx_WRITE_POINT - 1)) == 0x0d)                //如果是则判断上次接收的是否是0x0d,是则表示本次接收完毕
        {
            (*USARTx_WRITE_POINT)--;                            //写指针上移到0x0d位置，为在这个位置填入‘\0’做准备
            *(*USARTx_WRITE_POINT) = '\0';
            (*USARTx_Total_Frame)++;                            //本帧接收完毕,帧数加一
//            (*USARTx_Frame_Len) -= 2;                         //数据长度减去结束符0x0d所占的长度得到真实数据长度

            if((*USARTx_WRITE_POINT - (*USARTx_Frame_Len) + 1) < USARTx_Rev_Buff)//指针跑出缓冲区范围，说明已进入下个缓冲循
            {
                //填入帧长度到帧头，减2是减去0x0d和0x0a
                //帧长所在地址 = 缓冲区末地址 - 缓冲区首地址 + 写地址 - 净帧长（除掉0x0a和0x0d）
                *((USARTx_BUFF_MAX_ADDR - USARTx_Rev_Buff + (*USARTx_WRITE_POINT) - ((*USARTx_Frame_Len) - 2))) = *USARTx_Frame_Len - 2;
            }
            else
            {
                *(*USARTx_WRITE_POINT - (*USARTx_Frame_Len) + 1) = *USARTx_Frame_Len - 2;//填入帧长度到帧头，减2是减去0x0d和0x0a
            }

            (*USARTx_Frame_Len) = 0;                            //帧长度清零，为下次计数准备
            (*USARTx_WRITE_POINT) ++;                           //写数据指针下移，预留一个字节填写下一帧长度

            if((*USARTx_WRITE_POINT) > (USARTx_BUFF_MAX_ADDR))  //写指针大于缓冲区的最大地址值
            {
                *USARTx_WRITE_POINT = USARTx_Rev_Buff;          //将写指针指向缓冲区首地址,循环存储
            }

            return 1;                                           //本帧接收完毕，退出函数,返回1

        }
    }

    return 0;
}


/*
*********************************************************************************************************
*	函 数 名: USART1_IRQHandler
*	功能说明: 串口1中断服务函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
#if D_USART1_EN
void USART1_IRQHandler(void)
{
    int8_t  res;
    if(USART_GetFlagStatus(USART1, USART_IT_RXNE))              //接收到数据中断
    {
        res = USARTx_Revice_Data(USART1);                       //调用串口接收数据函数把接收到的数据
        //并存放到相应的数据缓冲区
        if(res == 1)                                            //接收到完整的帧
        {
            D_DEBUG_printf("USART1接收到完整的帧！");
        }
        else if(res == -1)
        {
            D_DEBUG_printf("USART1接收缓冲区已满！");
        }
    }
}
#endif
/*
*********************************************************************************************************
*	函 数 名: USART2_IRQHandler
*	功能说明: 串口2中断服务函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
#if D_USART2_EN
void USART2_IRQHandler(void)
{
    int8_t res;
    if(USART_GetFlagStatus(USART2, USART_IT_RXNE))              //接收到数据中断
    {
        res = USARTx_Revice_Data(USART2);                       //调用串口接收数据函数把接收到的数据
        //并存放到相应的数据缓冲区
        if(res == 1)                                            //接收到完整的帧
        {
            D_DEBUG_printf("USART2接收到完整的帧！");
        }
        else if(res == -1)
        {
            D_DEBUG_printf("USART2接收缓冲区已满！");
        }
    }
}
#endif
/*
*********************************************************************************************************
*	函 数 名: USART3_IRQHandler
*	功能说明: 串口3中断服务函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
#if D_USART3_EN
void USART3_IRQHandler(void)
{
    int8_t res;
    if(USART_GetFlagStatus(USART3, USART_IT_RXNE))              //接收到数据中断
    {
        res = USARTx_Revice_Data(USART3);                       //调用串口接收数据函数把接收到的数据
        //并存放到相应的数据缓冲区
        if(res == 1)                                            //接收到完整的帧
        {
            D_DEBUG_printf("USART3接收到完整的帧！");
        }
        else if(res == -1)
        {
            D_DEBUG_printf("USART3接收缓冲区已满！");
        }
    }
}
#endif
/*
*********************************************************************************************************
*	函 数 名: UART4_IRQHandler
*	功能说明: 串口4中断服务函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
#if D_UART4_EN
void UART4_IRQHandler(void)
{
    int8_t res;
    if(USART_GetFlagStatus(UART4, USART_IT_RXNE))               //接收到数据中断
    {
        res = USARTx_Revice_Data(UART4);                        //调用串口接收数据函数把接收到的数据
        //并存放到相应的数据缓冲区
        if(res == 1)                                            //接收到完整的帧
        {
            D_DEBUG_printf("UART4接收到完整的帧！");
        }
        else if(res == -1)
        {
            D_DEBUG_printf("UART4接收缓冲区已满！");
        }
    }
}
#endif
/*
*********************************************************************************************************
*	函 数 名: UART5_IRQHandler
*	功能说明: 串口5中断服务函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
#if D_UART5_EN
void UART5_IRQHandler(void)
{
    int8_t res;
    if(USART_GetFlagStatus(UART5, USART_IT_RXNE))               //接收到数据中断
    {
        res = USARTx_Revice_Data(UART5);                         //调用串口接收数据函数把接收到的数据
        //并存放到相应的数据缓冲区
        if(res == 1)                                            //接收到完整的帧
        {
            D_DEBUG_printf("UART5接收到完整的帧！");
        }
        else if(res == -1)
        {
            D_DEBUG_printf("UART5接收缓冲区已满！");
        }
    }
}
#endif

/*
*************************************************************************************************************
*	函 数 名: USARTx_Read()
*	功能说明: 串口读取数据函数
*	形    参: USART_TypeDef* P_USARTx : 从哪个串口中读数据
*	返 回 值: 1：读取成功  0：没有待读取的数据帧  -1：串口使能失败或其他原因导致的读取失败
*************************************************************************************************************
*/
int8_t G_USARTx_Read_Buff[D_USARTx_READ_BUFF_LEN];   //从串口接收缓冲区读出的数据将缓存在该区域内
int8_t USARTx_Read(USART_TypeDef* P_USARTx)
{
    uint8_t *USARTx_Rev_Buff;                       //指向串口缓冲区的指针
    uint8_t *USARTx_Total_Frame;                    //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    uint8_t **USARTx_READ_POINT;                    //指向读出USART_BUFF指针的指针
    uint8_t *USARTx_BUFF_MAX_ADDR;                  //指向接收缓冲区最大地址
    uint8_t *temp;

    /********************************串口的选择************************************/
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
        D_DEBUG_printf("所选串口未使能或使能失败！");
//            D_DEBUG_printf("%x",(uint32_t)P_USARTx);
//            while(1);
    }
    }

    /**********************************************************************************************************/

    /***********************************对选中的串口接收缓冲区进行读取*****************************************/

    if((*USARTx_Total_Frame) > 0)                                              //接收缓冲区内有待读取的数据帧
    {
        (*USARTx_Total_Frame) --;
        //*USARTx_READ_POINT为读指针地址，*(*USARTx_READ_POINT)为该帧的净帧长度
        temp = (*USARTx_READ_POINT) + (*(*USARTx_READ_POINT));
        if(temp < USARTx_BUFF_MAX_ADDR)                                         //本帧数据按地址递增存储，所有数据在同一个循环中
        {
            memcpy(G_USARTx_Read_Buff, *USARTx_READ_POINT, (*(*USARTx_READ_POINT)) + 2); //+1是为了把结束符'\0'也复制进去
            *USARTx_READ_POINT = temp + 2;
        }
        else
        {
            //复制上一个缓冲循环中从读指针位置到接收缓冲区的数据到读缓冲区
            memcpy(G_USARTx_Read_Buff, *USARTx_READ_POINT, (uint32_t)USARTx_BUFF_MAX_ADDR - (uint32_t)(*USARTx_READ_POINT) + 1);

            //从缓冲区首地址开始继续复制本帧剩余数据到读缓冲区
            memcpy(G_USARTx_Read_Buff + (uint32_t)USARTx_BUFF_MAX_ADDR - (uint32_t)(*USARTx_READ_POINT) + 1,
                   USARTx_Rev_Buff, (*(*USARTx_READ_POINT) + (uint32_t)(*USARTx_READ_POINT) + 1 - (uint32_t)USARTx_BUFF_MAX_ADDR));

            //计算下一帧数据的开始 = 读指针地址 + 净帧长 + 1 + 缓冲区首地址 - 缓冲区末地址
            *USARTx_READ_POINT = temp + 1 + (uint32_t)USARTx_Rev_Buff - (uint32_t)USARTx_BUFF_MAX_ADDR;
        }
        return 1;
    }
    else
    {
        return 0;                                       //返回0
    }

}

/**************单一串口读数据*************************/
void USART1_circulation()
{
    uint8_t *temp;
    if(USARTS_RX_Struct.Usart1_Total_Frame > 0 )
    {

        temp = USARTS_RX_Struct.Usart1_READ_POINT + (*USARTS_RX_Struct.Usart1_READ_POINT);
        //因为帧首第一个字节用于存储帧长，所以读取真实信息时读指针要加1个字节
        D_DEBUG_printf("%s", USARTS_RX_Struct.Usart1_READ_POINT + 1);
        if(temp < (&USARTS_RX_Struct.Usart1_Rx_Buff[99]))    //本帧数据按地址递增存储
        {
            //读完后读指针加帧长个字节,同时加2，跳过'\0'指向下一帧的帧首
            USARTS_RX_Struct.Usart1_READ_POINT = temp + 2;
        }
        else
        {

            //从缓冲区首地址开始继续读取本帧剩余信息，遇到本帧真正的结束符结束本次读取
            D_DEBUG_printf("%s", USARTS_RX_Struct.Usart1_Rx_Buff);

            //计算下一帧数据的开始
            USARTS_RX_Struct.Usart1_READ_POINT = temp + 1 - D_USART1_BUFF_LEN + 1;

        }


        USARTS_RX_Struct.Usart1_Total_Frame--;

    }
}

/*************************Copyright:CJ  (END OF FILE)********************/
