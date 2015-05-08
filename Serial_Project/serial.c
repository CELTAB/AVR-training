/********************************************************************************************/
/********************************************************************************************/
/****************************** 7 segments display (YSD-160AR4B-8) **************************/
/***********       2 Functions : - Displays the character written on the keyboard ***********/
/***********                     - Hexadecimal counter                            ***********/
/********************************************************************************************/
/*********** Optional Function : - Hexadécimal countdown (interrupt button)       ***********/
/********************************************************************************************/
/********************************************************************************************/
/***********                         _________________                            ***********/
/***********                        /        a        \                           ***********/
/***********                        \ ________________/                           ***********/
/***********                      / \                  / \                        ***********/
/***********                     |   |                |   |                       ***********/
/***********                     |   |                |   |                       ***********/
/***********                     | f |                | b |                       ***********/
/***********                     |   |                |   |                       ***********/
/***********                     |   |                |   |                       ***********/
/***********                     |   |                |   |                       ***********/
/***********                      \ / ________________ \ /                        ***********/
/***********                        /        g        \                           ***********/
/***********                        \ ________________/                           ***********/
/***********                      / \                  / \                        ***********/
/***********                     |   |                |   |                       ***********/
/***********                     |   |                |   |                       ***********/
/***********                     | e |                | c |                       ***********/
/***********                     |   |                |   |                       ***********/
/***********                     |   |                |   |                       ***********/
/***********                     |   |                |   |       ___             ***********/
/***********                      \ / ________________ \ /       /   \            ***********/
/***********                        /        d        \          |   |            ***********/
/***********                        \ ________________/          \ __/            ***********/
/********************************************************************************************/
/********************************************************************************************/
/** To use this programm, you need to connect to the atmega328p :                          **/
/** Segments (PINS) :                                                                      **/
/**   - a (7)     : PB0         - e (1) : PC1                                              **/
/**   - b (6)     : PB1         - f (9) : PC2           PINS 3 & 8 connected to Vcc        **/
/**   - c (4)     : PB2         - g (10): PC3                                              **/
/**   - d (2)     : PC0         - DP(5) : PC4                                              **/
/**   - Button_1  : PD2                                                                    **/
/**   - TXD       : PD0(RXD)    - RXD   : PD1(TXD)   (USB2Serial)                          **/
/**                                                                                        **/
/** For the connexion with the Arduino Uno :                                               **/
/**  ~11             on PB3                                                                **/
/**  12              on PB4                                                                **/
/**  13              on PB5                                                                **/
/**  ~10             on PC6 (Reset)                                                        **/
/**  5v              on Vcc                                                                **/
/**  Gnd             on Gnd                                                                **/
/********************************************************************************************/
/** The interruption (When you press the button) :                                         **/
/**                                                                                        **/
/** Stop the counting, do the countdown and return at the last function                    **/
/********************************************************************************************/
/********************************************************************************************/

/** Library **/
#include <usart.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
//#include <stdio.h>

/** Déclaration for CuteCom Interface **/
uint8_t state;
char tab_choose     [60] = "\nChoose function 0: enter character  1: hexadecimal counter\n";
char tab_letter     [26] = "\nYou just typed a letter : ";
char tab_number     [26] = "\nYou just typed a number : ";
char tab_exit       [32] = "\nExit function : enter character";
char tab_timec      [59] = "\nHow many time would you like counting between 0 and 9 ? : ";
char tab_interrupt  [26] = "\nYou just pressed a button ";
char tab_wrong      [13] = "\nWrong value ";
char tab_count      [26] = "\nThe program has counted : ";

/** Decoding 7 segments **/

void write_0 (void)
{
	PORTB = 0 ;
	PORTC = 24;
}
void write_1 (void)
{
	PORTB = 1 ;
	PORTC = 31;
}
void write_2 (void)
{
	PORTB = 4 ;
	PORTC = 20;
}
void write_3 (void)
{
	PORTB = 0 ;
	PORTC = 22;
}
void write_4 (void)
{
	PORTB = 1 ;
	PORTC = 19;
}
void write_5 (void)
{
	PORTB = 2 ;
	PORTC = 18;
}
void write_6 (void)
{
	PORTB = 2 ;
	PORTC = 16;
}
void write_7 (void)
{
	PORTB = 0 ;
	PORTC = 31;
}
void write_8 (void)
{
	PORTB = 0 ;
	PORTC = 16;
}
void write_9 (void)
{
	PORTB = 0 ;
	PORTC = 18;
}
void write_A (void)
{
	PORTB = 0 ;
	PORTC = 17;
}
void write_B (void)
{
	PORTB = 3 ;
	PORTC = 16;
}
void write_C (void)
{
	PORTB = 6 ;
	PORTC = 24;
}
void write_D (void)
{
	PORTB = 1 ;
	PORTC = 20;
}
void write_E (void)
{
	PORTB = 6 ;
	PORTC = 16;
}
void write_F (void)
{
	PORTB = 6 ;
	PORTC = 17;
}
void write_DP (void)
{
	PORTB = 7 ;
	PORTC = 15;
}

char write_car (char chx)
{
	switch (chx)
	{
		case '0'   : write_0();
		break;
		
		case '1'   : write_1();
		break;
		
		case '2'   : write_2();
		break;
		
		case '3'   : write_3();
		break;
		
		case '4'   : write_4();
		break;
		
		case '5'   : write_5();
		break;
		
		case '6'   : write_6();
		break;
		
		case '7'   : write_7();
		break;
		
		case '8'   : write_8();
		break;
		
		case '9'   : write_9();
		break;
		
		case 'a' : write_A();
		break;
		
		case 'b' : write_B();
		break;
		
		case 'c' : write_C();
		break;
		
		case 'd' : write_D();
		break;
		
		case 'e' : write_E();
		break;
		
		case 'f' : write_F();
		break;
		
		case '.' : write_DP();   
		break;
		
		case '@' :   
		break;
	}
	return chx;
}

void counter (void)
{
	state = 0;

		char i  = 0x30;
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
			if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i = 0x61;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i++;
		}
		if (state == 0)
		{
			write_car(i);
			_delay_ms(250);
			i = 0x30;
		}
}
void write_tab (char *tab, uint8_t size)
{
	uint8_t cpt;
	for (cpt = 0; cpt<size; cpt++)
	{
		USART_transmit_byte(tab[cpt]);
	}	
}

/** Interruption **/

ISR(INT0_vect)
{
 	char i;
 	//uint8_t state;
 	write_tab(tab_interrupt, 26);
 	

	for(i = 0x66; i>=0x61; i=i-1)
	{
		write_car(i);
		_delay_ms(250);
	}
	for(i = 0x39; i>=0x30; i=i-1)
	{
		write_car(i);
		_delay_ms(250);
	}
	//write_car('0');
 	state = 1;
}

int main (void)
{
	DDRD = 1<<PD2;                /*******************************/
	PORTD = 1<<PD2;               /*******************************/
	EIMSK = 1<<INT0;              /** Required to use interrupt **/
	MCUCR = 1<<ISC01 | 1<<ISC00;  /*******************************/
	sei();                        /*******************************/
	
	DDRB = 7;                     /**************************************************************************************************/
	DDRC = 31;                    /** PB0, PB1 and PB2 output config                                                               **/
	PORTB = 7;                    /** PC0, PC1, PC2, PC3 and PC4 output config                                                     **/
	PORTC = 31;                   /**************************************************************************************************/
	char chx, choose;             /** choose : Choose the function in  1st menu, chx : Receive character when you type at keyboard **/
	uint8_t state =0;             /** state : Used to manage interruption                                                          **/
	USART_init();                 /** USART_init() : Required to use USB2Serial communication                                      **/
	char count_time = 0x30;       /** count_time : Receive how many times you would like to count                                  **/
	char cpt_2;                   /** cpt_2 : increments for each count                                                            **/
	state = 0;                    /**************************************************************************************************/
	while(1)
	{
		write_tab(tab_choose, 60);
		choose = USART_receive_byte();
		USART_transmit_byte(choose);

		switch (choose)
		{
			case '0' : 	do
						{
							chx = USART_receive_byte();
							chx = write_car(chx);
							if ((chx >= 0x30)&&(chx <= 0x39))
							{
								write_tab(tab_number,26);
							}
							if ((chx >= 0x61)&&(chx <= 0x66))
							{
								write_tab(tab_letter,26);
							}
							USART_transmit_byte(chx);

						}while (chx != 0x40);
						write_tab(tab_exit,32);						
			break;
			
			case '1' : 
						cpt_2 = 0x30;
						write_tab(tab_timec,59);
						count_time = USART_receive_byte();
						
						USART_transmit_byte(count_time);
						
						if ((count_time < 0x30)||(count_time > 0x39))
						{
							write_tab(tab_wrong, 13);							
						}
						else
						{
							do
							{
								counter();
								cpt_2++;
								write_tab(tab_count, 26);
								USART_transmit_byte(cpt_2);
							}
							while (cpt_2 < count_time);
						}
			break;
							
			default  : 
			break;
		}
		state = 0;
	} 
	return 0;
}
