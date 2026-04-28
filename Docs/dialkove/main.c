/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

                      // RTOS object definitions
#include "main.h"
#define osFeature_MessageQ   1

extern osThreadId tid_StartThread;


osPoolDef(mpool, 1, int); // Define memory pool
osPoolId mpool;
osMessageQDef(stopStartMSB, 1, int); // Define message queue
osMessageQId stopStartMSB;
osMessageQDef(startStopMSB, 1, int); // Define message queue
osMessageQId startStopMSB;

/*
 * main: initialize and start the system
 */
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS
	
	init_rcc();
	init_com();
	init_control();
	mpool = osPoolCreate(osPool(mpool)); // create memory pool
  startStopMSB = osMessageCreate(osMessageQ(startStopMSB), NULL);
	stopStartMSB = osMessageCreate(osMessageQ(stopStartMSB), NULL); 
  // initialize peripherals here
	
  // create 'thread' functions that start executing,
  // example: tid_name = osThreadCreate (osThread(name), NULL);
	Init_Thread();
	Init_StartThread();
	Init_StopThread();

	osKernelStart ();                         // start thread execution 


}
