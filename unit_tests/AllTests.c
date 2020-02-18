/* Copyright (c) 2010 James Grenning and Contributed to Unity Project
 * ==========================================
 *  Unity Project - A Test Framework for C
 *  Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
 *  [Released under MIT License. Please refer to license.txt for details]
 * ========================================== */
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "main.h"
#include "unity_fixture.h"

int setup_basic(void);
static void runAllTests(void)
{
	RUN_TEST_GROUP(mygroup);
}


int main(void)
{
	setup_basic();
	const char *sample[] = {"test"};
    return UnityMain(1,sample , runAllTests);
}



/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
	UART_HandleTypeDef UartHandle;
int setup_basic(void)
{
	SystemInit();
	HAL_Init();
	BSP_LED_Init(LED2);

	/*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART1 configured as follow:
	      - Word Length = 8 Bits
	      - Stop Bit = One Stop bit
	      - Parity = ODD parity
	      - BaudRate = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance        = USARTx;

	  UartHandle.Init.BaudRate   = 9600;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_NONE;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;

	  if(HAL_UART_Init(&UartHandle) != HAL_OK)
	  {
	    /* Initialization Error */
	    //Error_Handler();
	  }

	HAL_UART_Init(&UartHandle);
	return 0;
}

PUTCHAR_PROTOTYPE
{
	 HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);
	 return ch;
}
