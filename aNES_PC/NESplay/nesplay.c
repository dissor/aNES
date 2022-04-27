#include "nesplay.h"

//������Ϸ,��ʼ��
int8_t load_nes(uint8_t *path)
{
    FILE *fp = NULL;

    // 1.���ö����Ʒ�ʽ"rb"�򿪣����ܻ�ȡ�����ļ�
    fp = fopen(path, "rb");
    if (fp == NULL)
    {
        printf("open %s error!\n", path);
        return -1;
    }
    printf("open %s successful!\n", path);

    // 2.��ȡ�ļ���С
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    rewind(fp);
    printf("size: %d\n", size);

    // 3.�����ڴ�ռ�
    char *buf = (char *)malloc(sizeof(char) * size);
    if (buf == NULL)
    {
        fclose(fp);
        printf("Memory error!\n");
        return -2;
    }
    printf("Memory successful!\n");

    // 4.�����ļ����ڴ�
    size_t len = fread(buf, sizeof(char), size, fp);
    if (len != size)
    {
        fclose(fp);
        free(buf);
        printf("Read error!%d\n", len);
        return -3;
    }
    printf("Read successful!\n");

    // 5.���й���
    // printf("%s\n", buf);
    // nes_main();

    fclose(fp);
    free(buf);
    return 0;
}

// NES��Ϸ
uint8_t nes_play(void)
{
    load_nes("../Images/0.demo.nes"); //��ʼnes��Ϸ
    // load_nes("../NES/README.TXT");
    return 0;
}
