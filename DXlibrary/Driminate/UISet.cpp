/*----------------------------------------------------------*/
/*UI�Ǘ��N���X         �@           �@�@�@�@�@�@�@�@�@�@�@�@*/
/*����ҁF����L�ʁ@�@�@�@�@                                */
/*�쐬���F2��5�� �@�@�@�@�@�@                               */
/*----------------------------------------------------------*/
#include "UISet.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
UISet::UISet()
{
	_itemImage[0] = LoadGraph("UI/Apple.png");
	_itemImage[1] = LoadGraph("UI/Banana.png");
	_itemImage[2] = LoadGraph("UI/OHPortion.png");
	_itemImage[3] = LoadGraph("UI/HPPortion.png");

	_itemPos = VGet(800.0f, 700.0f, 100.0f);
}

/// <summary>
/// ���s�܂Ƃ�
/// </summary>
void UISet::Update()
{
	for (int i = 0; i < 4; i++)
	{
		DrawRotaGraph(_itemPos.x + _itemPos.z * i, _itemPos.y, _siz[i], 0.0f, _itemImage[i], true);
	}
}