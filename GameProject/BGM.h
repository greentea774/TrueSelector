#pragma once

typedef enum {
    eBGM_Menu,    //���j���[���
    eBGM_Game,    //�Q�[�����
    eBGM_Config,  //�ݒ���
} eBGM ;

//�X�V
void BGM_Update();

void BGM_Load();

// ���� nextBGM �ɕύX����
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