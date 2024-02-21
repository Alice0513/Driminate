/*----------------------------------------------------------*/
/*シーン管理クラス  　　　　　　　　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月17日 　　　　　　                              */
/*----------------------------------------------------------*/
#include "SceneManager.h"
#include "TitleScene.h"
#include "Stage01Scene.h"
#include "Stage02Scene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "StageSelectScene.h"
#include "PlayerMgmt.h"

Scene SceneManager::NowSceneName = Title;
Scene SceneManager::SelectSceneName = Title;

/// <summary>
/// SceneManagerのコンストラクタ
/// </summary>
SceneManager::SceneManager()
{

}

/// <summary>
/// シーンの管理
/// </summary>
void SceneManager::SceneSelect()
{
	switch (SceneManager::NowSceneName)
	{
	case Title:
		_titleScene->Update();
		break;
	case StageSelect:
		_stageSelectScene->Update();
		break;
	case Stage01:
		_stage01Scene->Update();
		SceneManager::SelectSceneName = Stage01;
		break;
	case Stage02:
		_stage02Scene->Update();
		SceneManager::SelectSceneName = Stage02;
		break;
	case GameClear:
		_gameClearScene->Update();
		break;
	case GameOver:
		_gameOverScene->Update();
		break;
	default:
		break;
	}
}

void SceneManager::DeleteSet()
{
	delete _titleScene;
	delete _stage01Scene;
	delete _gameClearScene;
	delete _gameOverScene;
}