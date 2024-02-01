/*----------------------------------------------------------*/
/*�V�[���Ǘ��N���X�w�b�_�[�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��17�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#pragma once
#include "Dxlib.h"
#include <string> 
#include "TitleScene.h"
#include "Stage01Scene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "StageSelectScene.h"

// �V�[���ꗗ
static enum Scene
{
	Title,
	StageSelect,
	Stage01,
	Shop,
	GameClear,
	GameOver
};

class SceneManager
{
private:
	TitleScene* _titleScene = new TitleScene();
	Stage01Scene* _stage01Scene = new Stage01Scene();
	GameClearScene* _gameClearScene = new GameClearScene();
	GameOverScene* _gameOverScene = new GameOverScene();
	StageSelectScene* _stageSelectScene = new StageSelectScene();

public:
	static Scene NowSceneName;//���̃V�[��
	static Scene SelectSceneName;//���̃V�[��(�\��)

	SceneManager(); // �R���X�g���N�^
	void SceneSelect();
	void DeleteSet();

};