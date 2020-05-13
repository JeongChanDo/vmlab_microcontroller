// ***********************************************************
// Project:
// Author:
// Module description:
// ***********************************************************

#include <avr\io.h>              // Most basic include files
#include <util\delay.h>



int main(void) {
	unsigned char led = 0xFE;
   DDRC=0xFF;
   while(1) {
   	PORTC=led;
   	_delay_ms(200);
   	led <<=1;
   	led |= 0x01;
   	
   	if (led == 0xFF) led=0xFE;
   }

}

