#include "spi.h"

void SPI_Init(SPI_t* spi){
	uint32_t SPI_IRQn;
	uint32_t apbn;
	/* RCC */
	switch(spi->n){
			case 1:{
				RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
				spi->regs = SPI1;
				SPI_IRQn = SPI1_IRQn;
				apbn = 2;
				break;
			}
			case 2:{
				RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
				spi->regs = SPI2;
				SPI_IRQn = SPI2_IRQn;
				apbn = 1;
				break;
			}
			case 3:{
				RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
				spi->regs = SPI3;
				SPI_IRQn = SPI3_IRQn;
				apbn = 1;
				break;
			}
			case 4:{
				RCC->APB2ENR |= RCC_APB2ENR_SPI4EN;
				spi->regs = SPI4;
				SPI_IRQn = SPI4_IRQn;
				apbn = 2;
				break;
			}
			default:{
				return;
			}
	}
	
	
	/* Config */
	spi->regs->CR1 = SPI_CR1_SSM | SPI_CR1_SSI | (spi->br << SPI_CR1_BR_Pos);// 11.25MHz
	
	/* IRQ */
	spi->regs->CR2 = (spi->rxie << SPI_CR2_RXDMAEN_Pos) | (spi->txie << SPI_CR2_TXDMAEN_Pos);
	if(spi->rxie || spi->txie)
		NVIC_EnableIRQ(SPI_IRQn);
	
	//DMA
	if(spi->dmaTxE)
		spi->regs->CR2 |= SPI_CR2_TXDMAEN;
	if(spi->dmaRxE)
		spi->regs->CR2 |= SPI_CR2_RXDMAEN;

	
	
	///*Enable*/
	SPI1->CR1 |= SPI_CR1_SPE; 
}
