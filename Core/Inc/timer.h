/* Timer header file */

#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Private Include definition */
#include "main.h"

extern volatile uint8_t lcd_busy;

/* Function Prototypes */
void timer2_init(void);
void timer2_lcd_delay_ms(uint32_t ms_delay);
void TIM2_UP_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_H */
