#include "spi.h"

void SPI_Init(SPI_t* spi){
//    /*RCC*/
//	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN|RCC_AHB1ENR_DMA2EN;
//	
//	/*GPIO*/
//	GPIOB->MODER &= ~GPIO_MODER_MODE5_Msk;
//	GPIOB->MODER |= GPIO_MODER_MODE5_1;
//
//	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5_Msk;
//	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_0;
//	//GPIOB->OTYPER |= GPIO_OTYPER_OT5_Msk;
//	GPIOB->AFR[0] |= 5U<<GPIO_AFRL_AFSEL5_Pos;
//	
//	/*SPI2: Internal slave management (master) */
//	SPI1->CR1 = SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_MSTR | (1U<<SPI_CR1_BR_Pos);//|SPI_CR1_DFF  //18MHz
//	
//	/*DMA*/
//	DMA2_Stream3->CR = 0U;
//	while(DMA2_Stream3->CR != 0U){}
//	DMA2_Stream3->PAR = (uint32_t)&(SPI1->DR);
//	DMA2_Stream3->NDTR = buffSize;
//	DMA2_Stream3->CR |= (3U<<DMA_SxCR_CHSEL_Pos) | DMA_SxCR_PL_Msk | DMA_SxCR_DIR_0 | DMA_SxCR_MINC;//| DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0
//	DMA2_Stream3->FCR = 0U;
//	//DMA2_Stream3->CR |= DMA_SxCR_EN;
//	/*Enable*/
//	SPI1->CR2 = SPI_CR2_TXDMAEN;
//	SPI1->CR1 |= SPI_CR1_SPE; 
}
