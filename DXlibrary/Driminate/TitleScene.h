/*----------------------------------------------------------*/
/*タイトルシーン管理クラスヘッダー　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月17日 　　　　　　                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"

class TitleScene
{
private:
	int _titleLogo;
	int _enterPush;
public:
	TitleScene();
	void Update();
	void UISet();
};

