/*
 * @Author: dissor
 * @Date: 2022-04-28 10:58:24
 * @LastEditors: dissor
 * @LastEditTime: 2022-04-30 00:42:43
 * @FilePath: \aNES_PC\main.c
 * @Description:
 * guojianwenjonas@foxmail.com
 * Copyright (c) 2022 by dissor, All Rights Reserved.
 */

#include "main.h"
#include "nesplay.h"

HWND hwnd = NULL; //窗口句柄
int cxClient, cyClient;
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
        671,                 //窗口宽度
        359,                 //窗口高度
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

    static BITMAPFILEHEADER *pbmfh;
    static BITMAPINFO *pbmi;
    static BYTE *pBits;
    static int cxDib, cyDib;

    switch (message)
    {
    case WM_CREATE:
        _beginthread(GameThread, 0, NULL);

        // pbmfh = DibLoadImage("C:/Users/mylk/Desktop/NES/aNES/aNES_PC/0.bmp");
        // if (pbmfh == NULL)
        // {
        //     printf("DibLoadImage error!\n");
        //     return;
        // }

        FILE *file = NULL;
        file = fopen("C:/Users/mylk/Desktop/NES/aNES/aNES_PC/0.bmp", "rb");

        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        rewind(file);
        printf("size: %d\n", size);

        pbmfh = malloc(size);
        fread(pbmfh, 1, size, file);

        //获得信息头和像素位指针
        pbmi = (BITMAPINFO *)(pbmfh + 1);
        pBits = (BYTE *)pbmfh + pbmfh->bfOffBits;

        //获取图像大小(为方便，这里只处理BITMAPINFOHEADER结构的DIB）
        cxDib = pbmi->bmiHeader.biWidth;
        cyDib = abs(pbmi->bmiHeader.biHeight); //绝对值！
        return 0;

    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        return 0;

    //窗口绘制消息
    case WM_PAINT:
        // hdc = BeginPaint(hwnd, &ps);
        hdc = GetDC(hwnd); // GetWindowDC

        memset(pBits, 205, 60000);
        for (int i = 0; i < 655 * 50; i += 3)
        {
            *((char *)pBits + i) = 120;   // B
            *((char *)pBits + i + 1) = 0; // G
            *((char *)pBits + i + 2) = 0; // R
        }

        //从下到上DIB整图显示
        SetDIBitsToDevice(hdc,
                          0,
                          0,     // yDst
                          cxDib, //整幅图宽度
                          cyDib, //整幅图高度
                          0,
                          0,
                          0,     //第一扫描线
                          cyDib, //扫描线数量
                          pBits,
                          pbmi,
                          DIB_RGB_COLORS);

        ReleaseDC(hwnd, hdc);
        // EndPaint(hwnd, &ps);
        return 0;

    //窗口销毁消息
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

void GameThread(void *pMessage)
{
    nes_play();

    HBRUSH hBrush;
    HDC hdc;
    int xLeft, xRight, yTop, yBottom, iRed, iGreen, iBlue;

    while (TRUE)
    {
        if (cxClient != 0 || cyClient != 0)
        {
            xLeft = rand() % cxClient;
            xRight = rand() % cxClient;
            yTop = rand() % cyClient;
            yBottom = rand() % cyClient;

            iRed = rand() & 255; //取出最低位8位
            iGreen = rand() & 255;
            iBlue = rand() & 255;

            hdc = GetDC(hwnd);
            hBrush = CreateSolidBrush(RGB(iRed, iGreen, iBlue));
            SelectObject(hdc, hBrush);

            Rectangle(hdc, min(xLeft, xRight), min(yTop, yBottom),
                      max(xLeft, xRight), max(yTop, yBottom));

            DeleteObject(hBrush);
            ReleaseDC(hwnd, hdc);
        }
    }
}

BITMAPFILEHEADER *DibLoadImage(PTSTR pstrFileName)
{
    BOOL bSuccess;
    DWORD dwFileSize, dwHighSize, dwBytesRead;
    HANDLE hFile;
    BITMAPFILEHEADER *pbmfh;

    hFile = CreateFile(pstrFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
                       OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return NULL;
    //返回文件大小的低位字，保存在dwFileSize中，高位字保存在dwHighSize中
    dwFileSize = GetFileSize(hFile, &dwHighSize);
    if (dwHighSize) //文件太大，超过4G则dwHighSize不为0，退出
    {
        CloseHandle(hFile);
        return NULL;
    }
    //为位图文件分配内存，内存指针由文件头指针保管
    pbmfh = malloc(dwFileSize);
    if (!pbmfh)
    {
        CloseHandle(hFile);
        return NULL;
    }
    //读位图文件到内存
    bSuccess = ReadFile(hFile, pbmfh, dwFileSize, &dwBytesRead, NULL);
    CloseHandle(hFile);
    if ((!bSuccess) || (dwBytesRead != dwFileSize) ||
        (pbmfh->bfType != *(WORD *)"BM") || //位图标志“BM”
        (pbmfh->bfSize != dwFileSize))
    {
        free(pbmfh);
        return NULL;
    }
    return pbmfh;
}