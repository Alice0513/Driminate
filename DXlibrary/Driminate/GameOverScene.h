/*----------------------------------------------------------*/
/*�Q�[���I�[�o�[�̊Ǘ��N���X�w�b�_�[�@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��29�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"
#include <string> 

class GameOverScene
{
private:
	int _gameOver;
	int _retry, _stageSelect;
	int _cursor;

	float _imagePos[2] = {500.0f, 650.0f};
	int _num = 0;
public:
	GameOverScene();
	void Update();
};

