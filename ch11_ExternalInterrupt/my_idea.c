// ***********************************************************
// Project:
// Author:
// Module description:
// ***********************************************************
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR (INT0_vect)
{
  	PORTC = 0x00;
    _delay_ms(50);
    PORTC = 0xFF;
    _delay_ms(50);
}

int main(void)
{
  	 DDRC = 0xFF; // ��� ���
    PORTC = 0xFF; // ���̷���
    DDRD = 0x00; //�Է� ���
    PORTD = 0xFF; // ���� Ǯ�� ���

    EICRA = (0 << ISC01) | (0 << ISC00);
    //Low�� ������ ���� ���ͷ�Ʈ �߻� -> ���� Ǯ������ �⺻ ���� 1 -> ����ġ Ŭ���� 0-> INT0 �߻�
    EIMSK = (1 << INT0); //INT0 ���
    sei();//�۷ι� ���ͷ�Ʈ �ο��̺�
    while(1);
}
