#ifndef RTC_H
#define RTC_H
#include "drivers_common.h"

void RTC_Init( void );
void RTC_GetBCD(char* time);
void RTC_GetNUM(int* time);

#endif
