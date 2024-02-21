/*----------------------------------------------------------*/
/*ステージ選択のシーン管理クラス　　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月30日 　　　　　　                              */
/*----------------------------------------------------------*/
#include "StageSelectScene.h"
#include "SceneManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
StageSelectScene::StageSelectScene()
{
	_stageCnt = 0;
	_stage[0] = LoadGraph("Image/Stage/Stage01.png");
	//_stageCnt++;
	//_stage[1] = LoadGraph("Image/Stage/Stage02.png");
	//_stageCnt++;
	//_stage[2] = LoadGraph("Image/Stage/Stage03.png");

	_cursor = LoadGraph("Image/Cursor.png");

	_title = LoadGraph("UI/Titel.png");

	_stageUIPos[0] = 70.0f;
	_stageUIPos[_stageCnt] = 500.0f;
	_stageUIPos[10] = (_stageUIPos[_stageCnt] - _stageUIPos[0]) / _stageCnt;
}

/// <summary>
/// 更新用
/// </summary>
void StageSelectScene::Update()
{
	int time = 15;
	for (int i = 0; i < _stageCnt+1; i++)
	{
		if (0 < i < _stageCnt)
			_stageUIPos[i] = _stageUIPos[0] + _stageUIPos[10] * (i);

		DrawRotaGraph(950, _stageUIPos[i], 0.30f, 0.0f, _stage[i], true);
		Sleep(time);
	}

	DrawRotaGraph(780, _stageUIPos[_stageSelectNum], 0.20f, 0.0f, _cursor, true);
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (_stageSelectNum == _stageCnt+1) _stageSelectNum = -1;
		_stageSelectNum++;
		Sleep(time);
	}
	else if (CheckHitKey(KEY_INPUT_UP))
	{
		if (_stageSelectNum == 0) _stageSelectNum = _stageCnt + 2;
		_stageSelectNum--;
		Sleep(time);
	}

	Sleep(80);
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		switch (_stageSelectNum)
		{
		case 0:
			SceneManager::NowSceneName = Stage01;
			break;
		case 1:
			SceneManager::NowSceneName = Stage02;
			break;
		default:
			SceneManager::NowSceneName = Title;
			break;
		}
		Sleep(time);
	}
	if (_stageSelectNum == _stageCnt + 1)
	{
		DrawRotaGraph(870, 700, 0.20f, 0.0f, _cursor, true);

	}
	DrawRotaGraph(1000, 700, 0.20f, 0.0f, _title, true);
}