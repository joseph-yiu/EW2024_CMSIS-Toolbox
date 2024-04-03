#include <stdio.h>
#include "SSE300MPS3.h"
#include "cmsis_driver_config.h"

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
  return;
}
/*-------------------------*/
void led_set(uint32_t val)
{
  struct arm_mps3_io_dev_t* arm_mps3_io_dev=&MPS3_IO_DEV_S;
  arm_mps3_io_write_leds(arm_mps3_io_dev, ARM_MPS3_IO_ACCESS_PIN, 0, val);
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
