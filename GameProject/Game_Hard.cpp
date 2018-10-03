#include "Game_Hard.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "BGM.h"

int NumberH=1, SelectH=0, CountH=0, CountCH=0;
int BackH,MaruH,BatuH,KarsolH,kazuH[10],TimeH;
struct quiz_data_h{
	int Ans;
	char String1[256];
	char String2[256];
} quiz_data_H[QUIZ_HARD_MAX];

void Game_Hard_Load(){
	int  fpH, nH;//Time�̓��[�h�p
	char tmpH[256];
	fpH= FileRead_open("dat/quizhard.txt");//�t�@�C���ǂݍ���
			if(fpH == NULL){
                printfDx("read error\n");
                return;
			}
			//�N�C�Y�ǂݍ���
			for(nH=0;nH<QUIZ_HARD_MAX;nH++){
			FileRead_gets(quiz_data_H[nH].String1, 50, fpH );
			FileRead_gets(quiz_data_H[nH].String2, 50, fpH );
			FileRead_gets(tmpH, 256, fpH );
			quiz_data_H[nH].Ans = atoi(tmpH);
			}
			FileRead_close(fpH);

	BackH = LoadGraph( "Graph/back.png" ); //�w�i
	MaruH = LoadGraph( "Graph/Maru.png" ); //�Z
	BatuH = LoadGraph( "Graph/Batu.png" ); //�~
	KarsolH = LoadGraph( "Graph/karsol.png" ); // �}�E�X�J�[�\��
	LoadDivGraph( "Graph/kazu.png" , 10 , 10 , 1 , 45 , 70 , kazuH ); // �摜�̕����ǂݍ���.��
	//kazu��0��1���A1��2���A9��0���݂����Ɋi�[����Ă���

}

void Game_Hard_Update(){
	int Mouse = GetMouseInput();
	int xH=0,yH=0;
	GetMousePoint(&xH,&yH);

	CountH++; TimeH++;
	if(CountH==61){
	if(Mouse & MOUSE_INPUT_LEFT && 10<xH && 210>xH && 280<yH && 480>yH){
		SelectH = 2;
	}
	if(Mouse & MOUSE_INPUT_LEFT && 230<xH && 410>xH && 280<yH && 480>yH){
		SelectH = 2;
	}
	if(NumberH<=5 && ( SelectH==1 || SelectH==2)){//��ւ������Ȃ�
		if(SelectH==quiz_data_H[NumberH].Ans){//�����Ȃ��
			BGM_True(); NumberH+=1; SelectH=0; CountH=0; TimeH=0;
		}else{
			BGM_False(); NumberH+=1; SelectH=0; CountH=0; TimeH=0;
		}}
	}

	//3,5��ڂ͉��ł�������Č�������˂̂Ƃ���Ȃ̂ŁA�������Ԃ����炳�Ȃ��悤�ɂ���
	if(NumberH==3 || NumberH==5){
		TimeH = 62;
	}

	if(TimeH==661){
		BGM_False(); NumberH+=1; SelectH=0; CountH=0; TimeH=0;
	}

	if(NumberH==12){//�Ō�܂ŏI�������
		StopBGM_G(); BGM_GoMenu(); SelectH=0; NumberH=1; CountH=0; TimeH=0;
        SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
		BGM_ChangeBGM(eBGM_Menu);
		BGM_Update(); //BGM���X�V
	}

	CountCH++;
	if(Mouse & MOUSE_INPUT_LEFT && CountCH>10){//�N���b�N��
		Click(); CountCH=0;
	}

}

//�`��
void Game_Hard_Draw(){
	int xH, yH;
	GetMousePoint(&xH,&yH);

    DrawGraph( 0, 0, BackH, TRUE );//�w�i
	DrawFormatString( 595, 170, GetColor(255,138,0), "��");
	DrawFormatString( 30, 70, GetColor(255,255,255), "���");

	//��������
	if(NumberH<=10){
	if(TimeH>=121 && TimeH<=180){//9
		DrawGraph( 330, 170, kazuH[8], TRUE );
	}else if(TimeH>=61 && TimeH<=120){//10
		DrawGraph( 290, 170, kazuH[0], TRUE );
		DrawGraph( 330, 170, kazuH[9], TRUE );
	}else if(TimeH>=181 && TimeH<=240){//8
		DrawGraph( 330, 170, kazuH[7], TRUE );
	}else if(TimeH>=241 && TimeH<=300){//7
		DrawGraph( 330, 170, kazuH[6], TRUE );
	}else if(TimeH>=301 && TimeH<=360){//6
		DrawGraph( 330, 170, kazuH[5], TRUE );
	}else if(TimeH>=361 && TimeH<=420){//5
		DrawGraph( 330, 170, kazuH[4], TRUE );
	}else if(TimeH>=421 && TimeH<=480){//4
		DrawGraph( 330, 170, kazuH[3], TRUE );
	}else if(TimeH>=481 && TimeH<=540){//3
		DrawGraph( 330, 170, kazuH[2], TRUE );
	}else if(TimeH>=541 && TimeH<=600){//2
		DrawGraph( 330, 170, kazuH[1], TRUE );
	}else if(TimeH>=601 && TimeH<=660){//1
		DrawGraph( 330, 170, kazuH[0], TRUE );
	}}

	if(NumberH>=1, NumberH<=9){
		DrawGraph( 500, 50, kazuH[NumberH-1], TRUE );//���̐�
	}else if(NumberH==10){
		DrawGraph( 460, 50, kazuH[0], TRUE );
		DrawGraph( 500, 50, kazuH[9], TRUE );
	}else if(NumberH==11){
		DrawFormatString( 500, 60, GetColor(255,138,0), "FINISH!");
	}

	if(CountH==61){
	switch(NumberH){
	case 1://1���
		DrawFormatString( 30, 100, GetColor(255,255,255), "%s", quiz_data_H[0].String1 );
		DrawFormatString( 30, 120, GetColor(255,255,255), "%s", quiz_data_H[0].String2 );
		//DrawFormatString( 30, 140, GetColor(255,255,255), "��:%d", quiz_data[Qnumber[1]].Ans );
		DrawGraph( 10, 280, MaruH, TRUE );
		DrawGraph( 230, 280, BatuH, TRUE );
		CountH=60;
		break;
	case 2://2���
		DrawFormatString( 30, 100, GetColor(255,255,255), "%s", quiz_data_H[1].String1 );
		DrawFormatString( 30, 120, GetColor(255,255,255), "%s", quiz_data_H[1].String2 );
		//DrawFormatString( 30, 140, GetColor(255,255,255), "��:%d", quiz_data[Qnumber[1]].Ans );
		DrawGraph( 10, 280, MaruH, TRUE );
		DrawGraph( 230, 280, MaruH, TRUE );
		CountH=60;
		break;
	case 3://3���
		DrawFormatString( 30, 100, GetColor(255,255,255), "%s", quiz_data_H[2].String1 );
		DrawFormatString( 30, 120, GetColor(255,255,255), "%s", quiz_data_H[2].String2 );
		//DrawFormatString( 30, 140, GetColor(255,255,255), "��:%d", quiz_data[Qnumber[1]].Ans );
		DrawGraph( 10, 280, MaruH, TRUE );
		DrawGraph( 230, 280, MaruH, TRUE );
		CountH=60;
		break;
	case 4://4���
		DrawFormatString( 30, 100, GetColor(255,255,255), "%s", quiz_data_H[3].String1 );
		DrawFormatString( 30, 120, GetColor(255,255,255), "%s", quiz_data_H[3].String2 );
		//DrawFormatString( 30, 140, GetColor(255,255,255), "��:%d", quiz_data[Qnumber[1]].Ans );
		DrawGraph( 10, 280, MaruH, TRUE );
		DrawGraph( 230, 280, BatuH, TRUE );
		CountH=60;
		break;
	case 5://5���
		DrawFormatString( 30, 100, GetColor(255,255,255), "%s", quiz_data_H[4].String1 );
		DrawFormatString( 30, 120, GetColor(255,255,255), "%s", quiz_data_H[4].String2 );
		//DrawFormatString( 30, 140, GetColor(255,255,255), "��:%d", quiz_data[Qnumber[1]].Ans );
		DrawGraph( 10, 280, MaruH, TRUE );
		DrawGraph( 230, 280, MaruH, TRUE );
		CountH=60;
		break;
	case 6://���_���
		DrawFormatString( 20, 120, GetColor(255,255,255), "�傫�Ȑ��Łu�����Ă��A**�v");
		CountH=60; TimeH=0;
		if(SelectH==1 || SelectH==2){
		NumberH=12; SelectH=0; CountH=0; TimeH=0;
		}
		break;
	}//switch���̏I��芇��
	}
	DrawGraph( xH, yH, KarsolH, TRUE );

}