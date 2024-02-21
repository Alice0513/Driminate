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
	int _retry, _stageSelect;
	int _cursor;

	float _imagePos[2] = {500.0f, 650.0f};
	int _num = 0;
public:
	GameOverScene();
	void Update();
};

