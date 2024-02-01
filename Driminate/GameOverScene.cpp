/*----------------------------------------------------------*/
/*ゲームオーバーの管理クラス        　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月29日 　　　　　　                              */
/*----------------------------------------------------------*/
#include "GameOverScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameOverScene::GameOverScene()
{
	_gameOver = LoadGraph("Image/GameOver.png");
}

void GameOverScene::Update()
{
	DrawRotaGraph(600, 350, 0.5f, 0.0f, _gameOver, true);
}