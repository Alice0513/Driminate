/*----------------------------------------------------------*/
/*ステージのコリジョン管理クラスヘッダー  　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月19日 　　　　　　                              */
/*----------------------------------------------------------*/
#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "Dxlib.h"
#include "PlayerMgmt.h"

class StageCollision
{
private:
	PlayerMgmt* _playerMgmt;

	int _stageModel[5]; // ステージの
	int _spaceModel[2];    // 水の
	VECTOR _pos = VGet(0.0f, 0.0f, 0.0f);

	float _moveX = 3.0f;
	float _moveZ = 3.0f;
public:
	StageCollision();
	void GetPlayer(PlayerMgmt* PlayerMgmt);
	void Update(int num, VECTOR playerPos);
	bool HitCheck(int model, VECTOR pos, float* offset);
	bool HitTriangle(VECTOR tri_v0, VECTOR tri_v1, VECTOR tri_v2, VECTOR p);
	float GetTriangleIntersectionPointY(VECTOR tri_v0, VECTOR tri_v1, VECTOR tri_v2, VECTOR ray);
	void EvaluateNode();
	void DeleteSet();
};
