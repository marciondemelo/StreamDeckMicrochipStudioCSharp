/*
* KeysWithCsharpServer.c
*
* Created: 22/02/2023 21:10:40
* Author : marcio Melo
*/

#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>
#include <util/delay.h>
#include <util/twi.h>
#include "Functions/ButtonControl.h"
#include "Support/i2c_lcd.h"


void function_serial_command(char* RxBuffer);

volatile static uint16_t conta;
volatile static char Page = 1;

static char Page01Linha01[16] = "";
static char Page01Linha02[16] = "";
static char Page02Linha01[16] = "";
static char Page02Linha02[16] = "";

char RxBuffer[18];
volatile unsigned char RxCount = 0;


ISR(USART_RXC_vect) {
	while (!(UCSRA & (1 << RXC)));

		char recebido;
		recebido = UDR;
		if( strstr(recebido, "#")){
			RxBuffer[RxCount] = '\0';
			RxCount = 0;
printf(recebido);
		}else
		RxBuffer[RxCount++] = recebido;

}

void function_serial_command(char* RxBuffer){

	uint8_t position = 0;
	if(strstr(RxBuffer, "line01")){
		char temp[17];
		for (int i = 6; i<=strlen(RxBuffer); i++, position++ )
		{
			if(RxBuffer[i] == '@'){
				strcpy(Page01Linha01, temp);
				position = 0;
				continue;
			}
			temp[position] = RxBuffer[i];

		}
		strcpy(Page02Linha01, temp);

		}else if(strstr(RxBuffer, "line02")){
		char temp[17];
		for (int i = 4; i<=strlen(RxBuffer); i++, position++ )
		{
			if(RxBuffer[i] == '@'){
				strcpy(Page01Linha02, temp);
				position = 0;
				continue;
			}
			temp[position] = RxBuffer[i];

		}
		strcpy(Page02Linha02, temp);
	}
}

ISR(TIMER0_OVF_vect){
	conta++;
	if(conta== 30 || conta == 60 || conta == 90){
	}
	if(conta>=100){
		delay(6);
		if(Page == 1){
			Page = 0;
			twi_lcd_position(1, 0);
			twi_lcd_msg(Page01Linha01);
			twi_lcd_position(2, 0);
			twi_lcd_msg(Page01Linha02);
			}else{

			Page = 1;
			twi_lcd_position(1, 0);
			twi_lcd_msg(Page02Linha01);
			twi_lcd_position(2, 0);
			twi_lcd_msg(Page02Linha02);
		}

		conta=0;
	}
	TCNT0 = 99;
}


char buffer[5] = "     ";

int main(void) {

	//Inicializer_ADC();
	Inicializer_DigitalPins();

	UART_Init(MYUBRR);

	Inicializer_Timer_0(1024, 99, 1);

	twi_lcd_init(0x27);								//--- TWI LCD Initialize

	delay(50);
	strcpy(Page01Linha01, "PAG-A  1-Vol+");
	strcpy(Page01Linha02, "2-Vol- 3-Mute");

	strcpy(Page02Linha01, "PAG-A  4-Home");
	strcpy(Page02Linha02, "5-End  6-Prin");

	/*Enable global interruptions*/
	sei();
	conta = 0;

	while (1) {
		checkButton();
		pressButton();
		setPage();
		cpl_bit(PORTD, 0);

	}
}

void FillPage01(char *linha01, char *linha02){
	strcpy(Page01Linha01, linha01);
	strcpy(Page01Linha02, linha02);
}

void FillPage02(char *linha01, char *linha02){
	strcpy(Page02Linha01, linha01);
	strcpy(Page02Linha02, linha02);
}