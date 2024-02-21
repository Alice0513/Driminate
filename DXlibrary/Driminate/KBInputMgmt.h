/*----------------------------------------------------------*/
/*キーボード入力管理クラスヘッダー　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：2月1日  　　　　　　                              */
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

