#include "SSE300MPS3.h"
#include "RTE_Components.h"
#include "cmsis_driver_config.h"
/*---------------------------------------- */
// Function prototypes
void UART_Config(void);
int  UART_SendChar(uint32_t txchar);
char UART_ReceiveChar(void);
/* Porting layer for CMSIS-Compiler */
int stdio_init(void);
#ifdef RTE_CMSIS_Compiler_STDERR_Custom
int stderr_putchar(int ch);
#endif
#ifdef RTE_CMSIS_Compiler_STDOUT_Custom
int stdout_putchar(int ch);
#endif
#ifdef RTE_CMSIS_Compiler_STDIN_Custom
int stdin_getchar(void) ;
#endif
/*---------------------------------------- */
/*       UART control code       */
void UART_Config(void)
{
  struct uart_cmsdk_dev_t* arm_mps3_uart_dev=&UART0_CMSDK_DEV;
  uart_cmsdk_init(arm_mps3_uart_dev, 25000000);
  uart_cmsdk_tx_enable(arm_mps3_uart_dev);
  uart_cmsdk_rx_enable(arm_mps3_uart_dev);
  return;
}

int UART_SendChar(uint32_t txchar)
{
  struct uart_cmsdk_dev_t* arm_mps3_uart_dev=&UART0_CMSDK_DEV;
  if (txchar==10) {
    while (uart_cmsdk_write(arm_mps3_uart_dev, (uint8_t) 13)==UART_CMSDK_ERR_NOT_READY);
  }  
  while (uart_cmsdk_write(arm_mps3_uart_dev, (uint8_t) txchar)==UART_CMSDK_ERR_NOT_READY);
  return ((int) txchar);
}

char UART_ReceiveChar(void)
{
  struct uart_cmsdk_dev_t* arm_mps3_uart_dev=&UART0_CMSDK_DEV;
  enum uart_cmsdk_error_t ret_status;
  uint8_t read_data;
  do {
    ret_status = uart_cmsdk_read(arm_mps3_uart_dev, &read_data);
  } while (ret_status==UART_CMSDK_ERR_NOT_READY);
  return (char)(read_data);
}

/*---------------------------------------- */
/*    Porting layer for CMSIS-Compiler     */

/**
  Initialize stdio
 
  \return          0 on success, or -1 on error.
*/
int stdio_init (void) {
  UART_Config();
  return (0);	
}

/**
  Put a character to the stderr
 
  \param[in]   ch  Character to output
  \return          The character written, or -1 on write error.
*/
#ifdef RTE_CMSIS_Compiler_STDERR_Custom
int stderr_putchar (int ch) 
{
  return (UART_SendChar((uint32_t)ch));
}
#endif

/**
  Put a character to the stdout

  \param[in]   ch  Character to output
  \return          The character written, or -1 on write error.
*/
#ifdef RTE_CMSIS_Compiler_STDOUT_Custom
int stdout_putchar (int ch) 
{
  return (UART_SendChar((uint32_t)ch));
}
#endif
/**
  Get a character from the stdio
 
  \return     The next character from the input, or -1 on read error.
*/
#ifdef RTE_CMSIS_Compiler_STDIN_Custom
int stdin_getchar (void)
{
  return ((int) UART_ReceiveChar());
}
#endif
