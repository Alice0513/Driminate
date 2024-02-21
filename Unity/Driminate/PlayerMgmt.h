/*----------------------------------------------------------*/
/*player�̊Ǘ��N���X�w�b�_�[ �@     �@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��17�� �@�@�@�@�@�@                              */
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

	int _model;    // ���C���̃��f���i�[�p
	int _anima[2]; // idle,walk

	float _rot = 0.0f; // �v���C���[�̌����i�p�x�j
	float _rotSTR;
	float _animaTotalTime, _animaTime = 0.0f; // �A�j���[�V�����̎��ԊԊu
	int _attachIdx;

	VECTOR _pos = VGet(0.0f, 5.0f, 0.0f); // �ʒu
	VECTOR _dir = VGet(0.0f, 0.0f, 0.0f); // ����
	float _angleSpeed = 0.05f;

	bool _walkFlg = false;
	bool _nowWalkFlg = false;

	float _moveSpeed = 1.5f;    // �ړ���
	float _startSpeed = 1.5f;   // ���߂̑��x
	float _upSpeed = 1.0f;      // �A�C�e���g�p
	float _ohSpeed = 10.0f;     // OH���{
	bool _jumpFlg = false;
	float _jumpStart;
	float _jumpHeight = 100.0f;  //�W�����v�̍���
	float _startHeight = 50.0f; // ���߂̍���
	float _upHeight = 20.0f;     // �A�C�e���g�p
	float _ohHeight = 100.0f;   // OH���{
	float _jumpSpeed = 4.0f;

	// �����A�W�����v�̐ݒ�p
	bool _onFloor = false;
	bool _onWater = false;
	bool _onSide = false;
	bool _ohFlg = false;
	int _cnt = 0;
	int _timerCnt = 0;
	long start = 0;
	long end = 0;
	VECTOR _playerTimerPos = VGet(0.0f, 0.0f, 0.0f);

	// HP�֌W
	int _hp[2] = { 100, 100 }; // Now�AMax
	int _waterDamage = 10;     // ���̃_���[�W
	int _ohDamage = 20;        // OH�̃_���[�W
public:
	PlayerMgmt();
	void Update(int model);
	void Draw(); // �`��
	void Move(); // ����
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

