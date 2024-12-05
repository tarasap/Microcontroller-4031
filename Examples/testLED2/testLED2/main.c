#include "stm32f10x.h"


volatile uint32_t msTicks = 0; // Counter for milliseconds

// SysTick Initialization for 1ms interrupt
void SysTick_Init(void) {
    // SystemCoreClock is typically 72 MHz for STM32F103 by default
    uint32_t ticks = SystemCoreClock / 1000;

    SysTick->LOAD = ticks - 1;             
    SysTick->VAL = 0;                       
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE | 
                     SysTick_CTRL_TICKINT |   
                     SysTick_CTRL_ENABLE;    
}

void SysTick_Handler(void) {
    if (msTicks > 0) {
        msTicks--;
    }
}

void delay_ms(uint32_t ms) {
    msTicks = ms;  // Set delay counter
    while (msTicks > 0) {
        // Wait until msTicks reaches zero
        __WFI();   // Put CPU in sleep mode until next interrupt (optional)
    }
}


int main()
{
	
	
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
 AFIO->MAPR &= ~AFIO_MAPR_SWJ_CFG ;
 AFIO->MAPR |=  AFIO_MAPR_SWJ_CFG_1;


	SysTick_Init();
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ;
	GPIOC->CRH |= GPIO_CRH_MODE13 ;
	GPIOC->CRH &= ~GPIO_CRH_CNF13 ;

	
	while(1)
	{

		GPIOC->ODR |= GPIO_ODR_ODR13; //set
		
		
		//for(uint32_t i=0 ; i<5000 ;i++) //delay
		//for(uint32_t j=0 ; j<1000 ;j++);
		delay_ms(2000);
		
		GPIOC->ODR &= ~GPIO_ODR_ODR13; //reset
		
		
		//for(uint32_t i=0 ; i<2000 ;i++) //delay
		//	for(uint32_t j=0 ; j<1000 ;j++);
		delay_ms(3000);
 		
	}
	
}


