
#include <cmsis_os.h>                                           // CMSIS RTOS header file
#include <stdio.h>
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Thread (void const *argument);                             // thread function
osThreadId tid_Thread;                                          // thread id
osThreadDef (USARTIK, osPriorityNormal, 1, 0);                   // thread object


int Init_Thread (void) {

  tid_Thread = osThreadCreate (osThread(USARTIK), NULL);
  if(!tid_Thread) return(-1);
  
  return(0);
}

void Thread (void const *argument) {

  while (1) {
    printf("co to toto !!\r\n");
    osThreadYield();                                            // suspend thread
  }
}


