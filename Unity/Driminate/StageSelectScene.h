/*----------------------------------------------------------*/
/*�X�e�[�W�I���̃V�[���Ǘ��N���X�w�b�_�[�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��30�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"
#include <string> 
class StageSelectScene
{
private:
	int _stage[10], _cursor;

	int _stageCnt = 0;
	int _stageSelectNum = 0;

	float _stageUIPos[10];
public:
	StageSelectScene();
	void Update();
};

