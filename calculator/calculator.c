/*
 * calculator.c
 *
 * Created: 8/14/2024 10:49:59 PM
 *  Author: Dell
 */ 


#include <avr/io.h>
#include "HAL/Keypad/Keypad_int.h"
#include "HAL/LCD/LCD_int.h"
#include <math.h>
#include <stdio.h>
u8 ln = 0;
int main(void)
{
	LCD_vInit();
	keypad_vInit();
	u8 c = 255, op,Neg1= 0, Neg2 = 0, fl = 0;
	s32 x = 0, y = 0, f = 0, f1 = 0, f2 = 0, f3 = 0, a = 0;
	while(1)
	{
		c = keypad_u8check_press();
		if(a == 1){
			if(c == '-' && f == 0){
				Neg1 = 1;
				LCD_vSendChar(c);
			}
			else if(c >= 48 && c <= 57 && f == 0)
			{
				x = (x * 10) + (c - 48);
				LCD_vSendChar(c);
				f = 1;
			}
			else if(c >= 48 && c <= 57 && f == 1)
			{
				x = (x * 10) + (c - 48);
				LCD_vSendChar(c);
				
			}
			else if( f == 2 && f1 == 0 && c == '-'){
				Neg2 = 1;
				LCD_vSendChar(c);
			}
			else if(c >= 48 && c <= 57 && f == 2 && f1 == 0)
			{
				y = (y * 10) + (c - 48);
				LCD_vSendChar(c);
				f1 = 1;
			}
			else if(c >= 48 && c <= 57 && f1 == 1)
			{
				y = (y * 10) + (c - 48);
				LCD_vSendChar(c);
			}
			else if(((c == '+' )|| (c == '-') || (c == '*') || (c == '/') || (c == '=')) && f == 0)
			{
				LCD_vSendChar(c);
				f3 = 1;
			}
			else if(((c == '+' )|| (c == '-') || (c == '*') || (c == '/')) && f == 2)
			{
				LCD_vSendChar(c);
				f3 = 1;
			}
			else if(((c == '+' )|| (c == '-') || (c == '*') || (c == '/')) && f == 1)
			{
				op = c;  f = 2;
				LCD_vSendChar(c);
			}
			else if(((c == '=')) && (f == 1))
			{
				LCD_clearscreen();
				LCD_vGoTo(1, 3);
				LCD_vSendCMD(0x0c);
				LCD_vSend_string("syntax error");
				a = 0;
				
			}
			else if(c == '=')
			{
				if(f3 == 1){
					LCD_clearscreen();
					LCD_vGoTo(1, 3);
					LCD_vSendCMD(0x0c);
					LCD_vSend_string("syntax error");
					a = 0;
				}
				else
				{
					if(Neg1)x *= -1;
					if(Neg2)y *= -1;
					s32 z;
					double d;
					if(op == '+')
					{
						z = x + y;
					}
					else if(op == '-'){z = x - y;}
				else if(op == '*')
				{
					z = (x * y);
				}
				else if(op == '/')
				{
					if((x) % (y) != 0)fl = 1;
					if(y == 0)
					{
						f2 = 1;
						LCD_clearscreen();
						LCD_vGoTo(1, 3);
						LCD_vSendCMD(0x0c);
						LCD_vSend_string("math error");
						a = 0;
					}
					double s = x, i = y;
					d = s / i;
					z = x / y;
				}
				
				if(f2 == 0){
					LCD_vGoTo(2,2);
					LCD_vSendChar('=');
					if(fl == 1){
						char buf[20];
						if((Neg2 == 1 && Neg1 == 0) || (!Neg2 && Neg1)){
							LCD_vSendChar('-');
			                d *= -1;
						}
						LCD_sendFloat(d, buf, 3);
						LCD_vSend_string(buf);
					}
					else{
					  LCD_vWriteNum(z);
					}
					LCD_vSendCMD(0x0c);
					a = 0;
					
				}
			}
			
		}
	}
	if(c == 'C'){
		a = 1;
		LCD_clearscreen();
		c, op, fl = 0;
		x = 0, y = 0,  f = 0,Neg1= 0, Neg2 = 0, f1 = 0, f2 = 0, f3 = 0, ln = 0;
		LCD_vSendCMD(0x0E);
	}
}
}
