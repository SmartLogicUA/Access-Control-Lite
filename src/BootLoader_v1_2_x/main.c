/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.3 Professional
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : BootLoader 1.2.x
Version : v1.0
Date    : 09.12.2008
Author  : Taric                           
Company : My                              
Comments: Size Application 5888 word (ORG 0x1700) 
          EEPROM until 495

Chip type           : ATmega168
Program type        : Boot Loader - Size:1024words
Clock frequency     : 14,745600 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 256
*****************************************************/

#include <mega168.h>
#include <string.h>    
#include <delay.h>
#include <board.h>     
#include <g28147.h>

#define SPMEN  0
#define PGERS  1
#define PGWRT  2
#define BLBSET 3
#define RWWSRE 4
#define SIRGD  5
#define RWWSB  6
#define SPMIE  7
#define EEWE   1 
#define EEPE   1                          

/*****************************************************************************/
/*                G L O B A L    V A R I A B L E S                           */
/*****************************************************************************/
#pragma warn-

register unsigned char  Bufferl  @0;
register unsigned char  Bufferh  @1;

register unsigned int  reg_temp @2;

flash unsigned char *mas;

union {                                                 // union for conversion type long,int in char
  unsigned char byte[4];
  unsigned int word[2];
  unsigned long dword;      
 } number;

union {                                                 // union for check sum (interrupt)
 unsigned char crcb[2];
 unsigned int crcw;      
      } crci;      

unsigned char kkkk[]="Not correct CRC check sum";

#pragma warn+ 

eeprom unsigned char *pEEPROM;

unsigned int counter_PC=0;
unsigned char buffer_PC[275];

bit StartFlagPC=0;        

unsigned char BootHere[]="SBLFL";   

flash char FHandContr[]="SYHND 00006";                    // Get Handle Controller

/*****************************************************************************/
/*                 G O S T   2 8 1 4 7 - 8 9                                 */
/*****************************************************************************/

unsigned long S[2];
unsigned long KZU[8]={0xA9A3F144,0x3FE88BBB,0x567E73F8,0x99EE4EA4,
                      0x4765070B,0x3C1ED726,0x93E8D330,0x6E98971D}; // KEY

                      //46F1930960187A57B67699F378BA94522313163690CF001FDE7321121FD5896A



unsigned char K[128]={       // Gam_c
   0x0F, 0x04, 0x03, 0x06, 0x0D, 0x02, 0x09, 0x08, 0x00, 0x0C, 0x01, 0x0E, 0x07, 0x05, 0x0A, 0x0B,
   0xE0, 0x30, 0xC0, 0x20, 0xD0, 0x90, 0x10, 0xB0, 0x50, 0x40, 0x60, 0xA0, 0x00, 0xF0, 0x80, 0x70,
   0x04, 0x08, 0x0C, 0x01, 0x0E, 0x07, 0x00, 0x0F, 0x0B, 0x02, 0x09, 0x06, 0x05, 0x03, 0x0A, 0x0D,
   0x10, 0x90, 0x80, 0x50, 0xE0, 0xF0, 0xA0, 0xB0, 0x00, 0xC0, 0x70, 0x30, 0xD0, 0x60, 0x20, 0x40,
   0x09, 0x03, 0x04, 0x0C, 0x01, 0x00, 0x0B, 0x05, 0x06, 0x0F, 0x0D, 0x0E, 0x07, 0x02, 0x0A, 0x08,
   0xE0, 0x40, 0x90, 0xD0, 0xA0, 0x30, 0xF0, 0x10, 0xB0, 0x70, 0x80, 0x50, 0x60, 0xC0, 0x20, 0x00,
   0x02, 0x0A, 0x06, 0x0E, 0x05, 0x0D, 0x0C, 0x03, 0x07, 0x08, 0x0F, 0x00, 0x09, 0x0B, 0x01, 0x04,
   0xB0, 0x90, 0x80, 0x10, 0xA0, 0x60, 0xD0, 0x40, 0x00, 0x50, 0x20, 0xC0, 0xE0, 0xF0, 0x30, 0x70};

/*****************************************************************************/
/*                  F U N C T I O N  P R O T O T Y P E                       */
/*****************************************************************************/
void Receive_PC(void);
void ProgramFlashPage(unsigned char *);
void ProgramEEPROM(unsigned char *);
void InitSign(unsigned char *);

void SendAnswerR(char *);
void Print(flash char *data);
        
void crc2(unsigned char *,unsigned int *,unsigned int);
unsigned char check_flash_crc(void);
void WriteFlash(unsigned int P_address,unsigned char *pData);  
void ASCIIToHex(unsigned char *,unsigned int);
/*****************************************************************************/  

flash char tascii[]={"0123456789ABCDEF"};  

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
#define RX_BUFFER_SIZE0 64
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
#define TX_BUFFER_SIZE0 64
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

#pragma warn+ 

interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
// Place your code here
 RED_TOG                            
 GREEN_TOG                           
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
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x08;
DDRC=0x0C;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x00;
TCCR0B=0x00;
TCNT0=0x00;
OCR0A=0x00;
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
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x0D;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x08;
OCR1AL=0x20;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer 2 Stopped
// Mode: Normal top=FFh
// OC2A output: Disconnected
// OC2B output: Disconnected
ASSR=0x00;
TCCR2A=0x00;
TCCR2B=0x00;
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-14: Off
// Interrupt on any change on pins PCINT16-23: Off
EICRA=0x00;
EIMSK=0x00;
PCICR=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x00;
// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=0x02;
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
#asm("wdr")
#asm("sei")       // Global enable interrupts
Print("\r\nBootLoader v1.2.x");     

for(i=0;i!=12;i++)
{
 if(FHandContr[i]!=(*(pEEPROM+HND+i)))
  *(pEEPROM+HND+i)=FHandContr[i];
}             
Print("\r\nS/N ");
Print(&FHandContr[6]);

if(check_flash_crc())
{
 Print("\r\nCRC OK\r\n");
 while(tx_counterPC)
      #asm("wdr")

 delay_ms(120);
 #asm("cli")
 MCUCR=0x01;                         //interrupts vectors are in the boot sector
 MCUCR=0x00;
 #asm("jmp 0x000");                 // Run application code
}
else 
{
 Print("\r\nCRC ERROR\r\n"); 
}

SendAnswerR(BootHere);
   
while (1)                                                          
      { 
      // Place your code here
      #asm("wdr")
      if(rx_counterPC) Receive_PC();
      };
}

void WriteFlash(unsigned int P_address,unsigned char *pData)
{ 
 unsigned char i;
 #asm("wdr")
 #asm("cli");            
 while(EECR & (1<<EEPE));
 reg_temp = P_address<<7;
 SPMCSR|=(1<<PGERS) | (1<<SPMEN);
 #asm  
     mov r31,r3
     mov r30,r2
     spm
 #endasm
 while(SPMCSR&(1<<SPMEN));        // Polled to find out when the CPU is ready for further page updates
 SPMCSR|=(1<<RWWSRE)|(1<<SPMEN);  // RWWSB Flag cleared by software when the SPM operation is completed.
 #asm("spm")
 #asm("sei")
 #asm("wdr")
 for (i=0;i!=128;i+=2)
 { 
  #pragma warn-         
  Bufferh=*(pData+i+1);
  Bufferl=*(pData+i);
  reg_temp = i;
  SPMCSR =(1<<SPMEN);
  #asm  
     mov r31,r3
     mov r30,r2
     spm
  #endasm
  #pragma warn+
 }
 #asm("cli")
 reg_temp = P_address<<7;;
 SPMCSR|=(1<<PGWRT) | (1<<SPMEN);
 #asm  
    mov r31,r3
    mov r30,r2
    spm
 #endasm
 while(SPMCSR&(1<<SPMEN));        // Polled to find out when the CPU is ready for further page updates
 SPMCSR|=(1<<RWWSRE)|(1<<SPMEN);  // RWWSB Flag cleared by software when the SPM operation is completed.
 #asm("spm");
 #asm("sei");
}
unsigned char check_flash_crc(void)
{
 unsigned char mas1[128];
 unsigned int i;  
 unsigned int j;
 unsigned int k;
 #asm("wdr") 
 crci.crcw=0;
 while(EECR & (1<<EEPE));
 if((*(pEEPROM+508))>7) return 0;
 k=(*(pEEPROM+508));
 k<<=8; 
 k|=(*(pEEPROM+509));
 for(j=0;j!=k;j++)
 {
  for(i=0;i!=128;i++)
   mas1[i]=*(mas+i+j*128);
  crc2(&mas1[0],&crci.crcw,128);
 }              
 while(EECR & (1<<EEPE));
 if((crci.crcb[1]==(*(pEEPROM+510)))&&(crci.crcb[0]==(*(pEEPROM+511))))
 {
  return 1;
 }
 return 0;
}
/**
 * print with Flash memory string.  
 *
 * @param	*data	a pointer to the string command 
 **/
void Print(flash char *data){
 unsigned char i=0;
 do {     
   #asm("wdr")
   putcharPC(data[i]);
  }while(data[++i]); 
}

/********************************************************
***        OTHER SECTION         ORG 0x1800       *******
*********************************************************/

#asm(".CSEG")	
#asm(".ORG 0x1700")	
/*****************************************************************************/ 
void mmm(unsigned char *pData)
{
 unsigned char i;
 unsigned char a;
 #asm("wdr") 
 ASCIIToHex(&pData[0],128);
 for(i=0;i!=32;i++)
 {           
  a=pData[i*4];
  pData[i*4]=pData[i*4+3];
  pData[i*4+3]=a;
  a=pData[i*4+1];
  pData[i*4+1]=pData[i*4+2];
  pData[i*4+2]=a;  
 }  
 Gam_cD(&pData[0],&KZU[0],&K[0],16);
 for(i=0;i!=32;i++)
 {           
  a=pData[i*4];
  pData[i*4]=pData[i*4+3];
  pData[i*4+3]=a;
  a=pData[i*4+1];
  pData[i*4+1]=pData[i*4+2];
  pData[i*4+2]=a;  
 }  
}

void ProgramFlashPage(unsigned char *mas)
{           
 unsigned int addr; 
 unsigned char kkk[]="SFLSH0000OK";
 #asm("wdr")
 kkk[5]=mas[0];
 kkk[6]=mas[1];
 kkk[7]=mas[2];
 kkk[8]=mas[3];                 
 ASCIIToHex(&mas[0],2);
 addr=mas[1];
 mmm(&mas[4]);
 WriteFlash(addr,&mas[4]);
 SendAnswerR(kkk);
}

void ProgramEEPROM(unsigned char *mas)
{	    
 unsigned int addr;
 unsigned int lenght;
 unsigned int i;  
 unsigned char kkk[]="SEEPR0000OK";
 #asm("wdr")
 kkk[5]=mas[0];
 kkk[6]=mas[1];
 kkk[7]=mas[2];
 kkk[8]=mas[3];
 ASCIIToHex(&mas[0],4);
 addr=mas[0];
 addr<<=8;
 addr|=mas[1];       
 lenght=mas[2];
 lenght<<=8;
 lenght|=mas[3];
 ASCIIToHex(&mas[8],lenght);
 for(i=0;i!=lenght;i++)
 {                
  *(pEEPROM+addr+i)=mas[i+8];
 }
 if(addr==0x01FC)
 {
    SendAnswerR(kkk);
    while(tx_counterPC);
    while(1);
    //delay_ms(120);
   // #asm("cli") 
    //MCUCR=0x01;                         //interrupts vectors are in the boot sector
    //MCUCR=0x02;
    //#asm("jmp 0x1C00");                 // Run application code
 }                                         
  SendAnswerR(kkk);
}
/**
 * Send answer with Flash memory string.  
 *
 * @param	*data	a pointer to the string command 
 **/
void SendAnswerR(char *data){
 unsigned char i=0;
 unsigned char checkbyte=0;
 #asm("wdr")
 putcharPC('$');
 do {     
   #asm("wdr")
   checkbyte^=data[i];
   putcharPC(data[i]);
  }while(data[++i]); 
   putcharPC('*');
   putcharPC(tascii[(checkbyte&0xF0)>>4]);
   putcharPC(tascii[checkbyte&0x0F]);
   putcharPC('\n');     
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
    case '$': { StartFlagPC=1; counter_PC=0;}
    break;
    case '\n': 
        if(StartFlagPC)
        {
         StartFlagPC=0;
         data=0;                  
         counter_PC=0;
         while((buffer_PC[counter_PC] != '*')&&(buffer_PC[counter_PC] != '\n') )	  
         data^=buffer_PC[counter_PC++];                      
         if(buffer_PC[counter_PC]=='*')
         {      
          if((tascii[(data&0xF0)>>4]==buffer_PC[++counter_PC])&&(tascii[data&0x0F]==buffer_PC[++counter_PC]))

            {
                if(!strncmpf(buffer_PC, "PSIGN", 5))
	            {
	                InitSign(&buffer_PC[5]); 
	            }
	            if(!strncmpf(buffer_PC, "PFLSH", 5))
	            {         
	                ProgramFlashPage(&buffer_PC[5]);
	            }
 	            if(!strncmpf(buffer_PC, "PBLFL", 5))
 	            {         
                    Gost_init(&S[0]);
                    SendAnswerR(BootHere);	    
 	            }
                if(!strncmpf(buffer_PC, "PEEPR", 5))
	            {
	                ProgramEEPROM(&buffer_PC[5]);
                } 
            }
            else
            {
                SendAnswerR(kkkk);
            }
         } 
         else
         {
          ;//SendAnswerR(kkkk);
         }
    }
    break;
    default: 
        if(StartFlagPC) buffer_PC[counter_PC++]=data;  
    };
}                                   

void InitSign(unsigned char *mas)
{
 unsigned char answerC[]="SSIGNOK";
 #asm("wdr")
 ASCIIToHex(&mas[0],8);
 number.byte[3]=mas[0];
 number.byte[2]=mas[1];
 number.byte[1]=mas[2];
 number.byte[0]=mas[3];
 S[0]=number.dword;
 number.byte[3]=mas[4];
 number.byte[2]=mas[5];
 number.byte[1]=mas[6];
 number.byte[0]=mas[7];
 S[1]=number.dword;
 Gost_init(&S[0]);
 SendAnswerR(answerC);
}

/*****************************************************************************/

/**
 * Calculated CRC checksum 
 *
 * @param	*ZAdr	a pointer to the data 
 * @param	*DoAdr	a pointer to the CRC checksum returned
 * @param	lle	amount byte need for calculate CRC checksum
 **/
void crc2(unsigned char *ZAdr,unsigned int *DoAdr,unsigned int lle){
 unsigned char i;
 unsigned int C,NrBat;
 #asm("wdr")
 for(NrBat=0;NrBat!=lle;NrBat++,ZAdr++)
 {          
  C=((*DoAdr>>8)^*ZAdr)<<8;
  for(i=0;i!=8;i++)
   if (C&0x8000)
    C=(C<<1)^0x1021;
   else C=C<<1;
    *DoAdr=C^(*DoAdr<<8);
 }        
}   

void ASCIIToHex(char *mas,unsigned int num)
{
 unsigned char a,b;
 unsigned int i,j;
 #asm("wdr")
 for(i=0,j=0;j!=num;i+=2,j++)
 {             
    a=mas[i]-0x30;
    if(a>9) a-=7;
    a<<=4;
    b=mas[i+1]-0x30;
    if(b>9)b-=7;
    mas[j]=a|b;
 }
}