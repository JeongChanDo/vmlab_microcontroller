// ***********************************************************
// Project:
// Author:
// Module description:
// ***********************************************************

#include <avr\io.h>              // Most basic include files
#include <util/delay.h>

//LCD 8��Ʈ �������̽� �ʱ�ȭ �Լ�
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

//LCD ��� ó�� �Լ�
void LCD_command(unsigned char cmd)
{
	//0000 0100
	PORTG = 0x04; //E=1, RW=0, RS=0 -> ��� �������Ϳ� ��ɾ���
	PORTB = cmd;  // ��� ����
	_delay_us(1);
	PORTG = 0x00; //E=0, RW=0, RS=0
	// enable�� high���� low�� �������� valid data   -���� Ÿ�ֵ̹� ����
	_delay_us(1); //��� ����
	
}
// LCD ������ ó�� �Լ�
void LCD_data(unsigned char data)
{
	PORTG = 0x05;//E=1, RW=0, RS=1  LCD�� ǥ���� ���ڸ� �����ͷ������Ϳ� ����
	PORTB = data;//������ �� ����
	_delay_us(1);
	PORTG = 0x01;//E=0, RW=0, RS=1 LCD ������ ó����ȣ high->low
	_delay_us(1);
}

// ���ڿ� ó�� �Լ�
void LCD_string(unsigned char cmd, unsigned char *str)
{
	//���ڿ� ��� ��ġ ��� ����
	LCD_command(cmd);
	// ���ڿ� ������ null���� ���� ����
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
		LCD_string(0x80, str1);// ù°�� 0x80���� ����
		LCD_string(0xC0, str2);// ��°�� 0xC0���� ��
		_delay_ms(100);
	}
	return 1;
}


