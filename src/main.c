/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "main.h"
#include "q.h"

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

UART_HandleTypeDef UartHandle;
void main_uart_init();


int main(void)
{
	SystemInit();
	HAL_Init();
	BSP_LED_Init(LED2);
	main_uart_init();

#if defined(Q_SIZE) && defined(Q_MAXLEN)
	struct q *msg_q = q_create(Q_SIZE,Q_MAXLEN,0);
#else
	struct q *msg_q = q_create(5,20,0);
#endif

	printf("fw version: %s\r\n",FW_VERSION);
	uint8_t a[20] = {0};
	uint8_t b[20] = {1,2};
	uint8_t c[20] = {0x55,0xaa,0x5a,0xa5};
	q_add(msg_q,a,20);
	q_add(msg_q,b,20);
	q_add(msg_q,c,20);
	q_add(msg_q,c,20);
	q_add(msg_q,b,20);
	q_add(msg_q,a,20);
	q_print(msg_q);;

	for(;;){
		BSP_LED_Toggle(LED2);
		HAL_Delay(500);
	}


}

PUTCHAR_PROTOTYPE
{
	 HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);
	 return ch;
}

void main_uart_init()
{
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
}
