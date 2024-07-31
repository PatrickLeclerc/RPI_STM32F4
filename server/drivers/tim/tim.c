#include "tim.h"

void TIM_Init(TIM_t* tim){
	/* RCC */
	uint32_t TIM_IRQn;
	switch(tim->n){
		//APB1
		case 2:{
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
			tim->regs = TIM2;
			TIM_IRQn = TIM2_IRQn;
			break;
		}
		case 3:{
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
			tim->regs = TIM3;
			TIM_IRQn = TIM3_IRQn;
			break;
		}
		case 4:{
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
			tim->regs = TIM4;
			TIM_IRQn = TIM4_IRQn;
			break;
		}
		case 5:{
			RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
			tim->regs = TIM5;
			TIM_IRQn = TIM5_IRQn;
			break;
		}
		case 6:{
			RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
			tim->regs = TIM6;
			TIM_IRQn = TIM6_DAC_IRQn;
			break;
		}
		case 7:{
			RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
			tim->regs = TIM7;
			TIM_IRQn = TIM7_IRQn;
			break;
		}
		//APB2
		case 1:{
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			tim->regs = TIM1;
			TIM_IRQn = TIM1_UP_TIM10_IRQn;
			break;
		}
		case 8:{
			RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
			tim->regs = TIM8;
			TIM_IRQn = TIM8_UP_TIM13_IRQn;
			break;
		}
		default: return;
	}

	/* TIM */
	tim->regs->CR1 = TIM_CR1_ARPE;
	if(tim->urs)
		tim->regs->CR1 |= TIM_CR1_URS;
	tim->regs->PSC = tim->psc;
	tim->regs->ARR = tim->arr;
	tim->regs->CNT = 0U;
	
	/* Master */
	tim->regs->CR1 |= (tim->mms << TIM_CR2_MMS_Pos) | (tim->ccds << TIM_CR2_CCDS_Pos);
	
	/* Slave */
	tim->regs->SMCR |= (tim->ts << TIM_SMCR_TS_Pos) | (tim->sms << TIM_SMCR_SMS_Pos);
	
	/* NVIC and DMA */
	if(tim->uie){
		tim->regs->DIER |= TIM_DIER_UIE | TIM_DIER_UDE;
		NVIC_EnableIRQ(TIM_IRQn);
	}
	/*Update registers */
	tim->regs->EGR |= TIM_EGR_UG;

	/* Enable */
	tim->regs->CR1 |= TIM_CR1_CEN;
	
	
}