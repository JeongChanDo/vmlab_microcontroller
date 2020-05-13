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
  	 DDRC = 0xFF; // 출력 모드
    PORTC = 0xFF; // 하이레벨
    DDRD = 0x00; //입력 모드
    PORTD = 0xFF; // 내부 풀업 사용

    EICRA = (0 << ISC01) | (0 << ISC00);
    //Low가 들어오는 순간 인터럽트 발생 -> 내부 풀업으로 기본 상태 1 -> 스위치 클릭시 0-> INT0 발생
    EIMSK = (1 << INT0); //INT0 허용
    sei();//글로벌 인터럽트 인에이블
    while(1);
}
