/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#include "main.h"

#define BUFFER_SIZE 6


extern char *serial_wbuffer;

	USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
extern char rb[BUFFER_SIZE];
extern char wb[BUFFER_SIZE];


extern void init_com(void);
extern void init_control(void);




void delay(int i)
{
while(i!=0); 
}

/*
 * main: initialize and start the system
 */
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS
	
	// daj reset ked to pustim
	
  init_rcc();
	
	init_com();

  // initialize peripherals here
  init_control();

		
  // create 'thread' functions that start executing,
   Init_CheckThread();
		osKernelStart ();                         // start thread execution 
	

	


}
