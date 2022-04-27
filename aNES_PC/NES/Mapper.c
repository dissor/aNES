#include "Mapper.h"
// #include "Waves'NES.h"
// #include "Mapper000.h"
#include "Mapper002.h"

MAPPER NES_Mapper;
void Mapper_Init(void)
{
    NES_Mapper.Reset = Mapper_Reset;
    NES_Mapper.Write = Mapper_Write;
    NES_Mapper.Read = Mapper_Read;
    NES_Mapper.WriteLow = Mapper_WriteLow;
    NES_Mapper.ReadLow = Mapper_ReadLow;
    NES_Mapper.ExWrite = Mapper_ExWrite;
    NES_Mapper.ExRead = Mapper_ExRead;
    NES_Mapper.ExCmdRead = Mapper_ExCmdRead;
}

bool CreateMapper(int no)
{
    Mapper_Init();
    switch (no)
    {
    case 0:
        Mapper000_Init();
        break;
    case 2:
        Mapper002_Init();
        break;
    default:
        break;
    }
    return true;
}

void Mapper_Reset(void) {}

uint8_t Mapper_ReadLow(uint16_t addr)
{
    if (addr >= 0x6000 && addr <= 0x7FFF)
        return CPU_MEM_BANK[addr >> 13][addr & 0x1FFF];
    return (uint8_t)(addr >> 8);
}

void Mapper_WriteLow(uint16_t addr, uint8_t data)
{
    if (addr >= 0x6000 && addr <= 0x7FFF)
        CPU_MEM_BANK[addr >> 13][addr & 0x1FFF] = data;
}

void Mapper_Write(uint16_t addr, uint8_t data) {}

void Mapper_Read(uint16_t addr, uint8_t data) {}

uint8_t Mapper_ExRead(uint16_t addr)
{
    return 0x00;
}

void Mapper_ExWrite(uint16_t addr, uint8_t data) {}

uint8_t Mapper_ExCmdRead()
{
    return 0x00;
}
