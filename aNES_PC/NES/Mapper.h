#ifndef _MAPPER_H_
#define _MAPPER_H_
// #include "mytype.h"
#include "nes_main.h"

typedef struct
{
    void (*Reset)();
    void (*Write)(uint16_t addr, uint8_t data);
    void (*Read)(uint16_t addr, uint8_t data);
    uint8_t (*ReadLow)(uint16_t addr);
    void (*WriteLow)(uint16_t addr, uint8_t data);
    uint8_t (*ExRead)(uint16_t addr);
    void (*ExWrite)(uint16_t addr, uint8_t data);
    uint8_t (*ExCmdRead)();
} MAPPER;

extern MAPPER NES_Mapper;

void Mapper_Init(void);
bool CreateMapper(int no);
extern void Mapper_Reset(void);
void Mapper_Write(uint16_t addr, uint8_t data);
void Mapper_Read(uint16_t addr, uint8_t data);
uint8_t Mapper_ReadLow(uint16_t addr);
void Mapper_WriteLow(uint16_t addr, uint8_t data);
uint8_t Mapper_ExRead(uint16_t addr);
void Mapper_ExWrite(uint16_t addr, uint8_t data);
uint8_t Mapper_ExCmdRead(void);

#endif
