/*
 * hamlet.c
 *
 *  Created on: Feb. 5, 2022
 *      Author: Alex Steele
 */

#include <msp430.h>

#include "hamlet.h"



int frequency_to_pwm_period(int frequency) {
    return 1000000 / frequency;
}


void wait_sixteenth() {
    __delay_cycles(100000); // Delay for about 0.1 seconds.
}


void play_note(int note, int sixteenths) {
    TACTL = TASSEL_2 + MC_0; // SMCLK, down mode
    int period = frequency_to_pwm_period(note);
    CCR0 = period; // PWM Period
    CCTL1 = OUTMOD_7; // CCR1 reset/set
    CCR1 = period/2; // CCR1 PWM duty cycle
    TACTL = TASSEL_2 + MC_1; // SMCLK, up mode
    for (int s = sixteenths; s > 0; s--) {
        wait_sixteenth();
    }
}


void rest(int sixteenths) {
    TACTL = TASSEL_2 + MC_0; // SMCLK, down mode
    CCTL1 = OUTMOD_7; // CCR1 reset/set
    CCR1 = 0; // CCR1 PWM duty cycle
    TACTL = TASSEL_2 + MC_1; // SMCLK, up mode
    for (int s = sixteenths; s > 0; s--) {
        wait_sixteenth();
    }
}
