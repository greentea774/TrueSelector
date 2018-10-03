#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "BGM.h"
#include <math.h>

#define PI 3.141592654f

	int x, y,BackM,BackM2,MouseB,KarsolM,Title,Title2,MaskT,MaskT2,MaskOver;
	int Countm = 0, Countc = 0, FlagT = 1, CountM = 0;

void Menu_Load(){
	 BackM = LoadGraph( "Graph/backM.png" ); // �w�i
	 BackM2 = LoadGraph( "Graph/backM2.png" ); // �w�i
	 KarsolM = LoadGraph( "Graph/karsol.png" ); // �}�E�X�J�[�\��
	 Title = LoadGraph( "Graph/title.png" ); // �^�C�g��
	 Title2 = LoadGraph( "Graph/title2.png" ); // �^�C�g��2
	 MaskT = LoadGraph( "Graph/Menu_maskray.png" ); //��
	 MaskT2 = LoadGraph( "Graph/Menu_maskray2.png" ); //��2
	 MaskOver = LoadMask( "Graph/MaskOver.png" ); // �}�X�N�摜
}

//�X�V
void Menu_Update(){
	int Mouse = GetMouseInput();
	Countc++; Countm++;
	if(Countm>=20){
    if(Mouse & MOUSE_INPUT_LEFT && 9<x && 296>x && 379<y && 456>y && FlagT==1){//��ʂ̃X�^�[�g��������Ă�����
		CountM = 1;
	}
	if((Mouse & MOUSE_INPUT_LEFT) && (9>x || 296<x || 379>y || 456<y) && FlagT==1 && CountM==1){//�̈旣�ꔻ��
		CountM = 0;
	}
	if(!(Mouse & MOUSE_INPUT_LEFT) && 9<x && 296>x && 379<y && 456>y && FlagT==1 && CountM==1){
		StopBGM_M(); BGM_start(); Countm=0; CountM=0; Click();
        SceneMgr_ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
		BGM_ChangeBGM(eBGM_Game);
		BGM_Update(); //BGM���X�V
	  }
	 if(Mouse & MOUSE_INPUT_LEFT && 9<x && 296>x && 379<y && 456>y && FlagT==2){//��ʂ̃X�^�[�g��������Ă�����
		StopBGM_M(); BGM_start(); Countm=0;
        SceneMgr_ChangeScene(eScene_Game_Hard);//�V�[�����Q�[����ʂɕύX
		BGM_ChangeBGM(eBGM_Game);
		BGM_Update(); //BGM���X�V
	  }
    if(Mouse & MOUSE_INPUT_LEFT && 334<x && 621>x && 379<y && 456>y && Countc>10){//��ʂ̂����Ă���������Ă�����
		//StopBGM_M(); BGM_start(); Countm=0;
        //SceneMgr_ChangeScene(eScene_Config);//�V�[����ݒ��ʂɕύX
		//BGM_ChangeBGM(eBGM_Config);
		//BGM_Update(); //BGM���X�V
		BGM_False(); Countc=0;
    }
	if((Mouse & MOUSE_INPUT_LEFT) && (Mouse & MOUSE_INPUT_RIGHT) && 41<x && 561>x && 0<y && 181>y && FlagT==1){//��ʂ̃^�C�g���������ꂽ��
		FlagT =2; BGM_TitleDark();
	}else if(Mouse & MOUSE_INPUT_LEFT && 41<x && 561>x && 0<y && 181>y && FlagT==2){//��ʂ̃^�C�g���������ꂽ��
		FlagT =1; 
	}
	}
}

//�`��
void Menu_Draw(){
	GetMousePoint(&x,&y);

	if(Countm == 800){
		IAvoiceOP();
		Countm = 0;
	}

	if(FlagT==2){
	DrawGraph( 0, 0, BackM2, TRUE );
	DrawGraph( 50, 0, Title2, TRUE );//�^�C�g��
	CreateMaskScreen();     // �}�X�N��������
    DrawMask( 0, 0, MaskOver, DX_MASKTRANS_BLACK ); // �������݂̂�`��̈��
    DrawRotaGraph ( Countm*2, 120, 1.0, 0, MaskT2 , TRUE);
    DeleteMaskScreen(); // �}�X�N�����܂�
	}else if(FlagT==1){
	DrawGraph( 0, 0, BackM, TRUE );
	DrawGraph( 50, 0, Title, TRUE );//�^�C�g��
	CreateMaskScreen();     // �}�X�N��������
    DrawMask( 0, 0, MaskOver, DX_MASKTRANS_BLACK ); // �������݂̂�`��̈��
    DrawRotaGraph ( Countm*2, 120, 1.0, 0, MaskT , TRUE);
    DeleteMaskScreen(); // �}�X�N�����܂�
	}

	GetMousePoint(&x,&y);
	//DrawFormatString(400,200,GetColor(255,255,255),"�J�[�\�����W%d , %d",x,y);//�f�o�b�O�p
    DrawGraph( x, y, KarsolM, TRUE );

}