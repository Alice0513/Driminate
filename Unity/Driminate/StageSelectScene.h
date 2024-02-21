/*----------------------------------------------------------*/
/*ステージ選択のシーン管理クラスヘッダー　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月30日 　　　　　　                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"
#include <string> 
class StageSelectScene
{
private:
	int _stage[10], _cursor;

	int _stageCnt = 0;
	int _stageSelectNum = 0;

	float _stageUIPos[10];
public:
	StageSelectScene();
	void Update();
};

