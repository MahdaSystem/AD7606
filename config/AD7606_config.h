/**
  ******************************************************************************
  * File Name          : AD7606_config.h
  * Description        : AD7606 ADC Driver config header file.
	* Last Update				 : 20-Aug-2025
	*	Author						 : Hossein.M
	* Github						 : https://github.com/Hossein-M98
  ******************************************************************************
  *
  * Copyright (c) 2025 Mahda Embedded Systems 
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
#ifndef __AD7606_CONFIG_H
#define __AD7606_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#define USE_MACRO_DELAY      0 // 0: Use handler delay ,So you have to set ADC_Delay_US in Handler | 1: use Macro delay, So you have to set MACRO_DELAY_US Macro
#define MACRO_DELAY_US(x)    My_Delay_us(x) // If you want to use Macro delay, place your delay function in microseconds here



#endif /* __AD7606_CONFIG_H */
/************************ (C) COPYRIGHT MAHDA EMBEDDED SYSTEMS *****END OF FILE****/