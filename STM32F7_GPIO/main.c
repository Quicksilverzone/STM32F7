/*
This Code is Base project for STM32F767ZI for understanding basics of register based programming.

2019
Written by S.Emre KASAP 
e-mail: sevketemrekasap@gmail.com

16 Mhz HSI is used for very simple project like this but you can apply PLL settings for full 216 Mhz clcok speed.

*/

#include "stm32f7xx.h"                  // Device header

//----------- Function Prototypes---------------//

void Delay(__IO uint32_t nCount);
void GPIO_Init(void);



int main(void)
{

//------------System Config---------------------//

	
	SystemCoreClockUpdate();
	GPIO_Init();
	
	
//----------------------------------------------//	
		
	
	while(1)
	{	
		
	// Pins are selected for Nucleo STM32F767ZI onboard leds you can add or remove according to your system.	
		
		
  GPIOB->BSRR = 0x40800001;     // Set High PB0 
  Delay(8000000);         			// Wait for nearly a second for 16 Mhz system clock
  GPIOB->BSRR = 0x40010080; 		// Set High PB7
  Delay(8000000);
	GPIOB->BSRR = 0x00814000; 		// Set High PB14 
  Delay(8000000);	
		
	}	
}



void GPIO_Init(void)
{
	
	RCC->AHB1ENR |= 0x00000002;    // AHB1 Bus clock 
		
	GPIOB->MODER |= 0x00000001;    // PB0 Pin seted as output
	GPIOB->MODER |= 0x00004000;    // PB7 Pin seted as output
	GPIOB->MODER |= 0x10000000;    // PB14 Pin seted as output
	
	GPIOB->OTYPER |= 0x00000000;   // pull-push 
		
	GPIOB->OSPEEDR |= 0x00000020;  // PB0 High speed 
	GPIOB->OSPEEDR |= 0x00008000;  // PB7 High speed 
	GPIOB->OSPEEDR |= 0x30000000;  // PB14 High speed
				
}


void Delay( uint32_t nCount)
{
	
	while(nCount--);
	
}
