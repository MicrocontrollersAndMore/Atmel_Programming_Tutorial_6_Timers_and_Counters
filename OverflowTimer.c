// OverflowTimer.c

// LED on PC4 (pin 27)
// LED on PC5 (pin 28)

#ifndef F_CPU					// if F_CPU was not defined in Project -> Properties
#define F_CPU 1000000UL			// define it now as 1 MHz unsigned long
#endif

#include <avr/io.h>				// this is always included in AVR programs
#include <avr/interrupt.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
int main(void) {
	
	DDRC |= (1 << PC5) | (1 << PC4);			// set PC5 (pin 28) and PC4 (pin 27) for output
	
	/*
	TCCR0A - Timer/Counter 0 Control Register A
	
	bit           7         6         5         4        3       2        1        0
	name        COM0A1    COM0A0    COM0B1    COM0B0     -       -      WGM01    WGM00
	set to        0         0         0         0        0       0        0        0
	
	COM0A1 = 0    normal port operation, OC0A disconnected
	COM0A0 = 0
	
	COM0B1 = 0    normal port operation, OC0B disconnected
	COM0B0 = 0
	
	bit 3 = 0
	bit 2 = 0
	
	WGM01 = 0     "Normal" timer/counter mode
	WGM00 = 0
	*/
	TCCR0A = 0b00000000;
	
	/*
	TCCR0B - Timer/Counter 0 Control Register B
	
	bit           7          6        5       4         3         2         1        0
	name        FOC0A      FOC0B      -       -       WGM02      CS02      CS01     CS00
	set to        0          0        0       0         0         1         0        1
	
	FOC0A = 0     don't use Force Output Compare A
	FOC0B = 0
	
	bit 5 = 0
	bit 4 = 0
	
	WGM02 = 0     "Normal" timer/counter mode, see TCCR0A
	
	CS02 = 1
	CS01 = 0      clock / 1024
	CS00 = 1
	*/
	TCCR0B = 0b00000101;
	
	/*
	TIMSK0 - Timer/Counter 0 Interrupt Mask Register
	
	bit           7        6        5       4       3       2         1         0
	name          -        -        -       -       -     OCIE0B    OCIE0A    TOIE0
	set to        0        0        0       0       0       0         0         1
	
	bit 7 = 0     don't use Force Output Compare A
	bit 6 = 0
	bit 5 = 0
	bit 4 = 0
	bit 3 = 0
	OCIE0B = 0    don't enable Timer/Counter 0 Output Compare Match B Interrupt
	OCIE0A = 0    don't enable Timer/Counter 0 Output Compare Match A Interrupt Enable
	TOIE0 = 1     enable Timer/Counter 0 Overflow Interrupt
	*/
	TIMSK0 = 0b00000001;
	
	/*
	TCCR1A - Timer/Counter1 Control Register A
	
	bit           7         6         5         4        3       2        1        0
	name        COM1A1    COM1A0    COM1B1    COM1B0     -       -      WGM11    WGM10
	set to        0         0         0         0        0       0        0        0
	
	COM1A1 = 0    normal port operation, OC1A disconnected
	COM1A0 = 0
	
	COM1B1 = 0    normal port operation, OC1B disconnected
	COM1B0 = 0
	
	bit 3 = 0
	bit 2 = 0
	
	WGM11 = 0     "Normal" timer/counter mode
	WGM10 = 0
	*/
	TCCR1A = 0b00000000;
	
	/*
	TCCR1B - Timer/Counter1 Control Register B
	
	bit           7          6        5         4          3         2         1        0
	name        ICNC1      ICES1      -       WGM13      WGM12      CS12      CS11     CS10
	set to        0          0        0         0          0         0         1        0
	
	ICNC1 = 0     don't use Input Capture Noise Canceler
	ICES1 = 0     don't use Input Capture Edge Select
	
	bit 5 = 0
	
	WGM13 = 0
	WGM12 = 0     "Normal" timer/counter mode, see TCCR1A
	
	CS12 = 0
	CS11 = 1      clock / 8
	CS10 = 0
	*/
	TCCR1B = 0b00000010;
	
	/*
	TCCR1C - Timer/Counter1 Control Register C
	
	bit           7          6        5       4       3       2       1      0
	name        FOC1A      FOC1B      -       -       -       -       -      -
	set to        0          0        0       0       0       0       0      0
	
	FOC1A = 0     don't use Force Output Compare for Channel A
	FOC1B = 0     don't use Force Output Compare for Channel B
	
	bit 5 = 0
	bit 4 = 0
	bit 3 = 0
	bit 2 = 0
	bit 1 = 0
	bit 0 = 0
	*/
	TCCR1C = 0b00000000;
	
	/*
	TIMSK1 - Timer/Counter 1 Interrupt Mask Register
	
	bit           7        6        5        4       3       2         1         0
	name          -        -      ICIE1      -       -     OCIE1B    OCIE1A    TOIE1
	set to        0        0        0        0       0       0         0         1
	
	bit 7 = 0
	bit 6 = 0
	ICIE1 = 0     don't use Input Capture Interrupt Enable
	bit 4 = 0
	bit 3 = 0
	OCIE1B = 0    don't enable Timer/Counter 1 Output Compare Match B Interrupt
	OCIE1A = 0    don't enable Timer/Counter 1 Output Compare Match A Interrupt Enable
	TOIE1 = 1     enable Timer/Counter 1 Overflow Interrupt
	*/
	TIMSK1 = 0b00000001;
	
	sei();				// enable interrupts
	
	while (1) {	}
	
	return(0);					// should never get here, this is to prevent a compiler warning
}

///////////////////////////////////////////////////////////////////////////////////////////////////
ISR(TIMER0_OVF_vect) {
	PORTC ^= (1 << PC4);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
ISR(TIMER1_OVF_vect) {
	PORTC ^= (1 << PC5);
}



