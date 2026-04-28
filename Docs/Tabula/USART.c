
#include <cmsis_os.h>                                           // CMSIS RTOS header file
#include <stm32f0xx_usart.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Thread (void const *argument);                             // thread function
osThreadId tid_Thread;                                          // thread id
osThreadDef (Thread, osPriorityNormal, 1, 0);                   // thread object

#define BUFFER_SIZE 128

char *rbuff;
char *wbuff;

	USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

void init_control()
{
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}

void init_com()
{


   
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
   
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
     
  /* Configure USART1 pins:  Rx and Tx ----------------------------*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
	
  /* Enable USART1 IRQ */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
   
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure);
   
  USART_Cmd(USART2,ENABLE);
 
  USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
 
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
}


int check(const char* inputstring)
{

  if( strstr(inputstring, "PB_A\r\n"))
    {
        GPIOC->ODR ^= 1 << 8; 
			  return 0;
    }

  else if (strstr(inputstring, "PB_B\r\n") )
      {
        GPIOC->ODR ^= 1 << 9; 
				return 0;
      }
  else if (strstr(inputstring, "PB_C\r\n"))
    {
        ;
    }
  else if (strstr(inputstring, "PB_D") )
    {
      ;
    }

  else if (strstr(inputstring, "PB_E"))
  {;}

  else if (strstr(inputstring, "PB_F"))
  {;}

  else if (strstr(inputstring, "PB_G"))
  {;}

  else if (strstr(inputstring, "PB_H"))
  {;}

  else if (strstr(inputstring, "PB_I"))
  {;}

  else if (strstr(inputstring, "PB_J"))
  {;}

  else if (strstr(inputstring, "PB_K"))
  {;}

  if (strstr(inputstring, "PB_L"))
  {;}

  fail: return -1;

}


void USART2_IRQHandler(void)
{
 // static int tx_index = 0;
 // static int rx_index = 0;
  int i = 0;
  if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET) // Transmit the string in a loop
  {
		if( *wbuff+i != 0xD || i < BUFFER_SIZE) {
			USART_SendData(USART2, *wbuff+i );
		  i++;
		}
		else{ i=0; wbuff = NULL; }
		
  }
   
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // Received characters modify string
  {
		
    *(rbuff+i) = USART_ReceiveData(USART2);
		i++;
		if (i >= BUFFER_SIZE-1)
			i = 0;
		
  }
}

int Init_Thread (void) {

  tid_Thread = osThreadCreate (osThread(Thread), NULL);
  if(!tid_Thread) return(-1);
  
  return(0);
}

void Thread (void const *argument) {

  while (1) {
    ; // Insert thread code here...
		
		
		
		
    osThreadYield();                                            // suspend thread
  }
}


