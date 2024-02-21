/*----------------------------------------------------------*/
/*アイテムの管理クラス         　　   　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月26日 　　　　　　                              */
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
/// コンストラクタ
/// </summary>
ItemMgmt::ItemMgmt()
{
	_itemModel[0] = MV1LoadModel("Model/Item/Apple.mv1");
	_itemModel[1] = MV1LoadModel("Model/Item/Banana.mv1");
	_itemModel[4] = MV1LoadModel("Model/Item/Mushroom.mv1");
	_pos[0] = VGet(0.0f, 3.0f, 0.0f);
	_pos[1] = VGet(0.0f, 3.0f, 0.0f);
	_pos[4] = VGet(0.0f, 1.0f, 0.0f);

	_treeModel = MV1LoadModel("Model/Stage/Tree3.mv1");

	_shopModel = MV1LoadModel("Model/Stage/Hosue.mv1");

	for (int i = 0; i < 10; i++)
	{
		_collFlg[i] = false;
		_item[i] = 0;
	}
}

/// <summary>
/// 値のリセット
/// </summary>
void ItemMgmt::ValueReset()
{
	_ohProb = 0;
	for (int i = 0; i < 10; i++)
	{
		_collFlg[i] = false;
		_item[i] = 0;
	}
	GameClearFlg = false;
}

/// <summary>
/// 行う処理をまとめる
/// </summary>
void ItemMgmt::Update(VECTOR pos, int StageNum)
{
	_playerPos = pos;
	switch (StageNum)
	{
	case 0:
		Stage01();
		break;
	case 1:
		Stage02();
		break;
	}
	UI();
	ItemUse();
}

/// <summary>
/// Stage01のセット
/// </summary>
void ItemMgmt::Stage01()
{
	// リンゴ
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
	// バナナ
	num++;
	PosSet(-80, -200, 1);
	if (!_collFlg[num]) BananaDraw(num);
	// ------
	num++;
	PosSet(-110, -430, 1);
	if (!_collFlg[num]) BananaDraw(num);
	// ゴール
	num++;
	_pos[4] = VGet(0.0f, 3.0f, -1060.0f);
	GoalDraw();

	// モデル描画
	_treePos = VGet(80.0f, 0.0f, -106.0f);
	TreeDraw();
	TreeCollision(0);
	_treePos = VGet(-53.0f, 0.0f, -10.0f);
	TreeDraw();
	TreeCollision(1);
	_treePos = VGet(-120.0f, 0.0f, -150.0f);
	TreeDraw();
	TreeCollision(2);
	_treePos = VGet(45.0f, 0.0f, 8.0f);
	TreeDraw();
	TreeCollision(3);
	_treePos = VGet(-52.0f, 0.0f, -220.0f);
	TreeDraw();
	TreeCollision(4);
	_treePos = VGet(-90.0f, 0.0f, -490.0f);
	TreeDraw();
	TreeCollision(5);
	_treePos = VGet(100.0f, 0.0f, -630.0f);
	TreeDraw();
	TreeCollision(6);
	_treePos = VGet(50.0f, 0.0f, -490.0f);
	TreeDraw();
	TreeCollision(7);
	_treePos = VGet(-56.0f, 0.0f, -560.0f);
	TreeDraw();
	TreeCollision(8);
	_treePos = VGet(98.0f, 0.0f, -860.0f);
	TreeDraw();
	TreeCollision(9);
	_treePos = VGet(-40.0f, 0.0f, -1029.0f);
	TreeDraw();
	TreeCollision(10);
	_treePos = VGet(-120.0f, 0.0f, -970.0f);
	TreeDraw();
	TreeCollision(11);
	_treePos = VGet(-92.0f, 0.0f, -887.0f);
	TreeDraw();
	TreeCollision(12);
	_treePos = VGet(76.0f, 0.0f, -1085.0f);
	TreeDraw();
	TreeCollision(13);
	_treePos = VGet(61.0f, 0.0f, -1008.0f);
	TreeDraw();
	TreeCollision(14);
}

void ItemMgmt::Stage02()
{
	// リンゴ
	int num = 0;
	PosSet(100, 10, 0);
	if (!_collFlg[num]) AppleDraw(num);
	// お店 27
	MV1SetPosition(_shopModel, VGet(-55.0f, 0.0f, -950.0f));
	MV1SetScale(_shopModel, VGet(1.0f, 1.0f, 1.0f));
	MV1DrawModel(_shopModel);
	ShopCollision(-55.0f, -950.0f);
}

/// <summary>
/// 位置のセット
/// </summary>
void ItemMgmt::PosSet(float x, float z, int num)
{
	_pos[num] = VGet(x, 5.0f, z);
}

/// <summary>
/// リンゴの描画
/// </summary>
void ItemMgmt::AppleDraw(int num)
{
	Draw(0, VGet(1.0f, 1.0f, 1.0f));
	Collision(0, num);
}

/// <summary>
/// バナナの描画
/// </summary>
void ItemMgmt::BananaDraw(int num)
{
	Draw(1, VGet(1.0f, 1.0f, 1.0f));
	Collision(1, num);
}

/// <summary>
/// 木の描画
/// </summary>
void ItemMgmt::TreeDraw()
{
	MV1SetPosition(_treeModel, _treePos);
	MV1SetScale(_treeModel, VGet(2.0f, 2.0f, 2.0f));
	MV1DrawModel(_treeModel);
}

/// <summary>
/// 木の当たり判定
/// </summary>
void ItemMgmt::TreeCollision(int num)
{
	float x = pow(pow(_treePos.x - _playerPos.x, 2.0), 0.5);
	float z = pow(pow(_treePos.z - _playerPos.z, 2.0), 0.5);
	float dist = pow(pow(x, 2.0) + pow(z, 2.0), 0.5);

	if (dist <= 10.0f)
	{
		_playerMgmt->HitFlgList[num] = true;
	}
	else
	{
		_playerMgmt->HitFlgList[num] = false;
	}
}

/// <summary>
/// お店の当たり判定
/// </summary>
void ItemMgmt::ShopCollision(float shopX, float shopZ)
{
	if (_playerPos.x <= shopX + 38.0f && _playerPos.x >= shopX - 35.0f)
	{
		if (_playerPos.z <= shopZ + 35.0f && _playerPos.z >= shopZ - 29.0f)
		{
			_playerMgmt->HitFlgList[0] = true;
		}
	}
	else
	{
		_playerMgmt->HitFlgList[0] = false;
	}
}

/// <summary>
/// ゴールの描画
/// </summary>
void ItemMgmt::GoalDraw()
{
	Draw(4, VGet(3.0f, 3.0f, 3.0f));

	float x = pow(pow(_pos[4].x - _playerPos.x, 2.0), 0.5);
	float z = pow(pow(_pos[4].z - _playerPos.z, 2.0), 0.5);
	float dist = pow(pow(x, 2.0) + pow(z, 2.0), 0.5);
	if (dist <= 8.0f)
		GameClearFlg = true;
}

/// <summary>
/// 描画用
/// </summary>
void ItemMgmt::Draw(int num, VECTOR size)
{
	// モデル描画
	MV1SetPosition(_itemModel[num], _pos[num]);
	MV1SetScale(_itemModel[num], size);
	MV1DrawModel(_itemModel[num]);
}

/// <summary>
/// UI描画
/// </summary>
void ItemMgmt::UI()
{
	char Str1[256];
	for (int i = 0; i < 4; i++)
	{
		SetFontThickness(1);
		SetFontSize(30);
		sprintf_s(Str1, 256, "%d", _item[i]);
		DrawString(792 + 100 * i, 750, Str1, GetColor(255, 255, 255));
	}

	SetFontThickness(10);
	SetFontSize(17);

	sprintf_s(Str1, 256, "OH:%d", _ohProb);
	DrawString(1100, 10, Str1, GetColor(0, 0, 0));
}

/// <summary>
/// アイテム使用
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
/// OHになる
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
/// 当たり判定
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