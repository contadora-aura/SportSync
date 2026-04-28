
#include <cmsis_os.h>                                           // CMSIS RTOS header file
#include <usart_irq_func.h>
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
 void Show(void);
 
 extern char* serial_rbuffer;
 
 
 
void ShowThread (void const *argument);                             // thread function
osThreadId tsid_Thread;                                          // thread id
osThreadDef (ShowThread, osPriorityNormal, 1, 0);                   // thread object

int Init_Show_Thread (void) {

  tsid_Thread = osThreadCreate (osThread(ShowThread), NULL);
  if(!tsid_Thread) return(-1);
  
  return(0);
}

void ShowThread (void const *argument) {

  while (1) {
    //; // Insert thread code here...
		Show();
    osThreadYield();                                            // suspend thread
  }
}


void Show()
{

	serial_rbuffer = ":PB_A\r";
	osDelay(2000);
		serial_rbuffer = ":PB_B\r";
	osDelay(2000);
		serial_rbuffer = ":PB_A\r";
	osDelay(2000);
		serial_rbuffer = ":PB_B\r";
	osDelay(2000);
		serial_rbuffer = ":PB_A\r";
	osDelay(2000);
		serial_rbuffer = ":PB_B\r";
	osDelay(2000);
	
}

