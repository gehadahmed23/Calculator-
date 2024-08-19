/*
 * LCD_int.h
 *
 * Created: 8/14/2024 10:30:07 AM
 *  Author: Gehad Ahmed
 */ 


#ifndef LCD_INT_H_
#define LCD_INT_H_

 
 #include <util/delay.h>
 #include "../../MCAL/DIO/DIO_int.h"
 #include "LCD_config.h"
 
 #define LCD_CLR 0x01
 #define LCD_HOME 0x02
 #define LCD_ENTRY_MODE 0x06
 #define LCD_FUNSET_8BIT 0x38
 #define LCD_DISPON_CURON 0x0c
 
 #define LCD_CGRAM_ADDRESS 0x40
 #define LCD_DDRAM_SETCURS 0x80
 
 
void LCD_vInit(void);
void LCD_vSendCMD(u8 CMD);          // Send Instruction To LCD
void LCD_vSendChar(u8 Char);        // Send Char To LCD
void LCD_vSend_string(u8 *data);
void LCD_vGoTo(u8 x, u8 y); // x --> 16, y --> 2
void LCD_clearscreen();
void LCD_vWriteNum(s32 NUM);
void LCD_vSaveCustomChar(u8 CGRAMIndex, u8 CustomChar[]);
void LCD_vWriteCustomChar(u8 CGRAMIndex);
void LCD_sendFloat(float n, char* res, int afterpoint);
int intToStr(int x, char str[], int d);
void reverse(char* str, int len);


#endif /* LCD_INT_H_ */