// ***********************************************************
// Project:
// Author:
// Module description:
// ***********************************************************

#include <avr\io.h>              // Most basic include files
#include <util/delay.h>

//LCD 8비트 인터페이스 초기화 함수
void LCD_init()
{
	DDRB = 0xFF;
	DDRG = 0xFF;
	_delay_ms(20);
	LCD_command(0x38);
	LCD_command(0x08);
	LCD_command(0x01);
	_delay_ms(1);
	LCD_command(0x06);
	LCD_command(0x0E);

}

//LCD 명령 처리 함수
void LCD_command(unsigned char cmd)
{
	//0000 0100
	PORTG = 0x04; //E=1, RW=0, RS=0 -> 명령 레지스터에 명령쓰기
	PORTB = cmd;  // 명령 전달
	_delay_us(1);
	PORTG = 0x00; //E=0, RW=0, RS=0
	// enable을 high에서 low로 떨어져야 valid data   -동작 타이밍도 참고
	_delay_us(1); //명령 쓰기
	
}
// LCD 데이터 처리 함수
void LCD_data(unsigned char data)
{
	PORTG = 0x05;//E=1, RW=0, RS=1  LCD에 표시할 문자를 데이터레지스터에 쓰기
	PORTB = data;//데이터 값 전달
	_delay_us(1);
	PORTG = 0x01;//E=0, RW=0, RS=1 LCD 데이터 처리신호 high->low
	_delay_us(1);
}

// 문자열 처리 함수
void LCD_string(unsigned char cmd, unsigned char *str)
{
	//문자열 출력 위치 명령 전달
	LCD_command(cmd);
	// 문자열 마지막 null에서 루프 종료
	while (*str != '\0')
	{
		LCD_data(*str);
		str++;
	}
}

// ***********************************************************
// Main program
//
int main(void) {

	LCD_init();
	
	unsigned char str1[] ="LCD display";
	unsigned char str2[] = "  Example ";
	while (1)
	{
		LCD_string(0x80, str1);// 첫째줄 0x80부터 시작
		LCD_string(0xC0, str2);// 둘째줄 0xC0부터 시
		_delay_ms(100);
	}
	return 1;
}


