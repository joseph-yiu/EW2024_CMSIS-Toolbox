#if defined (CMSDK_CM7_SP)
  #include "CMSDK_CM7_SP.h"
  //#define USE_DWT_CYCLE_COUNTER
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM7_DP)
  #include "CMSDK_CM7_DP.h"
  //#define USE_DWT_CYCLE_COUNTER
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM7)
  #include "CMSDK_CM7.h"
  //#define USE_DWT_CYCLE_COUNTER
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM4_FP)
  #include "CMSDK_CM4_FP.h"
  //#define USE_DWT_CYCLE_COUNTER
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM4)
  #include "CMSDK_CM4.h"
  //#define USE_DWT_CYCLE_COUNTER
  #define CPU_CLK_SPEED 25000000
#elif defined (CMSDK_CM3)
  #include "CMSDK_CM3.h"
  //#define USE_DWT_CYCLE_COUNTER
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
  #define USE_DWT_CYCLE_COUNTER
  #define CPU_CLK_SPEED 20000000
#elif defined (IOTKit_CM33_FP)
  #include "IOTKit_CM33_FP.h"
  #define USE_DWT_CYCLE_COUNTER
  #define CPU_CLK_SPEED 20000000
#else
  #error device not defined
#endif

#define TIMER_CLK_SPEED 25000000

#ifdef USE_DWT_CYCLE_COUNTER
/*------------------------------------------------------------------------------
  Initialize DWT Cycle counter
*------------------------------------------------------------------------------*/
void timer_config(void) {
#if (defined (__CM_CMSIS_VERSION_MAIN) && (__CM_CMSIS_VERSION_MAIN>5))
  DCB->DEMCR  |= DCB_DEMCR_TRCENA_Msk; // Enable DWT
#else
  CoreDebug->DEMCR  |= CoreDebug_DEMCR_TRCENA_Msk; // Enable DWT
#endif
  DWT->CYCCNT  = 0;
  DWT->CTRL   |= DWT_CTRL_CYCCNTENA_Msk;  // Enable Cycle Counter  
  return;  
}


unsigned long get_100Hz_value(void)
{
  return (DWT->CYCCNT/(CPU_CLK_SPEED/100)); // 100 Hz value
}

#else

#if (defined (IOTKit_CM23) || (IOTKit_CM33) || (IOTKit_CM33_VHT) || (IOTKit_CM33_FP) || (IOTKit_CM33_FP_VHT))

void timer_config(void) {
  IOTKIT_SECURE_TIMER0->CTRL = 0;
  IOTKIT_SECURE_TIMER0->VALUE = 0;
  IOTKIT_SECURE_TIMER0->RELOAD = 0xFFFFFFFFUL;
  IOTKIT_SECURE_TIMER0->CTRL = 1; // Enable with internal clock
  return;
}

unsigned long get_100Hz_value(void)
{
  return ((0xFFFFFFFFUL-IOTKIT_SECURE_TIMER0->VALUE)/(TIMER_CLK_SPEED/100));
}

#else

void timer_config(void) {
  CMSDK_TIMER0->CTRL = 0;
  CMSDK_TIMER0->VALUE = 0;
  CMSDK_TIMER0->RELOAD = 0xFFFFFFFFUL;
  CMSDK_TIMER0->CTRL = 1; // Enable with internal clock
  return;
}

unsigned long get_100Hz_value(void)
{
  return ((0xFFFFFFFFUL-CMSDK_TIMER0->VALUE)/(TIMER_CLK_SPEED/100));
}

#endif

#endif


