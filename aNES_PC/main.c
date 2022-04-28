/*
 * @Author: dissor
 * @Date: 2022-04-28 10:58:24
 * @LastEditors: dissor
 * @LastEditTime: 2022-04-28 11:45:45
 * @FilePath: \aNES_PC\main.c
 * @Description:
 * guojianwenjonas@foxmail.com
 * Copyright (c) 2022 by dissor, All Rights Reserved.
 */

#include "main.h"
#include "nesplay.h"

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
    static TCHAR szClassName[] = TEXT("Hello Windows Classic"); //窗口类名
    HWND hwnd;                                                  //窗口句柄
    MSG msg;                                                    //消息
    WNDCLASS wndclass;                                          //窗口类

    /**********第1步：注册窗口类**********/
    //为窗口类的各个字段赋值
    wndclass.style = CS_HREDRAW | CS_VREDRAW;                     //窗口风格
    wndclass.lpfnWndProc = WndProc;                               //窗口过程
    wndclass.cbClsExtra = 0;                                      //暂时不需要理解
    wndclass.cbWndExtra = 0;                                      //暂时不需要理解
    wndclass.hInstance = hInstance;                               //当前窗口句柄
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);             //窗口图标
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);               //鼠标样式
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //窗口背景画刷
    wndclass.lpszMenuName = NULL;                                 //窗口菜单
    wndclass.lpszClassName = szClassName;                         //窗口类名
    RegisterClass(&wndclass);                                     //注册窗口

    /*****第2步：创建窗口(并让窗口显示出来)*****/
    hwnd = CreateWindow(
        szClassName,         //窗口类的名字
        TEXT("aNES_PC"),     //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW, //窗口风格
        CW_USEDEFAULT,       //初始化时x轴的位置
        CW_USEDEFAULT,       //初始化时y轴的位置
        500,                 //窗口宽度
        300,                 //窗口高度
        NULL,                //父窗口句柄
        NULL,                //窗口菜单句柄
        hInstance,           //当前窗口的句柄
        NULL                 //不使用该值
    );

    //显示窗口
    ShowWindow(hwnd, nCmdShow);

    //更新（绘制）窗口
    UpdateWindow(hwnd);

    /**********第3步：消息循环**********/
    // GetMessage 函数用来从消息队列中获取一条消息，并保存到 MSG 结构体变量
    // GetMessage 每获取到一条消息，最终都会丢给窗口过程（WndProc）去处理。
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); //翻译消息
        DispatchMessage(&msg);  //分派消息
    }

    return msg.wParam;
    // nes_play();
    return 0;
}

/**********第4步：窗口过程**********/
/**
 * GetMessage 每获取到一条消息，最终都会丢给窗口过程（WndProc）去处理
 * 窗口过程有一个参数 message，会传入发生的事件类型，常用的有：
 *      WM_CREATE：窗口被创建。
 *      WM_PAINT：窗口需要更新或重绘。
 *      WM_WM_DESTROY：窗口被销毁（关闭）。
 * @param hwnd
 * @param message
 * @param wParam
 * @param lParam
 * @return
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc; //设备环境句柄
    PAINTSTRUCT ps;
    RECT rect;

    switch (message)
    {
    //窗口绘制消息
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
        DrawText(
            hdc,
            TEXT("Hello World!"),
            -1,
            &rect,
            DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
        return 0;

        //窗口销毁消息
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}