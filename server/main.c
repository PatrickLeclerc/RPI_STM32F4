#include "nucleo.h"
volatile uint32_t tim2_flag = 0;

int main(){
	/* Basic */
	ACSU_Init(180U);
	RTC_Init();
	LED_Init();
	CP_Init(115200);	
    nucleo_printf("\033c");
	nucleo_printf("ACSU     : OK.\r\n");
	nucleo_printf("RTC      : OK.\r\n");
	nucleo_printf("LED      : OK.\r\n");
	nucleo_printf("COMPORT  : OK.\r\n");
    /*Peripherals*/
	//TIM
    TIM_t tim2 = {
		.n		= 2,
		.psc	= (180/2)*100 -1,
		.arr	= 9999, //1MHz
		.urs	= 1,
		.uie	= 1};
	TIM_Init(&tim2);
	nucleo_printf("TIM2     : OK.\r\n");
	//SPI
	nucleo_spi_init();
	nucleo_printf("SPI1     : OK.\r\n");
	
	while(1){
		if(tim2_flag){
			char time[8];
			RTC_GetBCD(time);
			nucleo_printf("\033c");//Clear
			nucleo_printf(time);nucleo_printf("\r\n");//Print time
			tim2_flag = 0;
		}	
		if(spirx_flag){
			static int i = 0;
			if(i++&1)
				LED_ON();
			else
				LED_OFF();
			spirx_flag = 0;
		}
	}
}
//TIM2
void TIM2_IRQHandler()
{
	if(TIM2->SR & TIM_SR_UIF){
		TIM2->SR &= ~TIM_SR_UIF;
		tim2_flag = 1;
	}
}
