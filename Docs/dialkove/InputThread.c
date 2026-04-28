
#include <cmsis_os.h>                                           // CMSIS RTOS header file
#include "usart_irq_func.h"
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/

enum STATES { predStartom, odStartovane, poStarte, Stopnute, ZASTAVENE}stavy;
extern osMessageQId stopStartMSB;
extern osMessageQId startStopMSB; 
extern int stoped;

int tick;
void check_inputs(void);
void delay(int i);
void Thread (void const *argument);                             // thread function
osThreadId tid_Thread;                                          // thread id
osThreadDef (Thread, osPriorityNormal, 1, 0);                   // thread object



int Init_Thread (void) {

  tid_Thread = osThreadCreate (osThread(Thread), NULL);
  if(!tid_Thread) return(-1);
  
  return(0);
}


void check_inputs()
{

		
	

		// Hostia Skore Minus --
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)){  
			osDelay(400);
				SERIAL_write(":PB_B\r\0");
			osDelay(1000);
		}

		// Hostia Skore Plus ++
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)){
			osDelay(400);
				SERIAL_write(":PB_A\r\0");
			osDelay(1000);
		}
		
		// Cas Reset
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)){
			osDelay(400);
				SERIAL_write(":PB_J\r\0");
			osDelay(1000);
		}
		
		// SIRENA
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)){
			osDelay(400);
				SERIAL_write(":PB_I\r\0");
			osDelay(1000);
		}
		
		// Domaci skore Minus --
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)){
					osDelay(400);
				SERIAL_write(":PB_E\r\0");
			osDelay(1000);
		}
		
		// Domaci skore Plus ++
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)){
			osDelay(400);
				SERIAL_write(":PB_F\r\0");
			osDelay(1000);		
		}
		
		// Hostia Sety Plus ++
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)){
					osDelay(400);
				SERIAL_write(":PB_C\r\0");
			osDelay(1000);
		}		
		
		// Hostia Sety Minus --
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)){
					osDelay(400);
				SERIAL_write(":PB_D\r\0");
			osDelay(1000);
		}
		
		// Domaci Sety Minus --
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)){
			osDelay(400);
				SERIAL_write(":PB_H\r\0");
			osDelay(1000);
		}			

		// Domaci Sety Plus ++
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)){
			osDelay(400);
			SERIAL_write(":PB_G\r\0");
			osDelay(1000);
		}
		
		// Reset Skore
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)){
						osDelay(400);
				SERIAL_write(":PB_M\r\0");
			osDelay(1000);
		}

		// Reset Sety
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)){
			osDelay(400);
				SERIAL_write(":PB_N\r\0");
			osDelay(1000);}
		
		
		//detekcia start stop cas
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15))
			osDelay(300);
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15))
			tick =1;
		else tick = 0;
			
		if(tick){
			if(stoped == 1)
				osMessagePut(stopStartMSB,1,0);
			else
				osMessagePut(startStopMSB,1,0);
		}
			
}



void Thread (void const *argument) {


  while (1) {
     // Insert thread code here...
		check_inputs();
		
    osThreadYield();                                            // suspend thread
  }
}


