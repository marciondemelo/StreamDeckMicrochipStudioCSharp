#include <util/twi.h>							//--- TWI Status File
#include <math.h>								//--- Math Func
#define SCL_CLK 400000L							//--- SCL for TWI
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))		//--- Bitrate formula

void twi_init();
void twi_repeated_start();
void PCF8574_write(unsigned char x);
void twi_write_cmd(unsigned char address);
void twi_lcd_position(char line, char column);
void twi_lcd_cmd(unsigned char x);
void twi_lcd_clear();
void twi_lcd_msg(char *c);
void twi_write_dwr(unsigned char val);
void twi_start();
void twi_stop();
char twi_read_ack();
char twi_read_nack();
void LCD_custom_char(unsigned char loc,unsigned char *msg);


/*
	START LCD CODE


*/

//#define PCF8574	0x27							//--- Slave Address is 7-Bit and Last Bit is either read or write
char addressLcd;
#define	WRITE			0
#define READ			1


unsigned char lcd = 0x00;						//--- Declaring a variable as lcd for data operation


/* Function to Initialize LCD in 4-Bit Mode, Cursor Setting and Row Selection */

void twi_lcd_init(char adsLcd)
{
	addressLcd = adsLcd;

	twi_init();									//--- TWI Initialize
	lcd = 0x04;						//--- EN = 1 for 25us initialize Sequence
	PCF8574_write(lcd);
	_delay_us(25);

	twi_lcd_cmd(0x03);				//--- Initialize Sequence
	twi_lcd_cmd(0x03);				//--- Initialize Sequence
	twi_lcd_cmd(0x03);				//--- Initialize Sequence
	twi_lcd_cmd(0x02);				//--- Return to Home
	twi_lcd_cmd(0x28);				//--- 4-Bit Mode 2 - Row Select
	twi_lcd_cmd(0x0F);				//--- Cursor on, Blinking on
	twi_lcd_cmd(0x01);				//--- Clear LCD
	twi_lcd_cmd(0x06);				//--- Auto increment Cursor
	twi_lcd_cmd(0x80);				//--- Row 1 Column 1 Address
	//twi_lcd_msg(" M-N-M-tech");	//--- String Send to LCD
	_delay_ms(1000);				//--- 1s Delay
	twi_lcd_clear();				//--- Clear LCD
	delay(100);
}


/* Function to Write data in PCF8574 */


void PCF8574_write(unsigned char x)
{
	twi_start();							//--- Start Condition
	//twi_write_cmd((PCF8574 << 1)| WRITE);	//--- SLA+W is Send 0x40
	twi_write_cmd((addressLcd << 1)| WRITE);
	twi_write_dwr(x);						//--- Data to Slave Device
	twi_stop();								//--- Stop Condition
}



/* Function to Write 4-bit data to LCD */

void twi_lcd_4bit_send(unsigned char x)
{
	unsigned char temp = 0x00;					//--- temp variable for data operation

	lcd &= 0x0F;								//--- Masking last four bit to prevent the RS, RW, EN, Backlight
	temp = (x & 0xF0);							//--- Masking higher 4-Bit of Data and send it LCD
	lcd |= temp;								//--- 4-Bit Data and LCD control Pin
	lcd |= (0x04);								//--- Latching Data to LCD EN = 1
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	_delay_us(1);								//--- 1us Delay
	lcd &= ~(0x04);								//--- Latching Complete
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	_delay_us(5);								//--- 5us Delay to Complete Latching

	temp = ((x & 0x0F)<<4);						//--- Masking Lower 4-Bit of Data and send it LCD
	lcd &= 0x0F;								//--- Masking last four bit to prevent the RS, RW, EN, Backlight
	lcd |= temp;								//--- 4-Bit Data and LCD control Pin
	lcd |= (0x04);								//--- Latching Data to LCD EN = 1
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	_delay_us(1);								//--- 1us Delay
	lcd &= ~(0x04);								//--- Latching Complete
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	_delay_us(5);								//--- 5us Delay to Complete Latching

}

/* Function to Write to LCD Command Register */

void twi_lcd_cmd(unsigned char x)
{
	lcd = 0x08;									//--- Enable Backlight Pin
	lcd &= ~(0x01);								//--- Select Command Register By RS = 0
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	twi_lcd_4bit_send(x);						//--- Function to Write 4-bit data to LCD

}


void twi_lcd_position(char line, char column){
	if(line == 1){
		twi_lcd_cmd(0x80);						//--- Row 1 Column 1 Address
	}
	if(line == 2){
		twi_lcd_cmd(0xC0);						//--- Row 2 Column 1 Address
	}
	delay(6);
	for (int i = 0; i < column; i++)
	{
		twi_lcd_cmd(0X14);
	}
}

/* Function to Write to LCD Command Register */

void twi_lcd_dwr(unsigned char x)
{
	lcd |= 0x09;								//--- Enable Backlight Pin & Select Data Register By RS = 1
	PCF8574_write(lcd);							//--- Send Data From PCF8574 to LCD PORT
	twi_lcd_4bit_send(x);						//--- Function to Write 4-bit data to LCD
}

/* Function to Send String of Data */
//site para criar caracteres https://omerk.github.io/lcdchargen/
void twi_lcd_msg(char *c)
{
	while (*c != '\0')							//--- Check Pointer for Null
	twi_lcd_dwr(*c++);							//--- Send the String of Data
}

/* Function to Execute Clear LCD Command */

void twi_lcd_clear()
{
	twi_lcd_cmd(0x01);
}

void LCD_custom_char(unsigned char loc,unsigned char *msg){

	unsigned char i;
	if(loc<8){
		twi_lcd_cmd(0x40+(loc*8));  /* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)  /* Write 8 byte for generation of 1 character */
		twi_lcd_dwr(msg[i]);
	}
}

/*
	END LCD CODE


*/











void twi_init()
{
	DDRC = 0x03;								//--- PORTC Last two bit as Output
	PORTC = 0x03;

	//usart_msg("CODE-N-LOGIC I2C:");				//--- Send String to Com Port of PC
	//usart_tx(0x0d);								//--- Next Line

	TWCR &= ~(1<<TWEN);							//--- Diable TWI
	TWBR = BITRATE(TWSR = 0x00);				//--- Bit rate with prescaler 4
	TWCR = (1<<TWEN);							//--- Enable TWI
	_delay_us(10);								//--- Delay
}

/* Function to Send Start Condition */
void twi_start()
{
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);		//--- Start Condition as per Datasheet
	while(!(TWCR & (1<<TWINT)));				//--- Wait till start condition is transmitted to Slave
	while(TW_STATUS != TW_START);				//--- Check for the acknowledgment 0x08 = TW_START
	//usart_msg("Start Exe.");					//--- Feedback msg to check for error
	//usart_tx(0x0D);								//--- Next Line
}


/* Function to Send Slave Address for Write operation */

void twi_write_cmd(unsigned char address)
{
	TWDR=address;								//--- SLA Address and write instruction
	TWCR=(1<<TWINT)|(1<<TWEN);					//--- Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT)));				//--- Wait till complete TWDR byte transmitted to Slave
	while(TW_STATUS != TW_MT_SLA_ACK);			//--- Check for the acknowledgment
	//usart_msg("ACK Received for MT SLA");		//--- Feedback msg to check for error
	//usart_tx(0x0D);								//--- Next Line
}


/* Function to Send Data to Slave Device  */

void twi_write_dwr(unsigned char data)
{
	TWDR=data;									//--- Put data in TWDR
	TWCR=(1<<TWINT)|(1<<TWEN);					//--- Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT)));				//--- Wait till complete TWDR byte transmitted to Slave
	while(TW_STATUS != TW_MT_DATA_ACK);			//--- Check for the acknowledgment
	//usart_msg("ACK Received for MT Data");		//--- Feedback msg to check error
	//usart_tx(0x0D);								//--- Next Line

}


/* Function to Send Stop Condition */

void twi_stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);		//--- Stop Condition as per Datasheet
}


/* Function to Send Repeated Start Condition */


void twi_repeated_start()
{
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);		//--- Repeated Start Condition as per Datasheet
	while(!(TWCR & (1<<TWINT)));				//--- Wait till restart condition is transmitted to Slave
	while(TW_STATUS != TW_REP_START);			//--- Check for the acknowledgment
	//usart_msg("Repeated Start Exe.");			//--- Feedback msg to check error
	//usart_tx(0x0D);								//--- Next Line
}


/* Function to Send Read Acknowledgment */

char twi_read_ack()
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);		//--- Acknowledgment Condition as per Datasheet
	while (!(TWCR & (1<<TWINT)));				//--- Wait until Acknowledgment Condition is transmitted to Slave
	while(TW_STATUS != TW_MR_DATA_ACK);			//--- Check for Acknowledgment
	//usart_msg("Receiving MR data ACK ");		//--- Feedback msg to check error
	//usart_tx(0x0D);								//--- Next Line
	return TWDR;								//--- Return received data from Slave
}

/* Function to Send Read No Acknowledgment */

char twi_read_nack()
{
	TWCR=(1<<TWEN)|(1<<TWINT);					//--- No Acknowledgment Condition as per Datasheet
	while (!(TWCR & (1<<TWINT)));				//--- Wait until No Acknowledgment Condition is transmitted to Slave
	while(TW_STATUS != TW_MR_DATA_NACK);		//--- Check for Acknowledgment
	//usart_msg("Receiving MR Data NACK");		//--- Feedback msg to check error
	//usart_tx(0x0D);								//--- Next Line
	return TWDR;								//--- Return received data
}
