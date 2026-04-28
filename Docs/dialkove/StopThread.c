
#include <cmsis_os.h>                                           // CMSIS RTOS header file
#include "usart_irq_func.h"
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
 
void Stop_Thread (void const *argument);                             // thread function
osThreadId tid_StopThread;         
osThreadDef (Stop_Thread, osPriorityNormal, 1, 0);                   // thread object

// message
extern osMessageQId startStopMSB;
extern osMessageQId stopStartMSB;

int stoped;

int Init_StopThread (void) {

  tid_StopThread = osThreadCreate (osThread(Stop_Thread), NULL);
  if(!tid_StopThread) return(-1);
  return(0);
}

void Stop_Thread (void const *argument) {

osEvent evet;
  while (1) {

			evet = osMessageGet(startStopMSB, osWaitForever); // wait for message
			if (evet.status == osEventMessage) 
			{
			  SERIAL_write("::PB_K\r\0");
				stoped = 1;
			}
			
		
		osThreadYield();
	

	 } // end while
} // end function


