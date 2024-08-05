#ifndef USART_H
#define USART_H
#include "drivers_common.h"
/*enums*/
//...

/*Structs*/
typedef struct __attribute__((__packed__)) USART{
	USART_TypeDef *		regs;
	uint32_t 			n;
	uint32_t			br;
	uint32_t			rxe;
	uint32_t			txe;
	uint32_t			rxie;
	uint32_t			txie;
	uint32_t			dmaRxE;
	uint32_t			dmaTxE;
}USART_t;
/*Functions*/
void USART_Init(USART_t* usart);
#endif