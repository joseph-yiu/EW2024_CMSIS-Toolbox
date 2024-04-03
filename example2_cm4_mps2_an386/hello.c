#include <stdio.h>
#ifdef CMSDK_CM4_FP
#include "CMSDK_CM4_FP.h"
#include "Board_LED.h"  /* Requires LED component and Keil Middleware Pack*/
#endif

void led_init(void);
void led_set(uint32_t val);
void SysTick_Handler(void);
extern int stdio_init (void);

int main(void)
{
  uint32_t ret_status;
  led_init();
  stdio_init();                         // Initialize stdio
  printf("Hello world\n");
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
#ifdef CMSDK_CM4_FP
  LED_Initialize();
#endif
  return;
}
/*-------------------------*/
void led_set(uint32_t val)
{
#ifdef CMSDK_CM4_FP
  LED_SetOut(val);
#endif
  return;
}
/*-------------------------*/
/* Execute at 10Hz */
void SysTick_Handler(void)
{
  static uint32_t curr_state=0; /* Current state 0 or 1 */
  static int32_t tick_count=0;
	
  curr_state ^=  1L;   /* Toggle */
  led_set(curr_state); /* Output */
  printf("%d\n", tick_count);
  tick_count++;
  return;
}
