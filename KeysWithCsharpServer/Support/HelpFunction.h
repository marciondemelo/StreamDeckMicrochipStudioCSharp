#define set_bit(y,bit)  (y|=(1<<bit))  //coloca em 1 o bit x da variavel y
#define clr_bit(y,bit)  (y&=~(1<<bit)) //coloca em 0 o bit x da variavel y
#define cpl_bit(y,bit)  (y^=(1<<bit))   //macro invert value
#define read_bit(y,bit) (y&(1<<bit))    //retorna 0 ou 1 conforme leitura do bit
#define delay(ms)       _delay_ms(ms)   //melhora compatibilidade do metodo delay

// Fun��o para trocar dois n�meros
void swap(char *x, char *y) {
	char t = *x; *x = *y; *y = t;
}

// Fun��o para reverter `buffer[i�j]`
char* reverse(char *buffer, int i, int j)
{
	while (i < j) {
		swap(&buffer[i++], &buffer[j--]);
	}

	return buffer;
}

// Fun��o iterativa para implementar a fun��o `itoa()` em C
char* itoa(int value, char* buffer, int base)
{
	// entrada inv�lida
	if (base < 2 || base > 32) {
		return buffer;
	}

	// considera o valor absoluto do n�mero
	int n = abs(value);

	int i = 0;
	while (n)
	{
		int r = n % base;

		if (r >= 10) {
			buffer[i++] = 65 + (r - 10);
		}
		else {
			buffer[i++] = 48 + r;
		}

		n = n / base;
	}

	// se o n�mero for 0
	if (i == 0) {
		buffer[i++] = '0';
	}

	// Se a base for 10 e o valor for negativo, a string resultante
	// � precedido por um sinal de menos (-)
	// Com qualquer outra base, o valor � sempre considerado sem sinal
	if (value < 0 && base == 10) {
		buffer[i++] = '-';
	}

	buffer[i] = '\0'; // string de termina��o nula

	// inverte a string e retorna
	return reverse(buffer, 0, i - 1);
}