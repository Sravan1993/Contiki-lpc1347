/**
 * \file
 *         Header file for the LPC1347-specific rtimer code
 * \author
 *         Christian Taedcke <hacking@taedcke.com>
 */
/**
 * \addtogroup lpc1347
 * @{
 *
 * \defgroup lpc1347-rtimer lpc1347 rtimer
 *
 * Implementation of the rtimer module for the lpc1347
 *
 * Use the Repetitive Interrupt Timer (RI-Timer) since it is always running.
 * It is a 48 bit timer running from the main clock.
 * The timer is configured so that it only uses 32 bit. Otherwise the following
 * lines in contiki-conf.h must be changed to use 64 bit types:
 *
 * typedef uint32_t rtimer_clock_t;
 * #define RTIMER_CLOCK_LT(a,b)     ((int32_t)((a)-(b)) < 0)
 *
 * At 32bit the maximum interval is 2^32 / CLK. At 72MHz it is about 59 seconds.
 */
#ifndef __RTIMER_ARCH_H__
#define __RTIMER_ARCH_H__

#include "sys/rtimer.h"
#include "system_LPC13Uxx.h"

/** \todo ctae find a better way, value is in __SYS_PLLCLKOUT in system_LPC13Uxx.h */
#define RTIMER_ARCH_SECOND (72000000UL)

/** \sa RTIMER_NOW() */
rtimer_clock_t rtimer_arch_now(void);

#endif /* __RTIMER_ARCH_H__ */

/**
 * @}
 */
