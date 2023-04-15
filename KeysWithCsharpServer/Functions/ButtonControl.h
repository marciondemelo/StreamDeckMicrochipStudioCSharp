#include "Pagination.h"

extern unsigned char pagName;
extern int valor;

unsigned char statusBtnDBack = '0';
unsigned char statusBtnDNext = '0';

unsigned char statusBtn06 = '0';
unsigned char statusBtn05 = '0';
unsigned char statusBtn04 = '0';
unsigned char statusBtn03 = '0';
unsigned char statusBtn02 = '0';
unsigned char statusBtn01 = '0';

unsigned char isConnected = '1';

void checkButton();
void pressButton();

void funcButtonPageA(unsigned char numButton) {
	if (numButton == '1')
	{
		printf("A1\n");
		statusBtn01 = '0';

	}
	else if (numButton == '2')
	{
		printf("A2\n");
		statusBtn02 = '0';

	}
	else if (numButton == '3')
	{
		printf("A3\n");
		statusBtn03 = '0';

	}
	else if (numButton == '4')
	{
		printf("A4\n");
		statusBtn04 = '0';

	}
	else if (numButton == '5')
	{
		printf("A5\n");
		statusBtn05 = '0';

	}
	else if (numButton == '6')
	{
		printf("A6\n");
		statusBtn06 = '0';

	}
}

void funcButtonPageB(unsigned char numButton) {
	if (numButton == '1')
	{
		printf("B1\n");
		statusBtn01 = '0';

	}
	else if (numButton == '2')
	{
		printf("B2\n");
		statusBtn02 = '0';

	}
	else if (numButton == '3')
	{
		printf("B3\n");
		statusBtn03 = '0';

	}
	else if (numButton == '4')
	{
		printf("B4\n");
		statusBtn04 = '0';

	}
	else if (numButton == '5')
	{
		printf("B5\n");
		statusBtn05 = '0';

	}
	else if (numButton == '6')
	{
		printf("B6\n");
		statusBtn06 = '0';

	}
}

void funcButtonPageC(unsigned char numButton) {
	if (numButton == '1')
	{
		printf("C1\n");
		statusBtn01 = '0';

	}
	else if (numButton == '2')
	{
		printf("C2\n");
		statusBtn02 = '0';

	}
	else if (numButton == '3')
	{
		printf("C3\n");
		statusBtn03 = '0';

	}
	else if (numButton == '4')
	{
		printf("C4\n");
		statusBtn04 = '0';

	}
	else if (numButton == '5')
	{
		printf("C5\n");
		statusBtn05 = '0';

	}
	else if (numButton == '6')
	{
		printf("C6\n");
		statusBtn06 = '0';

	}
}

void funcButtonPageD(unsigned char numButton) {
	if (numButton == '1')
	{
		printf("D1\n");
		statusBtn01 = '0';

	}
	else if (numButton == '2')
	{
		printf("D2\n");
		statusBtn02 = '0';

	}
	else if (numButton == '3')
	{
		printf("D3\n");
		statusBtn03 = '0';

	}
	else if (numButton == '4')
	{
		printf("D4\n");
		statusBtn04 = '0';

	}
	else if (numButton == '5')
	{
		printf("D5\n");
		statusBtn05 = '0';

	}
	else if (numButton == '6')
	{
		printf("D6\n");
		statusBtn06 = '0';

	}
}


void pressButton() {
	if (isConnected == '1') {

		if (read_bit(PIND, BtnDBack) > 0 && statusBtnDBack == '1') {
			if(valor == 3){
				valor = 0;
				}else{
				valor++;
			}
			statusBtnDBack = '0';
		}
		if (read_bit(PIND, BtnDNext) > 0 && statusBtnDNext == '1') {
			if(valor == 0){
				valor = 3;
				}else{
				valor--;
			}
			statusBtnDNext = '0';
		}

		if (read_bit(PINB, BtnB01) > 0 && statusBtn01 == '1') {
			if (pagName == 'A') {
				funcButtonPageA('1');
				} else if (pagName == 'B') {
				funcButtonPageB('1');
				} else if (pagName == 'C') {
				funcButtonPageC('1');
				} else if (pagName == 'D') {
				funcButtonPageD('1');
			}

		}
		if (read_bit(PINB, BtnB02) > 0 && statusBtn02 == '1') {
			if (pagName == 'A') {
				funcButtonPageA('2');
				} else if (pagName == 'B') {
				funcButtonPageB('2');
				} else if (pagName == 'C') {
				funcButtonPageC('2');
				} else if (pagName == 'D') {
				funcButtonPageD('2');
			}
		}
		if (read_bit(PINB, BtnB03) > 0 && statusBtn03 == '1') {
			if (pagName == 'A') {
				funcButtonPageA('3');
				} else if (pagName == 'B') {
				funcButtonPageB('3');
				} else if (pagName == 'C') {
				funcButtonPageC('3');
				} else if (pagName == 'D') {
				funcButtonPageD('3');
			}
		}
		if (read_bit(PIND, BtnD04) > 0 && statusBtn04 == '1') {
			if (pagName == 'A') {
				funcButtonPageA('4');
				} else if (pagName == 'B') {
				funcButtonPageB('4');
				} else if (pagName == 'C') {
				funcButtonPageC('4');
				} else if (pagName == 'D') {
				funcButtonPageD('4');
			}
		}

		if (read_bit(PIND, BtnD05) > 0 && statusBtn05 == '1') {
			if (pagName == 'A') {
				funcButtonPageA('5');
				} else if (pagName == 'B') {
				funcButtonPageB('5');
				} else if (pagName == 'C') {
				funcButtonPageC('5');
				} else if (pagName == 'D') {
				funcButtonPageD('5');
			}
		}

		if (read_bit(PIND, BtnD06) > 0 && statusBtn06 == '1') {
			if (pagName == 'A') {
				funcButtonPageA('6');
				} else if (pagName == 'B') {
				funcButtonPageB('6');
				} else if (pagName == 'C') {
				funcButtonPageC('6');
				} else if (pagName == 'D') {
				funcButtonPageD('6');
			}
		}
	}
}

void checkButton() {
	if (isConnected == '1') {
		//verifica se o pino D7 é 1(HIGH) e nega. Entra se o Pino D7 for false (LOW)


		if ((read_bit(PIND, BtnDBack)) ==0) {
			delay(10);
			statusBtnDBack = '1';
		}
		if ((read_bit(PIND, BtnDNext)) ==0) {
			delay(10);
			statusBtnDNext = '1';
		}

		if ((read_bit(PINB, BtnB01)) ==0) {
			delay(10);
			statusBtn01 = '1';
		}
		if ((read_bit(PINB, BtnB02)) == 0) {
			delay(10);
			statusBtn02 = '1';
		}
		if ((read_bit(PINB, BtnB03)) == 0) {
			delay(10);
			statusBtn03 = '1';
		}
		if ((read_bit(PIND, BtnD04)) == 0) {
			delay(10);
			statusBtn04 = '1';
		}
		if ((read_bit(PIND, BtnD05)) == 0) {
			delay(10);
			statusBtn05 = '1';
		}
		if ((read_bit(PIND, BtnD06)) == 0) {
			delay(10);
			statusBtn06 = '1';
		}
	}
}