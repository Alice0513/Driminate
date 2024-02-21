/*----------------------------------------------------------*/
/*�X�e�[�W�̃R���W�����Ǘ��N���X          �@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��19�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "StageCollision.h"

using namespace std;

// �R���W�������肷��m�[�h�\����
typedef struct _CollisionNode 
{
	int frameIndex; // �t���[���C���f�b�N�X
	string name;    // �t���[����
} CollisionNode;
static vector<CollisionNode*> colFrameVec;

/// <summary>
/// �R���X�g���N�^
/// </summary>
StageCollision::StageCollision()
{
	_stageModel[0] = MV1LoadModel("Model/Stage/Stage01.mv1");
	_spaceModel[0] = MV1LoadModel("Model/Stage/Water01.mv1");
	_stageModel[1] = MV1LoadModel("Model/Stage/Stage02.mv1");
	_spaceModel[1] = MV1LoadModel("Model/Stage/Water02.mv1");
}

void StageCollision::GetPlayer(PlayerMgmt* PlayerMgmt)
{
	_playerMgmt = PlayerMgmt;
}

/// <summary>
/// ��ɍs��
/// </summary>
void StageCollision::Update(int num, VECTOR playerPos)
{
	// Player�ƒn�ʃ��f���̃q�b�g����
	float offset = 0.0f;
	_playerMgmt->CollProcStage(HitCheck(_stageModel[num], playerPos, &offset), offset);
	_playerMgmt->CollProcWater(HitCheck(_spaceModel[num], playerPos, &offset), offset);
	_playerMgmt->CollProcStageSide(HitCheck(_stageModel[num], playerPos, &offset), offset);

	// ���f���`��
	MV1SetPosition(_stageModel[num], _pos);
	MV1SetScale(_stageModel[num], VGet(5.0f, 5.0f, 5.0f));
	MV1DrawModel(_stageModel[num]);

	// ���f���`��
	MV1SetPosition(_spaceModel[num], _pos);
	MV1SetScale(_spaceModel[num], VGet(5.0f, 5.0f, 5.0f));
	MV1DrawModel(_spaceModel[num]);
}

/// <summary>
/// �����蔻��
/// </summary>
bool StageCollision::HitCheck(int model, VECTOR pos, float* offset)
{
	bool result = false;

	// ������̂���|���S����T��
	for (int i = 0; i < colFrameVec.size(); i++)
	{
		MV1RefreshReferenceMesh(model, colFrameVec[i]->frameIndex, TRUE);

		// ���_�����[���h���W�ϊ�������ԂŃ|���S�������擾���܂�
		MV1_REF_POLYGONLIST  RefPoly = MV1GetReferenceMesh(model, colFrameVec[i]->frameIndex, TRUE);

		// �O�p�`�̐������ŌJ��Ԃ��������܂�
		for (int j = 0; j < RefPoly.PolygonNum; j++)
		{
			// �|���S���̒��_���W���擾
			// RefPoly.Vertexs�i���_���W�̔z��j
			// RefPoly.Polygons[j]�́A�|���S���z���j�Ԗڂ̃|���S�����w��
			// RefPoly.Polygons[j].VIndex[0]�́A�|���S���z���j�Ԗڂ̃|���S����0�Ԗڂ̒��_���w��
			VECTOR tri_v0 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[0]].Position;
			VECTOR tri_v1 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[1]].Position;
			VECTOR tri_v2 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[2]].Position;

			// �n�ʂ̏�ɏ悹��q�b�g����Ȃ̂ŁA���_�@���̌���������Y���W�̖@�����P���_�ł�
			// ������łȂ��|���S���̓q�b�g���肵�Ȃ�
			VECTOR tri_nv0 = VNorm(RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[0]].Normal);
			VECTOR tri_nv1 = VNorm(RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[1]].Normal);
			VECTOR tri_nv2 = VNorm(RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[2]].Normal);
			if (tri_nv0.y <= 0.0f || tri_nv1.y <= 0.0f || tri_nv2.y <= 0.0f) continue;

			// �|���S���̒��_���W���p�����[�^�[�Ƃ��ēn���A�O�p�`�̓��O��������܂�
			int hit = HitTriangle(tri_v0, tri_v1, tri_v2, pos);;
			if (hit == 1)
			{
				// �q�b�g����
				result = true;

				// �O�p�`�Ɣ���_�Ƃ̌�_��Y���W�����߂�
				//*offset_y = tri_v0.y;
				*offset = GetTriangleIntersectionPointY(tri_v0, tri_v1, tri_v2, pos);

				break;
			}
		}
	}
	return result;
}

/// <summary>
/// �O�p�`�̌���Y��
/// </summary>
float StageCollision::GetTriangleIntersectionPointY(VECTOR tri_v0, VECTOR tri_v1, VECTOR tri_v2, VECTOR ray)
{
	VECTOR n, vec1, vec2;
	float d = 0.0f;

	// �O�p�`�̒��_���W����Q�{�̃x�N�g�������
	vec1 = VSub(tri_v1, tri_v0);
	vec2 = VSub(tri_v2, tri_v1);

	// �O�p�`�̖@���x�N�g�����Z�o����
	n = VCross(vec1, vec2);

	// �@���x�N�g����P�ʃx�N�g����
	n = VNorm(n);

	d = -VDot(n, tri_v0);

	// ���ʂ̕�������ό`���Č����_�ƂȂ�Y���W�𓱂�
	// ���ʂ̕����� ax + by + cz + d = 0���
	//return -(n.x * ray.x + n.z * ray.z + d) / n.y;
	//float y = -(n.x * ray.x + n.z * ray.z + d) / n.y;
	float p = -(n.x * ray.x + n.z * ray.z + d);
	float y = p / n.y;

	return y;
}

/// <summary>
/// �O�p�`�̓����蔻��
/// </summary>
bool StageCollision::HitTriangle(VECTOR tri_v0, VECTOR tri_v1, VECTOR tri_v2, VECTOR p)
{
	VECTOR v0;
	VECTOR v1;
	VECTOR v2;

	// �T�C�N���x�N�g�����R�{���
	VECTOR t_v0 = VSub(tri_v1, tri_v0);
	VECTOR t_v1 = VSub(tri_v2, tri_v1);
	VECTOR t_v2 = VSub(tri_v0, tri_v2);

	// �e���_�Ɣ���_�܂ł̃x�N�g�����R�{���
	v0 = VSub(p, tri_v0);
	v1 = VSub(p, tri_v1);
	v2 = VSub(p, tri_v2);

	//�O�ς��Ƃ肷�ׂē��������̃x�N�g�����ǂ����𒲂ׂ�i�����Ȃ�����ɂ���j
	VECTOR cp1 = VCross(t_v0, v0);
	VECTOR cp2 = VCross(t_v1, v1);
	VECTOR cp3 = VCross(t_v2, v2);

	if (cp1.y >= 0.0f) {
		if (cp2.y >= 0.0f && cp3.y >= 0.0f) {
			// �����������Ȃ̂ŎO�p�`�̓���
			return true;
		}
	}
	else {
		if (cp2.y < 0.0f && cp3.y < 0.0f) {
			// �����������Ȃ̂ŎO�p�`�̓���
			return true;
		}
	}

	return false;
}

void traverse(int modelHandle, int parent_index, string root_name)
{
	// parent_index�Ŏw�肳�ꂽ�m�[�h�����q�m�[�h�����擾
	int num_of_child = MV1GetFrameChildNum(modelHandle, parent_index);
	for (int i = 0; i < num_of_child; i++)
	{
		int index = MV1GetFrameChild(modelHandle, parent_index, i);

		// ���b�V������0�ȏ�Ȃ�A���_�����݂���m�[�h�Ȃ̂ŁA�����蔻��m�[�h�Ƃ���vector�z��ɓo�^
		if (MV1GetFrameMeshNum(modelHandle, index) > 0)
		{
			if (MV1SetupReferenceMesh(modelHandle, index, TRUE) == 0)
			{	// DX���C�u�����Ƀ��b�V���Q�Ɨp�m�[�h�Ƃ��Ďw�����Ă���
				// �����Ńt���[���i�m�[�h�jindex���L�^���Ă���
				CollisionNode* colNodePtr = new CollisionNode;
				colNodePtr->frameIndex = index;                         // �t���[���C���f�b�N�X
				colNodePtr->name = MV1GetFrameName(modelHandle, index); // �t���[����
				colFrameVec.push_back(colNodePtr);                      // �R���W�������肷��m�[�h��vector�z��֒ǉ�
			}
		}

		// �ċA�R�[���ŊK�w��H��
		traverse(modelHandle, index, root_name);
	}
}

/// <summary>
/// �m�[�h��]��
/// </summary>
void StageCollision::EvaluateNode()
{
	for (int i = 0; i < 5; i++)
	{
		int root_index = MV1SearchFrame(_stageModel[i], "Stage");
		traverse(_stageModel[i], root_index, "Stage");
		root_index = MV1SearchFrame(_spaceModel[i], "Stage");
		traverse(_spaceModel[i], root_index, "Stage");
	}

}

/// <summary>
/// �j������
/// </summary>
void StageCollision::DeleteSet()
{
	delete _playerMgmt;
}