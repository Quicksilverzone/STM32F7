/*
This Code is Base project for STM32F767ZI for understanding basics of register based programming.


2019
Written by S.Emre KASAP 
e-mail: sevketemrekasap@gmail.com

16 Mhz HSI is used for very simple project like this but you can apply PLL settings for full 216 Mhz clock speed.

*/

#include "stm32f7xx.h"                  // Device header

int adcValue;

//------------Function prototypes--------------//

void ADC_Init(void);
int ADC_Read(void);
void Delay(__IO uint32_t nCount);


int main(void)
{

//------------System Config---------------------//

	
	SystemCoreClockUpdate();

	ADC_Init();
	
//----------------------------------------------//	
	
		
	
	while(1)
	{	
					
	while(!(ADC1->SR & 2)){}         // Wait for end of conversion
	adcValue = ADC1->DR;             // Store ADC data
  Delay(8000000);                  // Wait a moment 
		
	}	

}


void ADC_Init(void)   //  Setting GPIOA_PIN_3 as a analog input ADC1_IN3
{
		

	RCC->AHB1ENR = 0x1;    																						// Enable clock for GPIOA pins
	
	RCC->APB2ENR = 0x100;      																				// Enable ADC1 clock

	
	GPIOA->MODER  |= GPIO_MODER_MODER3_1 | GPIO_MODER_MODER3_0;       // Set pin 1 as analog mode
	
	GPIOA->OSPEEDR = 0x8;																			        // Set pin 1 High speed
		
	
	ADC->CCR = 0x00020000;                  													// ADC prescaler /6
	
	ADC1->CR1 = ADC_CR1_EOCIE;        		 														// Enable end of the conversion interrupt
	
                      
	ADC1->SMPR2 = 0x00000E00;               												 	// Set 480 cycle for SMP3 
	
	ADC1->SQR3 = 0x3;                      													  // Set 3th channel for sequance 1  
	
  ADC1->CR2 |= 0x3; 									  												    // Set ADON and CONT bits to enable adc with continious mode 
	
	ADC1->CR2 |= 0x40000000;               													  // Start ADC coversion
	
}


void Delay( uint32_t nCount)
{
	
	while(nCount--);
	
}

