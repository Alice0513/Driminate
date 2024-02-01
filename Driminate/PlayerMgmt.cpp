/*----------------------------------------------------------*/
/*playerの管理クラス   　　　　　　　     　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月17日 　　　　　　                              */
/*----------------------------------------------------------*/
#include <stdio.h>  
#include <time.h>  
#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "PlayerMgmt.h"
#include "CameraCntl.h"
#include "SceneManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerMgmt::PlayerMgmt()
{
	_anima[0] = MV1LoadModel("Model/Player/Idle.mv1");
	_anima[1] = MV1LoadModel("Model/Player/Walk.mv1");

	_attachIdx = MV1AttachAnim(_model, 0, _anima[0]); // モデルとアニメーションの関連付け
	_animaTotalTime = MV1GetAttachAnimTotalTime(_model, _attachIdx); // 時間
}

/// <summary>
/// 行う処理のまとめ
/// </summary>
/// <param name="model"></param>
void PlayerMgmt::Update(int model)
{
	_rotSTR = _rot;
	_model = model;
	Draw();
	Move();
	Animation();
}

/// <summary>
/// 描画
/// </summary>
void PlayerMgmt::Draw()
{
	// カメラ
	_cameraCntl->StageMove(_pos);
	// モデル描画
	MV1SetPosition(_model, _pos);
	MV1SetScale(_model, VGet(1.8f, 1.8f, 1.8f));
	MV1SetRotationXYZ(_model, _dir);
	MV1DrawModel(_model);

	char Str1[256];
	sprintf_s(Str1, 256, "PlayerPos:%.1f, %.1f, %.1f", _pos.x, _pos.y, _pos.z);
	DrawString(10, 10, Str1, GetColor(0, 0, 0));

	if (_ohFlg)
	{
		sprintf_s(Str1, 256, "OH中");
		DrawString(1100, 25, Str1, GetColor(0, 0, 0));
		HPDamage(_ohDamage);
	}
	if (_onWater)
	{
		HPDamage(_waterDamage);
	}
	if(_hp[0] <= 0)
		SceneManager::NowSceneName = GameOver;
}

/// <summary>
/// 動き
/// </summary>
void PlayerMgmt::Move()
{
	Jump();

	// 前進
	if (CheckHitKey(KEY_INPUT_W))
	{
		_pos.x -= sinf(_rot) * _moveSpeed;
		_pos.z -= cosf(_rot) * _moveSpeed;
		_nowWalkFlg = true;
	}
	// 後退
	else if (CheckHitKey(KEY_INPUT_S))
	{
		_pos.x += sinf(_rot) * _moveSpeed;
		_pos.z += cosf(_rot) * _moveSpeed;
		_nowWalkFlg = true;
	}
	// 右
	else if (CheckHitKey(KEY_INPUT_D))
	{
		_rotSTR -= std::acos(-1) / 2;
		_pos.x += sinf(_rotSTR) * (_moveSpeed - 0.5f);
		_pos.z += cosf(_rotSTR) * (_moveSpeed - 0.5f);
		_nowWalkFlg = true;
		_rotSTR = _rot;
	}
	// 左
	else if (CheckHitKey(KEY_INPUT_A))
	{
		_rotSTR -= std::acos(-1) / 2;
		_pos.x -= sinf(_rotSTR) * (_moveSpeed - 0.5f);
		_pos.z -= cosf(_rotSTR) * (_moveSpeed - 0.5f);
		_nowWalkFlg = true;
		_rotSTR = _rot;
	}else
	{
		_nowWalkFlg = false;
	}

	// →
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		_rot += _angleSpeed;
		_dir.y += _angleSpeed;
	}
	// ←
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		_rot -= _angleSpeed;
		_dir.y -= _angleSpeed;
	}
}

/// <summary>
/// ジャンプ処理
/// </summary>
void PlayerMgmt::Jump()
{
	// ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) && _cnt == 0)
	{
		_jumpFlg = true;
		_jumpStart = _pos.y;
		_cnt++;
	}
	// _onFloorは水
	if (_onWater || _onFloor) {}
	else _pos.y -= 2.0f;
}

/// <summary>
/// HPのダメージ
/// </summary>
void PlayerMgmt::HPDamage(int damage)
{//0.01s
	clock_t startTime = clock();
	if(clock() - startTime == 2000)
		_hp[0] -= damage;
}

/// <summary>
/// コリジョンのオフセット
/// </summary>
/// <param name="flg">当たり判定のフラグ</param>
/// <param name="offset">プレイヤーの半径</param>
void PlayerMgmt::CollProcStage(bool stageFlg, float offset_y)
{
	if (stageFlg)
	{
		if (_jumpFlg)
		{
			if (_pos.y < _jumpStart + _jumpHeight) _pos.y += _jumpSpeed;
			else
			{
				_jumpFlg = false;
			}
		}
		else if (_pos.y >= offset_y + 3.0f)
		{
			_pos.y -= _jumpSpeed;
		}
		else if (!_jumpFlg) _cnt = 0;
	}
	_onFloor = stageFlg;

}

/// <summary>
/// コリジョンのオフセット（サイド）
/// </summary>
void PlayerMgmt::CollProcStageSide(bool stageSideFlg, float offset)
{
	bool zFlg;

	// 時間処理計算
	if (_timerCnt == 0)
	{
		start = clock();
		_timerCnt++;
	}
	else
	{
		end = clock();
		if (end - start >= 1000)
		{
			_playerTimerPos = _pos;
			_timerCnt = 0;
		}
	}

	// 負の方向
	if (_playerTimerPos.z > _pos.z) zFlg = false;
	else zFlg = true;

	if (stageSideFlg && _onWater && _pos.y < -10.0f)
	{
		if (zFlg)
		{
			_pos.z -= 5.0f;
			_pos.y = -85.0f;
		}
		else
		{
			_pos.z += 5.0f;
			_pos.y = -85.0f;
		}
	}
}

/// <summary>
/// コリジョンのオフセット
/// </summary>
void PlayerMgmt::CollProcWater(bool waterFlg, float offset_y)
{
	if (waterFlg)
	{
		if (_jumpFlg)
		{
			if (_pos.y < _jumpStart + _jumpHeight) _pos.y += _jumpSpeed;
			else
			{
				_jumpFlg = false;
			}
		}
		else if (_pos.y >= offset_y + 2.0f)
		{
			_pos.y -= 2.0f;
		}
		else if (!_jumpFlg) _cnt = 0;
	}
	_onWater = waterFlg;
}

/// <summary>
/// アニメーションの追加
/// </summary>
void PlayerMgmt::Animation()
{
	// アニメーション生成用
	_animaTime += 0.5f; // 時間セット
	if (_animaTime > _animaTotalTime) _animaTime = 0.0f; // 終了させる
	// どの時間から生成
	MV1SetAttachAnimTime(_model, _attachIdx, _animaTime);

	//// アニメーションの切り替え
	// 歩く
	if (_nowWalkFlg && _nowWalkFlg != _walkFlg)
	{
		MV1DetachAnim(_model, _attachIdx); // アニメーションを外す
		_attachIdx = MV1AttachAnim(_model, 0, _anima[1]); // 切り替え
		_animaTotalTime = MV1GetAttachAnimTotalTime(_model, _attachIdx); // 時間
		_walkFlg = _nowWalkFlg;
	}
	// アイドル
	if(!_nowWalkFlg && _nowWalkFlg != _walkFlg)
	{
		MV1DetachAnim(_model, _attachIdx); // アニメーションを外す
		_attachIdx = MV1AttachAnim(_model, 0, _anima[0]); // 切り替え
		_animaTotalTime = MV1GetAttachAnimTotalTime(_model, _attachIdx); // 時間
		_walkFlg = _nowWalkFlg;
	}
}

/// <summary>
/// アイテムを使用
/// </summary>
void PlayerMgmt::ItemUse(int num)
{
	switch (num)
	{
	case 0:
		_moveSpeed += _upSpeed;
		break;
	case 1:
		_jumpHeight += _upHeight;
		break;
	case 2:
		break;
	case 3:
		_moveSpeed = _startSpeed;
		_jumpHeight = _startHeight;
		_ohFlg = false;
		break;
	}
}

/// <summary>
/// OHになる
/// </summary>
void PlayerMgmt::BecomeOH()
{
	_ohFlg = true;
	_moveSpeed = _startSpeed + _ohSpeed;
	_jumpHeight = _startHeight + _ohHeight;
}

/// <summary>
/// 削除
/// </summary>
void PlayerMgmt::DeleteSet()
{
	delete _cameraCntl;
}