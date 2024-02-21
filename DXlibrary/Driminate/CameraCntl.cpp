/*----------------------------------------------------------*/
/*camera�̐���N���X�w�b�_�[ �@     �@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��18�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "Dxlib.h"
#include "CameraCntl.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CameraCntl::CameraCntl()
{

}

/// <summary>
/// �l�̃��Z�b�g
/// </summary>
void CameraCntl::ValueReset()
{
	_angle = std::acos(-1) / 2;
}

/// <summary>
/// �X�e�[�W���J�����̓���
/// </summary>
/// <param name="playerPos"></param>
void CameraCntl::StageMove(VECTOR playerPos)
{
	// �J�����ƃv���C���[�̊Ԃ̋��������ɕۂ�
	//_pos.x = playerPos.x - _radius * cosf(_angle);
	_pos.y = playerPos.y + 50.0;
	//_pos.z = playerPos.z - _radius * sinf(_angle);

	// �J�����̎��_�A�����_�A�������ݒ肷��
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