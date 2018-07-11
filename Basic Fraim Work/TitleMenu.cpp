//=============================================================================
//
// �^�C�g�����j���[ [TitleMenu.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "TitleMenu.h"
#include "Texture.h"

//=============================================================================
// ������
void TitleMenu::Init()
{
	Button[Start_Idx] = new TitleButton;
	Button[Start_Idx]->Init(Start_Idx);
	Button[Exit_Idx] = new TitleButton;
	Button[Exit_Idx]->Init(Exit_Idx);

}

//=============================================================================
// �ŐV����
void TitleMenu::Update()
{
	for (int i = 0; i < Menu_Buttons_Max; i++)
	{
		Button[i]->Update();
	}
}

//=============================================================================
// �`�揈��
void TitleMenu::Draw()
{
	for (int i = 0; i < Menu_Buttons_Max; i++)
	{
		Button[i]->Draw();

	}
}

//=============================================================================
// �I������
void TitleMenu::Uninit()
{
	for (int i = 0; i < Menu_Buttons_Max; i++)
	{
		Button[i]->Uninit();
		delete Button[i];
	}
}








//=============================================================================
// ������
void TitleButton::Init(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	Poly.Size.x = SIZE_X;
	Poly.Size.y = SIZE_Y;
	Poly.Pos.x = POS_X;
	Poly.Pos.y = POS_Y;
	switch (no)
	{
	case TitleMenu::Start_Idx:
		Poly.TexId = TITLE_START_IDX;
		Poly.Pos.y = POS_Y;

		break;
	case TitleMenu::Exit_Idx:
		Poly.TexId = TITLE_EXIT_IDX;
		Poly.Pos.y = POS_Y + SIZE_Y;
		break;
	}
	Polygon::SetVtxdata(pDevice,&Poly);
}

//=============================================================================
// �ŐV����
void TitleButton::Update()
{
	SetPos(&Poly);
}

//=============================================================================
// �`�揈��
void TitleButton::Draw()
{
	LPDIRECT3DTEXTURE9 Texture = TextureList::GetInstance()->GetTexture(Poly.TexId);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	Polygon::Draw(pDevice, &Poly, &Texture);

}

//=============================================================================
// �I������
void TitleButton::Uninit()
{

}