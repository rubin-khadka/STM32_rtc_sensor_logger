/**
  * @file    temp_adc.c
  * @brief   Temperature ADC module - Register level implementation
  * @author  Rubin Khadka
  */
	
#include "temp_adc.h"

/* Initialize ADC1 Channel 0 for temperature measurement */
void temp_adc_init(void)
{
	// Enable ADC1 clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	// Power on ADC
	ADC1->CR2 |= ADC_CR2_ADON;
	
	// Configure Sampling time for Channel 0
	ADC1->SMPR2 &= ~(0x07 << 0);		// Clear existing sampling cycle
	ADC1->SMPR2 |= (TEMP_ADC_SAMPLING_TIME << 0);		// Set sampling cycle 28.5 
	
	// Configure conversion sequence 
	ADC1->SQR1 &= ~(0x0F << 20);   	// 1 conversion in sequence
	ADC1->SQR3 = TEMP_ADC_CHANNEL;  // SQ1[4:0] = Channel 0
	
	// ADC calibration 
	ADC1->CR2 |= ADC_CR2_RSTCAL;
	while (ADC1->CR2 & ADC_CR2_RSTCAL);
	
	ADC1->CR2 |= ADC_CR2_CAL;
	while (ADC1->CR2 & ADC_CR2_CAL);
	
	// Final configuration
	ADC1->CR2 &= ~ADC_CR2_CONT;  // Single conversion mode
	ADC1->CR2 &= ~ADC_CR2_ALIGN; // Right alignment
	
	// Enable ADC interrupt in NVIC
	NVIC_EnableIRQ(ADC1_2_IRQn);   
		
	// Brief stabilization delay
	for (volatile uint32_t i = 0; i < 100000; i++);  // Approx 1ms delay
}