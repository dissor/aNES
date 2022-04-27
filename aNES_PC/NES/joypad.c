#include "nes_main.h"
#include "joypad.h"
// #include "usart.h" // 串口
// #include "key.h"

uint8_t JOY_key = 0xFF;
JoyPadType JoyPad[2];

uint8_t NES_GetJoyPadVlaue(int JoyPadNum) //  得到手柄脉冲
{
    uint8_t retval = 0;
    if (JoyPadNum == 0)
    {
        retval = (JOY_key >> JoyPad[0].index) & 0X01;
        if (JoyPad[0].index == 20)
            retval = 1; // 20位表示控制器在位.
        // printf("\r\n 按键: %d",re val);  //我写的代码 测试用
        JoyPad[0].index++;
    }
    return retval;
}
//读取手柄按键值.
// FC手柄数据输出格式:
//每给一个脉冲,输出一位数据,输出顺序:
// A->B->SELECT->START->UP->DOWN->LEFT->RIGHT.
//总共8位,对于有C按钮的手柄,按下C其实就等于A+B同时按下.
//按下是0,松开是1.
//[0]:右  0--->7
//[1]:左
//[2]:下
//[3]:上
//[4]:Start
//[5]:Select
//[6]:B
//[7]:A
void NES_JoyPadReset(void)
{
    JoyPad[0].state = 1;
    JoyPad[0].index = 0;
    // JOY_key=0xFF-((右  <<7)|(左  <<6)|(下  <<5)|(上  <<4)|Start<<3)|Select<<2)|(B  <<1)|A   );
    // JOY_key = 0xFF - ((KEY5 << 7) | (KEY3 << 6) | (0X01 << 5) | (0X01 << 4) | (KEY1 << 3) | (KEY2 << 2) | (0X01 << 1) | KEY4);
    // JOYPAD_LAT=1;//   锁存一下
    //  JOYPAD_LAT=0;

    JoyPad[1].state = 1;
    JoyPad[1].index = 0;
}

void NES_JoyPadInit(void)
{
    JoyPad[0].state = 0; //状态为0,表示禁止
    JoyPad[0].index = 0;
    JoyPad[0].value = 1 << 20;

    JoyPad[1].state = 0;
    JoyPad[1].index = 0;
    JoyPad[1].value = 1 << 19;
}

void NES_JoyPadDisable(void)
{
}
