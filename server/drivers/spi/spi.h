#ifndef SPI_H
#define SPI_H
#include "drivers_common.h"

/*enums*/
//...

/*Structs*/
typedef struct __attribute__((__packed__)) SPI{
	SPI_TypeDef *		regs;
	uint32_t 			n;
	uint32_t			br;
	uint32_t			rxie;
	uint32_t			txie;
	uint32_t			dmaRxE;
	uint32_t			dmaTxE;
}SPI_t;
/*Functions*/
void SPI_Init(SPI_t* spi);

#endif
