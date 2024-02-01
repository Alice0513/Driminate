/*----------------------------------------------------------*/
/*cameraの制御クラスヘッダー 　     　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月18日 　　　　　　                              */
/*----------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "CameraCntl.h"

/// <summary>
/// コンストラクタ
/// </summary>
CameraCntl::CameraCntl()
{

}

/// <summary>
/// ステージ中カメラの動き
/// </summary>
/// <param name="playerPos"></param>
void CameraCntl::StageMove(VECTOR playerPos)
{
	// カメラとプレイヤーの間の距離を一定に保つ
	//_pos.x = playerPos.x - _radius * cosf(_angle);
	_pos.y = playerPos.y + 50.0;
	//_pos.z = playerPos.z - _radius * sinf(_angle);

	// カメラの視点、注視点、上方向を設定する
	SetCameraPositionAndTargetAndUpVec
	(
		_pos,
		VGet(playerPos.x, playerPos.y + 40.0, playerPos.z),
		VGet(0.0f, 1.0f, 0.0f)
	);
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		_angle -= _angleSpeed;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		_angle += _angleSpeed;
	}

	_pos.x = (playerPos.x + _radius * cosf(_angle));
	_pos.z = (playerPos.z + _radius * sinf(_angle));
}