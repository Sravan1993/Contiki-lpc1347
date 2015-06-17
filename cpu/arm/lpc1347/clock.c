#include <LPC13Uxx.h>
#include <sys/clock.h>
#include <sys/cc.h>
#include <sys/etimer.h>

#include "timer16.h"

static volatile clock_time_t current_clock = 0;
static volatile unsigned long current_seconds = 0;
static unsigned int second_countdown = CLOCK_SECOND;
static uint32_t interval;
extern volatile uint32_t timer16_0_counter[2];
#define TEST_TIMER_NUM		0

void
SysTick_Handler(void) __attribute__ ((interrupt));

void
SysTick_Handler(void)
{
   /* Clear the count flag */
   (void)SysTick->CTRL;

  //clear pending flag
  SCB->ICSR = SCB_ICSR_PENDSTCLR_Msk;
  current_clock++;
  if(etimer_pending() && etimer_next_expiration_time() <= current_clock) {
    etimer_request_poll();
    /* printf("%d,%d\n", clock_time(),etimer_next_expiration_time  	()); */

  }

  if (--second_countdown == 0) {
    current_seconds++;
    second_countdown = CLOCK_SECOND;
  }
}


void
clock_init()
{
    SysTick_Config(SystemCoreClock / CLOCK_SECOND);
    NVIC_SetPriority (SysTick_IRQn, 8);  /* set Priority for Systick Interrupt to 8 (high) */
    interval = SystemCoreClock/1000 - 1;
      if ( interval > 0xFFFF )
      {
    	interval = 0xFFFF;
       }
    /* Init timer for clock_delay_usec() */
      init_timer16(TEST_TIMER_NUM, interval);
      enable_timer16(TEST_TIMER_NUM);
}

clock_time_t
clock_time(void)
{
  return current_clock;
}


/**************************************************************************/
/*!
    @brief Causes a blocking delay on the specified 16-bit timer

    @param[in]  timer
                The 16-bit timer to use (must be 0 or 1)
    @param[in]  delayInUSecs
                The number of microseconds to wait
*/
/**************************************************************************/

/*
void timer16DelayUSecs(uint8_t timer, uint16_t delayInUSecs)
{
  if (timer == 0)
  {
    LPC_CT16B0->TCR  = 0x02;             Reset the timer
    LPC_CT16B0->PR   = SystemCoreClock / 1000000 - 1;             Set prescaler: TC is incremented every microsecond
    LPC_CT16B0->PWMC = 0x00;             Disable PWM mode
    LPC_CT16B0->MR0  = delayInUSecs;
    LPC_CT16B0->IR   = 0xff;             Reset all interrrupts
    LPC_CT16B0->MCR  = 0x04;             Stop the timer on match
    LPC_CT16B0->TCR  = 0x01;             Start timer

     Wait until delay time has elapsed
    while (LPC_CT16B0->TCR & 0x01);
  }
  else if (timer == 1)
  {
    LPC_CT16B1->TCR  = 0x02;             Reset the timer
    LPC_CT16B1->PR   = SystemCoreClock / 1000000 - 1;;             Set prescaler: TC is incremented every microsecond
    LPC_CT16B1->PWMC = 0x00;             Disable PWM mode
    LPC_CT16B1->MR0  = delayInUSecs;
    LPC_CT16B1->IR   = 0xff;             Reset all interrrupts
    LPC_CT16B1->MCR  = 0x04;             Stop the timer on match
    LPC_CT16B1->TCR  = 0x01;             Start timer

     Wait until delay time has elapsed
    while (LPC_CT16B1->TCR & 0x01);
  }
  return;
}
*/


void
clock_delay_usec(uint16_t dt)
{
//    timer16DelayUSecs(0, dt);
	if ((timer16_0_counter[0] > 0 && (timer16_0_counter[0] <= 400) ))
		return;
}

/*
 * Deprecated platform-specific routines.
 *
 */
void
clock_delay(unsigned int t)
{
    clock_delay_usec(t);
}

unsigned long
clock_seconds(void)
{
  return current_seconds;
}
