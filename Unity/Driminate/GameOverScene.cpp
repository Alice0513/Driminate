/*----------------------------------------------------------*/
/*�Q�[���I�[�o�[�̊Ǘ��N���X        �@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��29�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#include "GameOverScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameOverScene::GameOverScene()
{
	_gameOver = LoadGraph("Image/GameOver.png");
}

void GameOverScene::Update()
{
	DrawRotaGraph(600, 350, 0.5f, 0.0f, _gameOver, true);
}