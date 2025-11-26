/**
  * @file    temp_adc.h
  * @brief   Temperature ADC module for STM32F103 using LM35 sensor
  * @author  Rubin Khadka
  */
	
#ifndef TEMP_ADC_H
#define TEMP_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Include Definitions */
#include "timer.h"

/* Defines */
#define TEMP_ADC_CHANNEL 				0x00		// ADC Channel 0 (PA0)
#define TEMP_ADC_SAMPLING_TIME 	0x03		// 28.5 sampling cycle

// Sampling Time Values:
#define ADC_SAMPLE_1_5_CYCLES    0x00
#define ADC_SAMPLE_7_5_CYCLES    0x01  
#define ADC_SAMPLE_13_5_CYCLES   0x02
#define ADC_SAMPLE_28_5_CYCLES   0x03 
#define ADC_SAMPLE_41_5_CYCLES   0x04
#define ADC_SAMPLE_55_5_CYCLES   0x05
#define ADC_SAMPLE_71_5_CYCLES   0x06
#define ADC_SAMPLE_239_5_CYCLES  0x07


/* Function Prototypes */
void temp_adc_init(void);

#ifdef __cplusplus
}
#endif

#endif /* TEMP_ADC_H */