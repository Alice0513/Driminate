/*----------------------------------------------------------*/
/*ゲームのメイン制御　　　　　　　　　　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：1月17日 　　　　　　                              */
/*----------------------------------------------------------*/
#include <math.h>
#include "DxLib.h"
#include "SceneManager.h"

// グローバル

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true); //Windowモード
	SetWindowSizeChangeEnableFlag(false, false);// Windowsのサイズ固定
	//// 画面サイズの設定
	//SetGraphMode(1920, 1080, 32);
	SetGraphMode(1200, 800, 32);

	if (DxLib_Init() == -1) return -1;// DXライブラリ初期化の処理(エラーが起きたら直ちに終了)
	SetDrawScreen(DX_SCREEN_BACK);// 描画する画面の指定
	SetUseLighting(FALSE);//ライティング計算処理

	// 生成
	SceneManager* sceneManager = new SceneManager();

	//// メインループ
	// ESCキーが押されたら終了(画面を閉じる)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();// 画面削除
		DrawBox(0, 0, 1200, 800, GetColor(160, 216, 255), true);// 背景の色
		sceneManager->SceneSelect();

		ScreenFlip();// 画面フリップ
	}

	// newで作ったものをdelete
	sceneManager->DeleteSet();
	delete sceneManager;

	DxLib_End();// DXライブラリ使用の処理終了
	return 0;// ソフト終了
}