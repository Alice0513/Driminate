/*----------------------------------------------------------*/
/*タイトルシーン管理クラス  　　　　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月17日 　　　　　　                              */
/*----------------------------------------------------------*/
#include "TitleScene.h"
#include "SceneManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
	_titleLogo = LoadGraph("Image/TitleLogo.png");
	_enterPush = LoadGraph("Image/EnterPush.png");
}

/// <summary>
/// 実行まとめ
/// </summary>
void TitleScene::Update()
{
	UISet();
	Sleep(100);
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		SceneManager::NowSceneName = StageSelect;
	}
}

/// <summary>
/// UIセット
/// </summary>
void TitleScene::UISet()
{
	DrawRotaGraph(600, 350, 1.0f, 0.0f, _titleLogo, true);
	DrawRotaGraph(600, 650, 0.5f, 0.0f, _enterPush, true);
}