/*
************************************************************************
*
*   文件名称：BSP_USART.h
*   文件说明：BSP_USART.c对应的头文件
*   版    本：V1.0
*   修改记录：
*       版本号  日期            作者            说明
*       V1.0    2017-03-20      CJ              初次编写
*
*   Copyright  (C):CJ
*
************************************************************************
*/

#ifndef __BSP_USART_H__
#define __BSP_USART_H__

#include "sys.h"

/*
*********************************************************************************************************
*   
*   数据结构
*
*********************************************************************************************************
*/

extern USART_TypeDef *G_USARTx_printf;        //该全局变量用于设置将 printf 函数重定向到哪个串口，默认为USART1

//定义调试串口
#define DEBUF_USART			USART1

//重定向后串口发送函数
#define D_USART1_printf(...)    do{G_USARTx_printf = USART1; printf("[DATA FROM USART1]:\t"); printf(__VA_ARGS__); printf("\r\n");G_USARTx_printf = DEBUF_USART;}while(0)
#define D_USART2_printf(...)    do{G_USARTx_printf = USART2; printf("[DATA FROM USART2]:\t"); printf(__VA_ARGS__); printf("\r\n");G_USARTx_printf = DEBUF_USART;}while(0)
#define D_USART3_printf(...)    do{G_USARTx_printf = USART3; printf("[DATA FROM USART3]:\t"); printf(__VA_ARGS__); printf("\r\n");G_USARTx_printf = DEBUF_USART;}while(0)
#define D_UART4_printf(...)     do{G_USARTx_printf = UART4 ; printf("[DATA FROM UART4]:\t");  printf(__VA_ARGS__); printf("\r\n");G_USARTx_printf = DEBUF_USART;}while(0)
#define D_UART5_printf(...)     do{G_USARTx_printf = UART5 ; printf("[DATA FROM UART5]:\t");  printf(__VA_ARGS__); printf("\r\n");G_USARTx_printf = DEBUF_USART;}while(0)

#define D_DEBUG_printf(...)     do{G_USARTx_printf = DEBUF_USART; printf("[DEBUG INF]:\t"); printf(__VA_ARGS__);printf("\r\n");}while(0)

//串口裁剪配置
#define D_USART1_EN         1
#define D_USART2_EN         0
#define D_USART3_EN         0
#define D_UART4_EN          0
#define D_UART5_EN          0

//串口优先级设置
#define D_USART1_Priority   2
#define D_USART2_Priority   3
#define D_USART3_Priority   2
#define D_UART4_Priority    3
#define D_UART5_Priority    3

#define D_EN_USART1_RX      1
#define D_USART1_BUFF_LEN   100      //串口1接收缓冲区大小
#define D_EN_USART2_RX      1
#define D_USART2_BUFF_LEN   100      //串口2接收缓冲区大小
#define D_EN_USART3_RX      1
#define D_USART3_BUFF_LEN   100      //串口3接收缓冲区大小
#define D_EN_UART4_RX       1
#define D_UART4_BUFF_LEN    100      //串口4接收缓冲区大小
#define D_EN_UART5_RX       1
#define D_UART5_BUFF_LEN    100      //串口5接收缓冲区大小  
  

#define D_USARTx_READ_BUFF_LEN 100   //从串口接收缓冲区读出的数据将缓存在该区域的读缓冲区长度
extern int8_t G_USARTx_Read_Buff[D_USARTx_READ_BUFF_LEN];   //从串口接收缓冲区读出的数据将缓存在该区域内

//串口波特率和引脚配置
//USART1
#define D_USART1_BAND       115200
#define D_USART1_GPIO       GPIOA           //GPIOA:PA9->Tx  PA10->Rx   GPIOB:PB6->Tx  PB7->Rx
#define D_USART1_BUFF_SIZE  100

//USART2
#define D_USART2_BAND       115200
#define D_USART2_GPIO       GPIOA           //GPIOA:PA2->Tx  PA3->Rx   GPIOD:PD5->Tx   PD6->Rx USART2_TX引脚GPIOD5与LCD的FSMC_NEW引脚相同，故两者不能同时使用
#define D_USART2_BUFF_SIZE  100

//USART3   
#define D_USART3_BAND       115200
#define D_USART3_GPIO       GPIOC           //GPIOB:PB10->Tx  PB11->Rx   GPIOC:PC10->Tx  PC11->Rx   USART3与UART4不能同时映射到GPIOC
#define D_USART3_BUFF_SIZE  100

//UART4    
#define D_UART4_BAND        115200
#define D_UART4_GPIO        GPIOA           //GPIOA:PA0->Tx  PA1->Rx    GPIOC:PC10->Tx   PC11->Rx
#define D_UART4_BUFF_SIZE   100

//UART5   因为UART5没有引脚重映射功能，所以不需要提供引脚信息便可确定 
#define D_UART5_BAND        115200
#define D_UART5_BUFF_SIZE   100



//串口DMA选择配置 1为开启，0为不开启
#define D_USART1_DMA        1
#define D_USART2_DMA        1
#define D_USART3_DMA        1
#define D_UART4_DMA         1
#define D_UART5_DMA         1      

typedef struct                              //串口接受到的数据缓冲区和读写指针     
{
#if D_USART1_EN    
    uint8_t  Usart1_Rx_Buff[D_USART1_BUFF_LEN];
    uint8_t  Usart1_Read_Stop;              //缓冲区后第一个字节固定为结束符，防止读指针越界
    uint8_t  Usart1_Frame_Len;              //记录帧长度，
    uint8_t  Usart1_Total_Frame;            //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    uint8_t* Usart1_WRITE_POINT;            //写入USART_BUFF指针
    uint8_t* Usart1_READ_POINT;             //读出USART_BUFF指针
    uint8_t* Usart1_Rx_Buff_MAX_ADDR;       //缓冲区最大内存地址
#endif
    
#if D_USART2_EN    
    uint8_t  Usart2_Rx_Buff[D_USART2_BUFF_LEN];
    uint8_t  Usart2_Read_Stop;              //缓冲区后第一个字节固定为结束符，防止读指针越界
    uint8_t  Usart2_Frame_Len;              //记录帧长度，
    uint8_t  Usart2_Total_Frame;            //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    u8* Usart2_WRITE_POINT;            //写入USART_BUFF指针
    u8* Usart2_READ_POINT;             //读出USART_BUFF指针
    u8* Usart2_Rx_Buff_MAX_ADDR;       //缓冲区最大内存地址
#endif
    
#if D_USART3_EN    
    uint8_t  Usart3_Rx_Buff[D_USART3_BUFF_LEN];
    uint8_t  Usart3_Read_Stop;              //缓冲区后第一个字节固定为结束符，防止读指针越界
    uint8_t  Usart3_Frame_Len;              //记录帧长度
    uint8_t  Usart3_Total_Frame;            //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    uint8_t* Usart3_WRITE_POINT;            //写入USART_BUFF指针
    uint8_t* Usart3_READ_POINT;             //读出USART_BUFF指针
    uint8_t* Usart3_Rx_Buff_MAX_ADDR;       //缓冲区最大内存地址
#endif

#if D_UART4_EN    
    uint8_t  Uart4_Rx_Buff[D_UART4_BUFF_LEN];
    uint8_t  Uart4__Read_Stop;             //缓冲区后第一个字节固定为结束符，防止读指针越界
    uint8_t  Uart4_Frame_Len;              //记录帧长度，
    uint8_t  Uart4_Total_Frame;            //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    uint8_t* Uart4_WRITE_POINT;            //写入USART_BUFF指针
    uint8_t* Uart4_READ_POINT;             //读出USART_BUFF指针
    uint8_t* Uart4_Rx_Buff_MAX_ADDR;       //缓冲区最大内存地址
#endif
    
#if D_UART5_EN    
    uint8_t  Uart5_Rx_Buff[D_UART5_BUFF_LEN];
    uint8_t  Uart5__Read_Stop;             //缓冲区后第一个字节固定为结束符，防止读指针越界
    uint8_t  Uart5_Frame_Len;              //记录帧长度，
    uint8_t  Uart5_Total_Frame;            //记录接收到的数据帧数，写入一帧加1，读出一帧减一
    uint8_t* Uart5_WRITE_POINT;            //写入USART_BUFF指针
    uint8_t* Uart5_READ_POINT;             //读出USART_BUFF指针
    uint8_t* Uart5_Rx_Buff_MAX_ADDR;       //缓冲区最大内存地址
#endif 

}USARTS_RX_Typedef;

extern USARTS_RX_Typedef USARTS_RX_Struct;             //串口接受到的数据缓冲区和读写指针           



void BSP_USARTS_Init(void);
int8_t USARTx_Read(USART_TypeDef* P_USARTx);
void USARTS_Send_Strings(USART_TypeDef* P_USARTx, uint8_t* P_Str, uint32_t P_Str_Len);

#endif




/*************************Copyright:CJ  (END OF FILE)********************/
