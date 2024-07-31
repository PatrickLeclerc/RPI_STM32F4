#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "dma.h"
#include "rtc.h"
#include "spi.h"

//COMPORT
void CP_Init(uint32_t brr);
//Polling writes
int __io_putchar(int ch);
int _write(int file, char *ptr, int len);
//DMA writes
void DMA1_Stream6_IRQHandler();
void nucleo_printf(char *ptr);
//LED
void LED_ON();
void LED_OFF();
void LED_Init();
