/*----------------------------------------------------------*/
/*ゲームオーバーの管理クラスヘッダー　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月29日 　　　　　　                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"
#include <string> 

class GameOverScene
{
private:
	int _gameOver;
public:
	GameOverScene();
	void Update();
};

