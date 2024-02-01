/*----------------------------------------------------------*/
/*�Q�[���̃��C������@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F1��17�� �@�@�@�@�@�@                              */
/*----------------------------------------------------------*/
#include <math.h>
#include "DxLib.h"
#include "SceneManager.h"

// �O���[�o��

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true); //Window���[�h
	SetWindowSizeChangeEnableFlag(false, false);// Windows�̃T�C�Y�Œ�
	//// ��ʃT�C�Y�̐ݒ�
	//SetGraphMode(1920, 1080, 32);
	SetGraphMode(1200, 800, 32);

	if (DxLib_Init() == -1) return -1;// DX���C�u�����������̏���(�G���[���N�����璼���ɏI��)
	SetDrawScreen(DX_SCREEN_BACK);// �`�悷���ʂ̎w��
	SetUseLighting(FALSE);//���C�e�B���O�v�Z����

	// ����
	SceneManager* sceneManager = new SceneManager();

	//// ���C�����[�v
	// ESC�L�[�������ꂽ��I��(��ʂ����)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();// ��ʍ폜
		DrawBox(0, 0, 1200, 800, GetColor(160, 216, 255), true);// �w�i�̐F
		sceneManager->SceneSelect();

		ScreenFlip();// ��ʃt���b�v
	}

	// new�ō�������̂�delete
	sceneManager->DeleteSet();
	delete sceneManager;

	DxLib_End();// DX���C�u�����g�p�̏����I��
	return 0;// �\�t�g�I��
}