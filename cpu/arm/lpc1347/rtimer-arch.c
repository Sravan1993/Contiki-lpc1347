#include "rtimer-arch.h"
#include "energest.h"
#include "LPC13Uxx.h"
#define DEBUG 1
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

//todo ctae doc and check

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialize the RI timer register.
 *
 *        The RI Timer starts ticking automatically as soon as the device
 *        turns on. We don't need to turn on interrupts before the first call
 *        to rtimer_arch_schedule()
 */
void
rtimer_arch_init(void)
{
    //set counter value to 0 ao successful comaprison
    LPC_RITIMER->CTRL |= (1 << 1);

    //ignore the bits 33 to 48 -> only count 32 bit
    LPC_RITIMER->MASK_H = 0x0000FFFF;

}
/*---------------------------------------------------------------------------*/
/**
 * \brief Schedules an rtimer task to be triggered at time t
 * \param t The time when the task will need executed. This is an absolute
 *          time, in other words the task will be executed AT time \e t,
 *          not IN \e t ticks
 */
void
rtimer_arch_schedule(rtimer_clock_t t)
{
  rtimer_clock_t now;
  uint32_t primask = __get_PRIMASK();

  __set_PRIMASK(1);

  now = RTIMER_NOW();

  /*
   * New value must be a few ticks in the future.
   */
  if((int32_t)(t - now) < 20) {
    t = now + 20;
  }

  LPC_RITIMER->COMPVAL = t;

   __set_PRIMASK(primask);

  NVIC_EnableIRQ(RIT_IRQn);
}
/*---------------------------------------------------------------------------*/
/**
 * \brief The rtimer ISR
 *
 *        Interrupts are only turned on when we have an rtimer task to schedule
 *        Once the interrupt fires, the task is called and then interrupts no
 *        longer get acknowledged until the next task needs scheduled.
 */
__attribute__ ((section(".after_vectors")))
void
OSTIMER_IRQHandler(void)
{
  ENERGEST_ON(ENERGEST_TYPE_IRQ);

  //clear RIT interrupt
  LPC_RITIMER->CTRL |= 1;
  NVIC_DisableIRQ(RIT_IRQn);

  rtimer_run_next();

  ENERGEST_OFF(ENERGEST_TYPE_IRQ);
}
/*---------------------------------------------------------------------------*/
rtimer_clock_t
rtimer_arch_now(void)
{
    return LPC_RITIMER->COUNTER;
}
