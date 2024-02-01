/*----------------------------------------------------------*/
/*�X�e�[�W�I���̃V�[���Ǘ��N���X�@�@�@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��30�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#include "StageSelectScene.h"
#include "SceneManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
StageSelectScene::StageSelectScene()
{
	_stageCnt = 0;
	_stage[0] = LoadGraph("Image/Stage/Stage01.png");
	_stageCnt++;
	_stage[1] = LoadGraph("Image/Stage/Stage02.png");
	_stageCnt++;
	_stage[2] = LoadGraph("Image/Stage/Stage03.png");

	_cursor = LoadGraph("Image/Cursor.png");

	_stageUIPos[0] = 70.0f;
	_stageUIPos[_stageCnt] = 740.0f;
	_stageUIPos[10] = (_stageUIPos[_stageCnt] - _stageUIPos[0]) / _stageCnt;
}

/// <summary>
/// �X�V�p
/// </summary>
void StageSelectScene::Update()
{//50,130
	for (int i = 0; i < _stageCnt+1; i++)
	{
		if (0 < i < _stageCnt)
			_stageUIPos[i] = _stageUIPos[0] + _stageUIPos[10] * (i);

		DrawRotaGraph(950, _stageUIPos[i], 0.30f, 0.0f, _stage[i], true);
	}

	DrawRotaGraph(780, _stageUIPos[_stageSelectNum], 0.20f, 0.0f, _cursor, true);
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (_stageSelectNum == _stageCnt) _stageSelectNum = -1;
		_stageSelectNum++;
		Sleep(100);
	}
	else if (CheckHitKey(KEY_INPUT_UP))
	{
		if (_stageSelectNum == 0) _stageSelectNum = _stageCnt + 1;
		_stageSelectNum--;
		Sleep(100);
	}

	Sleep(50);
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		switch (_stageSelectNum)
		{
		case 0:
			SceneManager::NowSceneName = Stage01;
			break;
		}
	}
}