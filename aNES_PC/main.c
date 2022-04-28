/*
 * @Author: dissor
 * @Date: 2022-04-28 10:58:24
 * @LastEditors: dissor
 * @LastEditTime: 2022-04-28 11:25:39
 * @FilePath: \aNES_PC\main.c
 * @Description:
 * guojianwenjonas@foxmail.com
 * Copyright (c) 2022 by dissor, All Rights Reserved.
 */

#include "main.h"
#include "nesplay.h"
#include <windows.h>

/**
 * @description: 桌面程序主入口
 * @param {HINSTANCE} hInstance 当前窗口句柄
 * @param {HINSTANCE} hPrevInstance NULL
 * @param {LPSTR} lpCmdLine 命令行参数
 * @param {int} nCmdShow 窗口显示方式
 * @return {*}
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 父窗口句柄、内容、标题、按钮图标
    int nSelect = MessageBox(NULL, TEXT("hello world!"), TEXT("Welcome"), MB_OKCANCEL);

    if (nSelect == IDOK)
    {
        MessageBox(NULL, TEXT("确认"), TEXT("提示"), MB_OK);
    }
    else
    {
        MessageBox(NULL, TEXT("取消"), TEXT("提示"), MB_OK);
    }
    printf("hello world!\r\n");
    // nes_play();
    return 0;
}