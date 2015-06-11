#include "LPC13Uxx.h"
#include <nvic.h>
#include <sys/clock.h>
#include <sys/cc.h>
#include <sys/etimer.h>

static volatile clock_time_t current_clock = 0;
static volatile unsigned long current_seconds = 0;
static unsigned int second_countdown = CLOCK_SECOND;

void
SysTick_handler(void) __attribute__ ((interrupt));

void
SysTick_handler(void)
{
  (void)SysTick->CTRL;
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
  NVIC_SET_SYSTICK_PRI(8);
  SysTick->LOAD = SystemCoreClock/8/CLOCK_SECOND;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;
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
void timer16DelayUSecs(uint8_t timer, uint16_t delayInUSecs)
{
  if (timer == 0)
  {
    LPC_CT16B0->TCR  = 0x02;            /* Reset the timer */
    LPC_CT16B0->PR   = SystemCoreClock / 1000000 - 1;            /* Set prescaler: TC is incremented every microsecond */
    LPC_CT16B0->PWMC = 0x00;            /* Disable PWM mode */
    LPC_CT16B0->MR0  = delayInUSecs;
    LPC_CT16B0->IR   = 0xff;            /* Reset all interrrupts */
    LPC_CT16B0->MCR  = 0x04;            /* Stop the timer on match */
    LPC_CT16B0->TCR  = 0x01;            /* Start timer */

    /* Wait until delay time has elapsed */
    while (LPC_CT16B0->TCR & 0x01);
  }
  else if (timer == 1)
  {
    LPC_CT16B1->TCR  = 0x02;            /* Reset the timer */
    LPC_CT16B1->PR   = SystemCoreClock / 1000000 - 1;;            /* Set prescaler: TC is incremented every microsecond */
    LPC_CT16B1->PWMC = 0x00;            /* Disable PWM mode */
    LPC_CT16B1->MR0  = delayInUSecs;
    LPC_CT16B1->IR   = 0xff;            /* Reset all interrrupts */
    LPC_CT16B1->MCR  = 0x04;            /* Stop the timer on match */
    LPC_CT16B1->TCR  = 0x01;            /* Start timer */

    /* Wait until delay time has elapsed */
    while (LPC_CT16B1->TCR & 0x01);
  }
  return;
}


void
clock_delay_usec(uint16_t dt)
{
    timer16DelayUSecs(0, dt);
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

#if 0
/* The inner loop takes 4 cycles. The outer 5+SPIN_COUNT*4. */

#define SPIN_TIME 2 /* us */
#define SPIN_COUNT (((MCK*SPIN_TIME/1000000)-5)/4)

#ifndef __MAKING_DEPS__

void
clock_delay(unsigned int t)
{
#ifdef __THUMBEL__ 
  asm volatile("1: mov r1,%2\n2:\tsub r1,#1\n\tbne 2b\n\tsub %0,#1\n\tbne 1b\n":"=l"(t):"0"(t),"l"(SPIN_COUNT));
#else
#error Must be compiled in thumb mode
#endif
}
#endif
#endif /* __MAKING_DEPS__ */
unsigned long
clock_seconds(void)
{
  return current_seconds;
}
