/*----------------------------------------------------------*/
/*Stage01�V�[���Ǘ��N���X�w�b�_�[ �@�@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��17�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"
#include "PlayerMgmt.h"
#include "StageCollision.h"
#include "ItemMgmt.h"

class Stage01Scene
{
private:
	PlayerMgmt* _playerMgmt = new PlayerMgmt();
	StageCollision* _stageCollision = new StageCollision();
	ItemMgmt* _itemMgmt = new ItemMgmt();

	int _playerModel;// ���f���i�[�p
	int _cnt = 0;
public:
	Stage01Scene();
	void Update();
	void DeleteSet();
};

