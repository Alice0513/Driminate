/*----------------------------------------------------------*/
/*�Q�[���N���A�̊Ǘ��N���X        �@�@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��29�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#include "GameClearScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameClearScene::GameClearScene()
{
	_gameClear = LoadGraph("Image/GameClear.png");
}

/// <summary>
/// �X�V�p
/// </summary>
void GameClearScene::Update()
{
	DrawRotaGraph(600, 350, 0.5f, 0.0f, _gameClear, true);
}