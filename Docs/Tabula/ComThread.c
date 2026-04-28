
#include <cmsis_os.h>                                           // CMSIS RTOS header file

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Thread (void const *argument);                             // thread function
osThreadId comThread_id;                                          // thread id
osThreadDef (Thread, osPriorityNormal, 1, 0);                   // thread object

int Init_ComThread (void) {

  comThread_id = osThreadCreate (osThread(Thread), NULL);
  if(!comThread_id) return(-1);
  
  return(0);
}

char *znakofka;

void Thread (void const *argument) {

	
  while (1) {
    
		
		
		
    osThreadYield();                                            // suspend thread
  }
}


