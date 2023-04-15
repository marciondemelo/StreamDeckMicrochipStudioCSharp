

void USART_Init(unsigned int ubrr);
unsigned char UART_Receive(void);
void UART_Transmit(unsigned char data);
void Serialprintln(char data[]);
void Serialprint(char data[]);
int USART_printCHAR(char data, FILE *stream);

/*configuracao para poder utilizar o printf para imprimir na serial
Obs.: É necessario adicionar a linha "stdout = &USART_0_stream;" no UART_Init*/
static FILE USART_0_stream = FDEV_SETUP_STREAM(USART_printCHAR, NULL, _FDEV_SETUP_WRITE);
int USART_printCHAR(char data, FILE *stream){
	UART_Transmit(data);
	return 0;
}

void UART_Init(unsigned int ubrr) {
	// Configurar o valor de UBRR
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;

	// Habilitar o receptor e o transmissor
	UCSRB = (1<<RXEN)|(1<<TXEN);

	// Configurar o formato do frame: 8 bits de dados, 1 stop bit
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);

	// Habilitar a interrupção da porta serial
	UCSRB |= (1<<RXCIE);

	//Enable configuration to use "printf" in UART
	stdout = &USART_0_stream;
}

unsigned char UART_Receive(void) {
	// Esperar pela recepção do dado
	while (!(UCSRA & (1<<RXC)));

	// Retornar o dado recebido
	return UDR;
}

void UART_Transmit(unsigned char data) {
	// Esperar pelo buffer vazio
	while (!(UCSRA & (1<<UDRE)));

	// Enviar o dado
	UDR = data;

}


void Serialprintln(char data[]) {
	char addLine[] = "\r\n";
	for (int i = 0; data[i] != '\0'; i++) {
		UART_Transmit(data[i]);
	}
	for (int i = 0; addLine[i] != '\0'; i++) {
		UART_Transmit(addLine[i]);
	}
}

void Serialprint(char data[]) {

	for (int i = 0; data[i] != '\0'; i++) {
		UART_Transmit(data[i]);
	}
}