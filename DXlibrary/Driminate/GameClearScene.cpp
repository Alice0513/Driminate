/*----------------------------------------------------------*/
/*ゲームクリアの管理クラス        　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月29日 　　　　　　                              */
/*----------------------------------------------------------*/
#include "GameClearScene.h"
#include "SceneManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameClearScene::GameClearScene()
{
	_gameClear = LoadGraph("Image/GameClear.png");
}

/// <summary>
/// 更新用
/// </summary>
void GameClearScene::Update()
{
	DrawRotaGraph(600, 350, 0.5f, 0.0f, _gameClear, true);
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		SceneManager::NowSceneName = StageSelect;
	}
}