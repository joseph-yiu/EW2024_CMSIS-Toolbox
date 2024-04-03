#ifdef CMSDK_CM4_FP
#include "CMSDK_CM4_FP.h"
#include "Board_LED.h"  /* Requires LED component and Keil Middleware Pack*/
#endif

#ifdef CMSDK_CM4
#include "CMSDK_CM4.h"
#include "Board_LED.h"  /* Requires LED component and Keil Middleware Pack*/
#endif

void led_init(void);
void led_set(int val);
void SysTick_Handler(void);

int main(void)
{
  uint32_t ret_status;
  led_init();
  ret_status = SysTick_Config(SystemCoreClock/10);
  if (ret_status != 0) { /* 0=success, 1=error */
    while(1);
    }
  while(1) {
    __WFI();
    }
}

/*-------------------------*/
void led_init(void)
{
#if (defined (CMSDK_CM4_FP)||(CMSDK_CM4))
  LED_Initialize();
#endif
  return;
}
/*-------------------------*/
void led_set(int val)
{
#if (defined (CMSDK_CM4_FP)||(CMSDK_CM4))
  LED_SetOut(val);
#endif
  return;
}
/*-------------------------*/
/* Execute at 10Hz */
void SysTick_Handler(void)
{
  static int curr_state=0; /* Current state 0 or 1 */
  
  curr_state ^=  1L;   /* Toggle */
  led_set(curr_state); /* Output */
  return;
}
