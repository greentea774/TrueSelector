#include "Config.h"
#include "SceneMgr.h"
#include "Game.h"
#include "DxLib.h"
#include "BGM.h"

int Countcc=0;
//更新
void Config_Update(){
	int Mouse = GetMouseInput(),x,y;
	GetMousePoint(&x,&y);
    if(Mouse & MOUSE_INPUT_LEFT && 260<x && 355>x && 400<y && 415>y){//画面のもどるが押されていたら
		StopBGM_C(); BGM_GoMenu();
        SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
		BGM_ChangeBGM(eBGM_Menu);
		BGM_Update(); //BGMを更新
    }

	if(Mouse & MOUSE_INPUT_LEFT && 180<x && 250>x && 270<y && 285>y){
		Quiz_Reload();
	}

	Countcc++;
	if(Mouse & MOUSE_INPUT_LEFT && Countcc>5){
		Click(); Countcc=0;
	}
}

//描画
void Config_Draw(){
	int Handle, x, y;
	GetMousePoint(&x,&y);
    DrawString(180, 280,"リロード",GetColor(255,255,255));
    DrawString(260,400,"もどる",GetColor(255,255,255));

	Handle = LoadGraph( "Graph/karsol.png" ); // マウスカーソル
    DrawGraph( x, y, Handle, TRUE );
}