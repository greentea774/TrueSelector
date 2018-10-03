#include "DxLib.h"
#include "resource.h"
#include "SceneMgr.h"
#include "Game.h"
#include "Game_Hard.h"
#include "BGM.h"
#include "Menu.h"
#include <math.h>


#define PI 3.141592654f
int den3,dden3,Maoukon, counter=0,FpsTime[2]={0,},FpsTime_i=0;
double Fps=0.0;
//���[�v�ŕK���s���R�又��
int ProcessLoop(){
	if(ProcessMessage()!=0)return -1;//�v���Z�X�������G���[�Ȃ�-1��Ԃ�
	if(ClearDrawScreen()!=0)return -1;//��ʃN���A�������G���[�Ȃ�-1��Ԃ�
	return 0;
}

void Main_Load(){
	den3 = LoadGraph( "Graph/den3.png" );
	dden3 = LoadGraph( "Graph/01den3.png" );
	Maoukon = LoadGraph("Graph/Maoukon.png");
}

void FpsTimeFanction(){
        if(FpsTime_i== 0)
                FpsTime[0]=GetNowCount();               //1���ڂ̎��Ԏ擾
        if(FpsTime_i==49){
                FpsTime[1]=GetNowCount();               //50���ڂ̎��Ԏ擾
                Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//���肵���l����fps���v�Z
                FpsTime_i=0;//�J�E���g��������
        }
        else
                FpsTime_i++;//���݉����ڂ��J�E���g
        if(Fps != 0)
                DrawFormatString(540,450,GetColor(255,255,255),"FPS %.1f",Fps); //fps��\��
        return;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
    SetWindowIconID( ID_ICON ); SetMainWindowText("�N�C�Y�Q�[��"); ChangeWindowMode(TRUE); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	if(DxLib_Init() == -1 || SetDrawScreen( DX_SCREEN_BACK )!=0) return -1;//�������Ɨ���ʉ�
	SetFontSize( 20 ) ;                             //�T�C�Y��20�ɕύX
    SetFontThickness( 1 ) ;                         //������1�ɕύX
    ChangeFont( "HGS�n�p�p�߯�ߑ�" ) ;              //HGS�n�p�p�߯�ߑ̂ɕύX
	ChangeFontType( DX_FONTTYPE_ANTIALIASING );     //�A���`�G�C���A�X�t�H���g�ɕύX
	int Flag = 0, Time = 0, star =0, Mouse = GetMouseInput();

		if(Time == 0){// �I�[�v�j���O
			Game_Load();
			Game_Hard_Load();
			Menu_Load();
			Main_Load();
			BGM_Load();
			BGM_OP();
			for(Time=0;Time<=150;Time++){
				ClearDrawScreen();
				DrawGraph( 0, 0, den3, TRUE );
				DrawGraph( 200, 415, Maoukon, TRUE );
				DrawRotaGraph(500-star*2.4 , 240+sin(PI*2/120*star)*120, 1.0, 0.0, dden3, TRUE );
				ScreenFlip();
				if(star>=120){
				star = 120;
				}else{
				star++;
				}
			}
		}

    while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && SetMouseDispFlag(FALSE)==0){//��ʍX�V & ���b�Z�[�W���� & ��ʏ���

		if(Flag == 0){ //�ŏ��̈���BGM�𗬂�
			BGM_Update(); //BGM���X�V
			Flag = 1;
			}
			//�I������
		if(CheckHitKey(KEY_INPUT_ESCAPE)!=0){//Esc�L�[��������Ă�����
			break; //�I��
		}

        SceneMgr_Update();  //�X�V
		ClearDrawScreen(); // ��ʂ�����
        SceneMgr_Draw();    //�`��
		FpsTimeFanction(); //fps�\��
    }
        
    DxLib_End(); // DX���C�u�����I������
    return 0;
}