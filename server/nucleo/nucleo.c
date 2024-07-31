#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "nucleo.h"

//COMPORT
void CP_Init(uint32_t brr){
	USART_t usart2 = {
		.br = brr,
		.n = 2,
		.rxie = 0,
		.txie = 0,
		.dmaRxE = 0,
		.dmaTxE = 1};
	GPIO_t usart2_gpio = {
		.pins = 0x4U,//0xCU for rx/tx
		.mode = GPIO_MODE_AF,
		.af = 7,
		.port = 'A'};
	DMA_t usart2_dmaTX ={
		.n			= 1,
		.stream		= 6,
		.ch			= 4,
		.m0ar		= 0,
		.m1ar		= 0,
		.par		= (uint32_t)&(USART2->DR),
		.ndtr		= 0,
		.pl			= 0,
		.msize		= DMA_SIZE_B,
		.psize		= DMA_SIZE_B,
		.minc		= 1,
		.pinc		= 0,
		.dbm		= 0,
		.circ		= 0,
		.dir		= DMA_DIR_M2P,
		.tcie		= 1,
		.htie		= 0,
		.en			= 0};
	GPIO_Init(&usart2_gpio);
	DMA_Init(&usart2_dmaTX);
	USART_Init(&usart2);}
//DMA writes
static volatile int nucleo_printf_done = 1;
void DMA1_Stream6_IRQHandler(){
	if(DMA1->HISR & DMA_HISR_TCIF6){
		DMA1->HIFCR = DMA_HIFCR_CTCIF6;
		nucleo_printf_done = 1;
	}}

void nucleo_printf(char *ptr){
	//Wait for last TX to complete
	while(!nucleo_printf_done){}
	nucleo_printf_done = 0;
	//Write
	DMA1_Stream6->CR &= ~DMA_SxCR_EN;
	while(DMA1_Stream6->CR & DMA_SxCR_EN){}
	DMA1_Stream6->M0AR = (uint32_t) ptr;
	DMA1_Stream6->PAR = (uint32_t)&(USART2->DR);
	DMA1_Stream6->NDTR = (uint32_t) strlen(ptr);
	DMA1_Stream6->CR |= DMA_SxCR_EN;}

//Polling writes
int __io_putchar(int ch){
	while(!(USART2->SR & USART_SR_TXE)){}
	USART2->DR = ch;
	return ch;}
int _write(int file, char *ptr, int len){
	while(!nucleo_printf_done){}
    int DataIdx;

    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        __io_putchar(*ptr++);
    }
    return len;}

//LED
void LED_ON(){GPIOA->ODR |= 1 << 5;}
void LED_OFF(){GPIOA->ODR &= ~(1 << 5);}
void LED_Init(){
	GPIO_t led = {
  	  .af = 0,
  	  .mode = GPIO_MODE_OUT,
  	  .pins = 1<<5,
  	  .port = 'A',
  	};
	GPIO_Init(&led);
	LED_OFF();}


