#ifndef __KEY_H__
#define __KEY_H__	 
#include "BSP_DRIVE.h" 

/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/
#define KEY0        GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) //PB2-->BOOT1
#define WK_UP       GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) //PA0-->WKUP

/*��ֵ����*/
#define KEY0_PRES   1
#define WKUP_PRES   2


/*���淽ʽ��ͨ��λ��������ʽ��ȡIO*/
/*
#define KEY0 	PBin(2)   	//PB2
#define WK_UP 	PAin(0)		//PA0
*/

/*�ӿں���*/
void BSP_KEY_Init(void);	        //IO��ʼ��
uint8_t KEY_Scan(uint8_t);  		//����ɨ�躯��	


#endif
