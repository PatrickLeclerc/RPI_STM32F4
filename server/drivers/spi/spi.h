#ifndef SPI_H
#define SPI_H
#include "drivers_common.h"

/*enums*/
typedef enum SPI_BR{
	SPI_BR_FPDIV2 = 0,
	SPI_BR_FPDIV4,
	SPI_BR_FPDIV8,
	SPI_BR_FPDIV16,
	SPI_BR_FPDIV32,
	SPI_BR_FPDIV64,
	SPI_BR_FPDIV128,
	SPI_BR_FPDIV256
}SPI_BR_t;

/*Structs*/
typedef struct __attribute__((__packed__)) SPI{
	SPI_TypeDef *		regs;
	uint32_t 			n;
	SPI_BR_t			br;
	uint32_t			rxe;
	uint32_t			txe;
	uint32_t			rxie;
	uint32_t			txie;
	uint32_t			dmaRxE;
	uint32_t			dmaTxE;
}SPI_t;
/*Functions*/
void SPI_Init(SPI_t* spi);

#endif
