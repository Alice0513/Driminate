/*----------------------------------------------------------*/
/*Stage01シーン管理クラス   　　　　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月17日 　　　　　　                              */
/*----------------------------------------------------------*/
#include "Stage01Scene.h"
#include "PlayerMgmt.h"
#include "StageCollision.h"
#include "ItemMgmt.h"

/// <summary>
/// コンストラクタ
/// </summary>
Stage01Scene::Stage01Scene()
{
	_playerModel = MV1LoadModel("Model/Player/Player.mv1");
}

/// <summary>
/// 行う処理のまとめ
/// </summary>
void Stage01Scene::Update()
{
	_playerMgmt->Update(_playerModel);
	if (_cnt == 0)
	{
		_stageCollision->EvaluateNode();
		_cnt++;
	}
	_stageCollision->GetPlayer(_playerMgmt);
	_itemMgmt->GetPlayer(_playerMgmt);
	_stageCollision->Update(0, _playerMgmt->GetPlayerPos());
	_itemMgmt->Update(_playerMgmt->GetPlayerPos(), 0);
}

/// <summary>
/// 削除
/// </summary>
void Stage01Scene::DeleteSet()
{
	_playerMgmt->DeleteSet();
	_stageCollision->DeleteSet();
	delete _playerMgmt;
	delete _stageCollision;
	delete _itemMgmt;
}