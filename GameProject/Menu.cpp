#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "BGM.h"
#include <math.h>

#define PI 3.141592654f

	int x, y,BackM,BackM2,MouseB,KarsolM,Title,Title2,MaskT,MaskT2,MaskOver;
	int Countm = 0, Countc = 0, FlagT = 1, CountM = 0;

void Menu_Load(){
	 BackM = LoadGraph( "Graph/backM.png" ); // 背景
	 BackM2 = LoadGraph( "Graph/backM2.png" ); // 背景
	 KarsolM = LoadGraph( "Graph/karsol.png" ); // マウスカーソル
	 Title = LoadGraph( "Graph/title.png" ); // タイトル
	 Title2 = LoadGraph( "Graph/title2.png" ); // タイトル2
	 MaskT = LoadGraph( "Graph/Menu_maskray.png" ); //光
	 MaskT2 = LoadGraph( "Graph/Menu_maskray2.png" ); //光2
	 MaskOver = LoadMask( "Graph/MaskOver.png" ); // マスク画像
}

//更新
void Menu_Update(){
	int Mouse = GetMouseInput();
	Countc++; Countm++;
	if(Countm>=20){
    if(Mouse & MOUSE_INPUT_LEFT && 9<x && 296>x && 379<y && 456>y && FlagT==1){//画面のスタートが押されていたら
		CountM = 1;
	}
	if((Mouse & MOUSE_INPUT_LEFT) && (9>x || 296<x || 379>y || 456<y) && FlagT==1 && CountM==1){//領域離れ判定
		CountM = 0;
	}
	if(!(Mouse & MOUSE_INPUT_LEFT) && 9<x && 296>x && 379<y && 456>y && FlagT==1 && CountM==1){
		StopBGM_M(); BGM_start(); Countm=0; CountM=0; Click();
        SceneMgr_ChangeScene(eScene_Game);//シーンをゲーム画面に変更
		BGM_ChangeBGM(eBGM_Game);
		BGM_Update(); //BGMを更新
	  }
	 if(Mouse & MOUSE_INPUT_LEFT && 9<x && 296>x && 379<y && 456>y && FlagT==2){//画面のスタートが押されていたら
		StopBGM_M(); BGM_start(); Countm=0;
        SceneMgr_ChangeScene(eScene_Game_Hard);//シーンをゲーム画面に変更
		BGM_ChangeBGM(eBGM_Game);
		BGM_Update(); //BGMを更新
	  }
    if(Mouse & MOUSE_INPUT_LEFT && 334<x && 621>x && 379<y && 456>y && Countc>10){//画面のせっていが押されていたら
		//StopBGM_M(); BGM_start(); Countm=0;
        //SceneMgr_ChangeScene(eScene_Config);//シーンを設定画面に変更
		//BGM_ChangeBGM(eBGM_Config);
		//BGM_Update(); //BGMを更新
		BGM_False(); Countc=0;
    }
	if((Mouse & MOUSE_INPUT_LEFT) && (Mouse & MOUSE_INPUT_RIGHT) && 41<x && 561>x && 0<y && 181>y && FlagT==1){//画面のタイトルが押されたら
		FlagT =2; BGM_TitleDark();
	}else if(Mouse & MOUSE_INPUT_LEFT && 41<x && 561>x && 0<y && 181>y && FlagT==2){//画面のタイトルが押されたら
		FlagT =1; 
	}
	}
}

//描画
void Menu_Draw(){
	GetMousePoint(&x,&y);

	if(Countm == 800){
		IAvoiceOP();
		Countm = 0;
	}

	if(FlagT==2){
	DrawGraph( 0, 0, BackM2, TRUE );
	DrawGraph( 50, 0, Title2, TRUE );//タイトル
	CreateMaskScreen();     // マスクここから
    DrawMask( 0, 0, MaskOver, DX_MASKTRANS_BLACK ); // 黒い所のみを描画領域に
    DrawRotaGraph ( Countm*2, 120, 1.0, 0, MaskT2 , TRUE);
    DeleteMaskScreen(); // マスクここまで
	}else if(FlagT==1){
	DrawGraph( 0, 0, BackM, TRUE );
	DrawGraph( 50, 0, Title, TRUE );//タイトル
	CreateMaskScreen();     // マスクここから
    DrawMask( 0, 0, MaskOver, DX_MASKTRANS_BLACK ); // 黒い所のみを描画領域に
    DrawRotaGraph ( Countm*2, 120, 1.0, 0, MaskT , TRUE);
    DeleteMaskScreen(); // マスクここまで
	}

	GetMousePoint(&x,&y);
	//DrawFormatString(400,200,GetColor(255,255,255),"カーソル座標%d , %d",x,y);//デバッグ用
    DrawGraph( x, y, KarsolM, TRUE );

}