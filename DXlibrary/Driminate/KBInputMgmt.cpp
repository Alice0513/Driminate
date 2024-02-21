/*----------------------------------------------------------*/
/*キーボード入力管理クラス            　　　　　　　　　　　*/
/*制作者：白崎有彩　　　　　                                */
/*作成日：2月1日  　　　　　　                              */
/*----------------------------------------------------------*/
#include "Dxlib.h"
#include "KBInputMgmt.h"

bool KBInputMgmt::ReturnFlg = false;
bool KBInputMgmt::UpFlg = false;
bool KBInputMgmt::DownFlg = false;

/// <summary>
/// コンストラクタ
/// </summary>
KBInputMgmt::KBInputMgmt()
{

}

/// <summary>
/// 常に行う
/// </summary>
void KBInputMgmt::Update()
{

}