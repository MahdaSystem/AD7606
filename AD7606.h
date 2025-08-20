/**
  ******************************************************************************
  * File Name          : AD7606.h
  * Description        : AD7606 ADC Driver header file.
	* Last Update				 : 09-06-2022
	*	Author						 : Mohammad Sayadi
	* E-Mail						 : mo.sayadi@gmail.com
  ******************************************************************************
  *
  * Copyright (c) 2022 Mahda Embedded Systems 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of Mahda Embedded Systems nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for Mahda Embedded Systems.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY "MAHDA EMBEDDED SYSTEMS" AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL "MAHDA EMBEDDED SYSTEMS" OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AD7606_H
#define __AD7606_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdint.h>
#include <stdbool.h>
#include "NopDelay.h"

/* Private define ------------------------------------------------------------*/
typedef struct Struct_AD7606Handler
{
  void (*ADC_CS_HIGH)(void);               // Must be initialized
  void (*ADC_CS_LOW)(void);                // Must be initialized
  void (*ADC_START_HIGH)(void);            // If you don't want to use software start, the START pin must be pulled down then pass this as NULL
  void (*ADC_START_LOW)(void);             // If you don't want to use software start, the START pin must be pulled down then pass this as NULL
  void (*ADC_RESET_HIGH)(void);            // If you want to use software reset, the RESET pin must be pulled up then pass this as NULL
  void (*ADC_RESET_LOW)(void);             // If you want to use software reset, the RESET pin must be pulled up then pass this as NULL
  void (*ADC_Receive)(uint8_t*, uint32_t); // Must be initialized
  uint8_t (*ADC_DRDY_Read)(void);          // Can be initialized
  void (*ADC_Delay_US)(uint32_t);          // If you want to use Macro delay, you have to enable - define, Otherwise This function must be initialized!
} Type_AD7606Handler;

/* Functions -----------------------------------------------------------------*/
void AD7606_Init(Type_AD7606Handler* adcHandler);
void AD7606_ConvertStart(Type_AD7606Handler* adcHandler);
void AD7606_Read(Type_AD7606Handler* adcHandler, int16_t* data);

#endif /* __AD7606_H */
/************************ (C) COPYRIGHT MAHDA EMBEDDED SYSTEMS *****END OF FILE****/
