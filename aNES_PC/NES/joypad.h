
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#define JOYPAD_0 0
#define JOYPAD_1 1

#include "nes_main.h"

extern uint8_t JOY_key; // �����ֵ

typedef struct
{
    uint8_t state;  //״̬
    uint8_t index;  //��ǰ��ȡλ
    uint32_t value; // JoyPad ��ǰֵ
} JoyPadType;

/* function ------------------------------------------------------------------*/
void NES_JoyPadInit(void);
void NES_JoyPadReset(void);
void NES_JoyPadDisable(void);
uint8_t NES_GetJoyPadVlaue(int JoyPadNum);

#endif
