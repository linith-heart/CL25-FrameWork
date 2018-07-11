//=============================================================================
//
// タイトルメニュー [TitleMenu.cpp]
// Author : 川井一生
//
//=============================================================================
#include "TitleMenu.h"
#include "Texture.h"

//=============================================================================
// 初期化
void TitleMenu::Init()
{
	Button[Start_Idx] = new TitleButton;
	Button[Start_Idx]->Init(Start_Idx);
	Button[Exit_Idx] = new TitleButton;
	Button[Exit_Idx]->Init(Exit_Idx);

}

//=============================================================================
// 最新処理
void TitleMenu::Update()
{
	for (int i = 0; i < Menu_Buttons_Max; i++)
	{
		Button[i]->Update();
	}
}

//=============================================================================
// 描画処理
void TitleMenu::Draw()
{
	for (int i = 0; i < Menu_Buttons_Max; i++)
	{
		Button[i]->Draw();

	}
}

//=============================================================================
// 終了処理
void TitleMenu::Uninit()
{
	for (int i = 0; i < Menu_Buttons_Max; i++)
	{
		Button[i]->Uninit();
		delete Button[i];
	}
}








//=============================================================================
// 初期化
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
// 最新処理
void TitleButton::Update()
{
	SetPos(&Poly);
}

//=============================================================================
// 描画処理
void TitleButton::Draw()
{
	LPDIRECT3DTEXTURE9 Texture = TextureList::GetInstance()->GetTexture(Poly.TexId);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	Polygon::Draw(pDevice, &Poly, &Texture);

}

//=============================================================================
// 終了処理
void TitleButton::Uninit()
{

}