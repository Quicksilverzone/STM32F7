/*
This Code is Base project for STM32F767ZI for understanding basics of register based programming.


2019
Written by S.Emre KASAP 
e-mail: sevketemrekasap@gmail.com

16 Mhz HSI is used for very simple project like this but you can apply PLL settings for full 216 Mhz clock speed.

*/

#include "stm32f7xx.h"    
// Device header

//------------Function Prototypes-----------------//
void SystemClock_Init(void);
void Delay(__IO uint32_t nCount);
void UART4_Init(void);
void UART4_write(char* str);



int main(void)
{

//------------System Config---------------------//

	
	SystemCoreClockUpdate();
	UART4_Init();
	

	
	
	while(1)
	{	
		
		
	UART4_write("Hello STM32\r\n");	            // Send data from UART4 port 

		
	}	
	

}

void UART4_Init(void)
{
	
	uint32_t BaudRate = 9600;                   // Baudrate
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;        // Enable GPIOA Clock
	
	GPIOA->MODER |= 0x2;                        // Setting Alternata function for pin PA0 for TX
	GPIOA->MODER |= 0x8;                        // Setting Alternate function for pin PA1 fo RX
	
	
	GPIOA->AFR[0] = 0x8;       									// Setting alternate function as  UART4_TX (AF8)
	GPIOA->AFR[0] |= 0x80;     									// Setting alternat function as UART4_RX  (AF8)
	
	
	
	RCC->APB1ENR |= RCC_APB1ENR_UART4EN; 				// Enable UART4 Clock 
	
	
	UART4->BRR = SystemCoreClock/BaudRate;      // Setting Baudrate
	
	UART4->CR1 |= USART_CR1_TE;                 // UART Transmit enable
	UART4->CR1 |= USART_CR1_RE;                 // UART Receive enable
	UART4->CR1 |= USART_CR1_UE;                 // UART Function enable
		
	
}


void UART4_write(char* str)                   // Basic C programmig to print string
{
	
char*p=str;
int i = 0;
	
		while(*p)
		{
			Repeat:
			if(UART4->ISR & USART_ISR_TXE)            
		{	
						UART4->TDR = str[i];	
			p++;
			i++;			
		}
			else goto Repeat;		
		}		
}



void Delay( uint32_t nCount)                 // Delay Function
{
	
	while(nCount--);
	
}







