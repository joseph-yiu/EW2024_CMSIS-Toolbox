#if defined (CMSDK_CM7_SP)
  #include "CMSDK_CM7_SP.h"
#elif defined (CMSDK_CM7_DP)
  #include "CMSDK_CM7_DP.h"
#elif defined (CMSDK_CM7)
  #include "CMSDK_CM7.h"
#elif defined (CMSDK_CM4_FP)
  #include "CMSDK_CM4_FP.h"
#elif defined (CMSDK_CM4)
  #include "CMSDK_CM4.h"
#elif defined (CMSDK_CM3)
  #include "CMSDK_CM3.h"
#elif defined (CMSDK_CM0)
  #include "CMSDK_CM0.h"
#elif defined (CMSDK_CM0plus)
  #include "CMSDK_CM0plus.h"
#elif defined (IOTKit_CM23)
  #include "IOTKit_CM23.h"
#elif defined (IOTKit_CM33)
  #include "IOTKit_CM33.h"
#elif defined (IOTKit_CM33_FP)
  #include "IOTKit_CM33_FP.h"
#elif defined (SSE300_CM55)
  #include "SSE300MPS3.h"
  #include "cmsis_driver_config.h"  
#elif defined (SSE310_CM85)
  #include "SSE310MPS3.h"
  #include "cmsis_driver_config.h"  
#else
  #error device not defined
#endif

#include "RTE_Components.h"

/*---------------------------------------- */
// Function prototypes
void cache_init(void);

/*---------------------------------------- */
/* Enable caches if avalable */
void cache_init(void)
{
#if (defined (SSE310_CM85)||(SSE300_CM55)||(CMSDK_CM7)||(CMSDK_CM7_SP)||(CMSDK_CM7_DP))
#if __ICACHE_PRESENT
  SCB_EnableICache();
#endif
#if __DCACHE_PRESENT
  SCB_EnableDCache();
#endif
#endif
  return;
}  
