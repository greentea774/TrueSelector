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
//ループで必ず行う３大処理
int ProcessLoop(){
	if(ProcessMessage()!=0)return -1;//プロセス処理がエラーなら-1を返す
	if(ClearDrawScreen()!=0)return -1;//画面クリア処理がエラーなら-1を返す
	return 0;
}

void Main_Load(){
	den3 = LoadGraph( "Graph/den3.png" );
	dden3 = LoadGraph( "Graph/01den3.png" );
	Maoukon = LoadGraph("Graph/Maoukon.png");
}

void FpsTimeFanction(){
        if(FpsTime_i== 0)
                FpsTime[0]=GetNowCount();               //1周目の時間取得
        if(FpsTime_i==49){
                FpsTime[1]=GetNowCount();               //50周目の時間取得
                Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//測定した値からfpsを計算
                FpsTime_i=0;//カウントを初期化
        }
        else
                FpsTime_i++;//現在何周目かカウント
        if(Fps != 0)
                DrawFormatString(540,450,GetColor(255,255,255),"FPS %.1f",Fps); //fpsを表示
        return;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
    SetWindowIconID( ID_ICON ); SetMainWindowText("クイズゲーム"); ChangeWindowMode(TRUE); //ウィンドウモード変更と初期化と裏画面設定
	if(DxLib_Init() == -1 || SetDrawScreen( DX_SCREEN_BACK )!=0) return -1;//初期化と裏画面化
	SetFontSize( 20 ) ;                             //サイズを20に変更
    SetFontThickness( 1 ) ;                         //太さを1に変更
    ChangeFont( "HGS創英角ﾎﾟｯﾌﾟ体" ) ;              //HGS創英角ﾎﾟｯﾌﾟ体に変更
	ChangeFontType( DX_FONTTYPE_ANTIALIASING );     //アンチエイリアスフォントに変更
	int Flag = 0, Time = 0, star =0, Mouse = GetMouseInput();

		if(Time == 0){// オープニング
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

    while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && SetMouseDispFlag(FALSE)==0){//画面更新 & メッセージ処理 & 画面消去

		if(Flag == 0){ //最初の一回はBGMを流す
			BGM_Update(); //BGMを更新
			Flag = 1;
			}
			//終了処理
		if(CheckHitKey(KEY_INPUT_ESCAPE)!=0){//Escキーが押されていたら
			break; //終了
		}

        SceneMgr_Update();  //更新
		ClearDrawScreen(); // 画面を消す
        SceneMgr_Draw();    //描画
		FpsTimeFanction(); //fps表示
    }
        
    DxLib_End(); // DXライブラリ終了処理
    return 0;
}