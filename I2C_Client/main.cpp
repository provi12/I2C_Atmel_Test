/*
 * I2C_Client.cpp
 *
 * Created: 10-06-2021 11:50:22
 * Author : Admin
 */ 


#define F_CPU 16000000UL		/* Define CPU clock Frequency 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include inbuilt defined Delay header file */
#include <stdio.h>		/* Include standard I/O header file */
#include <string.h>		/* Include string header file */
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

#include "12c_client.h"	/* Include I2C client header file */

#define client_Address		0x20

int main(void)
{
	DDRA = 0xFF;
	
    
   char buffer[10];
   int8_t count = 0;
   
   Lcd4_Init();			/* Initialize LCD */
   I2C_client_Init(client_Address);		/* Initialize I2C */
   Lcd4_Set_Cursor(1,0);
   Lcd4_Write_String("client Device");
   
  while (1)
  {
	  switch(I2C_client_Listen())	/* Check for SLA+W or SLA+R */
	  {
		  case 0:
		  {
			  Lcd4_Set_Cursor(2,0);
			   Lcd4_Write_String("Receiving :       ");
			  do
			  {
				  sprintf(buffer, "%d    ", count);
				  
				  Lcd4_Set_Cursor(2,13);
				  Lcd4_Write_String(buffer);

				  count = I2C_client_Receive();/* Receive data byte*/
				  } while (count != -1);/* Receive until STOP/REPEATED START */
				  count = 0;
				  break;
			  }
			  case 1:
			  {
				  int8_t Ack_status;
				  Lcd4_Set_Cursor(2,0);
				  Lcd4_Write_String("Sending :       ");

				  do
				  {
					  Ack_status = I2C_client_Transmit(count);/* Send data byte */
					  sprintf(buffer, "%d    ",count);
						Lcd4_Set_Cursor(2,13);
						 Lcd4_Write_String(buffer);
					  count++;
					  } while (Ack_status == 0);/* Send until Ack is receive */
					  break;
				  }
				  default:
				  break;
			  }
		  }
}

