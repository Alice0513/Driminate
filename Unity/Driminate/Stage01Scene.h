/*----------------------------------------------------------*/
/*Stage01シーン管理クラスヘッダー 　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月17日 　　　　　　                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"
#include "PlayerMgmt.h"
#include "StageCollision.h"
#include "ItemMgmt.h"

class Stage01Scene
{
private:
	PlayerMgmt* _playerMgmt = new PlayerMgmt();
	StageCollision* _stageCollision = new StageCollision();
	ItemMgmt* _itemMgmt = new ItemMgmt();

	int _playerModel;// モデル格納用
	int _cnt = 0;
public:
	Stage01Scene();
	void Update();
	void DeleteSet();
};

