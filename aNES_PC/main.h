/*
 * @Author: dissor
 * @Date: 2022-04-26 12:22:45
 * @LastEditors: dissor
 * @LastEditTime: 2022-04-30 17:10:09
 * @FilePath: \aNES_PC\main.h
 * @Description:
 * guojianwenjonas@foxmail.com
 * Copyright (c) 2022 by dissor, All Rights Reserved.
 */
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <process.h>

BITMAPFILEHEADER *DibLoadImage(PTSTR pstrFileName);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void GameThread(void* pMessage);
void setdmp(int yline, uint16_t *dwPixel, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
