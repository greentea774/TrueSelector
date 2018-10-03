#include "DxLib.h"
#include "Config.h"
#include "Game.h"
#include "Menu.h"
#include "BGM.h"

static eBGM BGM = eBGM_Menu;    //シーン管理変数
int start, setstart, GoMenu, den3op, startop, click, Correct, Notcorrect, HandleM, HandleC, HandleG,TitleDark;

//更新
void BGM_Update(){
    switch(BGM){       //シーンによって処理を分岐
    case eBGM_Menu:    //現在の画面がメニューなら
		ChangeVolumeSoundMem( 25 , HandleM ); //BGMなので音量を80％にする
		ChangeVolumeSoundMem( 60 , setstart );
		PlaySoundMem( setstart, DX_PLAYTYPE_BACK);
	    PlaySoundMem( HandleM, DX_PLAYTYPE_LOOP); // 効果音を再生する
        break;//以下略

    case eBGM_Game:
		ChangeVolumeSoundMem( 60 , HandleG );
	    PlaySoundMem( HandleG, DX_PLAYTYPE_LOOP); // 効果音を再生する
		break;
    case eBGM_Config:
		ChangeVolumeSoundMem( 100 , HandleC );
	    PlaySoundMem( HandleC, DX_PLAYTYPE_LOOP); // 効果音を再生する
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
	PlaySoundMem( start, DX_PLAYTYPE_BACK); // 効果音を再生する
}

void BGM_GoMenu(){ 
	PlaySoundMem( GoMenu, DX_PLAYTYPE_BACK); // 効果音を再生する
}

void BGM_OP(){ 
	PlaySoundMem( den3op, DX_PLAYTYPE_BACK); // 効果音を再生する
}

void BGM_TitleDark(){
	ChangeVolumeSoundMem( 20, TitleDark );
	PlaySoundMem( TitleDark, DX_PLAYTYPE_BACK); // 効果音を再生する
}
void IAvoiceOP(){ 
	ChangeVolumeSoundMem( 255 , startop );
	PlaySoundMem( startop, DX_PLAYTYPE_BACK); //放置ボイス
}

void Click(){ 
	PlaySoundMem( click, DX_PLAYTYPE_BACK);//クリック
}

void BGM_True(){ 
	PlaySoundMem( Correct, DX_PLAYTYPE_BACK); // 効果音を再生する
}

void BGM_False(){ 
	PlaySoundMem( Notcorrect, DX_PLAYTYPE_BACK); // 効果音を再生する
}
// 引数 nextScene にシーンを変更する
void BGM_ChangeBGM(eBGM NextBGM){
    BGM = NextBGM;
}