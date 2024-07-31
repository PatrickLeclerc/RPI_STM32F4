#include "gpio.h"
void GPIO_Init(GPIO_t* gpio){
	/* RCC */
	switch(gpio->port){
		case 'A':{
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
			gpio->regs = GPIOA;
			break;
		}
		case 'B':{
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
			gpio->regs = GPIOB;
			break;
		}
		case 'C':{
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
			gpio->regs = GPIOC;
			break;
		}
		case 'D':{
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
			gpio->regs = GPIOD;
			break;
		}
		default : return;
	}
	
	/* MODER and OSPEEDR */
	for(int i = 0; i < 16; i++)
		if((gpio->pins>>i)&1U){
			//Clear
			gpio->regs->MODER 		&= ~(3U	<<(i*2));
			gpio->regs->OSPEEDR		&= ~(3U <<(i*2));
			gpio->regs->AFR[i>=8]	&= ~(15U	<<((i%8)*4));
			//Set
			gpio->regs->MODER 		|= (uint32_t)gpio->mode		<<(i*2);
			gpio->regs->OSPEEDR 	|= (uint32_t)gpio->speed	<<(i*2);
			gpio->regs->AFR[i>=8]	|= gpio->af					<<((i%8)*4);
		}
	gpio->regs->ODR = 0;
}