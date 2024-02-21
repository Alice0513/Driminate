/*----------------------------------------------------------*/
/*Stage02シーン管理クラスヘッダー 　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：2月8日  　　　　　　                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"
#include "PlayerMgmt.h"
#include "StageCollision.h"
#include "ItemMgmt.h"
#include "UISet.h"

class Stage02Scene
{
private:
	PlayerMgmt* _playerMgmt = new PlayerMgmt();
	StageCollision* _stageCollision = new StageCollision();
	ItemMgmt* _itemMgmt = new ItemMgmt();
	UISet* _uiSet = new UISet();

	int _playerModel;// モデル格納用
	int _cnt = 0;
public:
	Stage02Scene();
	void Update();
	void DeleteSet();
};