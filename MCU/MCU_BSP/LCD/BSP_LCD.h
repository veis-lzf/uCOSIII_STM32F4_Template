#ifndef __LCD_H
#define __LCD_H

#include "BSP_DRIVE.h"

/* ѡ��BANK1-BORSRAM1 ���� TFT����ַ��ΧΪ0X60000000~0X63FFFFFF
 * FSMC_A16 ��LCD��DC(�Ĵ���/����ѡ��)��
 * 16 bit => FSMC[24:0]��ӦHADDR[25:1]
 * �Ĵ�������ַ = 0X60000000
 * RAM����ַ = 0X60020000 = 0X60000000+2^16*2 = 0X60000000 + 0X20000 = 0X60020000
 * ��ѡ��ͬ�ĵ�ַ��ʱ����ַҪ���¼��㡣
 */
#define Bank1_LCD_D    ((u32)0x60020000)        //Disp Data ADDR
#define Bank1_LCD_C    ((u32)0x60000000)	    //Disp Reg ADDR

#define lcd_width  320
#define lcd_heigth 480

#define s1 0x01     // ��������
#define s2 0x02     //��������
#define s3 0x03     //��������
#define s4 0x04     //��������


typedef struct
{
    u16 p_color;    //������ɫ
    u16 b_color;    //������ɫ
    u16 id     ;    //LCD_ID
    u8  dir    ;    //����  0,��
    u16 width  ;    //LCD���
    u16 heigth ;    //LCD�߶�
}  _lcd_dev;

extern _lcd_dev lcd_dev;


//Lcd��ʼ������ͼ����ƺ���
void BSP_Lcd_Init(void);
void Lcd_Configuration(void);
void DataToWrite(u16 data);
void LCD_WR_REG(u16 Index, u16 CongfigTemp);
void Lcd_WR_Start(void);

//Lcd�߼����ƺ���
void Lcd_ColorBox(u16 x, u16 y, u16 xLong, u16 yLong, u16 Color);                                   //������亯��
void DrawPoint(u16 x, u16 y, u16 Color);                                                            //���㺯��
u16  ssd1289_GetPoint(u16 x, u16 y);                                                                //����
void LCD_Clear(u16 color);
void LCD_Fill_Pic(u16 x, u16 y, u16 pic_H, u16 pic_V, const unsigned char* pic);
void BlockWrite(unsigned int Xstart, unsigned int Xend, unsigned int Ystart, unsigned int Yend);
void SetCursor(u16, u16);                                                                           //���ù��
u16  ReadID(void);                                                                                  //read id
void Draw_Circle(u16, u16, u8, u16);                                                                //��Բ
void DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);                                           //����
void DrawRectangle(u16, u16, u16, u16, u16);                                                        //������
void LCD_Fill(u16, u16, u16, u16, u16 color);                                                       //������亯��
void ShowChar(u16 x, u16 y, u8 num, u8 size, u8 mode);						                        //��ʾһ���ַ�
void ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size);  						                        //��ʾһ������ ��λ0����ʾ
void ShowxNum(u16 x, u16 y, u32 num, u8 len, u8 size, u8 mode);		                                //��ʾ ����  ��λ0��ʾ
void ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, u8 *p);		                        //��ʾһ���ַ���
void DrawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, u8 *pData) ;        //��ʾͼƬ
void Delay(u16 t);                                                                                  //��ʱ����
void set_mode(u8 mode);                                                                             //���ƺ�����   mode:0,����    1,����
u16  Read_ID(void);
void LCD_showdouble(u16 x, u16 y, u16 width, u16 height, u8 size, double z);
void LCD_showint(u16 x, u16 y, u16 width, u16 height, u8 size, u16 z);

//��ɫ�Ķ���
#define  White          0xFFFF
#define  Black          0x0000
#define  Blue           0x001F
#define  Blue2          0x051F
#define  Red            0xF800
#define  Magenta        0xF81F
#define  Green          0x07E0
#define  Cyan           0x7FFF
#define  Yellow         0xFFE0


#endif
