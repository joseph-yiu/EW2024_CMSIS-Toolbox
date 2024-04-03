#if defined (CMSDK_CM7_SP)
  #include "CMSDK_CM7_SP.h"
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM7_DP)
  #include "CMSDK_CM7_DP.h"
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM7)
  #include "CMSDK_CM7.h"
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM4_FP)
  #include "CMSDK_CM4_FP.h"
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM4)
  #include "CMSDK_CM4.h"
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM3)
  #include "CMSDK_CM3.h"
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM0)
  #include "CMSDK_CM0.h"
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM0plus)
  #include "CMSDK_CM0plus.h"
  #define CPU_CLK_SPEED 25000000
#elif defined (IOTKit_CM23)
  #include "IOTKit_CM23.h"
  #define CPU_CLK_SPEED 20000000
#elif defined (IOTKit_CM33)
  #include "IOTKit_CM33.h"
  #define CPU_CLK_SPEED 20000000
#elif defined (IOTKit_CM33_FP)
  #include "IOTKit_CM33_FP.h"
  #define CPU_CLK_SPEED 20000000
#else
  #error device not defined
#endif

#include "stdio.h"

void timer_start(void);
void SysTick_Handler(void);
void get_tick_count(uint32_t *tp);
void HardFault_Handler(void);
#if defined ( __ICCARM__ )
#else
void _exit(void);
#endif

volatile uint32_t tick_count=0;

/*------------------------------*/
void timer_start(void)
{
  uint32_t return_code;
	
  SCB_EnableDCache();
  SCB_EnableICache();
	
  return_code = SysTick_Config(SystemCoreClock / 1000); // System running at 32MHz
  if (return_code!= 0) {
    __BKPT(0); // halt 
    while(1);
  }
  return;  
  }
/*------------------------------*/
void SysTick_Handler(void)
{
  tick_count++;
}
/*------------------------------*/
void get_tick_count(uint32_t *tp)
{
  *tp = tick_count;
  return;
}	
/*------------------------------*/
void HardFault_Handler(void)
{
/*  __asm("  .global __use_no_semihosting\n\t"); */
  __BKPT(0);
}
/*------------------------------*/
#if defined ( __ICCARM__ )
#else
void _exit(void)
{
  //printf("END: time=%d secs\n", tick_count/100);
  __BKPT(0);
}
#endif

/*------------------------------*/
#if defined (__ARMCC_VERSION)
#ifdef __MICROLIB
#else

/* Reference:                                                          */
/* https://mklimenko.github.io/english/2018/11/02/disable-semihosting/ */

#if __ARMCC_VERSION >= 6000000
    __asm(".global __use_no_semihosting");
#elif __ARMCC_VERSION >= 5000000
    #pragma import(__use_no_semihosting)
#else
    #error Unsupported compiler
#endif

#include <rt_sys.h>
#include <rt_misc.h>
#include <time.h>

void _sys_exit(int return_code) {
    while (1);
}

void _ttywrch(int ch){
}

char *_sys_command_string(char *cmd, int len){
    return NULL;
}

#endif
#endif  
