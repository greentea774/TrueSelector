#include "Game.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "BGM.h"

int Qnumber[11], Number=1, Point=0, Select=0, Count=0, Scene=0;//Numberは問題数を区切る用//Qnumberはランダム値を保管//Selectは選んだ解答
int Back,Maru,Batu,Karsol,kazu[10],Time=0,TrueG,FalseG,Gflag=0,Gcount=0;
struct quiz_data_t{
	int Ans;
	char String1[256];
	char String2[256];
} quiz_data[QUIZ_MAX];


void Quiz_Reload(){ //乱数値をリロードする
	for(Number=1;Number<11;Number++){
		Qnumber[Number] = GetRand(88);
	}
	Number=1;
}
void Game_Load(){
	int  fp, n, Flag=0;//Timeはロード用
	char tmp[256];
	fp = FileRead_open("dat/quiz.txt");//ファイル読み込み
			if(fp == NULL){
                printfDx("read error\n"); Time = 1;
                return;
			}
			//クイズ読み込み（狩生さんルート）
			for(n=0;n<QUIZ_MAX;n++){
			FileRead_gets(quiz_data[n].String1, 50, fp );
			FileRead_gets(quiz_data[n].String2, 50, fp );
			FileRead_gets(tmp, 256, fp );
			quiz_data[n].Ans = atoi(tmp);
			}
			FileRead_close(fp);
	
	//ランダム値を保持.
	for(Number=1;Number<11;Number++){
		Qnumber[Number] = GetRand(88);
	}
	Number=1;

	Back = LoadGraph( "Graph/back.png" ); //背景
	Maru = LoadGraph( "Graph/Maru.png" ); //〇
	Batu = LoadGraph( "Graph/Batu.png" ); //×
	TrueG = LoadGraph( "Graph/true.png" ); //○2
	FalseG = LoadGraph( "Graph/false.png" ); //×2
	Karsol = LoadGraph( "Graph/karsol.png" ); // マウスカーソル
	LoadDivGraph( "Graph/kazu.png" , 10 , 10 , 1 , 45 , 70 , kazu ); // 画像の分割読み込み.数
	//kazuは0に1が、1に2が、9に0がみたいに格納されている

}

void Game_Update(){
	int Mouse = GetMouseInput(),x,y;
	GetMousePoint(&x,&y);
    if(Mouse & MOUSE_INPUT_LEFT && 500<x && 550>x && 390<y && 415>y){ //画面のもどるが押されていたら
		StopBGM_G(); Quiz_Reload(); BGM_GoMenu(); Point=0; Select=0; Number=1; Count=0; Time=0; Scene=0; Gflag=0;
        SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
		BGM_ChangeBGM(eBGM_Menu);
		BGM_Update(); //BGMを更新
    }
	//Gflagはマウスのクリック状態//
	//Gflag = 0 : ○×とも押されていない//
	//Gflag = 1 : 正解//
	//Gflag = 2 : 不正解//
	//Gflag = 3 : ○が押された状態//
	//Gflag = 4 : ×が押された状態//
	//Gflag = 5 : 連打表示防止のための状態移行フラグ//
	Count++; Time++;

	if(Count==61 && Gflag!=5 && Gflag!=6){
	if(Mouse & MOUSE_INPUT_LEFT && 10<x && 210>x && 280<y && 480>y){//〇が押されたら
		Gflag = 3;
	}
	if(Mouse & MOUSE_INPUT_LEFT && Gflag == 3 && (10>x || 210<x || 280>y || 480<y)){//領域離れ判定
		Gflag = 0;
	}

	if(!(Mouse & MOUSE_INPUT_LEFT)&& 10<x && 210>x && 280<y && 480>y && Gflag==3){//ボタン離れ判定
		Select = 1; Gflag = 0; Click();
	}


	if(Mouse & MOUSE_INPUT_LEFT && 230<x && 410>x && 280<y && 480>y){//×が押されたら
		Gflag = 4;
	}
	if(Mouse & MOUSE_INPUT_LEFT && Gflag == 4 && (230>x || 410<x || 280>y || 480<y)){//領域離れ判定
			Gflag = 0;
	}

	if(!(Mouse & MOUSE_INPUT_LEFT) && Gflag==4 && 230<x && 410>x && 280<y && 480>y){///ボタン離れ判定
		Select = 2; Gflag = 0; Click();
	}


	if(Number<=10 && ( Select==1 || Select==2) && Gflag==0){//先へいかせない
		if(Select==quiz_data[Qnumber[Number]].Ans){//正解ならば
			BGM_True(); Gflag=1;
		}else{
			BGM_False(); Gflag=2;
		}}
	}

	if(Time==661 && Gflag==0){
		BGM_False(); Gflag=2;
	}

	if(Scene==2){//最後まで終わったら
		StopBGM_G(); Quiz_Reload(); BGM_GoMenu(); Point=0; Select=0; Number=1; Count=0; Time=0; Scene=0;
        SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
        SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
		BGM_ChangeBGM(eBGM_Menu);
		BGM_Update(); //BGMを更新
	}

}

//描画
void Game_Draw(){
	int x, y;
	GetMousePoint(&x,&y);

    DrawGraph( 0, 0, Back, TRUE );//背景
    DrawGraph( 10, 280, Maru, TRUE );//〇
    DrawGraph( 230, 280, Batu, TRUE );//×
	DrawFormatString( 585, 330, GetColor(255,138,0), "Pt");
	DrawFormatString( 595, 170, GetColor(255,138,0), "問");
	DrawFormatString( 595, 360, GetColor(255,138,0), "%d", Gflag);//デバッグ用
	//ポイント
	if(Point>0 && Point<10){
		DrawGraph( 530, 260, kazu[Point-1], TRUE );//得点の数
	}else if(Point==10){
		DrawGraph( 515, 260, kazu[0], TRUE );
		DrawGraph( 545, 260, kazu[9], TRUE );//0が9に格納されているため
	}else{
		DrawGraph( 530, 260, kazu[9], TRUE );//0が9に格納されているため
	}
	DrawFormatString( 30, 70, GetColor(255,255,255), "問題");

	//制限時間
	if(Number<=10){
	if(Time>=121 && Time<=180){//9
		DrawGraph( 330, 170, kazu[8], TRUE );
	}else if(Time>=61 && Time<=120){//10
		DrawGraph( 290, 170, kazu[0], TRUE );
		DrawGraph( 330, 170, kazu[9], TRUE );
	}else if(Time>=181 && Time<=240){//8
		DrawGraph( 330, 170, kazu[7], TRUE );
	}else if(Time>=241 && Time<=300){//7
		DrawGraph( 330, 170, kazu[6], TRUE );
	}else if(Time>=301 && Time<=360){//6
		DrawGraph( 330, 170, kazu[5], TRUE );
	}else if(Time>=361 && Time<=420){//5
		DrawGraph( 330, 170, kazu[4], TRUE );
	}else if(Time>=421 && Time<=480){//4
		DrawGraph( 330, 170, kazu[3], TRUE );
	}else if(Time>=481 && Time<=540){//3
		DrawGraph( 330, 170, kazu[2], TRUE );
	}else if(Time>=541 && Time<=600){//2
		DrawGraph( 330, 170, kazu[1], TRUE );
	}else if(Time>=601 && Time<=660){//1
		DrawGraph( 330, 170, kazu[0], TRUE );
	}}

    DrawString(500,400,"もどる",GetColor(255,255,255));
	if(Number>=1, Number<=9){
		DrawGraph( 500, 50, kazu[Number-1], TRUE );//問題の数
	}else if(Number==10){
		DrawGraph( 460, 50, kazu[0], TRUE );
		DrawGraph( 500, 50, kazu[9], TRUE );
	}else if(Number==11){
		DrawFormatString( 465, 80, GetColor(255,138,0), "FINISH!");
	}

	if(Count==61){
	switch(Scene){
	case 0://問題部
		DrawFormatString( 30, 100, GetColor(255,255,255), "%s", quiz_data[Qnumber[Number]].String1 );
		DrawFormatString( 30, 120, GetColor(255,255,255), "%s", quiz_data[Qnumber[Number]].String2 );
		if((Gflag==1 || Gflag==5) && Gcount<31){
			DrawGraph(0,0,TrueG,TRUE); Gcount++; Gflag=5;
		}else if(Gflag==5 && Gcount==31){
			Point+=1; Number+=1; Select=0; Count=0; Time=0; Gflag=0; Gcount=0;
		}
		if((Gflag==2 || Gflag==6) && Gcount<31){
			DrawGraph(0,0,FalseG,TRUE); Gcount++; Gflag=6;
		}else if(Gflag==6 && Gcount==31){
			Number+=1; Select=0; Count=0; Time=0; Gflag=0; Gcount=0;
		}
		if(Number==11){
		Scene+=1;
		}
		Count=60;
		break;
	case 1://得点画面
		DrawFormatString( 100, 120, GetColor(255,255,255), "得点：");

		if(Point>0 && Point<10){
			DrawGraph( 170, 90, kazu[Point-1], TRUE );//得点の数
		}else if(Point==10){
			DrawGraph( 150, 90, kazu[0], TRUE );
			DrawGraph( 190, 90, kazu[9], TRUE );//0が9に格納されているため
			DrawFormatString( 200, 200, GetColor(255,138,0), "PERFECT!!");
		}else{
			DrawGraph( 170, 90, kazu[9], TRUE );//0が9に格納されているため
		}
		if(Point==9 || Point==8){
		DrawFormatString( 200, 200, GetColor(255,138,0), "GREAT!");
		}else if(Point==7 || Point==6 || Point==5){
		DrawFormatString( 200, 200, GetColor(255,138,0), "GOOD");
		}
		Count=60; Time=0;
		if(Select==1 || Select==2){
		Number=12; Point=0; Select=0; Count=0; Time=0; Scene+=1;
		}
		break;
	}//switch文の終わり括弧
	}
	DrawGraph( x, y, Karsol, TRUE );

}