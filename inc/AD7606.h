/**
  ******************************************************************************
  * File Name          : AD7606.h
  * Description        : AD7606 ADC Driver header file.
	* Last Update				 : 26-Dec-2020
	*	Author						 : Mohammad Sayadi
	* E-Mail						 : mo.sayadi@gmail.com
  ******************************************************************************
  *
  * Copyright (c) 2020 Mahda Embedded Systems 
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
#include "stm32f7xx_hal.h"
#include "main.h"
#include <stdint.h>
#include <stdbool.h>
/* Private define ------------------------------------------------------------*/
enum Enum_AD7606_OverSampling {
	AD7606_OverSampling_NoOS = 0x00,
  AD7606_OverSampling_2 = 0x01,
  AD7606_OverSampling_4 = 0x02,
  AD7606_OverSampling_8 = 0x03,
  AD7606_OverSampling_16 = 0x04,
  AD7606_OverSampling_32 = 0x05,
  AD7606_OverSampling_64 = 0x06,
  AD7606_OverSampling_Invalid = 0x07,
};
typedef enum Enum_AD7606_OverSampling Type_AD7606_OverSampling;

enum Enum_AD7606_Range {
	AD7606_Range_5V = 0x00,
  AD7606_Range_10 = 0x01,
};
typedef enum Enum_AD7606_Range Type_AD7606_Range;

/* Functions -----------------------------------------------------------------*/
void AD7606_Init(uint8_t cardCount, bool OS1, bool OS2, bool range);
void AD7606_Read_OneCard(uint8_t cardNo, int16_t * data);
void AD7606_Read_All(int16_t * data);

#endif /* __AD7606_H */
/************************ (C) COPYRIGHT MAHDA EMBEDDED SYSTEMS *****END OF FILE****/
