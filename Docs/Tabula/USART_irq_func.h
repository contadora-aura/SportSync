

#include "main.h"

#define BUFFER_SIZE 32

int check( char* inputstring);
void USART2_IRQHandler(void);
void init_com(void);
void init_control(void);
void init_rcc(void);

int SERIAL_writeRSP( char* message, const char* response);

int SERIAL_write( char* message);

char* SERIAL_read(void);
