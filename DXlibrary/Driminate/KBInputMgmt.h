/*----------------------------------------------------------*/
/*�L�[�{�[�h���͊Ǘ��N���X�w�b�_�[�@�@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F2��1��  �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"
#include <string> 

class KBInputMgmt
{
private:
public:
	static bool ReturnFlg;
	static bool UpFlg;
	static bool DownFlg;

	KBInputMgmt();
	void Update();
};

