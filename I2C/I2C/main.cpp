/*
 * I2C.cpp
 *
 * Created: 10-06-2021 11:15:36
 * Author : Admin
 */ 

#define F_CPU 16000000UL			/* Define CPU Frequency e.g. here 8MHz */
#define SCL_CLK 400000UL
#define D4 eS_PORTA0
#define D5 eS_PORTA1
#define D6 eS_PORTA2
#define D7 eS_PORTA3
#define RS eS_PORTA6
#define EN eS_PORTA5
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "12c_master.h"

#define client_Write_Address		0x20
#define client_Read_Address		0x21
#define	count				10


int main(void)
{

DDRA = 0xFF;

char buffer[10];

Lcd4_Init();				/* Initialize LCD */
I2C_Init();			/* Initialize I2C */

Lcd4_Set_Cursor(1,0);
Lcd4_Write_String("Master Device");



while (1)
{
	Lcd4_Set_Cursor(2,0);
	Lcd4_Write_String("Sending :       ");
	
	I2C_Start(client_Write_Address);/* Start I2C with SLA+W */
	_delay_ms(5);
	for (uint8_t i = 0; i < count ; i++)
	{
		sprintf(buffer, "%d    ",i);
		
		Lcd4_Set_Cursor(2,13);
		Lcd4_Write_String(buffer);
		I2C_Write(i);	/* Send Incrementing count */
		_delay_ms(500);
	}
	
	Lcd4_Set_Cursor(2,0);
	Lcd4_Write_String("Receiving :       ");
	
	I2C_Repeated_Start(client_Read_Address);/* Repeated Start with SLA+R */
	_delay_ms(5);
	for (uint8_t i = 0; i < count; i++)
	{
		if(i < count - 1)
		sprintf(buffer, "%d    ", I2C_Read_Ack());/* Read & Ack of data */
		else
		sprintf(buffer, "%d    ", I2C_Read_Nack());/* Read & Nack to data */
		
		Lcd4_Set_Cursor(2,13);
		Lcd4_Write_String(buffer);
		
		_delay_ms(500);
	}
	I2C_Stop();		/* Stop I2C */
}
}

