// ***********************************************************
// Project:
// Author:
// Module description:
// ***********************************************************

#include <avr/io.h>
#include <util/delay.h>

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

	unsigned char seg[8] = {0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F};
  	unsigned char i;

	DDRA = 0xFF;
   DDRE = 0xFF;
   PORTE - 0x00;	//ÀüÃ¼ FND enable

   while (1)
   {
  		for (i = 0; i < 8; i++)
      {
      	PORTA = seg[i];
      	_delay_ms(100);
      }
  	}
}
