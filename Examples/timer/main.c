#include "stm32f10x.h"


int main()
{
	  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Configure PA0 as Alternate Function Push-Pull (TIM2 CH1)
    GPIOA->CRL &= ~GPIO_CRL_CNF0;       // Clear CNF0[1:0]
    GPIOA->CRL |= GPIO_CRL_CNF0_1;     // Set CNF0 to Alternate Function Push-Pull (10)
    GPIOA->CRL |= GPIO_CRL_MODE0_1; 	
	
	
	
	  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Set prescaler to 7200-1 (10 kHz timer clock)
    TIM2->PSC = 7200 - 1;
 
    // Set auto-reload value to 1000-1 (100 ms period, 10 Hz toggle frequency)
    TIM2->ARR = 8000 - 1;
	
    // Set compare value for toggle
		TIM2->CCR1 = 1;


    // Configure Output Compare for Channel 1 (Toggle mode)
    TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;       // Clear output compare mode bits
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1; // Set OC1M to Toggle (011)
		
		// Configure Output polarity
		TIM2->CCER |= TIM_CCER_CC1P;
		
		
		// Disable preload for simplicity
    TIM2->CCMR1 &= ~TIM_CCMR1_OC1PE;      



    // Enable output for Channel 1

    TIM2->CCER |= TIM_CCER_CC1E;

    // Enable the counter
    TIM2->CR1 |= TIM_CR1_CEN;
	
	
	
}
