#include "acsu.h"
#include "tim.h"
extern volatile uint32_t tim2_flag;

#include "usart.h"
#include "gpio.h"
#include "dma.h"
#include "rtc.h"

#include "spi.h"
#define SPI_RX_BUFF_SIZE 512
extern volatile uint8_t spirx[SPI_RX_BUFF_SIZE*2];
extern volatile uint8_t* spirx_ptr;
extern volatile uint8_t spirx_flag;

//TIM
void TIM2_IRQHandler();
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
//SPI
void nucleo_spi_init();
void DMA1_Stream3_IRQHandler();
