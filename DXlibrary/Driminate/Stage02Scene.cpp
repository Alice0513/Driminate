/*----------------------------------------------------------*/
/*Stage02シーン管理クラス   　　　　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：2月8日  　　　　　　                              */
/*----------------------------------------------------------*/
#include "Stage02Scene.h"
#include "PlayerMgmt.h"
#include "StageCollision.h"
#include "ItemMgmt.h"
#include "UISet.h"
#include "SceneManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
Stage02Scene::Stage02Scene()
{
	_playerModel = MV1LoadModel("Model/Player/Player.mv1");
}

/// <summary>
/// 行う処理のまとめ
/// </summary>
void Stage02Scene::Update()
{
	_playerMgmt->Update(_playerModel);
	if (_cnt == 0)
	{
		_stageCollision->EvaluateNode();
		_cnt++;
	}
	_stageCollision->GetPlayer(_playerMgmt);
	_itemMgmt->GetPlayer(_playerMgmt);
	_stageCollision->Update(1, _playerMgmt->GetPlayerPos());
	_itemMgmt->Update(_playerMgmt->GetPlayerPos(), 1);
	_uiSet->Update();

	if (_playerMgmt->GameOverFlg)
	{
		SceneManager::NowSceneName = GameOver;
		_playerMgmt->ValueReset();
		_itemMgmt->ValueReset();
	}
	else if (_itemMgmt->GameClearFlg)
	{
		SceneManager::NowSceneName = GameClear;
		_playerMgmt->ValueReset();
		_itemMgmt->ValueReset();
	}
}

/// <summary>
/// 削除
/// </summary>
void Stage02Scene::DeleteSet()
{
	_playerMgmt->DeleteSet();
	_stageCollision->DeleteSet();
	delete _playerMgmt;
	delete _stageCollision;
	delete _itemMgmt;
	delete _uiSet;
}
