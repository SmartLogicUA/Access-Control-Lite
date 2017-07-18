/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Professional
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Access Control Lite (wiegund26)
Version : v1.0
Date    : 24.02.2009
Author  : Taric
Company : My
Comments: 


Chip type           : ATmega168
Program type        : Application
Clock frequency     : 14,745600 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 256
*****************************************************/

#include <mega168.h>
#include <delay.h>
#include <board.h>
#include <string.h>

#define F_COMMANDNOTSUPPORT "SYCOMMAND NOT SUPPORT"

flash char F_VERSIA[]={"SYVER ACL v1.0"};

flash char tascii[]={"0123456789ABCDEF"};  

eeprom unsigned char *pEEPROM;

unsigned char CounterOpenPassage=0;  
unsigned char counter1=0;
unsigned char mas1[5]={0x0,0x0,0x0,0x0,0x0};
unsigned char counter2=0;
unsigned char mas2[5]={0x0,0x0,0x0,0x0,0x0};

unsigned char counter_adc0_h=0;
unsigned char counter_adc0_m=0;
unsigned char counter_adc0_l=0;
bit level_adc0_l=0;
bit level_adc0_m=0;
bit level_adc0_h=0;                         

unsigned char counter_but1_l=0;            
bit level_but1_l=0;            
unsigned char counter_but1_h=0;            
bit level_but1_h=0;            

#define DELAYMC240      20
#define DELAYPRG    10                                  // time delay 10 second to reset
#define NUMCARD     100                                 // amount cards
#define  MELODY 0x00005D7C 

unsigned long MusicRD1=0;
unsigned char MusicCounterRD1=0;

unsigned long MusicRD2=0;
unsigned char MusicCounterRD2=0;

#define MIN_VOLTAGE     0x4C
#define MAX_VOLTAGE     0x72

// Declare your variables in EEPROM here

eeprom unsigned char MasterCardE[2][3]={0xFF,0xFF,0xFF,     // Master card 1
                                       0xFF,0xFF,0xFF};    // Master card 2
                                                                
                                                                      // Declare card users
eeprom unsigned char CardE[NUMCARD][3]={0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 1 - 2
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 3 - 4
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 5 - 6
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 7 - 8
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 9 - 0
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 11 - 12
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 13 - 14
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 15 - 16
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 17 - 18
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 19 - 20
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 21 - 22
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 23 - 24
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 25 - 26
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 27 - 28
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 29 - 30
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 31 - 32
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 33 - 34
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 35 - 36
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 37 - 38
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 39 - 40
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 41 - 42
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 43 - 44
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 45 - 46
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 47 - 48
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 49 - 50
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 51 - 52
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 53 - 54
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 55 - 56
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 57 - 58
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 59 - 60
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 61 - 62
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 63 - 64
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 65 - 66
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 67 - 68
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 69 - 70
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 71 - 72
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 73 - 74
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 75 - 76
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 77 - 78
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 79 - 80
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 81 - 82
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 83 - 84
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 85 - 86
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 87 - 88
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 89 - 90
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 91 - 92
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 93 - 94
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 95 - 96
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF, // 97 - 98
                                       0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF};// 99 - 100

// Declare your global variables here

unsigned char Card[NUMCARD][3]; 
unsigned char MasterCard[2][3];

unsigned char BuzerCounter=0;                           // counter for buzer    
unsigned char GercCounter=0;                            // counter for gercon
unsigned char CounterOpenPassageC;                      // counter Open passage
unsigned char counterPRG=0;                             // counter delay propgraming card

char FHandContr[12];                                    // Get Handle Controller

bit StartFlagPC=0;                                      // start flag PC packet
unsigned char counter_PC=0;                             // counter byte receive with PC in current packet
unsigned char buffer_PC[64];                            // reveive buffer data PC 

unsigned char cpi_ram(unsigned char *);                 // Check authorized user card
unsigned char ReceiveCrd1(void);                        // Receive packet with reader-1
unsigned char ReceiveCrd2(void);                        // Receive packet with reader-2
void ProcessReader1(void);
void ProcessReader2(void);
void SetSCard(void);                                   // Set master card on reader-1
void PrgCard1(void);                                    // Clear user card and set user card on reader-1
void FindPrgCard1(void);                                // Add user card on reader-1
void PrgCard2(void);                                    // Clear user card and set user card on reader-2
void FindPrgCard2(void);                                // Add user card on reader-2

void Receive_PC(void);                                  // Receive data from PC and shaping packet
void SendAnswer(flash char *);                          // Send answer with Flash memory string
void SendAnswerF(flash char *);                         // Send answer with Flash memory string
void SendAnswerR(char *);                               // Send answer with RAM memory string
void eeprom2ram(void);

unsigned char IdenCard1[5];                           // buffer 1 byte identifier card user
unsigned char IdenCard2[5];                           // buffer 1 byte identifier card user
unsigned char counter_reader1=0;                        // counter receive byte reader-1
unsigned char counter_reader2=0;                        // counter receive byte reader-2

#define RXB8 1
#define TXB8 0
#define UPE 2
#define OVR 3
#define FE 4
#define UDRE 5
#define RXC 7

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<OVR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

// USART Receiver buffer
#define RX_BUFFER_SIZE0 32
char rx_buffer0[RX_BUFFER_SIZE0];

#if RX_BUFFER_SIZE0<256
unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;
#else
unsigned int rx_wr_index0,rx_rd_index0,rx_counter0;
#endif

// This flag is set on USART Receiver buffer overflow
bit rx_buffer_overflow0;

// USART Receiver interrupt service routine
interrupt [USART_RXC] void usart_rx_isr(void)
{
char status,data;
status=UCSR0A;
data=UDR0;
if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
   {
   rx_buffer0[rx_wr_index0]=data;
   if (++rx_wr_index0 == RX_BUFFER_SIZE0) rx_wr_index0=0;
   if (++rx_counter0 == RX_BUFFER_SIZE0)
      {
      rx_counter0=0;
      rx_buffer_overflow0=1;
      };
   };
}

#ifndef _DEBUG_TERMINAL_IO_
// Get a character from the USART Receiver buffer
#define _ALTERNATE_GETCHAR_
#pragma used+
char getchar(void)
{
char data;
while (rx_counter0==0);
data=rx_buffer0[rx_rd_index0];
if (++rx_rd_index0 == RX_BUFFER_SIZE0) rx_rd_index0=0;
#asm("cli")
--rx_counter0;
#asm("sei")
return data;
}
#pragma used-
#endif

// USART Transmitter buffer
#define TX_BUFFER_SIZE0 36
char tx_buffer0[TX_BUFFER_SIZE0];

#if TX_BUFFER_SIZE0<256
unsigned char tx_wr_index0,tx_rd_index0,tx_counter0;
#else
unsigned int tx_wr_index0,tx_rd_index0,tx_counter0;
#endif

// USART Transmitter interrupt service routine
interrupt [USART_TXC] void usart_tx_isr(void)
{
if (tx_counter0)
   {
   --tx_counter0;
   UDR0=tx_buffer0[tx_rd_index0];
   if (++tx_rd_index0 == TX_BUFFER_SIZE0) tx_rd_index0=0;
   };
}

#ifndef _DEBUG_TERMINAL_IO_
// Write a character to the USART Transmitter buffer
#define _ALTERNATE_PUTCHAR_
#pragma used+
void putchar(char c)
{
while (tx_counter0 == TX_BUFFER_SIZE0);
#asm("cli")
if (tx_counter0 || ((UCSR0A & DATA_REGISTER_EMPTY)==0))
   {
   tx_buffer0[tx_wr_index0]=c;
   if (++tx_wr_index0 == TX_BUFFER_SIZE0) tx_wr_index0=0;
   ++tx_counter0;
   }
else
   UDR0=c;
#asm("sei")
}
#pragma used-
#endif

// USART1 Receiver buffer
#define RX_BUFFER_SIZE1 16
char rx_buffer1[RX_BUFFER_SIZE1];

#if RX_BUFFER_SIZE1<256
unsigned char rx_wr_index1,rx_rd_index1,rx_counter1;
#else
unsigned int rx_wr_index1,rx_rd_index1,rx_counter1;
#endif

// This flag is set on USART1 Receiver buffer overflow
bit rx_buffer_overflow1;

// Get a character from the USART1 Receiver buffer
#pragma used+
char getchar1(void)
{
char data;
while (rx_counter1==0);
data=rx_buffer1[rx_rd_index1];
if (++rx_rd_index1 == RX_BUFFER_SIZE1) rx_rd_index1=0;
#asm("cli")
--rx_counter1;
#asm("sei")
return data;
}
#pragma used-

// USART2 Receiver buffer
#define RX_BUFFER_SIZE2 16
char rx_buffer2[RX_BUFFER_SIZE2];

#if RX_BUFFER_SIZE2<256
unsigned char rx_wr_index2,rx_rd_index2,rx_counter2;
#else
unsigned int rx_wr_index2,rx_rd_index2,rx_counter2;
#endif

// This flag is set on USART3 Receiver buffer overflow
bit rx_buffer_overflow2;

// Get a character from the USART3 Receiver buffer
#pragma used+
char getchar2(void)
{
char data;
while (rx_counter2==0);
data=rx_buffer2[rx_rd_index2];
if (++rx_rd_index2 == RX_BUFFER_SIZE2) rx_rd_index2=0;
#asm("cli")
--rx_counter2;
#asm("sei")
return data;
}

// Pin change 16-23 interrupt service routine
interrupt [PCINT2] void pin_change_isr2(void)
{
// Place your code here  
    switch (PIND&0x30) {
    case 0x10:
            { 
                TIFR2|=0x04;    
                TIMSK2|=0x04;       
                OCR2B=TCNT2+0xD5;
                mas2[4]<<=1;
                if(mas2[3]&0x80) mas2[4]|=0x01;
                mas2[3]<<=1;
                if(mas2[2]&0x80) mas2[3]|=0x01;
                mas2[2]<<=1;
                if(mas2[1]&0x80) mas2[2]|=0x01;
                mas2[1]<<=1;
                if(mas2[0]&0x80) mas2[1]|=0x01;
                mas2[0]<<=1;
                counter2++;
            }
    break;
    case 0x20:
            {
                    TIFR2|=0x04;    
                    TIMSK2|=0x04;       
                    OCR2B=TCNT2+0xD5;
                    mas2[4]<<=1;
                    if(mas2[3]&0x80) mas2[4]|=0x01;
                    mas2[3]<<=1;
                    if(mas2[2]&0x80) mas2[3]|=0x01;
                    mas2[2]<<=1;
                    if(mas2[1]&0x80) mas2[2]|=0x01;
                    mas2[1]<<=1;
                    if(mas2[0]&0x80) mas2[1]|=0x01;
                    mas2[0]<<=1;
                    mas2[0]|=0x01;
                    counter2++;

            } 
    break;
    }; 
    switch (PIND&0xC0) {
    case 0x40:
            { 
               TIFR2|=0x02;    
               TIMSK2|=0x02;       
               OCR2A=TCNT2+0xD5;
               mas1[4]<<=1;
               if(mas1[3]&0x80) mas1[4]|=0x01;
               mas1[3]<<=1;
               if(mas1[2]&0x80) mas1[3]|=0x01;
               mas1[2]<<=1;
               if(mas1[1]&0x80) mas1[2]|=0x01;
               mas1[1]<<=1;
               if(mas1[0]&0x80) mas1[1]|=0x01;
               mas1[0]<<=1;
               counter1++;
            } 
    break;
    case 0x80:
            {
                TIFR2|=0x02;    
                TIMSK2|=0x02;       
                OCR2A=TCNT2+0xD5;
                mas1[4]<<=1;
                if(mas1[3]&0x80) mas1[4]|=0x01;
                mas1[3]<<=1;
                if(mas1[2]&0x80) mas1[3]|=0x01;
                mas1[2]<<=1;
                if(mas1[1]&0x80) mas1[2]|=0x01;
                mas1[1]<<=1;
                if(mas1[0]&0x80) mas1[1]|=0x01;
                mas1[0]<<=1;
                mas1[0]|=0x01;
                counter1++;
            }
    break;
    }; 
}

// Standard Input/Output functions
#include <stdio.h>
unsigned char BuzerDelay=0;
// Timer 0 output compare A interrupt service routine
interrupt [TIM0_COMPA] void timer0_compa_isr(void)
{
// Place your code here
 if(!BUT)
 {
    counter_but1_h=0;
    if(!level_but1_l)
    {
        if(counter_but1_l>=DELAYMC240) 
        {
            level_but1_l=1;
            level_but1_h=0;
        }
        else
        {
            counter_but1_l++;    
        }    
    }
 }            
 else
 {           
    counter_but1_l=0;            
    if(!level_but1_h)
    {
        if(counter_but1_h>=DELAYMC240) 
        {
            level_but1_h=1;
            level_but1_l=0;            
            CounterOpenPassage=CounterOpenPassageC;
            if(BuzerCounter) BuzerCounter=40;
            BEEP_OFF
            RELAY1_ON                                              // relay On
            GREEN_ON                                               // led On
        }
        else
        {
            counter_but1_h++;    
        }    
   }
 } 
 if((BuzerCounter<30)&&(BuzerCounter))
 {
    if(BuzerDelay)BuzerDelay--;
    else
    {
        BEEP_TOG
        BuzerDelay=20;
    }
 }
  if(MusicCounterRD1) MusicCounterRD1--;
  else
  {
    if(MusicRD1) 
    {   
        MusicCounterRD1=4;
        if(MusicRD1&0x01){ LED1_ON BEEP1_ON}  
        else { LED1_OFF BEEP1_OFF}
        MusicRD1>>=1;
        if(!MusicRD1){ LED1_OFF BEEP1_OFF } 
    }
  } 
  if(MusicCounterRD2) MusicCounterRD2--;
  else
  {
    if(MusicRD2) 
    {   
        MusicCounterRD2=4;
        if(MusicRD2&0x01){ LED2_ON BEEP2_ON}  
        else { LED2_OFF BEEP2_OFF}
        MusicRD2>>=1;
        if(!MusicRD2){ LED2_OFF BEEP2_OFF } 
    }
  } 
}

// Timer 1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
// Place your code here
 if(CounterOpenPassage) 
 {
    CounterOpenPassage--;
    if(!CounterOpenPassage)
    {
        RELAY1_OFF 
        GREEN_OFF      
    }
 }
 else
    if(!counterPRG) RED_ON                             
 LEDS_ON    
 if(counterPRG) counterPRG--; 
 if(BuzerCounter)
 {
    BuzerCounter--;
    if(!BuzerCounter) BEEP_OFF
 }   
 if(GercCounter) GercCounter--;
}

// Timer 1 output compare B interrupt service routine
interrupt [TIM1_COMPB] void timer1_compb_isr(void)
{
 // Place your code here
 //RED_OFF
 if(!counterPRG) RED_OFF
 LEDS_OFF
}

// Timer 2 output compare interrupt service routine
interrupt [TIM2_COMPA] void timer2_compa_isr(void)
{
// Place your code here
 unsigned char i=0;
 TIMSK2&=~0x02;  
 if(mas1[0]&0x01)i++;
 mas1[0]>>=1;
 if(mas1[1]&0x01) mas1[0]|=0x80;
 mas1[1]>>=1;
 if(mas1[2]&0x01) mas1[1]|=0x80;
 mas1[2]>>=1;
 if(mas1[3]&0x01) mas1[2]|=0x80;
 mas1[3]>>=1;
 if(mas1[4]&0x01) mas1[3]|=0x80;
 mas1[4]>>=1;
 switch (counter1) {
    case 26:    {   
                     if(mas1[0]&0x01) i++; 
                     if(mas1[0]&0x02) i++;
                     if(mas1[0]&0x04) i++;
                     if(mas1[0]&0x08) i++;
                     if(mas1[0]&0x10) i++;
                     if(mas1[0]&0x20) i++;
                     if(mas1[0]&0x40) i++;
                     if(mas1[0]&0x80) i++;
                     if(mas1[1]&0x01) i++;
                     if(mas1[1]&0x02) i++;
                     if(mas1[1]&0x04) i++;
                     if(mas1[1]&0x08) i++;
                     if(i&0x01)
                     {                 
                        i=0;
                        if(mas1[1]&0x10) i++;
                        if(mas1[1]&0x20) i++;
                        if(mas1[1]&0x40) i++;
                        if(mas1[1]&0x80) i++;
                        if(mas1[2]&0x01) i++;
                        if(mas1[2]&0x02) i++;
                        if(mas1[2]&0x04) i++;
                        if(mas1[2]&0x08) i++;
                        if(mas1[2]&0x10) i++;
                        if(mas1[2]&0x20) i++;
                        if(mas1[2]&0x40) i++;
                        if(mas1[2]&0x80) i++;
                        if(mas1[3]&0x01) i++;
                        if(i&0x01)
                        {
                            counter1=0;
                            mas1[0]=mas1[1]=mas1[2]=mas1[3]=mas1[4]=0; 
                            return ;
                        }    
                     }
                mas1[3]=0;
                } 
    break;
    case 34: mas1[4]=0;
    break;
    case 37: mas1[4]&=0x07;
    break;       
    default:
    };                    
 for(i=5;i!=0;i--)
 {   
   rx_buffer1[rx_wr_index1]=mas1[i-1];
   if (++rx_wr_index1 == RX_BUFFER_SIZE1) rx_wr_index1=0;
    if (++rx_counter1 == RX_BUFFER_SIZE1)
    {
        rx_counter1=0;
        rx_buffer_overflow1=1;
    };
 } 
 counter1=0;
 mas1[0]=mas1[1]=mas1[2]=mas1[3]=mas1[4]=0; 
}
//bit Odd_Even=0;
// Timer 2 output compare interrupt service routine
interrupt [TIM2_COMPB] void timer2_compb_isr(void)
{
// Place your code here
 unsigned char i=0;                   
 TIMSK2&=~0x04;  
 if(mas2[0]&0x01)i++;
 mas2[0]>>=1;
 if(mas2[1]&0x01) mas2[0]|=0x80;
 mas2[1]>>=1;
 if(mas2[2]&0x01) mas2[1]|=0x80;
 mas2[2]>>=1;
 if(mas2[3]&0x01) mas2[2]|=0x80;
 mas2[3]>>=1;
 if(mas2[4]&0x01) mas2[3]|=0x80;
 mas2[4]>>=1;  
 switch (counter2) {
    case 26:    {
                     if(mas2[0]&0x01) i++; 
                     if(mas2[0]&0x02) i++;
                     if(mas2[0]&0x04) i++;
                     if(mas2[0]&0x08) i++;
                     if(mas2[0]&0x10) i++;
                     if(mas2[0]&0x20) i++;
                     if(mas2[0]&0x40) i++;
                     if(mas2[0]&0x80) i++;
                     if(mas2[1]&0x01) i++;
                     if(mas2[1]&0x02) i++;
                     if(mas2[1]&0x04) i++;
                     if(mas2[1]&0x08) i++;
                     if(i&0x01)
                     {                 
                        i=0;
                        if(mas2[1]&0x10) i++;
                        if(mas2[1]&0x20) i++;
                        if(mas2[1]&0x40) i++;
                        if(mas2[1]&0x80) i++;
                        if(mas2[2]&0x01) i++;
                        if(mas2[2]&0x02) i++;
                        if(mas2[2]&0x04) i++;
                        if(mas2[2]&0x08) i++;
                        if(mas2[2]&0x10) i++;
                        if(mas2[2]&0x20) i++;
                        if(mas2[2]&0x40) i++;
                        if(mas2[2]&0x80) i++;
                        if(mas2[3]&0x01) i++;
                        if(i&0x01)
                        {
                            counter2=0;
                            mas2[0]=mas2[1]=mas2[2]=mas2[3]=mas2[4]=0; 
                            return ;
                        }    
                     }
                   mas2[3]=0; 
                } 
    break;
    case 34: mas2[4]=0;
    break;
    case 37: mas2[4]&=0x07;
    break;      
    };
 for(i=5;i!=0;i--)
 {   
    rx_buffer2[rx_wr_index2]=mas2[i-1];
    if (++rx_wr_index2 == RX_BUFFER_SIZE2) rx_wr_index2=0;
    if (++rx_counter2 == RX_BUFFER_SIZE2)
    {
        rx_counter2=0;                                              
        rx_buffer_overflow2=1;
    };
 } 
 counter2=0;
 mas2[0]=mas2[1]=mas2[2]=mas2[3]=mas2[4]=0; 
}
#define ADC_VREF_TYPE 0x60

// ADC interrupt service routine
interrupt [ADC_INT] void adc_isr(void)
{
unsigned char adc_data;
// Read the 8 most significant bits
// of the AD conversion result
adc_data=ADCH;                              
// Place your code here
                if(MIN_VOLTAGE>adc_data)
                {
                 counter_adc0_m=0;                       
                 counter_adc0_h=0;            
                 if(!level_adc0_l)
                 {
                    if(counter_adc0_l>=DELAYMC240) 
                        {
                            level_adc0_l=1;
                            level_adc0_m=0;
                            level_adc0_h=0;           
                            if(CounterOpenPassage) BuzerCounter=40;
                            else BuzerCounter=30;            
                        }
                    else
                        {
                            counter_adc0_l++;    
                        }    
                 }
                }
                else
                {            
                 if((adc_data>MIN_VOLTAGE)&&(adc_data<MAX_VOLTAGE))
                 {           
                  counter_adc0_l=0;            
                  counter_adc0_h=0;            
                  if(!level_adc0_m)
                  {
                     if(counter_adc0_m>=DELAYMC240) 
                         {
                             level_adc0_m=1;
                             level_adc0_l=0;            
                             level_adc0_h=0;
                             BEEP_OFF;     
                             BuzerCounter=0;
                         }
                     else
                         {
                             counter_adc0_m++;    
                        }    
                  }
                 }
                 else
                 {            
                  if(MAX_VOLTAGE<adc_data)
                  {           
                   counter_adc0_l=0;            
                   counter_adc0_m=0;            
                   if(!level_adc0_h)
                   {
                      if(counter_adc0_h>=DELAYMC240) 
                        {
                            level_adc0_h=1;
                            level_adc0_m=0;
                            level_adc0_l=0;
                            BuzerCounter=30;                               
                            if(CounterOpenPassage) BuzerCounter=40;
                            else BuzerCounter=30;            
                        }
                      else
                        {
                            counter_adc0_h++;    
                        }
                   }             
                  }
                 }
                }            
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here
unsigned char i;
// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif
   
// Input/Output Ports initialization
// Port B initialization
// Func7=In Func6=In Func5=In Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=T State6=T State5=T State4=0 State3=0 State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0x1F;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=Out Func2=Out Func1=In Func0=In 
// State6=T State5=T State4=T State3=0 State2=0 State1=T State0=P 
PORTC=0x13;
DDRC=0x0C;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=P State2=P State1=T State0=T 
PORTD=0x0C;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 14,400 kHz
// Mode: CTC top=OCR0A
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x02;
TCCR0B=0x05;
TCNT0=0x00;
OCR0A=0x90;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 14,400 kHz
// Mode: CTC top=OCR1A
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: On
TCCR1A=0x00;
TCCR1B=0x0D;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x38;
OCR1AL=0x40;
OCR1BH=0x02;
OCR1BL=0xFF;


// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 14,400 kHz
// Mode: Normal top=FFh
// OC2A output: Disconnected
// OC2B output: Disconnected
ASSR=0x00;
TCCR2A=0x00;
TCCR2B=0x07;
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-14: Off
// Interrupt on any change on pins PCINT16-23: On
EICRA=0x00;
EIMSK=0x00;
PCICR=0x04;
PCMSK2=0xF0;
PCIFR=0x04;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x02;
// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=0x06;
// Timer/Counter 2 Interrupt(s) initialization
TIMSK2=0x00;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART0 Mode: Asynchronous
// USART Baud rate: 9600
UCSR0A=0x00;
UCSR0B=0xD8;
UCSR0C=0x06;
UBRR0H=0x00;
UBRR0L=0x5F;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
ADCSRB=0x00;

// ADC initialization
// ADC Clock frequency: 460,800 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: Timer0 Compare Match
// Only the 8 most significant bits of
// the AD conversion result are used
// Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
// ADC4: On, ADC5: On
DIDR0=0x00;
ADMUX=ADC_VREF_TYPE|0x06;
ADCSRA=0xAD;
ADCSRB&=0xF8;
ADCSRB|=0x03;


// Watchdog Timer initialization
// Watchdog Timer Prescaler: OSC/256k
// Watchdog Timer interrupt: Off
#pragma optsize-
#asm("wdr")
WDTCSR=0x1F;
WDTCSR=0x0F;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif


if(SELECTTIME) CounterOpenPassageC=2;                                             // Check: 1 - electro-mechanic lock; 0 - electro-magnetic lock.   
else CounterOpenPassageC=5;

pEEPROM=0;
for(i=0;i!=11;i++)
 FHandContr[i]=(*(pEEPROM+HND+i));
FHandContr[11]=0;

eeprom2ram();

SendAnswer(&F_VERSIA[6]);                      

// Global enable interrupts
#asm("sei")
if(!SETMCARD) SetSCard(); 

while (1)
      {
      // Place your code here
       #asm("wdr")       
      if(rx_counterRD1)                                  // if receive byte PUSART, proccesing 
       if(ReceiveCrd1()) ProcessReader1();             // if receive packet with reader-1, then proccesing packet
      if(rx_counterRD2)                                   // if receive byte PUSART, proccesing                          
       if(ReceiveCrd2()) ProcessReader2();             // if receive packet with reader-2, then proccesing packet
      if(rx_buffer_overflowPC)  {StartFlagPC=0;rx_buffer_overflowPC=0;}
      // Check receive byte with PC
      if(rx_counterPC)          Receive_PC();  
      };
}                 
/**
 * Receive data from PC and shaping packet  
 **/
void Receive_PC(void)
{
 unsigned char data;
 #asm("wdr")
 data=getcharPC(); 
  switch (data) {
    case '$': { StartFlagPC=1; counter_PC=0; }
    break;
    case '\n': 
        if(StartFlagPC)
        {  
         StartFlagPC=0;
         buffer_PC[counter_PC]=0;
         counter_PC=0;
         data=0;
         while((buffer_PC[counter_PC] != '*')&&(buffer_PC[counter_PC] != '\n')) data^=buffer_PC[counter_PC++];
       	 if((tascii[(data&0xF0)>>4]==buffer_PC[++counter_PC])&&(tascii[(data&0x0F)]==buffer_PC[++counter_PC]))
         {
            if(!strncmpf(buffer_PC, "PCHND", 5))
	        { SendAnswerR(FHandContr); return; }
    		if(!strncmpf(buffer_PC, "PCVER", 5))
            { SendAnswerF(F_VERSIA); return; }
    		if(!strncmpf(buffer_PC, "PBLFL", 5))
		    {        
		        #asm("cli")
                pEEPROM=0;
                *(pEEPROM+CRCEH)=0xFF;
                *(pEEPROM+CRCEL)=0xFF;
 	            while(1);
            }
	        SendAnswerF(F_COMMANDNOTSUPPORT);
	        return; 
		 }   
	}
    break;  
    default: 
        if(StartFlagPC)
        {
         buffer_PC[counter_PC++]=data;
        }  
    };
}   
                
/**
 * Send answer with Flash memory string.  
 *
 * @param	*data	a pointer to the string command 
 **/
void SendAnswer(flash char *data){
 unsigned char i=0;
  do {     
   #asm("wdr")
   putcharPC(data[i]);
  }while(data[++i]); 
}                               
/**
 * Send answer with Flash memory string  
 *
 * @param	*data	a pointer to the string command 
 **/
void SendAnswerF(flash char *data){
 unsigned char i=0;
 unsigned char checkbyte=0;
  putcharPC('$'); 
  do {     
   #asm("wdr")
   checkbyte^=data[i];
   putcharPC(data[i]);
  }while(data[++i]); 
   putcharPC('*');
   putcharPC(tascii[(checkbyte&0xF0)>>4]);
   putcharPC(tascii[checkbyte&0x0F]);
   putcharPC('\r');
   putcharPC('\n');     
}
/**
 * Send answer with Flash memory string  
 *
 * @param	*data	a pointer to the string command 
 **/
void SendAnswerR(char *data){
 unsigned char i=0;
 unsigned char checkbyte=0;
  putcharPC('$'); 
  do {     
   #asm("wdr")
   checkbyte^=data[i];
   putcharPC(data[i]);
  }while(data[++i]);
  putcharPC('*');
   putcharPC(tascii[(checkbyte&0xF0)>>4]);
   putcharPC(tascii[checkbyte&0x0F]);
   putcharPC('\r');
   putcharPC('\n');     
}
/**
 * Load with EEPROM to RAM setting.  
 **/             
void eeprom2ram(void)
{
 unsigned char i,j;
 #asm("wdr")         
 for(j=0;j!=NUMCARD;j++)
  for(i=0;i!=3;i++)           
   Card[j][i]=CardE[j][i];
 for(i=0;i!=3;i++)           
  MasterCard[0][i]=MasterCardE[0][i];
 for(i=0;i!=3;i++)           
  MasterCard[1][i]=MasterCardE[1][i]; 
}                                    


/**
 * Receive packet with reader-1   
 *
 * @return	0	        not packet receive 
 * @return	1	        packet receive 
 **/
unsigned char ReceiveCrd1(void)
{
 unsigned char data;        
 #asm("wdr")                
 while(rx_counterRD1)
 {              
  data=getcharRD1();    
  IdenCard1[counter_reader1++]=data;
  if(counter_reader1==5)
  {
     counter_reader1=0;
     return 1;
  }
 } 
 return 0; 
}

/**
 * Receive packet with reader-2   
 *
 * @return	0	        not packet receive 
 * @return	1	        packet receive 
 **/
unsigned char ReceiveCrd2(void)
{
 unsigned char data;        
 #asm("wdr")                
 while(rx_counterRD2)
 {              
  data=getcharRD2();    
  IdenCard2[counter_reader2++]=data;
  if(counter_reader2==5)
  {
      counter_reader2=0;
      return 1;
  }
 } 
 return 0; 
}

/**
 * Check identifier card user  
 *
 * @param	*mas_iden       a pointer to the data: user identifier 
 *
 * @return	0	        not card register 
 * @return	1	        card register 
 **/
unsigned char cpi_ram(unsigned char *mas){
 unsigned char num;
 unsigned char i;
  #asm("wdr")       
  for(num=0;num!=NUMCARD;num++)
   {
    #asm("wdr") 
    i=0;         
      if(Card[num][i++]==mas[0])
       if(Card[num][i++]==mas[1])
        if(Card[num][i]==mas[2])     
         return 1;
   }
 return 0;
}
/**
 * Proccesing packet with reader-1   
 **/
void ProcessReader1(void)
{
  #asm("wdr")  
  if((MasterCard[0][0]==IdenCard1[2])&&(MasterCard[0][1]==IdenCard1[3])&&(MasterCard[0][2]==IdenCard1[4]))
   {PrgCard1();return;}
  if((MasterCard[1][0]==IdenCard1[2])&&(MasterCard[1][1]==IdenCard1[3])&&(MasterCard[1][2]==IdenCard1[4]))
   {FindPrgCard1();return;}
    if (cpi_ram(&IdenCard1[2]))
    { 
        CounterOpenPassage=CounterOpenPassageC;
        if(BuzerCounter) BuzerCounter=40;
        BEEP_OFF
        MusicRD1=MELODY;
        RELAY1_ON
        GREEN_ON  
    } 
    else
    {
        GREEN_OFF
        CounterOpenPassage=0;
        RELAY1_OFF                   
    }     
}  

/**
 * Proccesing packet with reader-2   
 **/
void ProcessReader2(void)
{              
  #asm("wdr")       
  if((MasterCard[0][0]==IdenCard2[2])&&(MasterCard[0][1]==IdenCard2[3])&&(MasterCard[0][2]==IdenCard2[4]))
   {PrgCard2();return;}
  if((MasterCard[1][0]==IdenCard2[2])&&(MasterCard[1][1]==IdenCard2[3])&&(MasterCard[1][2]==IdenCard2[4]))
   {FindPrgCard2();return;}
    if(cpi_ram(&IdenCard2[2]))
    { 
        CounterOpenPassage=CounterOpenPassageC;
        if(BuzerCounter) BuzerCounter=40;
        BEEP_OFF
        MusicRD2=MELODY;
        RELAY1_ON         
        GREEN_ON  
    } 
    else
    {
        GREEN_OFF   
        CounterOpenPassage=0;
        RELAY1_OFF  
    }      
}                                 

/**
 * Set master card on reader-1   
 **/
void SetSCard(void)
{                     
 unsigned char num;
 unsigned char i;         
 num=0;
 while(1)
 {                       
    #asm("wdr")                
    RED_ON
    if(rx_counterRD1)                          
    {
        if(ReceiveCrd1()) 
        {
            i=0;
            #asm("cli")         
            MasterCardE[num][i++]=IdenCard1[2];
            MasterCardE[num][i++]=IdenCard1[3];
            MasterCardE[num++][i]=IdenCard1[4];     
            #asm("sei")
            GREEN_ON                     
            delay_ms(400);
            RED_ON
            if(num==2)
            {
                #asm("cli")
                while(1)
                #asm("wdr");
            }
        }                        
    }
    if(rx_counterRD2)                          
    {
        if(ReceiveCrd2()) 
        {
            i=0;
            #asm("cli")         
            MasterCardE[num][i++]=IdenCard2[2];
            MasterCardE[num][i++]=IdenCard2[3];
            MasterCardE[num++][i]=IdenCard2[4];     
            #asm("sei")
            GREEN_ON                     
            delay_ms(400);
            RED_ON
            if(num==2)
            {
                #asm("cli")
                while(1)
                #asm("wdr");
            }
        }                        
    }
 }
}

/**
 * Clear user card and set user card on reader-1   
 **/ 
void PrgCard1(void)
{                     
 unsigned char num;
 unsigned char i;         
 #asm("wdr")  
 for(num=0;num!=NUMCARD;num++) 
  for(i=0;i!=3;i++) 
   CardE[num][i]=0xFF;
 counterPRG=DELAYPRG;
 num=0;
 while((counterPRG)&&(num<NUMCARD))
 {                       
       #asm("wdr")                
       RED_ON
       if(rx_counter1)                          
        {
         if(ReceiveCrd1()) 
         {
          i=0;
          #asm("cli")         
          CardE[num][i++]=IdenCard1[2];
          CardE[num][i++]=IdenCard1[3];
          CardE[num++][i]=IdenCard1[4];     
          #asm("sei")
          GREEN_ON                     
          counterPRG=DELAYPRG;
          delay_ms(400);
         }                        
       }
 }
 #asm("cli")
 GREEN_ON                         
 while(1);
} 
/**
 * Add user card on reader-1
 **/ 
void FindPrgCard1(void)
{                     
 unsigned char num;
 unsigned char i;         
 #asm("wdr")                
 counterPRG=DELAYPRG;
 num=0;
 while((counterPRG)&&(num<NUMCARD))
 {                       
      #asm("wdr")
      i=0;
      if((CardE[num][i++]==0xFF)&&(CardE[num][i++]==0xFF)&&(CardE[num][i++]==0xFF))
      {
       RED_ON
       if(rx_counter1)                          
        {
         if(ReceiveCrd1()) 
         {
          i=0;
          #asm("cli")         
          CardE[num][i++]=IdenCard1[2];
          CardE[num][i++]=IdenCard1[3];
          CardE[num][i]=IdenCard1[4];     
          #asm("sei")
          GREEN_ON                     
          counterPRG=DELAYPRG;
          delay_ms(400);
         }                        
       }  
     }  
     else
      num++;     
 }
 #asm("cli")
 GREEN_ON                          
 while(1);
}   

/**
 * Clear user card and set user card on reader-2   
 **/ 
void PrgCard2(void)
{                     
 unsigned char num;
 unsigned char i;         
 #asm("wdr")                
 for(num=0;num!=NUMCARD;num++) 
  for(i=0;i!=3;i++) 
   CardE[num][i]=0xFF;
 counterPRG=DELAYPRG;
 num=0;
 while((counterPRG)&&(num<NUMCARD))
 {                       
       #asm("wdr")                
       RED_ON
       if(rx_counterRD2)                          
        {
         if(ReceiveCrd2()) 
         {
          i=0;
          #asm("cli")         
          CardE[num][i++]=IdenCard2[2];
          CardE[num][i++]=IdenCard2[3];
          CardE[num++][i]=IdenCard2[4];     
          #asm("sei")
          GREEN_ON                     
          counterPRG=DELAYPRG;
          delay_ms(400);
         }                        
       }
 }
 #asm("cli")
 GREEN_ON                         
 while(1);
} 

/**
 * Add user card on reader-2
 **/ 
void FindPrgCard2(void)
{                     
 unsigned char num;
 unsigned char i;         
 #asm("wdr")                
 counterPRG=DELAYPRG;
 num=0;
 while((counterPRG)&&(num<NUMCARD))
 {                       
      #asm("wdr")
      i=0;
      if((CardE[num][i++]==0xFF)&&(CardE[num][i++]==0xFF)&&(CardE[num][i++]==0xFF))
      {
       RED_ON
       if(rx_counterRD2)                          
        {
         if(ReceiveCrd2()) 
         {
          i=0;
          #asm("cli")         
          CardE[num][i++]=IdenCard2[2];
          CardE[num][i++]=IdenCard2[3];
          CardE[num][i]=IdenCard2[4];     
          #asm("sei")
          GREEN_ON                     
          counterPRG=DELAYPRG;
          delay_ms(400);
         }                        
       }  
      }  
      else
       num++;     
 }
 #asm("cli")
 GREEN_ON                          
 while(1);
} 