#include "usart.h"

void USART_Init(USART_t* usart){
	uint32_t USART_IRQn;
	uint32_t apbn;
	/* RCC */
	switch(usart->n){
			case 1:{
				RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
				usart->regs = USART1;
				USART_IRQn = USART1_IRQn;
				apbn = 2;
				break;
			}
			case 2:{
				RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
				usart->regs = USART2;
				USART_IRQn = USART2_IRQn;
				apbn = 1;
				break;
			}
			case 3:{
				RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
				usart->regs = USART3;
				USART_IRQn = USART3_IRQn;
				apbn = 1;
				break;
			}
			case 4:{
				RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
				usart->regs = UART4;
				USART_IRQn = UART4_IRQn;
				apbn = 1;
				break;
			}
			case 5:{
				RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
				usart->regs = UART5;
				USART_IRQn = UART5_IRQn;
				apbn = 1;
				break;
			}
			case 6:{
				RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
				usart->regs = USART6;
				USART_IRQn = USART6_IRQn;
				apbn = 2;
				break;
			}
			default:{
				return;
			}
	}
	//DMA
	if(usart->dmaTxE)
		usart->regs->CR3 |= USART_CR3_DMAT;
	if(usart->dmaRxE)
		usart->regs->CR3 |= USART_CR3_DMAR;
	
	/* Baudrate */
	if(apbn == 1)
		usart->regs->BRR = 8 * SystemCoreClock / (16 * 2 * usart->br);
	else 
		usart->regs->BRR = 8 * SystemCoreClock / (16 * 4 * usart->br);
	
	/* IRQ */
	usart->regs->CR1 |= (usart->rxie << USART_CR1_RXNEIE_Pos) | (usart->txie << USART_CR1_TXEIE_Pos);
	if(usart->rxie || usart->txie)
		NVIC_EnableIRQ(USART_IRQn);
	
	/* Enable */
	usart->regs->CR1 = USART_CR1_TE | USART_CR1_RE;
	usart->regs->CR1 |= USART_CR1_UE;

}