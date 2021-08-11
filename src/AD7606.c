/**
  ******************************************************************************
  * File Name          : AD7606.c
  * Description        : AD7606 ADC Driver source file.
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

#include "AD7606.h"
		
static uint8_t ad7606_CardCount = 0;
static uint8_t __for__AD7606_Read_OneCard = 0;
static uint8_t __for__AD7606_Read_All = 0;

/* Consider MS3 as 0 always. Temporary
  Actually the MS3 is the 8th bit.
  -------------------------------------------------
  |  b7 |  b6 |  b5 |  b4 | b3  | b2  | b1  | b0  |
  | MS3 | MS2 | MS1 | MS0 |  X  |  X  |  X  |  X  |
  -------------------------------------------------
                         |||
  -------------------------------------------------
  |  b7 |  b6 |  b5 |  b4 | b3  | b2  | b1  | b0  |
  |  X  | MS2 | MS1 | MS0 |  X  |  X  |  X  |  X  |
  -------------------------------------------------
  */
static uint32_t bsrr_for_mcs[16] = {
  /*   ACTIVATED  1 */ 0x700000, // 0xF00000
  /*   ACTIVATED  2 */ 0x600010, // 0xE00010
  /*   ACTIVATED  3 */ 0x500020, // 0xD00020
  /*   ACTIVATED  4 */ 0x400030, // 0xC00030
  /*   ACTIVATED  5 */ 0x300040, // 0xB00040
  /*   ACTIVATED  6 */ 0x200050, // 0xA00050
  /*   ACTIVATED  7 */ 0x100060, // 0x900060
  /*   ACTIVATED  8 */ 0x000070, // 0x800070
  /* DEACTIVATED  9 */ 0x000000, // 0x700080
  /* DEACTIVATED 10 */ 0x000000, // 0x600090
  /* DEACTIVATED 11 */ 0x000000, // 0x5000A0
  /* DEACTIVATED 12 */ 0x000000, // 0x4000B0
  /* DEACTIVATED 13 */ 0x000000, // 0x3000C0
  /* DEACTIVATED 14 */ 0x000000, // 0x2000D0
  /* DEACTIVATED 15 */ 0x000000, // 0x1000E0
  /* DEACTIVATED 16 */ 0x000000, // 0x0000F0
};

#define _AD7606_SELECT_CARD(x) AD7606_MS0_GPIO_Port->BSRR = bsrr_for_mcs[x]

static uint32_t _AD7606_MCS_BSRR_HIGH = (uint32_t)AD7606_MCS_Pin;
static uint32_t _AD7606_MCS_BSRR_LOW  = (uint32_t)AD7606_MCS_Pin << 16;
#define _AD7606_MCS_HIGH() AD7606_MCS_GPIO_Port->BSRR = _AD7606_MCS_BSRR_HIGH
#define _AD7606_MCS_LOW()  AD7606_MCS_GPIO_Port->BSRR = _AD7606_MCS_BSRR_LOW

static uint32_t _AD7606_RDSCLK_BSRR_HIGH = (uint32_t)AD7606_RDSCLK_Pin;
static uint32_t _AD7606_RDSCLK_BSRR_LOW  = (uint32_t)AD7606_RDSCLK_Pin << 16;
#define _AD7606_RDSCLK_HIGH() AD7606_RDSCLK_GPIO_Port->BSRR = _AD7606_RDSCLK_BSRR_HIGH
#define _AD7606_RDSCLK_LOW()  AD7606_RDSCLK_GPIO_Port->BSRR = _AD7606_RDSCLK_BSRR_LOW

static uint32_t _AD7606_CONVST_BSRR_HIGH = (uint32_t)AD7606_CONVST_Pin;
static uint32_t _AD7606_CONVST_BSRR_LOW  = (uint32_t)AD7606_CONVST_Pin << 16;
#define _AD7606_CONVST_HIGH() AD7606_CONVST_GPIO_Port->BSRR = _AD7606_CONVST_BSRR_HIGH
#define _AD7606_CONVST_LOW()  AD7606_CONVST_GPIO_Port->BSRR = _AD7606_CONVST_BSRR_LOW

static uint32_t _AD7606_RESET_BSRR_HIGH = (uint32_t)AD7606_RESET_Pin;
static uint32_t _AD7606_RESET_BSRR_LOW  = (uint32_t)AD7606_RESET_Pin << 16;
#define _AD7606_RESET_HIGH() AD7606_RESET_GPIO_Port->BSRR = _AD7606_RESET_BSRR_HIGH
#define _AD7606_RESET_LOW()  AD7606_RESET_GPIO_Port->BSRR = _AD7606_RESET_BSRR_LOW

static uint32_t _AD7606_RANGE_BSRR_HIGH = (uint32_t)AD7606_RANGE_Pin;
static uint32_t _AD7606_RANGE_BSRR_LOW  = (uint32_t)AD7606_RANGE_Pin << 16;
#define _AD7606_RANGE_HIGH() AD7606_RANGE_GPIO_Port->BSRR = _AD7606_RANGE_BSRR_HIGH
#define _AD7606_RANGE_LOW()  AD7606_RANGE_GPIO_Port->BSRR = _AD7606_RANGE_BSRR_LOW

static uint32_t _AD7606_OS1_BSRR_HIGH = (uint32_t)AD7606_OS1_Pin;
static uint32_t _AD7606_OS1_BSRR_LOW  = (uint32_t)AD7606_OS1_Pin << 16;
#define _AD7606_OS1_HIGH() AD7606_OS1_GPIO_Port->BSRR = _AD7606_OS1_BSRR_HIGH
#define _AD7606_OS1_LOW()  AD7606_OS1_GPIO_Port->BSRR = _AD7606_OS1_BSRR_LOW

static uint32_t _AD7606_OS2_BSRR_HIGH = (uint32_t)AD7606_OS2_Pin;
static uint32_t _AD7606_OS2_BSRR_LOW  = (uint32_t)AD7606_OS2_Pin << 16;
#define _AD7606_OS2_HIGH() AD7606_OS2_GPIO_Port->BSRR = _AD7606_OS2_BSRR_HIGH
#define _AD7606_OS2_LOW()  AD7606_OS2_GPIO_Port->BSRR = _AD7606_OS2_BSRR_LOW

#define _AD7606_IS_BUSY() (((AD7606_BUSY_GPIO_Port->IDR & AD7606_BUSY_Pin) != (uint32_t)GPIO_PIN_RESET) ? (0) : (1))

#define _AD7606_READ_LOW()  ((AD7606_D0_GPIO_Port->IDR >> 8) & 0x00FF)
#define _AD7606_READ_HIGH() ((AD7606_D8_GPIO_Port->IDR << 8) & 0xFF00)

#define _AD7606_Delay_Init()
#define _AD7606_DELAY() __nop(); __nop(); __nop(); __nop()
#define _AD7606_DELAY_2X() _AD7606_DELAY(); _AD7606_DELAY()
#define _AD7606_DELAY_4X() _AD7606_DELAY_2X(); _AD7606_DELAY_2X()
#define _AD7606_DELAY_6X() _AD7606_DELAY_2X(); _AD7606_DELAY_2X(); _AD7606_DELAY_2X()
#define _AD7606_DELAY_8X() _AD7606_DELAY_4X(); _AD7606_DELAY_4X()

/* Functions ------------------------------------------------------------------------------------ */
void AD7606_Init(uint8_t cardCount, bool OS1, bool OS2, bool range) {
	_AD7606_Delay_Init();
	ad7606_CardCount = cardCount;

  if(OS1) _AD7606_OS1_HIGH(); else _AD7606_OS1_LOW();
  if(OS2) _AD7606_OS2_HIGH(); else _AD7606_OS2_LOW();
  
  if(range) _AD7606_RANGE_HIGH(); else _AD7606_RANGE_LOW();
  
	_AD7606_RESET_HIGH();
	_AD7606_DELAY_4X();
	_AD7606_RESET_LOW();
	_AD7606_DELAY_4X();
	
	_AD7606_CONVST_HIGH();
	_AD7606_DELAY_4X();
  
	_AD7606_RDSCLK_HIGH();
	_AD7606_DELAY_4X();
}
void AD7606_Read_OneCard(uint8_t cardNo, int16_t * data) {
	_AD7606_SELECT_CARD(cardNo);
	_AD7606_MCS_LOW();
	_AD7606_DELAY_4X();
	for(__for__AD7606_Read_OneCard = 0; __for__AD7606_Read_OneCard < 8; __for__AD7606_Read_OneCard++) {				
		_AD7606_RDSCLK_LOW();
		_AD7606_DELAY_6X();
    data[__for__AD7606_Read_OneCard] = _AD7606_READ_HIGH() | _AD7606_READ_LOW();
		_AD7606_RDSCLK_HIGH();
		_AD7606_DELAY_6X();
	}
	_AD7606_MCS_HIGH();
  _AD7606_DELAY_4X();
}
void AD7606_Read_All(int16_t * data) {
	for(__for__AD7606_Read_All = 0 ; __for__AD7606_Read_All < ad7606_CardCount ; __for__AD7606_Read_All++) {
		AD7606_Read_OneCard(__for__AD7606_Read_All, &data[__for__AD7606_Read_All * 8]);
  }
	_AD7606_CONVST_LOW();
	_AD7606_DELAY_8X();
	_AD7606_CONVST_HIGH();
}
