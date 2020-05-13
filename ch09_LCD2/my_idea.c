// ***********************************************************
// Project:
// Author:
// Module description:
// ***********************************************************

#include <avr\io.h>              // Most basic include files
#include <util/delay.h>

//DDRAM 설정 : 0x80+DDRAM addr 값
#define LINE1 0x80	//첫번째 라인의 DDRAM addr : 0x00->0x80+0x00
#define LINE2 0xC0	//두번째 라인의 DDRAM addr : 0x40->0x80+0x40

//PG2=LCD_EN, PG1=RW, PG0=RS에 연결
#define CMD_WRITE		0xFC	//명령어 쓰기 E=1, RW=0, RS=0
#define CMD_READ		0xFE	//명령어 읽기 E=1, RW=1, RS=0
#define DATA_WRITE	0xFD	//데이터 쓰기 E=1, RW=0, RS=1
#define DATA_READ		0xFF	//데이터 읽기 E=1, RW=1, RS=1
#define LCD_EN			0x04	//PG2에 연결

//LCD에 명령을 쓰기위한 함수
void LCD_cmd_write(unsigned char cmd)
{
	PORTG = CMD_WRITE;
	PORTB = cmd;
	PORTG =PORTG^LCD_EN;
	_delay_ms(2);
}
//LCD에 데이터를 쓰기 위한 함수
void LCD_data_write(unsigned char data)
{
	PORTG = DATA_WRITE;
	PORTB = data;
	PORTG = PORTG^LCD_EN;
	_delay_ms(2);
}

void init_LCD(void)
{
	_delay_ms(15);
	LCD_cmd_write(0x38);//명령레지스터에 0x38 전달
	_delay_ms(5);
	LCD_cmd_write(0x38);
	_delay_us(100);
	LCD_cmd_write(0x38);
	LCD_cmd_write(0x08);
	LCD_cmd_write(0x01);
	LCD_cmd_write(0x06);
	LCD_cmd_write(0x0C);
}

//LCD에 문자열 표시하기위한 함수
void LCD_wr_string(char d_line, char *str)
{
	LCD_cmd_write(d_line);
	while(*str != '\0')
	{
		LCD_data_write(*str);
		str++;
	}
}
//ATmega128 포트 초기화
void init_system(void)
{
	//B,G- LCD
	DDRB=0xFF;
	DDRG=0xFF;
	//C- LED, D-SWITCH
	DDRC=0xFF;
	DDRD=0x00;
	PORTC=0xFF;
	PORTD=0xFF;//내부풀업 사용
}

int main()
{
	init_system();
	init_LCD();


	unsigned char sw1, sw2;
	while(1)
	{
		sw1 = PIND & 0xFE;//1111 1110 -PD 0번 스위치 눌릴때
		sw2 = PIND & 0xFD;//1111 1101 -PD 1번 스위치가 눌릴때
		
		if (sw1 == PIND)
		{
			LCD_wr_string(LINE1, "   switch 1 ");
			LCD_wr_string(LINE2, "200ms Blinking");
			PORTC = 0xFE;//1111 1110 0번 LED 블링크
			_delay_ms(200);
			PORTC = 0xFF;
			_delay_ms(200);
		}	
		else if (sw2 == PIND)
		{
			LCD_wr_string(LINE1, "  switch 2");
			LCD_wr_string(LINE2, " 500ms blinking!");
			PORTC= 0xFD;
			_delay_ms(500);
			PORTC= 0xFF;
			_delay_ms(500);
		}
		else
		{
			LCD_wr_string(LINE1, "    ");
			LCD_wr_string(LINE2, "     ");
		}
	}
	return 1;
}



