#include "dma.h"
void DMA_Init(DMA_t* dma){
	uint32_t DMA_IRQn;
	/*RCC*/
	if(dma->n==1){
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
		switch(dma->stream){
			case 0:{
				dma->regs = DMA1_Stream0;
				DMA_IRQn = DMA1_Stream0_IRQn;
				break;
			}
			case 1:{
				dma->regs = DMA1_Stream1;
				DMA_IRQn = DMA1_Stream1_IRQn;
				break;
			}
			case 2:{
				dma->regs = DMA1_Stream2;
				DMA_IRQn = DMA1_Stream2_IRQn;
				break;
			}
			case 3:{
				dma->regs = DMA1_Stream3;
				DMA_IRQn = DMA1_Stream3_IRQn;
				break;
			}
			case 4:{
				dma->regs = DMA1_Stream4;
				DMA_IRQn = DMA1_Stream4_IRQn;
				break;
			}
			case 5:{
				dma->regs = DMA1_Stream5;
				DMA_IRQn = DMA1_Stream5_IRQn;
				break;
			}
			case 6:{
				dma->regs = DMA1_Stream6;
				DMA_IRQn = DMA1_Stream6_IRQn;
				break;
			}
			case 7:{
				dma->regs = DMA1_Stream7;
				DMA_IRQn = DMA1_Stream7_IRQn;
				break;
			}
			default:{
				return;
			}
			
		}
		
	}
		
	else if(dma->n==2){
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;	
		switch(dma->stream){
			case 0:{
				dma->regs = DMA2_Stream0;
				DMA_IRQn = DMA2_Stream0_IRQn;
				break;
			}
			case 1:{
				dma->regs = DMA2_Stream1;
				DMA_IRQn = DMA2_Stream1_IRQn;
				break;
			}
			case 2:{
				dma->regs = DMA2_Stream2;
				DMA_IRQn = DMA2_Stream2_IRQn;
				break;
			}
			case 3:{
				dma->regs = DMA2_Stream3;
				DMA_IRQn = DMA2_Stream3_IRQn;
				break;
			}
			case 4:{
				dma->regs = DMA2_Stream4;
				DMA_IRQn = DMA2_Stream4_IRQn;
				break;
			}
			case 5:{
				dma->regs = DMA2_Stream5;
				DMA_IRQn = DMA2_Stream5_IRQn;
				break;
			}
			case 6:{
				dma->regs = DMA2_Stream6;
				DMA_IRQn = DMA2_Stream6_IRQn;
				break;
			}
			case 7:{
				dma->regs = DMA2_Stream7;
				DMA_IRQn = DMA2_Stream7_IRQn;
				break;
			}
			default:{
				return;
			}
			
		}
	}
	else return;

	/* Stream and Channel */
	dma->regs->CR = 0U;
	while(dma->regs->CR != 0U){}
	dma->regs->CR |= (dma->ch<<DMA_SxCR_CHSEL_Pos);
	
	/* M0AR, M1AR, PAR NDTR*/
	dma->regs->M0AR = dma->m0ar;
	dma->regs->M1AR = dma->m1ar;
	dma->regs->PAR  = dma->par;
	dma->regs->NDTR = dma->ndtr;
		
	/* Size, Priority and Increment */
	dma->regs->CR |= ((uint32_t)dma->psize << DMA_SxCR_PSIZE_Pos) | ((uint32_t)dma->msize << DMA_SxCR_MSIZE_Pos);
	dma->regs->CR |= DMA_SxCR_PL_Msk;
	dma->regs->CR |= (dma->pinc << DMA_SxCR_PINC_Pos) | (dma->minc << DMA_SxCR_MINC_Pos);
	dma->regs->FCR = 0U;
	
	/* Direction */
	dma->regs->CR |= ((uint32_t)dma->dir << DMA_SxCR_DIR_Pos);
	
	/* CIRC */
	dma->regs->CR |= (dma->circ << DMA_SxCR_CIRC_Pos);
	
	/* DBM */
	dma->regs->CR |= (dma->dbm << DMA_SxCR_DBM_Pos);
	
	/* IRQ */
	dma->regs->CR |= (dma->htie << DMA_SxCR_HTIE_Pos) | (dma->tcie << DMA_SxCR_TCIE_Pos);
	if(dma->htie || dma->tcie)
		NVIC_EnableIRQ(DMA_IRQn);
	
	/* Enable */
	if(dma->en)
		dma->regs->CR |= DMA_SxCR_EN;
}
void DMA_Reload(DMA_t* dma){	
	dma->regs->CR &= ~DMA_SxCR_EN;
	while(dma->regs->CR & DMA_SxCR_EN){}
	/* M0AR, M1AR, PAR NDTR*/
	dma->regs->M0AR = dma->m0ar;
	dma->regs->M1AR = dma->m1ar;
	dma->regs->PAR  = dma->par;
	dma->regs->NDTR = dma->ndtr;
}
void DMA_Enable(DMA_t* dma){	
	dma->regs->CR |= DMA_SxCR_EN;
}
void DMA_Disable(DMA_t* dma){	
	dma->regs->CR &= ~DMA_SxCR_EN;
}
