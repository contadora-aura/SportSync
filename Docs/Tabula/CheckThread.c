
#include <cmsis_os.h>                                           // CMSIS RTOS header file
#include "checkthread.h"
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Thread (void const *argument);                             // thread function
osThreadId tid_Thread;                                          // thread id
osThreadDef (Thread, osPriorityNormal, 1, 0);                   // thread object

int Init_Thread (void) {

  tid_Thread = osThreadCreate (osThread(Thread), NULL);
  if(!tid_Thread) return(-1);
  
  return(0);
}

int check( char* inputstring)
{

  if( strstr(inputstring, "PB_A\r"))
    {
			  int temp = 10000;
        GPIOB->ODR = 1 << 8; 
			  
			  while(temp != 0 )
					temp--;
			  GPIOB->ODR = 0 << 8; 
			
			//  serial_rbuffer = "";
			
			  return 0;
    }

  else if (strstr(inputstring, "PB_B\r") )
      {
			  int temp = 10000;
        GPIOB->ODR = 1 << 9; 
			  
			  while(temp != 0 )
					temp--;
			  GPIOB->ODR = 0 << 9; 
			
			  //serial_rbuffer = "";
      }
  else if (strstr(inputstring, "PB_C\r"))
    {
			  int temp = 10000;
        GPIOB->ODR = 1 << 10; 
			  
			  while(temp != 0 )
					temp--;
			  GPIOB->ODR = 0 << 10; 
			
			  //serial_rbuffer = "";
    }
  else if (strstr(inputstring, "PB_D\r") )
    {
			  int temp = 100;
        GPIOB->ODR = 1 << 11; 
			  
			  while(temp != 0 )
					temp--;
			  GPIOB->ODR = 0 << 11; 
			
			  
				return 0;
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

  return -1;

}

int RESULT;

void Thread (void const *argument) {

  while (1) {
   
		RESULT = check( (char*)argument);

    osThreadYield();                                            // suspend thread
  }
}


