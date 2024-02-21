/*----------------------------------------------------------*/
/*�^�C�g���V�[���Ǘ��N���X  �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��17�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#include "TitleScene.h"
#include "SceneManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
{
	_titleLogo = LoadGraph("Image/TitleLogo.png");
	_enterPush = LoadGraph("Image/EnterPush.png");
}

/// <summary>
/// ���s�܂Ƃ�
/// </summary>
void TitleScene::Update()
{
	UISet();
	Sleep(100);
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		SceneManager::NowSceneName = StageSelect;
	}
}

/// <summary>
/// UI�Z�b�g
/// </summary>
void TitleScene::UISet()
{
	DrawRotaGraph(600, 350, 1.0f, 0.0f, _titleLogo, true);
	DrawRotaGraph(600, 650, 0.5f, 0.0f, _enterPush, true);
}