/*----------------------------------------------------------*/
/*cameraの制御クラスヘッダー 　     　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月18日 　　　　　　                              */
/*----------------------------------------------------------*/
#pragma once
#include <cmath>
#include <iostream>
#include "Dxlib.h"

class CameraCntl
{
private:
	// std::acos(-1)  180度
	float _angle = std::acos(-1)/2; // 角度
	float _angleSpeed = 0.05f; // 角度のスピード
	float _radius = 72.0f; // 半径
	VECTOR _pos = VGet(0.0f, 60.0f, -72.0f); // 位置
public:
	CameraCntl();
	void ValueReset();
	void StageMove(VECTOR playerPos);
};