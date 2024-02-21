/*----------------------------------------------------------*/
/*camera�̐���N���X�w�b�_�[ �@     �@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��18�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#pragma once
#include <cmath>
#include <iostream>
#include "Dxlib.h"

class CameraCntl
{
private:
	// std::acos(-1)  180�x
	float _angle = std::acos(-1)/2; // �p�x
	float _angleSpeed = 0.05f; // �p�x�̃X�s�[�h
	float _radius = 72.0f; // ���a
	VECTOR _pos = VGet(0.0f, 60.0f, -72.0f); // �ʒu
public:
	CameraCntl();
	void ValueReset();
	void StageMove(VECTOR playerPos);
};