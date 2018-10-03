#pragma once

typedef enum {
    eBGM_Menu,    //メニュー画面
    eBGM_Game,    //ゲーム画面
    eBGM_Config,  //設定画面
} eBGM ;

//更新
void BGM_Update();

void BGM_Load();

// 引数 nextBGM に変更する
void BGM_ChangeBGM(eBGM nextBGM);

void StopBGM_G();

void StopBGM_M();

void StopBGM_C();

void BGM_start();

void BGM_GoMenu();

void BGM_TitleDark();

void IAvoiceOP();

void Click();

void BGM_True();

void BGM_False();

void BGM_OP();