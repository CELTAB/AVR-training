   /**********************************************************************/    /****************************************************/
   /**********************************************************************/    /**                 *      |     *                 **/
   /********************** Program for Traffic Lights ********************/    /**                 *            *                 **/
   /************ Simulation two street with call for pedestrian **********/    /**                 *      |     *                 **/
   /**********************************************************************/    /**         B1      *            *                 **/
   /**********************************************************************/    /**              G1 *      |     *    P2   B2      **/
   /** To use this programm, you need to connect to the atmega328p :    **/    /**         P1   Y1 *            *                 **/
   /**                                                                  **/    /**              R1 *      |     * R2 Y2 G2        **/
   /** Red_led_1        on PB0      (street_1)  :  R1                   **/    /********************            ********************/
   /** Red_led_2        on PC2       (street_2)  :  R2                  **/    /**          ______                                **/
   /**                                                                  **/    /**         |______|                               **/
   /** Yellow_led_1     on PB1       (street_1)  :  Y1                  **/    /** __ __ __ ______               __ __ __ __ __ __**/
   /** Yellow_led_2     on PC1      (street_2)  :  Y2                   **/    /**         |______|                               **/
   /**                                                                  **/    /**          ______                     street_2   **/
   /** Green_led_1      on PB2       (street_1)  :  G1                  **/    /**         |______|                               **/
   /** Green_led_2      on PC0       (street_2)  :  G2                  **/    /******************** _  _  _  _ ********************/
   /**                                                                  **/    /**        G2 Y2 R2 *| || || || |* R1              **/
   /** Pedestrian_led_1 on PC5    (street_1)  :  P1                     **/    /**                 *|_||_||_||_|* Y1   P1         **/
   /** Pedestrian_led_2 on PC3    (street_2)  :  P2                     **/    /**        B2 P2    *            * G1              **/
   /**                                                                  **/    /**                 *      |     *      B1         **/
   /** Button_1         on PD2       (street_1)  :  B1                  **/    /**                 *            *                 **/
   /** Button_2         on PD3       (street_2)  :  B2                  **/    /**                 *      |     *                 **/
   /**                                                                  **/    /**                 *  street_1  *                 **/
   /** For the connexion with the Arduino Uno :                         **/    /****************************************************/
   /**  ~11             on PB3                                          **/
   /**  12              on PB4                                          **/
   /**  13              on PB5                                          **/
   /**  ~10             on PC6 (Reset)                                  **/
   /**  5v              on Vcc                                          **/
   /**  Gnd             on Gnd                                          **/
   /**********************************************************************/
   /**********************************************************************/
   /** Be careful with pedestrian's call :                              **/
   /**    -This only works if the green LEDs are lit                    **/
   /**    -There can not have two consecutive calls                     **/
   /**********************************************************************/
   /**********************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned int state = 0;
void blink_blue_1 (void)
{                                       /*******************************/
  PORTC |= (1<<PC5);                  /** Blue_led_1 blinks         **/
  _delay_ms(200);                     /*******************************/
  PORTC &= ~(1<<PC5);
  _delay_ms(200);
}
void blink_blue_2 (void)
{                                       /*******************************/
  PORTC |= (1<<PC3);                  /** Blue_led_2 blinks         **/
  _delay_ms(200);                     /*******************************/
  PORTC &= ~(1<<PC3);
  _delay_ms(200);
}
void green_1 (void)
{                                       /*******************************/
  PORTB = 4;                          /** Green_led_1 is turned on  **/
  _delay_ms(3000);                    /*******************************/
}
void green_2 (void)
{                                       /*******************************/
  PORTC |= 1<<PC0;                    /** Green_led_2 is turned on  **/
  _delay_ms(3000);                    /*******************************/
}
void orange_1 (void)
{                                       /*******************************/
  PORTB = 2;                          /** Yellow_led_1 is turned on **/
  _delay_ms(1500);                  /*******************************/
}
void orange_2 (void)
{                                       /*******************************/
  PORTC |= 1<< PC1;                   /** Yellow_led_2 is turned on **/
  _delay_ms(1500);                  /*******************************/
}
void red_1 (void)
{                                       /*******************************/
  PORTB = 1;                          /** Red_led_1 is turned on    **/
}                                       /*******************************/
void red_2 (void)
{                                       /*******************************/
  PORTC = 4;                          /** Red_led_2 is turned on    **/
}                                       /*******************************/
void blue_1 (void)
{                                       /*******************************/
  PORTC = 32;                          /** Blue_led_1 is turned on   **/
}                                       /*******************************/
void blue_2 (void)
{                                       /*******************************/
  PORTC |= 1 << 3;                    /** Blue_led_2 is turned on   **/
}                                       /*******************************/
void step_1 (void)
{
  red_2();
  blue_2();
  green_1();
}
void step_2 (void)
{
  red_2();
  blue_2();
  orange_1();
}
void step_3 (void)
{
  int i;
  red_2();
  red_1();
  for(i = 0; i<10; i++)
  {
    blink_blue_2();
  }
}
void step_4 (void)
{
  red_1();
  blue_1();
  green_2();
}
void step_5 (void)
{
  red_1();
  blue_1();
  orange_2();
}
void step_6 (void)
{
  int i;
  red_1();
  red_2();
  for(i = 0; i<10; i++)
  {
    blink_blue_1();
  }
}
void walk_call_1 (void)
{
  if ((PORTB == 4)&(state != 2))
  {                                   /*******************************/
    step_2();                       /** Red_led_1 comes faster    **/
    step_3();                       /*******************************/
    state = 1;
  }
}
void walk_call_2 (void)
{
  if ((PORTC == 33)&(state != 1))
  {                                   /*******************************/
    step_5();                       /** Red_led_2 comes faster    **/
    step_6();                       /*******************************/
    state = 2;
  }
}
ISR(INT0_vect)
{
  walk_call_1();         /** interrupt when the button_1 is pressed **/
}
ISR(INT1_vect)
{
  walk_call_2();         /** interrupt when the button_2 is pressed **/
}
int main (void)
{
  DDRB = 7;                       /** Put PB0, PB1 and PB2 in Output**/

  DDRC = 47;            /** Put PC0, PC1, PC2, PC3 and PC5 in Output**/

  DDRD = 1<<PD2;          /***********************************/
  DDRD |= 1<<PD3;          /***********************************/
  PORTD = 1<<PD2;          /**                               **/
  PORTD |= 1<<PD3;              /**                               **/
  EIMSK = 1<<INT0;                /**  Required to use interrupt    **/
  EIMSK |= 1<<INT1;        /**                               **/
  MCUCR = 1<<ISC01 | 1<<ISC00;    /**                               **/
  MCUCR |= 1<<ISC11 | 1<<ISC10;   /***********************************/
  sei();                          /***********************************/

  while(1)
  {
    if (state != 2)
    {
      state = 0;
      step_1();
    }
    if (state == 1)
    {
      step_4();
      step_5();
      step_6();
    }
    else
    {
      if(state != 2)
      {
        step_2();
        step_3();
      }
    }
    if (state != 1)
    {
      state = 0;
      step_4();

    }
    if (state == 2)
    {

      step_1();
      step_2();
      step_3();
    }
    else
    {
      if(state !=1)
      {
        step_5();
        step_6();
      }
    }
  }
  return 0;

}

