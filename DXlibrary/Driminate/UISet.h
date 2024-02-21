/*----------------------------------------------------------*/
/*UI管理クラスヘッダー 　           　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：2月5日 　　　　　　                               */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"

class UISet
{
private:
	int _itemImage[4];
	VECTOR _itemPos;
	float _siz[4] = { 0.05f, 0.1f, 0.18f, 0.4f };
public:
	UISet();
	void Update();
};

