
#include <cmsis_os.h>                                           // CMSIS RTOS header file
#include "stm32f0xx_gpio.h"
#include "string.h"
#include "USART_irq_func.h"
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Thread (void const *argument);                             // thread function
osThreadId tid_Thread;                                          // thread id
osThreadDef (Thread, osPriorityNormal, 1, 0);                   // thread object
void clear_rbuffer(void);


int Init_CheckThread (void) {

  tid_Thread = osThreadCreate (osThread(Thread), NULL);
  if(!tid_Thread) return(-1);
  
  return(0);
}


extern char* serial_rbuffer;

void Thread (void const *argument) {

  while (1) {
    check(serial_rbuffer); // Insert thread code here...
    osThreadYield();                                            // suspend thread
		
  }
}

int check( char* inputstring)
{

	// toto zbieha pri kazdom naplneni buffera, nemozete to dat sem
	
	
  if( strstr(inputstring, ":PB_A\r"))  /// hostia skore ++
    {
			//GPIO_SetBits(GPIOC, GPIO_Pin_8);

			GPIO_ResetBits(GPIOF, GPIO_Pin_6);

			osDelay(15);

			//GPIO_ResetBits(GPIOC, GPIO_Pin_8);
			GPIO_SetBits(GPIOF, GPIO_Pin_6);
			osDelay(15);
			clear_rbuffer();
			
			return 0;
    }

		else if (strstr(inputstring, ":PB_B\r") ) /// hostia skore --
      {
				//GPIO_SetBits(GPIOC, GPIO_Pin_9);
				
				GPIO_ResetBits(GPIOF, GPIO_Pin_7);
				osDelay(15);
				//GPIO_ResetBits(GPIOC, GPIO_Pin_9);
			  GPIO_SetBits(GPIOF, GPIO_Pin_7);
				osDelay(15);
				clear_rbuffer();
			  return 0;
      }
			else if (strstr(inputstring, ":PB_C\r"))   //hostia sety ++
    {
			GPIO_ResetBits(GPIOA, GPIO_Pin_13);

			osDelay(15);

			//GPIO_ResetBits(GPIOC, GPIO_Pin_8);
			GPIO_SetBits(GPIOA, GPIO_Pin_13);
			osDelay(15);
			clear_rbuffer();
			
			return 0;
    }
		else if (strstr(inputstring, ":PB_D\r") )  ///hostia sety --
    {
			GPIO_ResetBits(GPIOA, GPIO_Pin_15);

			osDelay(15);

			//GPIO_ResetBits(GPIOC, GPIO_Pin_8);
			GPIO_SetBits(GPIOA, GPIO_Pin_15);
			osDelay(15);
			clear_rbuffer();
			
			return 0;
    }

		else if (strstr(inputstring, ":PB_E\r"))   // domaci skore ++
  {
			GPIO_ResetBits(GPIOC, GPIO_Pin_10);

			osDelay(15);

			//GPIO_ResetBits(GPIOC, GPIO_Pin_8);
			GPIO_SetBits(GPIOC, GPIO_Pin_10);
			osDelay(15);
			clear_rbuffer();
			
			return 0;
	}

		else if (strstr(inputstring, ":PB_F\r"))  // domaci skore --
  {
			GPIO_ResetBits(GPIOC, GPIO_Pin_11);

			osDelay(15);

			//GPIO_ResetBits(GPIOC, GPIO_Pin_8);
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			osDelay(15);
			clear_rbuffer();
			
			return 0;
	}

		else if (strstr(inputstring, ":PB_G\r"))  // domaci sety ++
  {
		
			GPIO_ResetBits(GPIOC, GPIO_Pin_12);

			osDelay(15);

			//GPIO_ResetBits(GPIOC, GPIO_Pin_8);
			GPIO_SetBits(GPIOC, GPIO_Pin_12);
			osDelay(15);
			clear_rbuffer();
			
			return 0;
	}

		else if (strstr(inputstring, ":PB_H\r")) // domaci sety -- 
  {
			GPIO_ResetBits(GPIOD, GPIO_Pin_2);

			osDelay(15);

			//GPIO_ResetBits(GPIOC, GPIO_Pin_8);
			GPIO_SetBits(GPIOD, GPIO_Pin_2);
			osDelay(15);
			clear_rbuffer();
			
			return 0;
	}

		else if (strstr(inputstring, ":PB_I\r"))//sirena
  {
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
			osDelay(4000);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
      clear_rbuffer();
			  return 0;
	}

		else if (strstr(inputstring, ":PB_J\r"))//cas reset
  {
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			osDelay(15);
			
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_SetBits(GPIOA, GPIO_Pin_8);
			osDelay(10);
      clear_rbuffer();
			  return 0;
	}

		else if (strstr(inputstring, ":PB_K\r"))//cas stop
  {
				GPIO_SetBits(GPIOA, GPIO_Pin_8);
				osDelay(5);
				clear_rbuffer();
			  return 0;
	}

		else if (strstr(inputstring, ":PB_L\r")) //cas start
  {
		
			  GPIO_ResetBits(GPIOA, GPIO_Pin_8);
				osDelay(5);
				clear_rbuffer();
			  return 0;
	}
	else if (strstr(inputstring, ":PB_M\r")) //skore reset
	{
			GPIO_SetBits(GPIOB, GPIO_Pin_4); 
			osDelay(10);
			
			GPIO_ResetBits(GPIOB, GPIO_Pin_4);
			osDelay(10);
      clear_rbuffer();
			return 0;
	}
	
		else if (strstr(inputstring, ":PB_N\r")) //sety reset
  {
			GPIO_SetBits(GPIOB, GPIO_Pin_3);
			osDelay(10);
			
			GPIO_ResetBits(GPIOB, GPIO_Pin_3);
			osDelay(10);
      clear_rbuffer();
			return 0;
	}
		else if (strstr(inputstring, ":PB_O\r")) //pocitanie minut
  {
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
			osDelay(1000);
			
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			osDelay(1000);
      clear_rbuffer();
			return 0;
	}
  else
		return -1;

}

void clear_rbuffer(void)
{
 int index;
	for( index = 0; index < BUFFER_SIZE ; index++)
	{
		*(serial_rbuffer+index) = ' ';
	}
}



