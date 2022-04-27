
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#define JOYPAD_0 0
#define JOYPAD_1 1

#include "nes_main.h"

extern uint8_t JOY_key; // 保存键值

typedef struct
{
    uint8_t state;  //状态
    uint8_t index;  //当前读取位
    uint32_t value; // JoyPad 当前值
} JoyPadType;

/* function ------------------------------------------------------------------*/
void NES_JoyPadInit(void);
void NES_JoyPadReset(void);
void NES_JoyPadDisable(void);
uint8_t NES_GetJoyPadVlaue(int JoyPadNum);

#endif
