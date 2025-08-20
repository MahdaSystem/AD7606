#include "AD7606.h"

#define USE_MACRO_DELAY      0                              // 0: Use handler delay ,So you have to set ADC_Delay_US in Handler | 1: use Macro delay, So you have to set MACRO_DELAY_US Macro
#define MACRO_DELAY_US(x)    Delay_us(x)                    // If you want to use Macro delay, place your delay function in microseconds here

// Delay configuration: (DO NOT EDIT THIS BLOCK)
#if USE_MACRO_DELAY == 0
#define Delay_US(x)   adcHandler->ADC_Delay_US(x)
#else
#define Delay_US(x)   MACRO_DELAY_US(x)
#ifndef MACRO_DELAY_US
#error "MACRO_DELAY_US is not defined. Please Use handler delay or config MACRO_DELAY_US macro, You can choose it on USE_MACRO_DELAY define"
#endif
#endif

/*
  RESET high pulse width 50ns
  Minimum CONVST low pulse 25ns
  Minimum CONVST high pulse 25ns
  Delay from CS until DOUT three-state disabled/delay from CS until MSB valid: 35ns
*/

typedef union Union_Int16 // cuz bug
{
  int16_t Int16;
  uint16_t Uint16;
	struct
  {
    uint8_t Part1;
    uint8_t Part2;
	};
	uint8_t Array[2];
} Type_Int16;

//static uint8_t tempAdcDataHolder[16] = { 0 };
static volatile Type_Int16 tempAdcDataHolder[8] = { 0 };

/* Functions ------------------------------------------------------------------------------------ */
void AD7606_Init(Type_AD7606Handler* adcHandler)
{
  if (!adcHandler)
    return;

  adcHandler->ADC_CS_HIGH();

  adcHandler->ADC_RESET_LOW();
  Delay_US(10);
	adcHandler->ADC_RESET_HIGH();
	Delay_US(10);
	adcHandler->ADC_RESET_LOW();
	Delay_US(10);
	
	adcHandler->ADC_START_LOW();
	Delay_US(1);
}
void AD7606_ConvertStart(Type_AD7606Handler* adcHandler)
{
  adcHandler->ADC_START_LOW();
  Delay_US(1);
	adcHandler->ADC_START_HIGH();
}
void AD7606_Read(Type_AD7606Handler* adcHandler, int16_t* data)
{
  adcHandler->ADC_CS_LOW();
  Delay_US(1);
  adcHandler->ADC_Receive((uint8_t*)tempAdcDataHolder, sizeof(int16_t) * 8);
  adcHandler->ADC_CS_HIGH();
  Delay_US(1);

  Type_Int16* pData = (Type_Int16*)data;

  pData[0].Part1 = tempAdcDataHolder[0].Part2;
  pData[0].Part2 = tempAdcDataHolder[0].Part1;

  pData[1].Part1 = tempAdcDataHolder[1].Part2;
  pData[1].Part2 = tempAdcDataHolder[1].Part1;
  
  pData[2].Part1 = tempAdcDataHolder[2].Part2;
  pData[2].Part2 = tempAdcDataHolder[2].Part1;

  pData[3].Part1 = tempAdcDataHolder[3].Part2;
  pData[3].Part2 = tempAdcDataHolder[3].Part1;

  pData[4].Part1 = tempAdcDataHolder[4].Part2;
  pData[4].Part2 = tempAdcDataHolder[4].Part1;

  pData[5].Part1 = tempAdcDataHolder[5].Part2;
  pData[5].Part2 = tempAdcDataHolder[5].Part1;

  pData[6].Part1 = tempAdcDataHolder[6].Part2;
  pData[6].Part2 = tempAdcDataHolder[6].Part1;

  pData[7].Part1 = tempAdcDataHolder[7].Part2;
  pData[7].Part2 = tempAdcDataHolder[7].Part1;
}
