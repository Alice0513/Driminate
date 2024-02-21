/*----------------------------------------------------------*/
/*シーン管理クラスヘッダー　　　　　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月17日 　　　　　　                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"
#include <string> 
#include "TitleScene.h"
#include "Stage01Scene.h"
#include "Stage02Scene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "StageSelectScene.h"
#include "PlayerMgmt.h"

// シーン一覧
static enum Scene
{
	Title,
	StageSelect,
	Stage01,
	Stage02,
	Shop,
	GameClear,
	GameOver
};

class SceneManager
{
private:
	TitleScene* _titleScene = new TitleScene();
	Stage01Scene* _stage01Scene = new Stage01Scene();
	Stage02Scene* _stage02Scene = new Stage02Scene();
	GameClearScene* _gameClearScene = new GameClearScene();
	GameOverScene* _gameOverScene = new GameOverScene();
	StageSelectScene* _stageSelectScene = new StageSelectScene();
	PlayerMgmt* _playerMgmt = new PlayerMgmt();

public:
	static Scene NowSceneName;//今のシーン
	static Scene SelectSceneName;//次のシーン(予定)

	SceneManager(); // コンストラクタ
	void SceneSelect();
	void DeleteSet();

};