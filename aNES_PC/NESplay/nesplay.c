#include "nesplay.h"
#include "nes_main.h"
#include "nes_rom.h"
#include "gui.h"
//////////////////////////////////////////////////////////////////////////////////
//�ҵ� STM32������
// APP-NESģ���� ����
//�޸�����:2012/10/3
//�汾��V1.0
//////////////////////////////////////////////////////////////////////////////////

u8 *rom_file;
// const u8* nes_caption_tbl[GUI_LANGUAGE_NUM]={"NESģ����","NESģ�M��","NES Emulator",};

//������Ϸ����
// void nes_load_ui(void)
//{
//	app_filebrower((u8*)nes_caption_tbl[gui_phy.language],0X05);//��ʾ����
//  	gui_fill_rectangle(0,20,240,300,BLACK);				//����ɫ
//}
//Ƶ������
// PLL,��Ƶ��
void nes_clock_set(u8 PLL)
{
    u8 tPLL = PLL;
    u8 temp = 0;
    RCC->CFGR &= 0XFFFFFFFC;   //�޸�ʱ��Ƶ��Ϊ�ڲ�8M
    RCC->CR &= ~0x01000000;    // PLLOFF
    RCC->CFGR &= ~(0XF << 18); //���ԭ��������
    PLL -= 2;                  //����2����λ
    RCC->CFGR |= PLL << 18;    //����PLLֵ 2~16
    RCC->CFGR |= 1 << 16;      // PLLSRC ON
    FLASH->ACR |= 0x12;        // FLASH 2����ʱ����
    RCC->CR |= 0x01000000;     // PLLON
    while (!(RCC->CR >> 25))
        ;                //�ȴ�PLL����
    RCC->CFGR |= 0x02;   // PLL��Ϊϵͳʱ��
    while (temp != 0x02) //�ȴ�PLL��Ϊϵͳʱ�����óɹ�
    {
        temp = RCC->CFGR >> 2;
        temp &= 0x03;
    }
    //˳��������ʱ�ʹ���
    delay_init(tPLL * 8);      //��ʱ��ʼ��
    uart_init(tPLL * 8, 9600); //����1��ʼ��
}

//////////////////////////////////

//������Ϸ,��ʼ��
void load_nes(u8 *path)
{
    u8 res;
    u32 len;
    u16 i;
    FIL *f_nes;
    u8 *p;
    //	u16 tpad_temp=tpad_default_val;
    LCD_Clear(WHITE);                             //����
                                                  //	nes_load_ui();
    f_nes = (FIL *)gui_memin_malloc(sizeof(FIL)); //����FIL�ֽڵ��ڴ�����
    if (f_nes == NULL)
        return;                                        //����ʧ��
    res = f_open(f_nes, (const TCHAR *)path, FA_READ); //���ļ���
    if (res == 0)
    {
        rom_file = gui_memin_malloc(f_nes->fsize); //����f_nes->fsize�ֽڵ��ڴ�����
        if (rom_file)
        {
            p = rom_file;
            for (len = 0; len < f_nes->fsize; len += 512)
            {
                f_read(f_nes, fatbuf, 512, &br); //��ȡ�ļ�
                for (i = 0; i < br; i++)         //���Ƶ�SRAM����
                {
                    *p = fatbuf[i];
                    p++;
                }
                if (br != 512)
                    break;
            }
        }
        else
            res = 1; //����ʧ��
        f_close(f_nes);
    }
    gui_memin_free(f_nes); //�ͷ��ڴ�
    if (res == 0)
    {
        // 		nes_clock_set(16);			//����Ϊ128M ��Ƶ�˵� Σ��
        // 		delay_init(128);			//����Ϊ128M ��Ƶ�˵� Σ��
        //		tpad_default_val=(tpad_default_val*16/9)+1;
        nes_main();
        //		tpad_default_val=tpad_temp;
        // 		nes_clock_set(9);			//����Ϊ72M
        // 		delay_init(72);
    }
    gui_memin_free(rom_file);
}

// NES��Ϸ
u8 nes_play(void)
{
    //  	DIR nesdir;		//nesdirר��
    FILINFO nesinfo;
    //	u8 res;
    u8 rval = 0; //����ֵ
    u8 *pname = 0;
    //	u8 *fn;

    // 	_btn_obj* rbtn;		//���ذ�ť�ؼ�
    //  	_filelistbox_obj * flistbox;
    //	_filelistbox_list * filelistx; 	//�ļ�

    //	JOYPAD_Init();
    //	app_filebrower((u8*)APP_MFUNS_CAPTION_TBL[6][gui_phy.language],0X07);	//ѡ��Ŀ���ļ�,���õ�Ŀ������
    //   	flistbox=filelistbox_creat(0,20,240,280,1,12);		//����һ��filelistbox
    //	if(flistbox==NULL)rval=1;							//�����ڴ�ʧ��.
    //	else
    //	{
    //		flistbox->fliter=FLBOX_FLT_NES;	//�����ļ�
    // 		filelistbox_addlist(flistbox,(u8*)APP_DISK_NAME_TBL[0][gui_phy.language],0);		//����0
    //		filelistbox_addlist(flistbox,(u8*)APP_DISK_NAME_TBL[1][gui_phy.language],0);		//����1
    //		filelistbox_draw_listbox(flistbox);
    //	}
    //
    //	//Ϊ���ļ������뻺����
    // 	nesinfo.lfsize = _MAX_LFN * 2 + 1;
    //	nesinfo.lfname = gui_memin_malloc(nesinfo.lfsize);
    //	if(nesinfo.lfname==NULL)rval=1;//�����ڴ�ʧ��
    //   	else gui_memset((u8*)nesinfo.lfname,0,nesinfo.lfsize);
    //
    //	rbtn=btn_creat(199,300,40,19,0,0x03);//�������ְ�ť
    //	if(rbtn==NULL)rval=1;	//û���㹻�ڴ湻����

    //   	while(rval==0)
    //	{
    //		tp_dev.scan(0);
    //		in_obj.get_key(&tp_dev,IN_TYPE_TOUCH);	//�õ�������ֵ
    //		delay_ms(5);
    //		if(system_task_return)break;	  		//TPAD����
    // 		filelistbox_check(flistbox,&in_obj);	//ɨ���ļ�
    //		res=btn_check(rbtn,&in_obj);
    //		if(res)
    //		{
    //			if(((rbtn->sta&0X80)==0))//��ť״̬�ı���
    //			{
    //				if(flistbox->dbclick!=0X81)
    //				{
    // 					filelistx=filelist_search(flistbox->list,flistbox->selindex);//�õ���ʱѡ�е�list����Ϣ
    //					if(filelistx->type==FICO_DISK)//�Ѿ�������������
    //					{
    //						break;
    //					}else filelistbox_back(flistbox);//�˻���һ��Ŀ¼
    //				}
    // 			}
    //		}
    //		if(flistbox->dbclick==0X81)//˫���ļ���
    //		{
    //     		rval=f_opendir(&nesdir,(const TCHAR*)flistbox->path); //��ѡ�е�Ŀ¼
    //			if(rval)break;
    //			dir_sdi(&nesdir,flistbox->findextbl[flistbox->selindex-flistbox->foldercnt]);
    //	 		rval=f_readdir(&nesdir,&nesinfo);//��ȡ�ļ���Ϣ
    //			if(rval)break;//�򿪳ɹ�
    //			fn=(u8*)(*nesinfo.lfname?nesinfo.lfname:nesinfo.fname);
    //			pname=gui_memin_malloc(strlen((const char*)fn)+strlen((const char*)flistbox->path)+2);//�����ڴ�
    //			if(pname==NULL)rval=1;//����ʧ��
    //			{
    //				pname=gui_path_name(pname,flistbox->path,fn);	//�ļ�������·��
    // 				LCD_Clear(0X0);//����
    // 				FSMC_Bank1E->BWTR[6]|=2<<0; 			//��ַ����ʱ�䣨ADDSET��Ϊ3��HCLK
    // 				FSMC_Bank1E->BWTR[6]|=3<<8; 		 	//���ݱ���ʱ�䣨ADDSET��Ϊ4��HCLK
    // 				//SRAM����
    //				FSMC_Bank1->BTCR[5]|=6<<8; 				//���ݱ���ʱ�䣨DATAST��Ϊ7��HCLK 7/128M=55ns

    //			load_nes(pname);	//��ʼnes��Ϸ
    load_nes("0:/NES/��������.nes"); //��ʼnes��Ϸ
                                     //				LCD_Clear(BLACK);	//����

    // 			}
    //			flistbox->dbclick=0;	//���÷��ļ����״̬
    //			gui_memin_free(pname);	//�ͷ��ڴ�
    //		    pname=NULL;
    //			delay_ms(100);
    //			filelistbox_rebuild_filelist(flistbox);//�ؽ�flistbox
    // 			system_task_return=0;//�ո��˳����������Ϸ,�������˳����ѭ��
    //		}
    //	}
    gui_memin_free(pname); //�ͷ��ڴ�
    gui_memin_free(nesinfo.lfname);
    return rval;
}
