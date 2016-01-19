#pragma once
#include "includes.h"

#define USART1_BUF_SIZE			40

void USART1_Init(void);
void Send_Char(u8 Char);
void Send_String(uint8_t *pData,char len);