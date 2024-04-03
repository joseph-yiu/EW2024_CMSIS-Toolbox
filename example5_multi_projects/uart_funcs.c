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
#else
  #error device not defined
#endif

#include "RTE_Components.h"

#if (defined (IOTKit_CM23) || (IOTKit_CM33) || (IOTKit_CM33_FP))
// Map macros
#define CMSDK_UART_CTRL_TXEN_Msk IOTKIT_UART_CTRL_TXEN_Msk
#define CMSDK_UART_CTRL_RXEN_Msk IOTKIT_UART_CTRL_RXEN_Msk
#define CMSDK_UART_STATE_TXBF_Msk IOTKIT_UART_STATE_TXBF_Msk
#define CMSDK_UART_STATE_RXBF_Msk IOTKIT_UART_STATE_RXBF_Msk

/* These platforms support TrustZone. So we have to decide if the
  UART used is a Secure UART or Non-secure UART */
#if (defined (__ARM_FEATURE_CMSE ) && (__ARM_FEATURE_CMSE == 3))
// Secure code 
#define CMSDK_UART0 IOTKIT_SECURE_UART0
//#define CMSDK_UART0 IOTKIT_UART0
#else
// Non-secure code
// Note: For simple projects we run the codes in Secure state only
#define CMSDK_UART0 IOTKIT_SECURE_UART0
//#define CMSDK_UART0 IOTKIT_UART0
#endif
#endif
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
  CMSDK_UART0->CTRL = 0;         /* Disable UART when changing configuration */
  CMSDK_UART0->BAUDDIV = 651;    /* 25MHz / 38400 = 651 */
  CMSDK_UART0->CTRL = CMSDK_UART_CTRL_TXEN_Msk|CMSDK_UART_CTRL_RXEN_Msk;  
  /* Update CTRL register to new value */
  return;
}

int UART_SendChar(uint32_t txchar)
{
  if (txchar == 10) UART_SendChar(13);
	
  while(CMSDK_UART0->STATE & CMSDK_UART_STATE_TXBF_Msk);
  CMSDK_UART0->DATA = txchar;
  return ((int) txchar);
}

char UART_ReceiveChar(void)
{
  while(!(CMSDK_UART0->STATE & CMSDK_UART_STATE_RXBF_Msk));
  return (char)(CMSDK_UART0->DATA);
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
