
#include <cmsis_os.h>                                           // CMSIS RTOS header file
#include "usart_irq_func.h"
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void StartThread (void const *argument);                             // thread function
osThreadId tid_StartThread;   // thread id
extern osThreadId tid_StopThread;   // thread id
osThreadDef (StartThread, osPriorityNormal, 1, 0);                   // thread object

// message
extern osMessageQId startStopMSB;
extern osMessageQId stopStartMSB;
extern int stoped;

int Init_StartThread (void) {

  tid_StartThread = osThreadCreate (osThread(StartThread), NULL);
  if(!tid_StartThread) return(-1);
  return(0);
}

void StartThread (void const *argument) {

osEvent evt;
  while (1) {

		evt = osMessageGet(stopStartMSB, osWaitForever); // wait for message
		if (evt.status == osEventMessage) 
		{
			SERIAL_write("::PB_L\r\0");
			stoped =0 ;
		}
		
		osThreadYield();
	
  }	

} // function end



