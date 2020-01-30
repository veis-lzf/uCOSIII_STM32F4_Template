/*
************************************************************************
*
*   �ļ����ƣ�BSP_USART.h
*   �ļ�˵����BSP_USART.c��Ӧ��ͷ�ļ�
*   ��    ����V1.0
*   �޸ļ�¼��
*       �汾��  ����            ����            ˵��
*       V1.0    2017-03-20      CJ              ���α�д
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
*   ���ݽṹ
*
*********************************************************************************************************
*/

extern USART_TypeDef *G_USARTx_printf;        //��ȫ�ֱ����������ý� printf �����ض����ĸ����ڣ�Ĭ��ΪUSART1

//������Դ���
#define DEBUF_USART			USART1

//�ض���󴮿ڷ��ͺ���
#define D_USART1_printf(...)    do{G_USARTx_printf = USART1; printf("[DATA FROM USART1]:\t"); printf(__VA_ARGS__); printf("\r\n");G_USARTx_printf = DEBUF_USART;}while(0)
#define D_USART2_printf(...)    do{G_USARTx_printf = USART2; printf("[DATA FROM USART2]:\t"); printf(__VA_ARGS__); printf("\r\n");G_USARTx_printf = DEBUF_USART;}while(0)
#define D_USART3_printf(...)    do{G_USARTx_printf = USART3; printf("[DATA FROM USART3]:\t"); printf(__VA_ARGS__); printf("\r\n");G_USARTx_printf = DEBUF_USART;}while(0)
#define D_UART4_printf(...)     do{G_USARTx_printf = UART4 ; printf("[DATA FROM UART4]:\t");  printf(__VA_ARGS__); printf("\r\n");G_USARTx_printf = DEBUF_USART;}while(0)
#define D_UART5_printf(...)     do{G_USARTx_printf = UART5 ; printf("[DATA FROM UART5]:\t");  printf(__VA_ARGS__); printf("\r\n");G_USARTx_printf = DEBUF_USART;}while(0)

#define D_DEBUG_printf(...)     do{G_USARTx_printf = DEBUF_USART; printf("[DEBUG INF]:\t"); printf(__VA_ARGS__);printf("\r\n");}while(0)

//���ڲü�����
#define D_USART1_EN         1
#define D_USART2_EN         0
#define D_USART3_EN         0
#define D_UART4_EN          0
#define D_UART5_EN          0

//�������ȼ�����
#define D_USART1_Priority   2
#define D_USART2_Priority   3
#define D_USART3_Priority   2
#define D_UART4_Priority    3
#define D_UART5_Priority    3

#define D_EN_USART1_RX      1
#define D_USART1_BUFF_LEN   100      //����1���ջ�������С
#define D_EN_USART2_RX      1
#define D_USART2_BUFF_LEN   100      //����2���ջ�������С
#define D_EN_USART3_RX      1
#define D_USART3_BUFF_LEN   100      //����3���ջ�������С
#define D_EN_UART4_RX       1
#define D_UART4_BUFF_LEN    100      //����4���ջ�������С
#define D_EN_UART5_RX       1
#define D_UART5_BUFF_LEN    100      //����5���ջ�������С  
  

#define D_USARTx_READ_BUFF_LEN 100   //�Ӵ��ڽ��ջ��������������ݽ������ڸ�����Ķ�����������
extern int8_t G_USARTx_Read_Buff[D_USARTx_READ_BUFF_LEN];   //�Ӵ��ڽ��ջ��������������ݽ������ڸ�������

//���ڲ����ʺ���������
//USART1
#define D_USART1_BAND       115200
#define D_USART1_GPIO       GPIOA           //GPIOA:PA9->Tx  PA10->Rx   GPIOB:PB6->Tx  PB7->Rx
#define D_USART1_BUFF_SIZE  100

//USART2
#define D_USART2_BAND       115200
#define D_USART2_GPIO       GPIOA           //GPIOA:PA2->Tx  PA3->Rx   GPIOD:PD5->Tx   PD6->Rx USART2_TX����GPIOD5��LCD��FSMC_NEW������ͬ�������߲���ͬʱʹ��
#define D_USART2_BUFF_SIZE  100

//USART3   
#define D_USART3_BAND       115200
#define D_USART3_GPIO       GPIOC           //GPIOB:PB10->Tx  PB11->Rx   GPIOC:PC10->Tx  PC11->Rx   USART3��UART4����ͬʱӳ�䵽GPIOC
#define D_USART3_BUFF_SIZE  100

//UART4    
#define D_UART4_BAND        115200
#define D_UART4_GPIO        GPIOA           //GPIOA:PA0->Tx  PA1->Rx    GPIOC:PC10->Tx   PC11->Rx
#define D_UART4_BUFF_SIZE   100

//UART5   ��ΪUART5û��������ӳ�书�ܣ����Բ���Ҫ�ṩ������Ϣ���ȷ�� 
#define D_UART5_BAND        115200
#define D_UART5_BUFF_SIZE   100



//����DMAѡ������ 1Ϊ������0Ϊ������
#define D_USART1_DMA        1
#define D_USART2_DMA        1
#define D_USART3_DMA        1
#define D_UART4_DMA         1
#define D_UART5_DMA         1      

typedef struct                              //���ڽ��ܵ������ݻ������Ͷ�дָ��     
{
#if D_USART1_EN    
    uint8_t  Usart1_Rx_Buff[D_USART1_BUFF_LEN];
    uint8_t  Usart1_Read_Stop;              //���������һ���ֽڹ̶�Ϊ����������ֹ��ָ��Խ��
    uint8_t  Usart1_Frame_Len;              //��¼֡���ȣ�
    uint8_t  Usart1_Total_Frame;            //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    uint8_t* Usart1_WRITE_POINT;            //д��USART_BUFFָ��
    uint8_t* Usart1_READ_POINT;             //����USART_BUFFָ��
    uint8_t* Usart1_Rx_Buff_MAX_ADDR;       //����������ڴ��ַ
#endif
    
#if D_USART2_EN    
    uint8_t  Usart2_Rx_Buff[D_USART2_BUFF_LEN];
    uint8_t  Usart2_Read_Stop;              //���������һ���ֽڹ̶�Ϊ����������ֹ��ָ��Խ��
    uint8_t  Usart2_Frame_Len;              //��¼֡���ȣ�
    uint8_t  Usart2_Total_Frame;            //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    u8* Usart2_WRITE_POINT;            //д��USART_BUFFָ��
    u8* Usart2_READ_POINT;             //����USART_BUFFָ��
    u8* Usart2_Rx_Buff_MAX_ADDR;       //����������ڴ��ַ
#endif
    
#if D_USART3_EN    
    uint8_t  Usart3_Rx_Buff[D_USART3_BUFF_LEN];
    uint8_t  Usart3_Read_Stop;              //���������һ���ֽڹ̶�Ϊ����������ֹ��ָ��Խ��
    uint8_t  Usart3_Frame_Len;              //��¼֡����
    uint8_t  Usart3_Total_Frame;            //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    uint8_t* Usart3_WRITE_POINT;            //д��USART_BUFFָ��
    uint8_t* Usart3_READ_POINT;             //����USART_BUFFָ��
    uint8_t* Usart3_Rx_Buff_MAX_ADDR;       //����������ڴ��ַ
#endif

#if D_UART4_EN    
    uint8_t  Uart4_Rx_Buff[D_UART4_BUFF_LEN];
    uint8_t  Uart4__Read_Stop;             //���������һ���ֽڹ̶�Ϊ����������ֹ��ָ��Խ��
    uint8_t  Uart4_Frame_Len;              //��¼֡���ȣ�
    uint8_t  Uart4_Total_Frame;            //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    uint8_t* Uart4_WRITE_POINT;            //д��USART_BUFFָ��
    uint8_t* Uart4_READ_POINT;             //����USART_BUFFָ��
    uint8_t* Uart4_Rx_Buff_MAX_ADDR;       //����������ڴ��ַ
#endif
    
#if D_UART5_EN    
    uint8_t  Uart5_Rx_Buff[D_UART5_BUFF_LEN];
    uint8_t  Uart5__Read_Stop;             //���������һ���ֽڹ̶�Ϊ����������ֹ��ָ��Խ��
    uint8_t  Uart5_Frame_Len;              //��¼֡���ȣ�
    uint8_t  Uart5_Total_Frame;            //��¼���յ�������֡����д��һ֡��1������һ֡��һ
    uint8_t* Uart5_WRITE_POINT;            //д��USART_BUFFָ��
    uint8_t* Uart5_READ_POINT;             //����USART_BUFFָ��
    uint8_t* Uart5_Rx_Buff_MAX_ADDR;       //����������ڴ��ַ
#endif 

}USARTS_RX_Typedef;

extern USARTS_RX_Typedef USARTS_RX_Struct;             //���ڽ��ܵ������ݻ������Ͷ�дָ��           



void BSP_USARTS_Init(void);
int8_t USARTx_Read(USART_TypeDef* P_USARTx);
void USARTS_Send_Strings(USART_TypeDef* P_USARTx, uint8_t* P_Str, uint32_t P_Str_Len);

#endif




/*************************Copyright:CJ  (END OF FILE)********************/
