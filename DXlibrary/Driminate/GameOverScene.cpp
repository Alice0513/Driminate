/*----------------------------------------------------------*/
/*�Q�[���I�[�o�[�̊Ǘ��N���X        �@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��29�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#include "GameOverScene.h"
#include "SceneManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameOverScene::GameOverScene()
{
	_gameOver = LoadGraph("Image/GameOver.png");
	_retry = LoadGraph("UI/Retry.png");
	_stageSelect = LoadGraph("UI/StageSelect.png");
	_cursor = LoadGraph("Image/Cursor.png");
}

void GameOverScene::Update()
{
	DrawRotaGraph(600, 350, 0.5f, 0.0f, _gameOver, true);
	DrawRotaGraph(600, 500, 0.3f, 0.0f, _retry, true);
	DrawRotaGraph(600, 650, 0.3f, 0.0f, _stageSelect, true);

	DrawRotaGraph(420, _imagePos[_num], 0.2f, 0.0f, _cursor, true);

	if (CheckHitKey(KEY_INPUT_UP))
	{
		_num--;
		if (_num == -1) _num = 1;
		Sleep(250);
	}
	else if (CheckHitKey(KEY_INPUT_DOWN))
	{
		_num++;
		if (_num == 2) _num = 0;
		Sleep(250);
	}

	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		switch (_num)
		{
		case 0:
			SceneManager::NowSceneName = SceneManager::SelectSceneName;
			break;
		case 1:
			SceneManager::NowSceneName = StageSelect;
			break;
		default:
			break;
		}
	}
}