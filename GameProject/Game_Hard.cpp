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
	int  fpH, nH;//Timeはロード用
	char tmpH[256];
	fpH= FileRead_open("dat/quizhard.txt");//ファイル読み込み
			if(fpH == NULL){
                printfDx("read error\n");
                return;
			}
			//クイズ読み込み
			for(nH=0;nH<QUIZ_HARD_MAX;nH++){
			FileRead_gets(quiz_data_H[nH].String1, 50, fpH );
			FileRead_gets(quiz_data_H[nH].String2, 50, fpH );
			FileRead_gets(tmpH, 256, fpH );
			quiz_data_H[nH].Ans = atoi(tmpH);
			}
			FileRead_close(fpH);

	BackH = LoadGraph( "Graph/back.png" ); //背景
	MaruH = LoadGraph( "Graph/Maru.png" ); //〇
	BatuH = LoadGraph( "Graph/Batu.png" ); //×
	KarsolH = LoadGraph( "Graph/karsol.png" ); // マウスカーソル
	LoadDivGraph( "Graph/kazu.png" , 10 , 10 , 1 , 45 , 70 , kazuH ); // 画像の分割読み込み.数
	//kazuは0に1が、1に2が、9に0がみたいに格納されている

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
	if(NumberH<=5 && ( SelectH==1 || SelectH==2)){//先へいかせない
		if(SelectH==quiz_data_H[NumberH].Ans){//正解ならば
			BGM_True(); NumberH+=1; SelectH=0; CountH=0; TimeH=0;
		}else{
			BGM_False(); NumberH+=1; SelectH=0; CountH=0; TimeH=0;
		}}
	}

	//3,5問目は何でもするって言ったよねのところなので、制限時間を減らさないようにする
	if(NumberH==3 || NumberH==5){
		TimeH = 62;
	}

	if(TimeH==661){
		BGM_False(); NumberH+=1; SelectH=0; CountH=0; TimeH=0;
	}

	if(NumberH==12){//最後まで終わったら
		StopBGM_G(); BGM_GoMenu(); SelectH=0; NumberH=1; CountH=0; TimeH=0;
        SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
		BGM_ChangeBGM(eBGM_Menu);
		BGM_Update(); //BGMを更新
	}

	CountCH++;
	if(Mouse & MOUSE_INPUT_LEFT && CountCH>10){//クリック音
		Click(); CountCH=0;
	}

}

//描画
void Game_Hard_Draw(){
	int xH, yH;
	GetMousePoint(&xH,&yH);

    DrawGraph( 0, 0, BackH, TRUE );//背景
	DrawFormatString( 595, 170, GetColor(255,138,0), "問");
	DrawFormatString( 30, 70, GetColor(255,255,255), "問題");

	//制限時間
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
		DrawGraph( 500, 50, kazuH[NumberH-1], TRUE );//問題の数
	}else if(NumberH==10){
		DrawGraph( 460, 50, kazuH[0], TRUE );
		DrawGraph( 500, 50, kazuH[9], TRUE );
	}else if(NumberH==11){
		DrawFormatString( 500, 60, GetColor(255,138,0), "FINISH!");
	}

	if(CountH==61){
	switch(NumberH){
	case 1://1問目
		DrawFormatString( 30, 100, GetColor(255,255,255), "%s", quiz_data_H[0].String1 );
		DrawFormatString( 30, 120, GetColor(255,255,255), "%s", quiz_data_H[0].String2 );
		//DrawFormatString( 30, 140, GetColor(255,255,255), "解答:%d", quiz_data[Qnumber[1]].Ans );
		DrawGraph( 10, 280, MaruH, TRUE );
		DrawGraph( 230, 280, BatuH, TRUE );
		CountH=60;
		break;
	case 2://2問目
		DrawFormatString( 30, 100, GetColor(255,255,255), "%s", quiz_data_H[1].String1 );
		DrawFormatString( 30, 120, GetColor(255,255,255), "%s", quiz_data_H[1].String2 );
		//DrawFormatString( 30, 140, GetColor(255,255,255), "解答:%d", quiz_data[Qnumber[1]].Ans );
		DrawGraph( 10, 280, MaruH, TRUE );
		DrawGraph( 230, 280, MaruH, TRUE );
		CountH=60;
		break;
	case 3://3問目
		DrawFormatString( 30, 100, GetColor(255,255,255), "%s", quiz_data_H[2].String1 );
		DrawFormatString( 30, 120, GetColor(255,255,255), "%s", quiz_data_H[2].String2 );
		//DrawFormatString( 30, 140, GetColor(255,255,255), "解答:%d", quiz_data[Qnumber[1]].Ans );
		DrawGraph( 10, 280, MaruH, TRUE );
		DrawGraph( 230, 280, MaruH, TRUE );
		CountH=60;
		break;
	case 4://4問目
		DrawFormatString( 30, 100, GetColor(255,255,255), "%s", quiz_data_H[3].String1 );
		DrawFormatString( 30, 120, GetColor(255,255,255), "%s", quiz_data_H[3].String2 );
		//DrawFormatString( 30, 140, GetColor(255,255,255), "解答:%d", quiz_data[Qnumber[1]].Ans );
		DrawGraph( 10, 280, MaruH, TRUE );
		DrawGraph( 230, 280, BatuH, TRUE );
		CountH=60;
		break;
	case 5://5問目
		DrawFormatString( 30, 100, GetColor(255,255,255), "%s", quiz_data_H[4].String1 );
		DrawFormatString( 30, 120, GetColor(255,255,255), "%s", quiz_data_H[4].String2 );
		//DrawFormatString( 30, 140, GetColor(255,255,255), "解答:%d", quiz_data[Qnumber[1]].Ans );
		DrawGraph( 10, 280, MaruH, TRUE );
		DrawGraph( 230, 280, MaruH, TRUE );
		CountH=60;
		break;
	case 6://得点画面
		DrawFormatString( 20, 120, GetColor(255,255,255), "大きな声で「愛してるよ、**」");
		CountH=60; TimeH=0;
		if(SelectH==1 || SelectH==2){
		NumberH=12; SelectH=0; CountH=0; TimeH=0;
		}
		break;
	}//switch文の終わり括弧
	}
	DrawGraph( xH, yH, KarsolH, TRUE );

}