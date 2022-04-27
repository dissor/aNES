#include "nes_main.h"

// #include "malloc.h"
// #include "key.h"


// uint8_t nesruning = 0; //初始化为真
// uint8_t frame_cnt;     //统计帧数
// // uint8_t  *rom_file;          //NES游戏rom的存储地址
// // NES 帧周期循环
// void NesFrameCycle(void)
// {
//     int clocks; // CPU执行时间
//     //启动模拟器循环，检查VROM设置，若卡带为0，初始化VROM
//     // if ( NesHeader.byVRomSize == 0)
//     //设置VROM存储区位置。
//     frame_cnt = 0;
//     nesruning = 1;
//     while (nesruning)
//     {
//         // scanline: 0~19 VBANK 段，若PPU使能NMI，将产生NMI 中断
//         frame_cnt++; //帧计数器
//         SpriteHitFlag = FALSE;
//         for (PPU_scanline = 0; PPU_scanline < 20; PPU_scanline++)
//         {
//             exec6502(CLOCKS_PER_SCANLINE);
//         }
//         // scanline: 20, PPU加载设置，执行一次空的扫描时间
//         exec6502(CLOCKS_PER_SCANLINE);
//         // NesHBCycle();  //水平周期
//         PPU_scanline++; // 20++
//         PPU_Reg.NES_R2 &= ~R2_SPR0_HIT;
//         // scanline: 21~261
//         for (; PPU_scanline < SCAN_LINE_DISPALY_END_NUM; PPU_scanline++)
//         {
//             if ((SpriteHitFlag == TRUE) && ((PPU_Reg.NES_R2 & R2_SPR0_HIT) == 0))
//             {
//                 clocks = sprite[0].x * CLOCKS_PER_SCANLINE / NES_DISP_WIDTH;
//                 exec6502(clocks); //需重点优化
//                 PPU_Reg.NES_R2 |= R2_SPR0_HIT;
//                 exec6502(CLOCKS_PER_SCANLINE - clocks);
//             }
//             else
//                 exec6502(CLOCKS_PER_SCANLINE); //耗时大户

//             if (PPU_Reg.NES_R1 & (R1_BG_VISIBLE | R1_SPR_VISIBLE)) //若为假，关闭显示
//             {
//                 if (SpriteHitFlag == FALSE)
//                     NES_GetSpr0HitFlag(PPU_scanline - SCAN_LINE_DISPALY_START_NUM); //查找Sprite #0 碰撞标志
//             }
//             if ((frame_cnt % 3) == 0) //每3帧显示一次	   //耗时大户
//             {
//                 NES_RenderLine(PPU_scanline - SCAN_LINE_DISPALY_START_NUM); //水平同步与显示一行
//             }
//         }
//         // scanline: 262 完成一帧
//         exec6502(CLOCKS_PER_SCANLINE);
//         PPU_Reg.NES_R2 |= R2_VBlank_Flag; //设置VBANK 标志
//         //若使能PPU VBANK中断，则设置VBANK
//         if (PPU_Reg.NES_R0 & R0_VB_NMI_EN)
//         {
//             NMI_Flag = SET1; //完成一帧扫描，产生NMI中断
//         }
//         //设置帧IRQ标志，同步计数器，APU等
//         // A mapper function in V-Sync 存储器切换垂直VBANK同步
//         // MapperVSync();
//         //读取控制器JoyPad状态,更新JoyPad控制器值*/
//         // NES_JoyPadUpdateValue();	 //systick 中断读取按键值

//         //单独的返回键（KEY6）扫描程序
//         if (KEY_Scan_f())
//             break; //退出 //退出模拟器
//     }
// }

//返回值:0,执行OK;
//	  其他,错误代码
uint8_t nes_main(char *rom_file)
{
    uint16_t offset = 0;
    uint8_t res;
    NesHeader *neshreader = (NesHeader *)rom_file;

    // 1.判断文件类型，NES文件以NES(4EH 45H 53H)开始。
    if (strncmp(neshreader->filetype, "NES", 3) != 0)
    {
        printf("\r\n文件未加载或文件类型错误, NES模拟器退出。");
        return 1;
    }
    else
    {
        printf("\r\n文件加载完成。");
        printf("\r\n  16kB  ROM 的数目: %d", neshreader->romnum);
        printf("\r\n   8kB VROM 的数目: %d", neshreader->vromnum);
        if ((neshreader->romfeature & 0x01) == 0)
        {
            printf("\r\n  水平镜像");
        }
        else
        {
            printf("\r\n  垂直镜像");
        }

        if ((neshreader->romfeature & 0x02) == 0)
        {
            printf("\r\n  无记忆SRAM");
        }
        else
        {
            printf("\r\n  有记忆SRAM");
        }

        if ((neshreader->romfeature & 0x04) == 0)
        {
            printf("\r\n  无512字节的trainer($7000-$71FF)");
        }
        else
        {
            offset = 512;
            printf("\r\n  有512字节的trainer(ROM格式暂不支持)");
        }

        if ((neshreader->romfeature & 0x08) == 0)
        {
            printf("\r\n  2屏幕VRAM布局");
        }
        else
        {
            printf("\r\n  4屏幕VRAM布局(暂不支持)");
        }

        printf("\r\n  iNES Mapper Numbers: %d", (neshreader->rommappernum & 0xF0) | (neshreader->romfeature >> 4));
    }
    res = nes_mem_creat(); //申请内存
    if (res == 0)          //申请成功了.则运行游戏
    {
        // //初始化nes 模拟器
        // init6502mem(0,                                                                                               // exp_rom
        //             0,                                                                                               // sram 由卡类型决定, 暂不支持
        //             ((uint8_t *)&rom_file[offset + 0x10]),                                                                // prg_rombank, 存储器大小 由卡类型决定
        //             neshreader->romnum);                                                                             //初始化6502存储器镜像
        // reset6502();                                                                                                 //复位
        // PPU_Init(((uint8_t *)&rom_file[offset + 0x10] + (neshreader->romnum * 0x4000)), (neshreader->romfeature & 0x01)); // PPU_初始化
        // NES_JoyPadInit();
        // NesFrameCycle(); //模拟器循环执行
    }
    nes_mem_delete(); //释放内存
    return res;
}


//开辟nes运行所需的RAM.
//返回值:0,成功;
//    其他,错误代码.
uint8_t nes_mem_creat(void)
{
    // ram6502 = (uint8_t *)mymalloc(2048); //申请2K内存
    // if (ram6502 == NULL)
    //     return 1;                     //申请失败
    // NameTable = (uint8_t *)mymalloc(2048); //申请2K内存
    // if (NameTable == NULL)
    //     return 2;
    // Buffer_scanline = (uint16_t *)mymalloc((8 + 256 + 8) * 2);
    // if (Buffer_scanline == NULL)
    //     return 3;
    return 0;
}

//删除nes运行时申请的RAM
void nes_mem_delete(void)
{
    // myfree(ram6502);
    // myfree(NameTable);
    // myfree(Buffer_scanline);
}
