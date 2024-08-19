/*
 * LCD_prog.c
 *
 * Created: 8/14/2024 10:29:55 AM
 *  Author: Gehad Ahmed
 */ 

#include "LCD_int.h"

void LCD_vInit(void){
	
	DIO_voidSetPortDir(LCD_PORT, DIO_PORT_OUTPUT);
	DIO_voidSetPinDir(LCD_EN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDir(LCD_RW,DIO_PIN_OUTPUT);
	DIO_voidSetPinDir(LCD_RS,DIO_PIN_OUTPUT);
	
	_delay_ms(31);
	LCD_vSendCMD(LCD_FUNSET_8BIT);
	_delay_ms(40);
	LCD_vSendCMD(LCD_DISPON_CURON);
	_delay_ms(40);
	LCD_vSendCMD(LCD_CLR);
	_delay_ms(1.54);
	LCD_vSendCMD(LCD_ENTRY_MODE);
	_delay_ms(2);
}
void LCD_vSendCMD(u8 CMD){
	DIO_voidSetPinVal(LCD_RW,DIO_PIN_LOW);
	DIO_voidSetPinVal(LCD_RS,DIO_PIN_LOW);
	DIO_voidSetPortVal(LCD_PORT, CMD);
	
	DIO_voidSetPinVal(LCD_EN, DIO_PIN_HIGH);
	DIO_voidSetPinVal(LCD_EN, DIO_PIN_LOW);
	_delay_ms(5);
}         
void LCD_vSendChar(u8 Char){
	DIO_voidSetPinVal(LCD_RW,DIO_PIN_LOW);
	DIO_voidSetPinVal(LCD_RS,DIO_PIN_HIGH);
	DIO_voidSetPortVal(LCD_PORT, Char);
	
	DIO_voidSetPinVal(LCD_EN, DIO_PIN_HIGH);
	DIO_voidSetPinVal(LCD_EN, DIO_PIN_LOW);
	_delay_ms(5);
}

void LCD_vGoTo(u8 x, u8 y)
{
	if(x <= 16 && y <= 2 && x != 0 && y != 0){
		switch(y)
		{
			case 1 : LCD_vSendCMD(127 + x);break;
			case 2 : LCD_vSendCMD(191 + x);break;
			default : break;
		}
	}
}
void LCD_clearscreen()
{
	LCD_vSendCMD(LCD_CLR);
	_delay_ms(2);
}
void LCD_vSend_string(u8 *data){
	while((*data) != '\0')
	{
		LCD_vSendChar(*data);
		data++;
		
	}
}
void LCD_vWriteNum(s32 NUM){
	if(NUM == 0){
		LCD_vSendChar('0');
	}
	if(NUM < 0){
		LCD_vSendChar('-');
		NUM *= -1;
	}
	s32 temp = 1;
	while(NUM > 0){
		temp = (temp * 10) + (NUM % 10);
		NUM /= 10;
	}
	while(temp != 1){
		LCD_vSendChar((temp % 10) + '0');
		temp /= 10;
	}
}
void LCD_vSaveCustomChar(u8 CGRAMIndex, u8 CustomChar[]){
	LCD_vSendCMD(LCD_CGRAM_ADDRESS+(CGRAMIndex * 8));
	for(u8 i = 0; i < 8; i++){
		LCD_vSendChar(CustomChar[i]);
	}
	LCD_vSendCMD(LCD_DDRAM_SETCURS);
}
void LCD_vWriteCustomChar(u8 CGRAMIndex){
	if(CGRAMIndex){
		LCD_vSendChar(CGRAMIndex);
	}
}
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	
	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
	str[i++] = '0';
	
	reverse(str, i);
	str[i] = '\0';
	return i;
}

void reverse(char* str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

void Clear_buffer(char *res){
	int i = 0;
	while(res[i] != '\0'){
		res[i] = '\0';
		i++;
	}
}

void LCD_sendFloat(float n, char* res, int afterpoint)
{
	Clear_buffer(res);
	// Extract integer part
	int ipart = (int)n;
	
	// Extract floating part
	float fpart = n - (float)ipart;
	
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.';
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}