#include "LPC13Uxx.h"
#include <stdio.h>
#include "dev/watchdog.h"

void
watchdog_init(void)
{
    /* Enable AHB clock to the WWDT domain. */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 15);

    /* Enable the WWDT clock source Watchdog Oscillator*/
    LPC_SYSCON->PDRUNCFG &= ~(1 << 6);

    /* Set watchdog oscillator frequency to */
    /* Fclkana = 1.4MHz, DIVSEL = 0 -> wdt_osc_clk = 700kHz*/
    LPC_SYSCON->WDTOSCCTRL = (3 << 5);

    /* Enable Lock bit and set clock source to watchtdog oscillator */
    LPC_WWDT->CLKSEL = 0; /* clear to ensure that the LOCK bit is zero */
    LPC_WWDT->CLKSEL = 1 | (1 << 31);

    /* Set reset value of watchdog timer. Results in T_WDCLK * 4 * (TC + 1) */
    /* About two seconds watchdog timeout */
    LPC_WWDT->TC = 350000;

    /** Enable Watchdog and perform reset on timeout  and enable LOCK bit to prevent powering down watchdog clock. */
    LPC_WWDT->MOD = 3 | (1 << 5);

}

void
watchdog_start(void)
{
    watchdog_periodic();
}

void watchdog_periodic(void)
{
    uint32_t primask = __get_PRIMASK();
    __set_PRIMASK(1);
    LPC_WWDT->FEED = 0xAA;
    LPC_WWDT->FEED = 0x55;
    __set_PRIMASK(primask);
}

void watchdog_stop(void)
{
    //not possible
}

void watchdog_reboot(void)
{
    //immediate reboot -> only half feed
    //or without int while(1)
    NVIC_SystemReset();
}
