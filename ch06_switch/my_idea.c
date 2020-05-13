// ***********************************************************
// Project:
// Author:
// Module description:
// ***********************************************************

#include <avr\io.h>              // Most basic include files
#include <util/delay.h>       // Add the necessary ones


int main(void)
{
	DDRC = 0xFF;
    PORTC = 0xFF;
    DDRD = 0x00;
    PORTD = 0xFF;
    unsigned char key;

    while (1)
    {
    	key = PIND & 0xFE;
		
        if (key == PIND)
        {
        	PORTC=0xFF;
            _delay_ms(200);
            PORTC =0x00;
            _delay_ms(200);
        }
        else
        	PORTC = 0xFF;
	}
}

