#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "nucleo.h"

volatile uint8_t spirx[SPI_RX_BUFF_SIZE*2] = {};
volatile uint8_t* spirx_ptr;
volatile uint8_t spirx_flag;
//COMPORT
void CP_Init(uint32_t brr){
	USART_t usart2 = {
		.br = brr,
		.n = 2,
		.rxe = 0,
		.txe = 1,
		.rxie = 0,
		.txie = 0,
		.dmaRxE = 0,
		.dmaTxE = 1};
	GPIO_t usart2_gpio = {
		.pins = 0xC & 0x4U,//RX: 0x4, TX: 0x8 
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



//SPI
void DMA1_Stream3_IRQHandler(){
	if(DMA1->LISR & DMA_LISR_HTIF3){
		DMA1->LIFCR = DMA_LIFCR_CHTIF3;
		spirx_ptr = &spirx[0];
	}
	if(DMA1->LISR & DMA_LISR_TCIF3){
		DMA1->LIFCR = DMA_LIFCR_CTCIF3;
		spirx_ptr = &spirx[SPI_RX_BUFF_SIZE/2];
	}}
void nucleo_spi_init(){
	SPI_t spi2 = {
		.regs = 0,
		.n = 2,
		.br = SPI_BR_FPDIV4, // 180/2 /2 (APB1) / FPDIV => 11.25MHz
		.rxe = 1,
		.txe = 0,
		.rxie = 0,
		.txie = 0,
		.dmaRxE = 0,
		.dmaTxE = 0
	};
	GPIO_t spi2_gpio = {
		.pins = 0x1 | 0x2 | 0x7, //MOSI | MISO | SCK
		.mode = GPIO_MODE_AF,
		.af = 5,
		.port = 'C'};
	DMA_t spi2_dmaRX ={
		.n			= 1,
		.stream		= 3,//TX => .stream = 4,
		.ch			= 0,//TX => .ch		= 0,
		.m0ar		= spirx,
		.m1ar		= 0,
		.par		= (uint32_t)&(SPI2->DR),
		.ndtr		= (SPI_RX_BUFF_SIZE*2),
		.pl			= DMA_PL_HIGH,
		.msize		= DMA_SIZE_B,
		.psize		= DMA_SIZE_B,
		.minc		= 1,
		.pinc		= 0,
		.dbm		= 0,
		.circ		= 1,
		.dir		= DMA_DIR_P2M,
		.tcie		= 1,
		.htie		= 1,
		.en			= 1};

		GPIO_Init(&spi2_gpio);
		DMA_Init(&spi2_dmaRX);
		SPI_Init(&spi2);}
