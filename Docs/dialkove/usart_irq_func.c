
#include "usart_irq_func.h"

USART_InitTypeDef usart;
GPIO_InitTypeDef gpio;
NVIC_InitTypeDef nvic;
EXTI_InitTypeDef exti;

	
char rb[BUFFER_SIZE];
char wb[BUFFER_SIZE];

char *serial_rbuffer;
char *serial_wbuffer;
static int started;
int i = 0;
int	j = 0;

int cmd_begin_detection = 0;  // znacka pre detekciu zaciatku prikazu


int start = 0;


void init_rcc(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}


void init_control()
{

	
	
  gpio.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpio);

	
	  gpio.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_8| GPIO_Pin_15  ;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio);
	
	  gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &gpio);
	
  gpio.GPIO_Pin = GPIO_Pin_1;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &gpio);



}



void init_com()
{

  /* Configure USART1 pins:  Rx and Tx ----------------------------*/
  gpio.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_10;
  gpio.GPIO_Speed = GPIO_Speed_10MHz;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &gpio);
	

  /* Enable USART1 IRQ */
  nvic.NVIC_IRQChannel = USART1_IRQn;
  nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
  nvic.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic);
   
  usart.USART_BaudRate = 57600;
  usart.USART_WordLength = USART_WordLength_8b;
  usart.USART_StopBits = USART_StopBits_1;
  usart.USART_Parity = USART_Parity_No;
  usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &usart);
   
  USART_Cmd(USART1,ENABLE);
 
 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	serial_rbuffer = rb;
	serial_wbuffer = wb;
	
	memset(&wb,'\0',sizeof(wb));
	memset(&rb,0,sizeof(rb));
	
	
	  
}

void USART1_IRQHandler(void)
{

  if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET) // Transmit the string in a loop
  {
		     if(  *(serial_wbuffer+i) != '\0' || i >= BUFFER_SIZE-1)  // zistuje pritomnost ukoncovacieho znaku alebo koniec buffera
			   {
				   USART_SendData(USART1, (uint16_t)*(serial_wbuffer+i)  );
					 
	
			   }else if( *(serial_wbuffer+i) == '\0' )
         { 
					 i=0; 
				   memset(&serial_wbuffer,NULL,sizeof(wb)); 
					 USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
				 }
				 else { 
					 i=0; 
					 memset(&serial_wbuffer,NULL,sizeof(wb)); 
					 USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
				 }
				 i++;	
	}
   
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) // Received characters modify string
  {
		
//    *(serial_rbuffer+j) = USART_ReceiveData(USART2);
//	  j++;
//		
//		
//		if (j >= BUFFER_SIZE )
//			j = 0;
//		check(serial_rbuffer);
		char temp;
		temp = USART_ReceiveData(USART1); // nacitanie znaku z registra
		
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
	USART_ClearITPendingBit(USART1, USART_IT_RXNE );
}

int SERIAL_writeRSP( char* message, const char* response){ return 0; }

int SERIAL_write( char* message)
{ 

	
	serial_wbuffer = message;
  while( serial_wbuffer != NULL)
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	
return 0;

}

char* SERIAL_read()
{

	return serial_rbuffer;

	
}

