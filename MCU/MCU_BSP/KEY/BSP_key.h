#ifndef __KEY_H__
#define __KEY_H__	 
#include "BSP_DRIVE.h" 

/*下面的方式是通过直接操作库函数方式读取IO*/
#define KEY0        GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) //PB2-->BOOT1
#define WK_UP       GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) //PA0-->WKUP

/*键值返回*/
#define KEY0_PRES   1
#define WKUP_PRES   2


/*下面方式是通过位带操作方式读取IO*/
/*
#define KEY0 	PBin(2)   	//PB2
#define WK_UP 	PAin(0)		//PA0
*/

/*接口函数*/
void BSP_KEY_Init(void);	        //IO初始化
uint8_t KEY_Scan(uint8_t);  		//按键扫描函数	


#endif
