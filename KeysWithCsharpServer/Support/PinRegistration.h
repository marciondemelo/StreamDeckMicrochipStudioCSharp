
#include "../Support/HelpFunction.h"

void Inicializer_ADC(void);
void Inicializer_DigitalPins(void);
unsigned int ReadPin00_ADC(void);
unsigned int ReadPin_ADC(unsigned char canal);
void Inicializer_Timer_0(uint16_t prescaleValue, unsigned char startCount, unsigned char enableInterruption);
unsigned char Timer_0_Finish(void);

#define  BtnDBack 2
#define  BtnDNext 3

#define BtnB01 1
#define BtnB02 2
#define BtnB03 3
#define BtnD04 5
#define BtnD05 6
#define BtnD06 7

//#define blue 1              //pc1
//#define green 2             //pc2
//#define red 3               //pc3

volatile unsigned char startCount_m;

void Inicializer_DigitalPins(void){

	clr_bit(DDRB, BtnB01); //define como input (invert de 1 para 0)
	clr_bit(DDRB, BtnB02); //define como input (invert de 1 para 0)
	clr_bit(DDRB, BtnB03); //define como input (invert de 1 para 0)
	clr_bit(DDRD, BtnD04); //define como input (invert de 1 para 0)
	clr_bit(DDRD, BtnDBack); //define como input (invert de 1 para 0)
	clr_bit(DDRD, BtnDNext); //define como input (invert de 1 para 0)
	clr_bit(DDRD, BtnD05); //define como input (invert de 1 para 0)
	clr_bit(DDRD, BtnD06); //define como input (invert de 1 para 0)
	//set_bit(DDRC, red);	//define como output (1)
	//set_bit(DDRC, green); //define como output (1)
	//set_bit(DDRC, blue); //define como output (1)

	set_bit(PORTB, BtnB01); //define como pullup
	set_bit(PORTB, BtnB02); //define como pullup
	set_bit(PORTB, BtnB03); //define como pullup
	set_bit(PORTD, BtnDBack); //define como pullup
	set_bit(PORTD, BtnDNext); //define como pullup
	set_bit(PORTD, BtnD04); //define como pullup
	set_bit(PORTD, BtnD05); //define como pullup
	set_bit(PORTD, BtnD06); //define como pullup

}



void Inicializer_ADC(void){
	//Habilita a referência de tensão interna do ADC e ativa o canal 0
	ADMUX |= (1<<REFS0);		//voltagem de referencia
	ADMUX &=~(1<<REFS1);

	ADMUX &=~(1<<ADLAR);		//ajustar o resultado


	ADCSRA |= (1<<ADPS0);		//configura o prescaler/divisor para 128 e 125KHz (16000/128 = 125KHz)
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);

	ADCSRA |= (1<<ADEN);		//Habilita o ADC
}

unsigned int ReadPin00_ADC(void){
	uint8_t canal = 0b00000001;			//Limitar a 5 entradas que temos apenas 6bit AD
	ADMUX = (ADMUX & 0xF0) | canal; //Limpar os ultimos 4bits de ADMUX
	ADCSRA |= (1 << ADSC);			//Inicia a conversão
	while ( (ADCSRA) & (1<<ADSC) );	//Aguarda a finalização da conversão
	return ( ADC );					//Retorna o valor convertido
}
/*
unsigned int ReadPin_ADC(uint8_t canal){

	canal &= 0b00001111;			//Limitar a 5 entradas que temos apenas 6bit AD
	ADMUX = (ADMUX & 0xF0) | canal; //Limpar os ultimos 4bits de ADMUX
	ADCSRA |= (1 << ADSC);			//Inicia a conversão
	while ( (ADCSRA) & (1<<ADSC) );	//Aguarda a finalização da conversão
	return ( ADC );					//Retorna o valor convertido
}
*/
void Inicializer_Timer_0(uint16_t prescaleValue, unsigned char startCount, unsigned char enableInterruption){
	if(prescaleValue == 1){
		TCCR0 = (1<<CS00);
		}else if(prescaleValue == 8){
		TCCR0 = (1<<CS01);
		}else if(prescaleValue == 64){
		TCCR0 = (1<<CS00) | (1<<CS01);
		}else if(prescaleValue == 256){
		TCCR0 = (1<<CS02);
		}else if(prescaleValue == 1024){
		TCCR0 = (1<<CS00) | (1<<CS02);
	}
	TCNT0 = startCount;
	if(enableInterruption == 1){
		TIMSK |= (1<<TOIE0);
	}
}

unsigned char Timer_0_Finish(void){
	if(TIFR & (1<<TOV0)){
		TCNT0 = startCount_m;
		TIFR |= (1<<TOV0);
		return 1;
		}else{
		return 0;
	}
}
