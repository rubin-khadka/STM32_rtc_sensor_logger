/* Timer source file */

#include "timer.h"

volatile uint8_t lcd_busy = 0;

void timer2_init(void)
{
	// Enable timer 2 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	// Define tick rate for timer 2
	TIM2->PSC = 639;
	TIM2->CNT = 0x00;
	
	// Update interrupt enabled
	TIM2->DIER |= TIM_DIER_UIE;
	
	// Clear any pending interrupt flag
	TIM2->SR &= ~TIM_SR_UIF;
	
	// Configure NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}

void timer2_lcd_delay_ms(uint32_t ms_delay)
{
	
	// Stop timer if it is running
	TIM2->CR1 &= ~TIM_CR1_CEN;
	
	// Clear any pending interrupt 
	TIM2->SR &= ~TIM_SR_UIF;
	
	// Set ARR for desired delay (10 microsecond base)
	uint32_t ticks = ms_delay * 10; // convert ms to ticks
	TIM2->ARR = ticks - 1;					// ARR = ticks - 1
	TIM2->CNT = 0;									// Reset counter
	
	// Start timer and set busy flag 
	lcd_busy = 1;
	TIM2->CR1 |= TIM_CR1_CEN;
	
}

void TIM2_UP_IRQHandler(void)
{
	
	// Check if the interrupt is caused by timer
	if(TIM2->SR & TIM_SR_UIF)
	{
		
		TIM2->SR &= ~TIM_SR_UIF;		// Clear interrupt flag
		TIM2->CR1 &= ~TIM_CR1_CEN;	//stop timer 
		
		lcd_busy = 0;
	}
}
