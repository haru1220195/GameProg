#include "DxLib.h"
#include "hed.h"
#include <math.h>
int ga[100];
int ga2[50];

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	ChangeWindowMode(TRUE); 
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	ga[1]=LoadGraph("�摜/back.png");
	ga[7]=LoadGraph("�摜/back2.png");
	LoadDivGraph("�摜/titlemenu.png",3,1,3,122,42,&ga[2]);
	LoadDivGraph("�摜/titlemenu2.png",24,2,12,150,40,&ga[8]);
	LoadDivGraph("�摜/field.png",20,4,5,80,50,&ga[34]);
	start(ga);
	while(1){
		if(ProcessMessage()!=0){
			break;
		}
		ClearDrawScreen();
		mainloop(ga,ga2);
		ScreenFlip();
	}
	DxLib_End();    // DX���C�u�����I������
	return 0;
}


