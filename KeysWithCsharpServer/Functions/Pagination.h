
#include "../Support/PinRegistration.h"
#include "../Support/UART.h"

void setPage() ;
void changeColor();
int valor = 0;
unsigned char pagName = 'A';

void setPage() {

	changeColor();
}

void changeColor() {
	if (valor == 3) {
		if (pagName != 'D') {
			pagName = 'D';
			printf("pageD\n");
			delay(10);
			//cpl_bit(PORTC,green);
			//set_bit(PORTC,red);
			//set_bit(PORTC,blue);
		}
		} else if (valor == 2) {
		if (pagName != 'C') {
			pagName = 'C';
			printf("pageC\n");
			delay(10);
			//cpl_bit(PORTC, green);
			//cpl_bit(PORTC, red);
			//set_bit(PORTC, blue);
		}
		} else if (valor == 1) {
		if (pagName != 'B') {
			pagName = 'B';
			printf("pageB\n");
			delay(10);
			//cpl_bit(PORTC, green);
			//set_bit(PORTC, red);
			//cpl_bit(PORTC, blue);
		}
		} else if (valor == 0){
		if (pagName != 'A') {
			pagName = 'A';
			printf("pageA\n");
			delay(10);
			//set_bit(PORTC, green);
			//cpl_bit(PORTC, red);
			//cpl_bit(PORTC, blue);
		}
	}
}