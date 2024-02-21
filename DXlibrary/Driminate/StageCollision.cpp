/*----------------------------------------------------------*/
/*ステージのコリジョン管理クラス          　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月19日 　　　　　　                              */
/*----------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "StageCollision.h"

using namespace std;

// コリジョン判定するノード構造体
typedef struct _CollisionNode 
{
	int frameIndex; // フレームインデックス
	string name;    // フレーム名
} CollisionNode;
static vector<CollisionNode*> colFrameVec;

/// <summary>
/// コンストラクタ
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
/// 常に行う
/// </summary>
void StageCollision::Update(int num, VECTOR playerPos)
{
	// Playerと地面モデルのヒット判定
	float offset = 0.0f;
	_playerMgmt->CollProcStage(HitCheck(_stageModel[num], playerPos, &offset), offset);
	_playerMgmt->CollProcWater(HitCheck(_spaceModel[num], playerPos, &offset), offset);
	_playerMgmt->CollProcStageSide(HitCheck(_stageModel[num], playerPos, &offset), offset);

	// モデル描画
	MV1SetPosition(_stageModel[num], _pos);
	MV1SetScale(_stageModel[num], VGet(5.0f, 5.0f, 5.0f));
	MV1DrawModel(_stageModel[num]);

	// モデル描画
	MV1SetPosition(_spaceModel[num], _pos);
	MV1SetScale(_spaceModel[num], VGet(5.0f, 5.0f, 5.0f));
	MV1DrawModel(_spaceModel[num]);
}

/// <summary>
/// 当たり判定
/// </summary>
bool StageCollision::HitCheck(int model, VECTOR pos, float* offset)
{
	bool result = false;

	// 当たりのあるポリゴンを探す
	for (int i = 0; i < colFrameVec.size(); i++)
	{
		MV1RefreshReferenceMesh(model, colFrameVec[i]->frameIndex, TRUE);

		// 頂点をワールド座標変換した状態でポリゴン情報を取得します
		MV1_REF_POLYGONLIST  RefPoly = MV1GetReferenceMesh(model, colFrameVec[i]->frameIndex, TRUE);

		// 三角形の数だけで繰り返し処理します
		for (int j = 0; j < RefPoly.PolygonNum; j++)
		{
			// ポリゴンの頂点座標を取得
			// RefPoly.Vertexs（頂点座標の配列）
			// RefPoly.Polygons[j]は、ポリゴン配列のj番目のポリゴンを指す
			// RefPoly.Polygons[j].VIndex[0]は、ポリゴン配列のj番目のポリゴンの0番目の頂点を指す
			VECTOR tri_v0 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[0]].Position;
			VECTOR tri_v1 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[1]].Position;
			VECTOR tri_v2 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[2]].Position;

			// 地面の上に乗せるヒット判定なので、頂点法線の向きを見てY座標の法線が１頂点でも
			// 上向きでないポリゴンはヒット判定しない
			VECTOR tri_nv0 = VNorm(RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[0]].Normal);
			VECTOR tri_nv1 = VNorm(RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[1]].Normal);
			VECTOR tri_nv2 = VNorm(RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[2]].Normal);
			if (tri_nv0.y <= 0.0f || tri_nv1.y <= 0.0f || tri_nv2.y <= 0.0f) continue;

			// ポリゴンの頂点座標をパラメーターとして渡し、三角形の内外判定をします
			int hit = HitTriangle(tri_v0, tri_v1, tri_v2, pos);;
			if (hit == 1)
			{
				// ヒットした
				result = true;

				// 三角形と判定点との交点のY座標を求める
				//*offset_y = tri_v0.y;
				*offset = GetTriangleIntersectionPointY(tri_v0, tri_v1, tri_v2, pos);

				break;
			}
		}
	}
	return result;
}

/// <summary>
/// 三角形の交差Y軸
/// </summary>
float StageCollision::GetTriangleIntersectionPointY(VECTOR tri_v0, VECTOR tri_v1, VECTOR tri_v2, VECTOR ray)
{
	VECTOR n, vec1, vec2;
	float d = 0.0f;

	// 三角形の頂点座標から２本のベクトルを作る
	vec1 = VSub(tri_v1, tri_v0);
	vec2 = VSub(tri_v2, tri_v1);

	// 三角形の法線ベクトルを算出する
	n = VCross(vec1, vec2);

	// 法線ベクトルを単位ベクトル化
	n = VNorm(n);

	d = -VDot(n, tri_v0);

	// 平面の方程式を変形して交差点となるY座標を導く
	// 平面の方程式 ax + by + cz + d = 0より
	//return -(n.x * ray.x + n.z * ray.z + d) / n.y;
	//float y = -(n.x * ray.x + n.z * ray.z + d) / n.y;
	float p = -(n.x * ray.x + n.z * ray.z + d);
	float y = p / n.y;

	return y;
}

/// <summary>
/// 三角形の当たり判定
/// </summary>
bool StageCollision::HitTriangle(VECTOR tri_v0, VECTOR tri_v1, VECTOR tri_v2, VECTOR p)
{
	VECTOR v0;
	VECTOR v1;
	VECTOR v2;

	// サイクルベクトルを３本作る
	VECTOR t_v0 = VSub(tri_v1, tri_v0);
	VECTOR t_v1 = VSub(tri_v2, tri_v1);
	VECTOR t_v2 = VSub(tri_v0, tri_v2);

	// 各頂点と判定点までのベクトルを３本作る
	v0 = VSub(p, tri_v0);
	v1 = VSub(p, tri_v1);
	v2 = VSub(p, tri_v2);

	//外積をとりすべて同じ方向のベクトルかどうかを調べる（同じなら内部にある）
	VECTOR cp1 = VCross(t_v0, v0);
	VECTOR cp2 = VCross(t_v1, v1);
	VECTOR cp3 = VCross(t_v2, v2);

	if (cp1.y >= 0.0f) {
		if (cp2.y >= 0.0f && cp3.y >= 0.0f) {
			// 向きが同じなので三角形の内側
			return true;
		}
	}
	else {
		if (cp2.y < 0.0f && cp3.y < 0.0f) {
			// 向きが同じなので三角形の内側
			return true;
		}
	}

	return false;
}

void traverse(int modelHandle, int parent_index, string root_name)
{
	// parent_indexで指定されたノードが持つ子ノード数を取得
	int num_of_child = MV1GetFrameChildNum(modelHandle, parent_index);
	for (int i = 0; i < num_of_child; i++)
	{
		int index = MV1GetFrameChild(modelHandle, parent_index, i);

		// メッシュ数が0以上なら、頂点が存在するノードなので、当たり判定ノードとしてvector配列に登録
		if (MV1GetFrameMeshNum(modelHandle, index) > 0)
		{
			if (MV1SetupReferenceMesh(modelHandle, index, TRUE) == 0)
			{	// DXライブラリにメッシュ参照用ノードとして指示しておく
				// ここでフレーム（ノード）indexを記録しておく
				CollisionNode* colNodePtr = new CollisionNode;
				colNodePtr->frameIndex = index;                         // フレームインデックス
				colNodePtr->name = MV1GetFrameName(modelHandle, index); // フレーム名
				colFrameVec.push_back(colNodePtr);                      // コリジョン判定するノードをvector配列へ追加
			}
		}

		// 再帰コールで階層を辿る
		traverse(modelHandle, index, root_name);
	}
}

/// <summary>
/// ノードを評価
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
/// 破棄する
/// </summary>
void StageCollision::DeleteSet()
{
	delete _playerMgmt;
}