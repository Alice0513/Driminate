/*----------------------------------------------------------*/
/*Stage02�V�[���Ǘ��N���X�w�b�_�[ �@�@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F2��8��  �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"
#include "PlayerMgmt.h"
#include "StageCollision.h"
#include "ItemMgmt.h"
#include "UISet.h"

class Stage02Scene
{
private:
	PlayerMgmt* _playerMgmt = new PlayerMgmt();
	StageCollision* _stageCollision = new StageCollision();
	ItemMgmt* _itemMgmt = new ItemMgmt();
	UISet* _uiSet = new UISet();

	int _playerModel;// ���f���i�[�p
	int _cnt = 0;
public:
	Stage02Scene();
	void Update();
	void DeleteSet();
};