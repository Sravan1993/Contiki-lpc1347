/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-13
 * (c) NXP Semiconductors 2013-2015
 * Generated linker script file for LPC1347
 * Created from generic_c.ld (7.7.2 ())
 * By LPCXpresso v7.7.2 [Build 379] [2015-03-31]  on Fri Jun 12 20:16:36 IST 2015
 */


INCLUDE "mypjt_Debug_lib.ld"

MEMORY
{
  /* Define each memory region */
  MFlash64 (rx) : ORIGIN = 0x0, LENGTH = 0x10000 /* 64K bytes */
  RamLoc8 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x2000 /* 8K bytes */
  RamUsb2 (rwx) : ORIGIN = 0x20004000, LENGTH = 0x800 /* 2K bytes */
  RamPeriph2 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x800 /* 2K bytes */


}
  /* Define a symbol for the top of each memory region */
  __top_MFlash64 = 0x0 + 0x10000;
  __top_RamLoc8 = 0x10000000 + 0x2000;
  __top_RamUsb2 = 0x20004000 + 0x800;
  __top_RamPeriph2 = 0x20000000 + 0x800;


ENTRY(ResetISR)

SECTIONS
{

    /* MAIN TEXT SECTION */    
    .text : ALIGN(4)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))
        
        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        LONG(LOADADDR(.data_RAM3));
        LONG(    ADDR(.data_RAM3));
        LONG(  SIZEOF(.data_RAM3));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        LONG(    ADDR(.bss_RAM3));
        LONG(  SIZEOF(.bss_RAM3));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */
        

        *(.after_vectors*)
        
    } >MFlash64
    
    .text : ALIGN(4)    
    {
         *(.text*)
        *(.rodata .rodata.* .constdata .constdata.*)
        . = ALIGN(4);
        
    } > MFlash64

    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this. 
     */
    .ARM.extab : ALIGN(4)
    {
    	*(.ARM.extab* .gnu.linkonce.armextab.*)
    } > MFlash64
    __exidx_start = .;
    
    .ARM.exidx : ALIGN(4)
    {
    	*(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > MFlash64
    __exidx_end = .;
    
    _etext = .;
        
    
    /* DATA section for RamUsb2 */
    .data_RAM2 : ALIGN(4)
    {
       FILL(0xff)
       PROVIDE(__start_data_RAM2 = .) ;
       *(.ramfunc.$RAM2)
       *(.ramfunc.$RamUsb2)
    	*(.data.$RAM2*)
    	*(.data.$RamUsb2*)
       . = ALIGN(4) ;
       PROVIDE(__end_data_RAM2 = .) ;
    } > RamUsb2 AT>MFlash64
    
    /* DATA section for RamPeriph2 */
    .data_RAM3 : ALIGN(4)
    {
       FILL(0xff)
       PROVIDE(__start_data_RAM3 = .) ;
       *(.ramfunc.$RAM3)
       *(.ramfunc.$RamPeriph2)
    	*(.data.$RAM3*)
    	*(.data.$RamPeriph2*)
       . = ALIGN(4) ;
       PROVIDE(__end_data_RAM3 = .) ;
    } > RamPeriph2 AT>MFlash64
    
    /* MAIN DATA SECTION */
    

    .uninit_RESERVED : ALIGN(4)
    {
        KEEP(*(.bss.$RESERVED*))
        . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > RamLoc8

	
	/* Main DATA section (RamLoc8) */
	.data : ALIGN(4)
	{
	   FILL(0xff)
	   _data = . ;
	   *(vtable)
	   *(.ramfunc*)
	   *(.data*)
	   . = ALIGN(4) ;
	   _edata = . ;
	} > RamLoc8 AT>MFlash64

    /* BSS section for RamUsb2 */
    .bss_RAM2 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
    	*(.bss.$RAM2*)
    	*(.bss.$RamUsb2*)
       . = ALIGN(4) ;
       PROVIDE(__end_bss_RAM2 = .) ;
    } > RamUsb2
    /* BSS section for RamPeriph2 */
    .bss_RAM3 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM3 = .) ;
    	*(.bss.$RAM3*)
    	*(.bss.$RamPeriph2*)
       . = ALIGN(4) ;
       PROVIDE(__end_bss_RAM3 = .) ;
    } > RamPeriph2

    /* MAIN BSS SECTION */
    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(end = .);
    } > RamLoc8
        
    /* NOINIT section for RamUsb2 */
    .noinit_RAM2 (NOLOAD) : ALIGN(4)
    {
    	*(.noinit.$RAM2*)
    	*(.noinit.$RamUsb2*)
       . = ALIGN(4) ;
    } > RamUsb2 
    /* NOINIT section for RamPeriph2 */
    .noinit_RAM3 (NOLOAD) : ALIGN(4)
    {
    	*(.noinit.$RAM3*)
    	*(.noinit.$RamPeriph2*)
       . = ALIGN(4) ;
    } > RamPeriph2 
    
    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(4)
    {
        _noinit = .;
        *(.noinit*) 
         . = ALIGN(4) ;
        _end_noinit = .;
    } > RamLoc8
    
    PROVIDE(_pvHeapStart = DEFINED(__user_heap_base) ? __user_heap_base : .);
    PROVIDE(_vStackTop = DEFINED(__user_stack_top) ? __user_stack_top : __top_RamLoc8 - 0);
}
