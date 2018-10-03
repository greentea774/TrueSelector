#include "DxLib.h"
#include "Config.h"
#include "Game.h"
#include "Menu.h"
#include "BGM.h"

static eBGM BGM = eBGM_Menu;    //�V�[���Ǘ��ϐ�
int start, setstart, GoMenu, den3op, startop, click, Correct, Notcorrect, HandleM, HandleC, HandleG,TitleDark;

//�X�V
void BGM_Update(){
    switch(BGM){       //�V�[���ɂ���ď����𕪊�
    case eBGM_Menu:    //���݂̉�ʂ����j���[�Ȃ�
		ChangeVolumeSoundMem( 25 , HandleM ); //BGM�Ȃ̂ŉ��ʂ�80���ɂ���
		ChangeVolumeSoundMem( 60 , setstart );
		PlaySoundMem( setstart, DX_PLAYTYPE_BACK);
	    PlaySoundMem( HandleM, DX_PLAYTYPE_LOOP); // ���ʉ����Đ�����
        break;//�ȉ���

    case eBGM_Game:
		ChangeVolumeSoundMem( 60 , HandleG );
	    PlaySoundMem( HandleG, DX_PLAYTYPE_LOOP); // ���ʉ����Đ�����
		break;
    case eBGM_Config:
		ChangeVolumeSoundMem( 100 , HandleC );
	    PlaySoundMem( HandleC, DX_PLAYTYPE_LOOP); // ���ʉ����Đ�����
        break;
    }
}

void BGM_Load(){
	start = LoadSoundMem("Sound/start.ogg"); 
	setstart = LoadSoundMem("Sound/setstart.ogg"); 
	GoMenu = LoadSoundMem("Sound/GoMenu.ogg");
	den3op = LoadSoundMem("Sound/den3op.ogg");
	startop = LoadSoundMem("Sound/startop.wav");
	click = LoadSoundMem("Sound/Click.ogg");
	Correct = LoadSoundMem("Sound/Correct.ogg");
	Notcorrect = LoadSoundMem("Sound/Notcorrect.ogg");
	HandleM = LoadSoundMem("Sound/OP.ogg");
	HandleG = LoadSoundMem("Sound/Quiz.ogg");
	HandleC = LoadSoundMem("Sound/Config.ogg");
	TitleDark = LoadSoundMem("Sound/TitleDark.ogg");
}

void StopBGM_M(){
	StopSoundMem(HandleM);
}

void StopBGM_G(){
	StopSoundMem(HandleG);
}

void StopBGM_C(){
	StopSoundMem(HandleC);
}

void BGM_start(){
	PlaySoundMem( start, DX_PLAYTYPE_BACK); // ���ʉ����Đ�����
}

void BGM_GoMenu(){ 
	PlaySoundMem( GoMenu, DX_PLAYTYPE_BACK); // ���ʉ����Đ�����
}

void BGM_OP(){ 
	PlaySoundMem( den3op, DX_PLAYTYPE_BACK); // ���ʉ����Đ�����
}

void BGM_TitleDark(){
	ChangeVolumeSoundMem( 20, TitleDark );
	PlaySoundMem( TitleDark, DX_PLAYTYPE_BACK); // ���ʉ����Đ�����
}
void IAvoiceOP(){ 
	ChangeVolumeSoundMem( 255 , startop );
	PlaySoundMem( startop, DX_PLAYTYPE_BACK); //���u�{�C�X
}

void Click(){ 
	PlaySoundMem( click, DX_PLAYTYPE_BACK);//�N���b�N
}

void BGM_True(){ 
	PlaySoundMem( Correct, DX_PLAYTYPE_BACK); // ���ʉ����Đ�����
}

void BGM_False(){ 
	PlaySoundMem( Notcorrect, DX_PLAYTYPE_BACK); // ���ʉ����Đ�����
}
// ���� nextScene �ɃV�[����ύX����
void BGM_ChangeBGM(eBGM NextBGM){
    BGM = NextBGM;
}