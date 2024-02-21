/*----------------------------------------------------------*/
/*�V�[���Ǘ��N���X  �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��17�� �@�@�@�@�@�@                              */
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
/// SceneManager�̃R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
{

}

/// <summary>
/// �V�[���̊Ǘ�
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