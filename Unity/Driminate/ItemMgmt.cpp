/*----------------------------------------------------------*/
/*�A�C�e���̊Ǘ��N���X         �@�@   �@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��26�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <random>
#include "ItemMgmt.h"
#include "PlayerMgmt.h"
#include "SceneManager.h"

void ItemMgmt::GetPlayer(PlayerMgmt* PlayerMgmt)
{
	_playerMgmt = PlayerMgmt;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
ItemMgmt::ItemMgmt()
{
	_itemModel[0] = MV1LoadModel("Model/Item/Apple.mv1");
	_itemModel[1] = MV1LoadModel("Model/Item/Banana.mv1");
	_itemModel[4] = MV1LoadModel("Model/Item/Mushroom.mv1");
	_pos[0] = VGet(0.0f, 3.0f, 0.0f);
	_pos[1] = VGet(0.0f, 3.0f, 0.0f);
	_pos[4] = VGet(0.0f, 1.0f, 0.0f);

	for (int i = 0; i < 10; i++)
	{
		_collFlg[i] = false;
		_item[i] = 0;
	}
}

/// <summary>
/// �s���������܂Ƃ߂�
/// </summary>
void ItemMgmt::Update(VECTOR pos, int StageNum)
{
	_playerPos = pos;
	switch (StageNum)
	{
	case 0:
		Stage01();
		break;
	}
	UI();
	ItemUse();
}

void ItemMgmt::Stage01()
{
	// �����S
	int num = 0;
	PosSet(100, 10, 0); 
	if(!_collFlg[num]) AppleDraw(num);
	// ------
	num++;
	PosSet(45, -200, 0);
	if (!_collFlg[num]) AppleDraw(num);
	// ------
	num++;
	PosSet(-80, -100, 0);
	if (!_collFlg[num]) AppleDraw(num);
	// ------
	num++;
	PosSet(95, -450, 0);
	if (!_collFlg[num]) AppleDraw(num);
	// ------
	num++;
	PosSet(-100, -600, 0);
	if (!_collFlg[num]) AppleDraw(num);
	// �o�i�i
	num++;
	PosSet(-80, -200, 1);
	if (!_collFlg[num]) BananaDraw(num);
	// ------
	num++;
	PosSet(-110, -430, 1);
	if (!_collFlg[num]) BananaDraw(num);
	// �S�[��
	num++;
	_pos[4] = VGet(0.0f, 3.0f, -1060.0f);
	GoalDraw();
}

/// <summary>
/// �ʒu�̃Z�b�g
/// </summary>
void ItemMgmt::PosSet(float x, float z, int num)
{
	_pos[num] = VGet(x, 5.0f, z);
}

/// <summary>
/// �����S�̕`��
/// </summary>
void ItemMgmt::AppleDraw(int num)
{
	Draw(0, VGet(1.0f, 1.0f, 1.0f));
	Collision(0, num);
}

/// <summary>
/// �o�i�i�̕`��
/// </summary>
void ItemMgmt::BananaDraw(int num)
{
	Draw(1, VGet(1.0f, 1.0f, 1.0f));
	Collision(1, num);
}

/// <summary>
/// �S�[���̕`��
/// </summary>
void ItemMgmt::GoalDraw()
{
	Draw(4, VGet(3.0f, 3.0f, 3.0f));

	float x = pow(pow(_pos[4].x - _playerPos.x, 2.0), 0.5);
	float z = pow(pow(_pos[4].z - _playerPos.z, 2.0), 0.5);
	float dist = pow(pow(x, 2.0) + pow(z, 2.0), 0.5);
	if (dist <= 8.0f)
		SceneManager::NowSceneName = GameClear;
}

/// <summary>
/// �`��p
/// </summary>
void ItemMgmt::Draw(int num, VECTOR size)
{
	// ���f���`��
	MV1SetPosition(_itemModel[num], _pos[num]);
	MV1SetScale(_itemModel[num], size);
	MV1DrawModel(_itemModel[num]);
}

/// <summary>
/// UI�`��
/// </summary>
void ItemMgmt::UI()
{
	char Str1[256];
	sprintf_s(Str1, 256, "�����S:%d", _item[0]);
	DrawString(10, 25, Str1, GetColor(0, 0, 0));
	sprintf_s(Str1, 256, "�΂Ȃ�:%d", _item[1]);
	DrawString(10, 40, Str1, GetColor(0, 0, 0));
	sprintf_s(Str1, 256, "HP��:%d", _item[2]);
	DrawString(10, 55, Str1, GetColor(0, 0, 0));
	sprintf_s(Str1, 256, "OH����:%d", _item[3]);
	DrawString(10, 70, Str1, GetColor(0, 0, 0));

	sprintf_s(Str1, 256, "OH:%d", _ohProb);
	DrawString(1100, 10, Str1, GetColor(0, 0, 0));
}

/// <summary>
/// �A�C�e���g�p
/// </summary>
void ItemMgmt::ItemUse()
{
	int time = 100;
	if (CheckHitKey(KEY_INPUT_1) && _item[0] != 0)
	{
		_playerMgmt->ItemUse(0);
		_item[0]--;
		_ohProb += _ohUpRatio;
		BecomeOH();
		Sleep(time);
	}
	else if (CheckHitKey(KEY_INPUT_2) && _item[1] != 0)
	{
		_playerMgmt->ItemUse(1);
		_item[1]--;
		_ohProb += _ohUpRatio;
		BecomeOH();
		Sleep(time);
	}
	else if (CheckHitKey(KEY_INPUT_3) && _item[2] != 0)
	{
		_playerMgmt->ItemUse(2);
		_item[2]--;
		Sleep(time);
	}
	else if (CheckHitKey(KEY_INPUT_4) && _item[3] != 0)
	{
		_playerMgmt->ItemUse(3);
		_item[3]--;
		_ohProb = 0;
		Sleep(time);
	}
}

/// <summary>
/// OH�ɂȂ�
/// </summary>
void ItemMgmt::BecomeOH()
{
	int rnd = (rand() % 100) + 1;
	if (rnd <= _ohProb)
	{
		_playerMgmt->BecomeOH();
	}
}

/// <summary>
/// �����蔻��
/// </summary>
void ItemMgmt::Collision(int num, int collisionNum)
{
	float x = pow(pow(_pos[num].x - _playerPos.x, 2.0), 0.5);
	float z = pow(pow(_pos[num].z - _playerPos.z, 2.0), 0.5);
	float dist = pow(pow(x, 2.0) + pow(z, 2.0), 0.5);

	if (dist <= 8.0f)
	{
		_collFlg[collisionNum] = true;
		_item[num]++;
	}
	else _collFlg[collisionNum] = false;
}

//_playerMgmt->ItemUse(num);