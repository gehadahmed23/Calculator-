/*
 * LCD_config.h
 *
 * Created: 8/14/2024 10:30:19 AM
 *  Author: Gehad Ahmed
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

//Bit Mode
#define four_bits_mode

#define LCD_PORT DIO_PORTA
#define LCD_RS DIO_PORTC, DIO_PIN0
#define LCD_RW DIO_PORTC, DIO_PIN1
#define LCD_EN DIO_PORTC, DIO_PIN2





#endif /* LCD_CONFIG_H_ */