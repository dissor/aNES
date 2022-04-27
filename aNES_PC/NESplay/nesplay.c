#include "nesplay.h"

//加载游戏,开始玩
int8_t load_nes(uint8_t *path)
{
    FILE *fp = NULL;

    // 1.采用二进制方式"rb"打开，才能获取整个文件
    fp = fopen(path, "rb");
    if (fp == NULL)
    {
        printf("open %s error!\n", path);
        return -1;
    }
    printf("open %s successful!\n", path);

    // 2.获取文件大小
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    rewind(fp);
    printf("size: %d\n", size);

    // 3.分配内存空间
    char *buf = (char *)malloc(sizeof(char) * size);
    if (buf == NULL)
    {
        fclose(fp);
        printf("Memory error!\n");
        return -2;
    }
    printf("Memory successful!\n");

    // 4.拷贝文件到内存
    size_t len = fread(buf, sizeof(char), size, fp);
    if (len != size)
    {
        fclose(fp);
        free(buf);
        printf("Read error!%d\n", len);
        return -3;
    }
    printf("Read successful!\n");

    // 5.运行功能
    // printf("%s\n", buf);
    // nes_main();

    fclose(fp);
    free(buf);
    return 0;
}

// NES游戏
uint8_t nes_play(void)
{
    load_nes("../Images/0.demo.nes"); //开始nes游戏
    // load_nes("../NES/README.TXT");
    return 0;
}
