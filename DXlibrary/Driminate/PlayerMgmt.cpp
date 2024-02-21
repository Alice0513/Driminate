/*----------------------------------------------------------*/
/*player�̊Ǘ��N���X   �@�@�@�@�@�@�@     �@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��17�� �@�@�@�@�@�@                              */
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
/// �R���X�g���N�^
/// </summary>
PlayerMgmt::PlayerMgmt()
{
	_anima[0] = MV1LoadModel("Model/Player/Idle.mv1");
	_anima[1] = MV1LoadModel("Model/Player/Walk.mv1");

	_shadowModel = MV1LoadModel("Model/Player/Shadow.mv1");

	_attachIdx = MV1AttachAnim(_model, 0, _anima[0]); // ���f���ƃA�j���[�V�����̊֘A�t��
	_animaTotalTime = MV1GetAttachAnimTotalTime(_model, _attachIdx); // ����
	for (int i = 0; i < 50; i++)
	{
		HitFlgList[i] = false;
	}
}

/// <summary>
/// �l�̃��Z�b�g
/// </summary>
void PlayerMgmt::ValueReset()
{
	_pos = VGet(0.0f, 5.0f, 0.0f);
	_moveSpeed = _startSpeed;
	_jumpHeight = _startHeight;
	_rot = 0.0f;
	_dir = VGet(0.0f, 0.0f, 0.0f);
	GameOverFlg = false;
	_hp[0] = _hp[1];
	_cameraCntl->ValueReset();
}

/// <summary>
/// �s�������̂܂Ƃ�
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
/// �`��
/// </summary>
void PlayerMgmt::Draw()
{
	_shadowPos.x = _pos.x;
	_shadowPos.z = _pos.z;
	// �J����
	_cameraCntl->StageMove(_pos);
	// ���f���`��
	MV1SetPosition(_model, _pos);
	MV1SetScale(_model, VGet(1.8f, 1.8f, 1.8f));
	MV1SetRotationXYZ(_model, _dir);
	MV1DrawModel(_model);

	// ���f���`��
	MV1SetPosition(_shadowModel, _shadowPos);
	MV1SetScale(_shadowModel, VGet(0.07f, 0.5f, 0.07f));
	MV1DrawModel(_shadowModel);

	for (int i = 0; i < 50; i++)
	{
		if (HitFlgList[i])
		{
			_hitFlg = true;
			break;
		}
		else _hitFlg = false;
	}

	char Str1[256];
	sprintf_s(Str1, 256, "PlayerPos:%.1f, %.1f, %.1f", _pos.x, _pos.y, _pos.z);
	DrawString(10, 10, Str1, GetColor(0, 0, 0));
	sprintf_s(Str1, 256, "PlayerHP:%d", _hp[0]);
	DrawString(10, 25, Str1, GetColor(0, 0, 0));

	if (_ohFlg)
	{
		sprintf_s(Str1, 256, "OH��");
		DrawString(1100, 25, Str1, GetColor(0, 0, 0));
		HPDamage(_ohDamage);
	}
	if (_onWater && _pos.y == -89.0f)
	{
		//GameOverFlg = true;
		HPDamage(_waterDamage);
	}
	if(_hp[0] <= 0 || _pos.y <= -300.0f)
		GameOverFlg = true;
}

/// <summary>
/// ����
/// </summary>
void PlayerMgmt::Move()
{
	Jump();
	// �O�i
	if (CheckHitKey(KEY_INPUT_W))
	{
		if (_nowMoveFlg[0] && _hitFlg){}
		else
		{
			_pos.x -= sinf(_rot) * _moveSpeed;
			_pos.z -= cosf(_rot) * _moveSpeed;
			KeyMoveCheck(0);
		}
	}
	// ���
	else if (CheckHitKey(KEY_INPUT_S))
	{
		if (_nowMoveFlg[1] && _hitFlg){}
		else
		{
			_pos.x += sinf(_rot) * _moveSpeed;
			_pos.z += cosf(_rot) * _moveSpeed;
			KeyMoveCheck(1);
		}
	}
	// �E
	else if (CheckHitKey(KEY_INPUT_D))
	{
		if (_nowMoveFlg[2] && _hitFlg){}
		else
		{
			_rotSTR -= std::acos(-1) / 2;
			_pos.x += sinf(_rotSTR) * (_moveSpeed - 0.5f);
			_pos.z += cosf(_rotSTR) * (_moveSpeed - 0.5f);
			KeyMoveCheck(2);
			_rotSTR = _rot;
		}
	}
	// ��
	else if (CheckHitKey(KEY_INPUT_A))
	{
		if (_nowMoveFlg[3] && _hitFlg){}
		else
		{
			_rotSTR -= std::acos(-1) / 2;
			_pos.x -= sinf(_rotSTR) * (_moveSpeed - 0.5f);
			_pos.z -= cosf(_rotSTR) * (_moveSpeed - 0.5f);
			KeyMoveCheck(3);
			_rotSTR = _rot;
		}
	}else
	{
		_nowWalkFlg = false;
	}

	// ��
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		_rot += _angleSpeed;
		_dir.y += _angleSpeed;
	}
	// ��
	else if (CheckHitKey(KEY_INPUT_LEFT))
	{
		_rot -= _angleSpeed;
		_dir.y -= _angleSpeed;
	}
}

/// <summary>
/// ���̓���
/// </summary>
void PlayerMgmt::KeyMoveCheck(int num)
{
	_nowWalkFlg = true;
	_timer++;
	if (_timer == 10)
	{
		for (int i = 0; i < 5; i++)
		{
			_nowMoveFlg[i] = false;
		}
		_nowMoveFlg[num] = true;
		_timer = 0;
	}
}

/// <summary>
/// �W�����v����
/// </summary>
void PlayerMgmt::Jump()
{
	// �W�����v
	if (CheckHitKey(KEY_INPUT_SPACE) && _cnt == 0)
	{
		_jumpFlg = true;
		_jumpStart = _pos.y;
		_cnt++;
	}
	// _onFloor�͐�
	if (_onWater || _onFloor) {}
	else _pos.y -= 2.0f;
}

/// <summary>
/// HP�̃_���[�W
/// </summary>
void PlayerMgmt::HPDamage(int damage)
{//0.01s
	_hp[0] -= damage;
}

/// <summary>
/// �R���W�����̃I�t�Z�b�g
/// </summary>
/// <param name="flg">�����蔻��̃t���O</param>
/// <param name="offset">�v���C���[�̔��a</param>
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

		_shadowPos.y = 1.5f;
	}
	_onFloor = stageFlg;

}

/// <summary>
/// �R���W�����̃I�t�Z�b�g�i�T�C�h�j
/// </summary>
void PlayerMgmt::CollProcStageSide(bool stageSideFlg, float offset)
{
	bool zFlg;

	// ���ԏ����v�Z
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

	// ���̕���
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
/// �R���W�����̃I�t�Z�b�g
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

		_shadowPos.y = -89.0f;
	}
	_onWater = waterFlg;
}

/// <summary>
/// �A�j���[�V�����̒ǉ�
/// </summary>
void PlayerMgmt::Animation()
{
	// �A�j���[�V���������p
	_animaTime += 0.5f; // ���ԃZ�b�g
	if (_animaTime > _animaTotalTime) _animaTime = 0.0f; // �I��������
	// �ǂ̎��Ԃ��琶��
	MV1SetAttachAnimTime(_model, _attachIdx, _animaTime);

	//// �A�j���[�V�����̐؂�ւ�
	// ����
	if (_nowWalkFlg && _nowWalkFlg != _walkFlg)
	{
		MV1DetachAnim(_model, _attachIdx); // �A�j���[�V�������O��
		_attachIdx = MV1AttachAnim(_model, 0, _anima[1]); // �؂�ւ�
		_animaTotalTime = MV1GetAttachAnimTotalTime(_model, _attachIdx); // ����
		_walkFlg = _nowWalkFlg;
	}
	// �A�C�h��
	if(!_nowWalkFlg && _nowWalkFlg != _walkFlg)
	{
		MV1DetachAnim(_model, _attachIdx); // �A�j���[�V�������O��
		_attachIdx = MV1AttachAnim(_model, 0, _anima[0]); // �؂�ւ�
		_animaTotalTime = MV1GetAttachAnimTotalTime(_model, _attachIdx); // ����
		_walkFlg = _nowWalkFlg;
	}
}

/// <summary>
/// �A�C�e�����g�p
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
/// OH�ɂȂ�
/// </summary>
void PlayerMgmt::BecomeOH()
{
	_ohFlg = true;
	_moveSpeed = _startSpeed + _ohSpeed;
	_jumpHeight = _startHeight + _ohHeight;
}

/// <summary>
/// �폜
/// </summary>
void PlayerMgmt::DeleteSet()
{
	delete _cameraCntl;
}