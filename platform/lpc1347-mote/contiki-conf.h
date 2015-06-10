/*
 * Copyright (c) 2005, Swedish Institute of Computer Science
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

#ifndef CONTIKI_CONF_H_
#define CONTIKI_CONF_H_


#ifndef PLATFORM_CONF_H_
#define PLATFORM_CONF_H_

#include "LPC13Uxx.h"
#include <stdint.h>

#define CCIF
#define CLIF

/*
 * Definitions below are dictated by the hardware and not really
 * changeable!
 */

#define PLATFORM_HAS_LEDS   1

// Types for clocks and uip_stats
typedef unsigned long clock_time_t;
//typedef uint64_t clock_time_t;

typedef uint8_t   u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef int32_t s32_t;
typedef unsigned short uip_stats_t;

#define ENERGEST_TOTAL_IS_RTIMER_T
typedef uint64_t rtimer_clock_t;
#define RTIMER_CLOCK_LT(a,b)     ((signed short)((a)-(b)) < 0)

// the low-level radio driver
#define NETSTACK_CONF_RADIO   cc2520_driver

// The rate of the system clock (Can be changed here)
#define CLOCK_CONF_SECOND 10000

/*
 * SPI Driver
 */
//void cc2520_arch_fifop_int_init(void);
//void cc2520_arch_fifop_int_enable(void);
//void cc2520_arch_fifop_int_disable(void);
 
#
/* include the project config */
/* PROJECT_CONF_H might be defined in the project Makefile */
#ifdef PROJECT_CONF_H
#include PROJECT_CONF_H
#endif /* PROJECT_CONF_H */

#endif /* CONTIKI_CONF_H_ */
#endif /* PLATFORM_CONF_H_ */
