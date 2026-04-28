
#include "usart_irq_func.h"





	USART_InitTypeDef usart;
  GPIO_InitTypeDef gpio;
  NVIC_InitTypeDef nvic;
  EXTI_InitTypeDef exti;

char rb[BUFFER_SIZE];
char wb[BUFFER_SIZE];

char *serial_rbuffer;
char *serial_wbuffer;

int i = 0;
int	j = 0;

int cmd_begin_detection = 0;  // znacka pre detekciu zaciatku prikazu

void init_rcc(void)
{

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
}

void init_control()
{

	
  gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_10MHz;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOF, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_2 ;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_10MHz;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOD, &gpio);
	
	
	gpio.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_10MHz;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB, &gpio);
	
	gpio.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_10MHz;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOC, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_8;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_10MHz;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA, &gpio);

  
	GPIO_SetBits(GPIOF, GPIO_Pin_7);
	GPIO_SetBits(GPIOF, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_13);
	GPIO_SetBits(GPIOA, GPIO_Pin_15);
	GPIO_SetBits(GPIOC, GPIO_Pin_10);
	GPIO_SetBits(GPIOC, GPIO_Pin_11);
	GPIO_SetBits(GPIOC, GPIO_Pin_12);
	GPIO_SetBits(GPIOD, GPIO_Pin_2);
}



void init_com()
{

  /* Configure USART1 pins:  Rx and Tx ----------------------------*/
  gpio.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3;
  gpio.GPIO_Speed = GPIO_Speed_10MHz;
  gpio.GPIO_Mode = GPIO_Mode_AF;
  gpio.GPIO_OType = GPIO_OType_PP;
  gpio.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &gpio);
	
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
	
  /* Enable USART1 IRQ */
  nvic.NVIC_IRQChannel = USART2_IRQn;
  nvic.NVIC_IRQChannelPriority = 0;
  nvic.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic);
   
  usart.USART_BaudRate = 57600;
  usart.USART_WordLength = USART_WordLength_8b;
  usart.USART_StopBits = USART_StopBits_1;
  usart.USART_Parity = USART_Parity_No;
  usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &usart);
   
  USART_Cmd(USART2,ENABLE);
 
 
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	serial_rbuffer = rb;
	serial_wbuffer = wb;
	
	memset(&wb,0,sizeof(wb));
	memset(&rb,0,sizeof(rb));
	
	
	  
}

void USART2_IRQHandler(void)
{

  if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET) // Transmit the string in a loop
  {
		     if(  *(serial_wbuffer+i) != '\r' || i >= BUFFER_SIZE-1)  // zistuje pritomnost ukoncovacieho znaku alebo koniec buffera
			   {
				   USART_SendData(USART2, (uint16_t)*(serial_wbuffer+i) );
	
			   }else if( *(serial_wbuffer+i) == NULL )
         { 
					 i=0; 
				   memset(&serial_wbuffer,NULL,sizeof(wb)); 
					 USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
				 }
				 else { 
					 i=0; 
					 memset(&serial_wbuffer,NULL,sizeof(wb)); 
					 USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
				 }
				 i++;	
	}
   
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // Received characters modify string
  {
		
//    *(serial_rbuffer+j) = USART_ReceiveData(USART2);
//	  j++;
//		
//		
//		if (j >= BUFFER_SIZE )
//			j = 0;
//		check(serial_rbuffer);
		char temp;
		temp = USART_ReceiveData(USART2); // nacitanie znaku z registra
		
		if( temp == '\r' ){					//koniec prikazu ?
		  *(serial_rbuffer+j) = '\r';    // 1 znak do buffra
			cmd_begin_detection = 0;  // zaciatok prikazu detekovany
			j= 0;
		}
		
		else if( temp == ':' ){					//zaciatok prikazu ?
		  *serial_rbuffer = ':';    // 1 znak do buffra
			cmd_begin_detection = 1;  // zaciatok prikazu detekovany
			j++;
		}

		if(cmd_begin_detection == 1 && j < BUFFER_SIZE && temp != ':')
	  {
			*(serial_rbuffer+j) = temp;
			j++;
		}

	
  }
	USART_ClearITPendingBit(USART2, USART_IT_RXNE );
}

int SERIAL_writeRSP( char* message, const char* response){ return 0; }

int SERIAL_write( char* message)
{ 

	
	serial_wbuffer = message;
  while( serial_wbuffer != NULL)
		USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	
return 0;

}

char* SERIAL_read()
{

	return serial_rbuffer;

	
}

