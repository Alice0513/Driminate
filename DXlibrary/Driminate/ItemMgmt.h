/*----------------------------------------------------------*/
/*アイテムの管理クラスヘッダー 　　   　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月26日 　　　　　　                              */
/*----------------------------------------------------------*/
#pragma once
#include <vector>
#include <stdio.h>
#include <math.h>
#include "Dxlib.h"
#include "PlayerMgmt.h"

class ItemMgmt
{
private:
	PlayerMgmt* _playerMgmt;

	int _itemModel[10];
	VECTOR _pos[10];
	VECTOR _playerPos = VGet(0.0f, 0.0f, 0.0f);

	bool _collFlg[10];

	int _item[10];
	int _ohUpRatio = 25;
	int _ohProb = 0;

	int _treeModel;
	VECTOR _treePos = VGet(0.0f, 0.0f, 0.0f);

	int _shopModel;

public:
	ItemMgmt();
	void ValueReset();
	void Update(VECTOR pos, int StageNum);
	void Draw(int num, VECTOR size);
	void Stage01();
	void Stage02();
	void PosSet(float x, float z, int num);
	void TreeDraw();
	void TreeCollision(int num);
	void ShopCollision(float shopX, float shopZ);
	void AppleDraw(int num);
	void BananaDraw(int num);
	void GoalDraw();
	void Collision(int num, int collisionNum);
	void UI();
	void ItemUse();
	void BecomeOH();
	void GetPlayer(PlayerMgmt* PlayerMgmt);

	bool GameClearFlg = false;
};

