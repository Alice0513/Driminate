/*----------------------------------------------------------*/
/*playerの管理クラスヘッダー 　     　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月17日 　　　　　　                              */
/*----------------------------------------------------------*/
#pragma once
#include <chrono>
#include <thread>
#include "Dxlib.h"
#include "CameraCntl.h"

class PlayerMgmt
{
private:
	CameraCntl* _cameraCntl = new CameraCntl();

	int _model;    // メインのモデル格納用
	int _anima[2]; // idle,walk

	float _rot = 0.0f; // プレイヤーの向き（角度）
	float _rotSTR;
	float _animaTotalTime, _animaTime = 0.0f; // アニメーションの時間間隔
	int _attachIdx;

	VECTOR _pos = VGet(0.0f, 5.0f, 0.0f); // 位置
	VECTOR _dir = VGet(0.0f, 0.0f, 0.0f); // 方向
	float _angleSpeed = 0.05f;

	bool _walkFlg = false;
	bool _nowWalkFlg = false;

	float _moveSpeed = 1.5f;    // 移動量
	float _startSpeed = 1.5f;   // 初めの速度
	float _upSpeed = 1.0f;      // アイテム使用
	float _ohSpeed = 10.0f;     // OH実施
	bool _jumpFlg = false;
	float _jumpStart;
	float _jumpHeight = 100.0f;  //ジャンプの高さ
	float _startHeight = 50.0f; // 初めの高さ
	float _upHeight = 20.0f;     // アイテム使用
	float _ohHeight = 100.0f;   // OH実施
	float _jumpSpeed = 4.0f;

	// 速さ、ジャンプの設定用
	bool _onFloor = false;
	bool _onWater = false;
	bool _onSide = false;
	bool _ohFlg = false;
	int _cnt = 0;
	int _timerCnt = 0;
	long start = 0;
	long end = 0;
	VECTOR _playerTimerPos = VGet(0.0f, 0.0f, 0.0f);

	// HP関係
	int _hp[2] = { 100, 100 }; // Now、Max
	int _waterDamage = 10;     // 水のダメージ
	int _ohDamage = 20;        // OHのダメージ
public:
	PlayerMgmt();
	void Update(int model);
	void Draw(); // 描画
	void Move(); // 動き
	void Jump();
	void HPDamage(int damage);
	void CollProcStage(bool stageFlg, float offset_y);
	void CollProcStageSide(bool stageSideFlg, float offset);
	void CollProcWater(bool waterFlg, float offset_y);
	void Animation();
	void DeleteSet();
	void ItemUse(int num);
	void BecomeOH();

	VECTOR GetPlayerPos()
	{
		return _pos;
	}
};

