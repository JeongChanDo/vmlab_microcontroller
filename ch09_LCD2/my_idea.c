// ***********************************************************
// Project:
// Author:
// Module description:
// ***********************************************************

#include <avr\io.h>              // Most basic include files
#include <util/delay.h>

//DDRAM ���� : 0x80+DDRAM addr ��
#define LINE1 0x80	//ù��° ������ DDRAM addr : 0x00->0x80+0x00
#define LINE2 0xC0	//�ι�° ������ DDRAM addr : 0x40->0x80+0x40

//PG2=LCD_EN, PG1=RW, PG0=RS�� ����
#define CMD_WRITE		0xFC	//��ɾ� ���� E=1, RW=0, RS=0
#define CMD_READ		0xFE	//��ɾ� �б� E=1, RW=1, RS=0
#define DATA_WRITE	0xFD	//������ ���� E=1, RW=0, RS=1
#define DATA_READ		0xFF	//������ �б� E=1, RW=1, RS=1
#define LCD_EN			0x04	//PG2�� ����

//LCD�� ����� �������� �Լ�
void LCD_cmd_write(unsigned char cmd)
{
	PORTG = CMD_WRITE;
	PORTB = cmd;
	PORTG =PORTG^LCD_EN;
	_delay_ms(2);
}
//LCD�� �����͸� ���� ���� �Լ�
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
	LCD_cmd_write(0x38);//��ɷ������Ϳ� 0x38 ����
	_delay_ms(5);
	LCD_cmd_write(0x38);
	_delay_us(100);
	LCD_cmd_write(0x38);
	LCD_cmd_write(0x08);
	LCD_cmd_write(0x01);
	LCD_cmd_write(0x06);
	LCD_cmd_write(0x0C);
}

//LCD�� ���ڿ� ǥ���ϱ����� �Լ�
void LCD_wr_string(char d_line, char *str)
{
	LCD_cmd_write(d_line);
	while(*str != '\0')
	{
		LCD_data_write(*str);
		str++;
	}
}
//ATmega128 ��Ʈ �ʱ�ȭ
void init_system(void)
{
	//B,G- LCD
	DDRB=0xFF;
	DDRG=0xFF;
	//C- LED, D-SWITCH
	DDRC=0xFF;
	DDRD=0x00;
	PORTC=0xFF;
	PORTD=0xFF;//����Ǯ�� ���
}

int main()
{
	init_system();
	init_LCD();


	unsigned char sw1, sw2;
	while(1)
	{
		sw1 = PIND & 0xFE;//1111 1110 -PD 0�� ����ġ ������
		sw2 = PIND & 0xFD;//1111 1101 -PD 1�� ����ġ�� ������
		
		if (sw1 == PIND)
		{
			LCD_wr_string(LINE1, "   switch 1 ");
			LCD_wr_string(LINE2, "200ms Blinking");
			PORTC = 0xFE;//1111 1110 0�� LED ��ũ
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



