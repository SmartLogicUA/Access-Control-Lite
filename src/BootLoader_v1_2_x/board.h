/*
  CodeVisionAVR C Compiler
  (C) 2008 Taras Drozdovsky, My.
*/

#ifndef _BOARD_INCLUDED_
#define _BOARD_INCLUDED_

#include <mega168.h>
                     
#define CRCEH       511
#define CRCEL       510
#define HND         496

#define PLED1           2
#define PLED2           0

#define LED1_ON         PORTB.PLED1=1;
#define LED1_OFF        PORTB.PLED1=0;
#define LED2_ON         PORTB.PLED2=1;
#define LED2_OFF        PORTB.PLED2=0;
#define LEDS_ON         {LED1_ON LED2_ON}
#define LEDS_OFF        {LED1_OFF LED2_OFF}
                         
#define PBEEP1          3
#define PBEEP2          1    

#define PORT_BEEP1      PORTB

#define BEEP1_ON        PORTB.PBEEP1=1;
#define BEEP1_OFF       PORTB.PBEEP1=0;
#define BEEP2_ON        PORTB.PBEEP2=1;
#define BEEP2_OFF       PORTB.PBEEP2=0;
#define BEEP_ON         PORTB.4=1;                    // buzer ON on board
#define BEEP_OFF        PORTB.4=0;                   // buzer OFF on board
#define BEEP_TOG        PORTB.4=~PORTB.4;            // buzer ON on board
#define BEEPS_TOG       {BEEP_TOG PORTB.PBEEP1=~PORTB.PBEEP1;PORTB.PBEEP2=~PORTB.PBEEP2;}  // buzer ON on board
#define BEEPS_OFF       {BEEP_OFF BEEP1_OFF BEEP2_OFF}  // buzer ON on board
#define BEEPS_ON        {BEEP_ON BEEP1_ON BEEP2_ON}  // buzer ON on board

#define PGREEN          3
#define PRED            2

#define GREEN_ON        {PORTC.PGREEN=1;RED_OFF}               // led red ON on board // ADC
#define GREEN_OFF       PORTC.PGREEN=0;                      // led red ON on board 
#define GREEN_TOG       PORTC.PGREEN=~PORTC.PGREEN;               // led red ON on board 
#define RED_ON          {PORTC.PRED=1;GREEN_OFF}                      // led red ON on board // ADC
#define RED_OFF         PORTC.PRED=0;                      // led red ON on board 
#define RED_TOG         PORTC.PRED=~PORTC.PRED;               // led red ON on board 

#define PRELAY1         5

#define RELAY1_OFF      PORTB.PRELAY1=0;                      // relay-1 off
#define RELAY1_ON       PORTB.PRELAY1=1;                      // relay-1 on

#define BUT             PINC.0

#define SELECTTIME      PINC.1

#define rx_counterRD1   rx_counter1
#define getcharRD1      getchar1

#define rx_counterRD2   rx_counter2
#define getcharRD2      getchar2

#define rx_buffer_overflowPC rx_buffer_overflow0
#define rx_counterPC    rx_counter0
#define tx_counterPC    tx_counter0
#define putcharPC       putchar
#define getcharPC       getchar

#endif         