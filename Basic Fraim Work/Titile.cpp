//=============================================================================
//
// タイトル [Title.cpp]
// Author : 川井一生
//
//=============================================================================
#include "main.h"
#include "Title.h"
#include "Game.h"
#include "input.h"
#include "TitleObject.h"
#include "BG.h"


//=============================================================================
// グローバル
TitleObject Title::m_TitleObject;

//=============================================================================
// 初期化処理
void Title::Init()
{
	CurrentScene = Title_Scene_Idx;
	InitTexture(Title_Scene_Idx);

	//ObjectList::Getinstance()->Append(new BackGround);
	//ObjectList::Getinstance()->Append(new TitleMenu);
	m_TitleObject.GetList()->Append(new BackGround);
	m_TitleObject.GetList()->Append(new TitleMenu);

	m_TitleObject.Init();
}

//=============================================================================
// 最新処理
Scene* Title::Update()
{
	m_TitleObject.Update();

	if (GetKeyboardTrigger(DIK_B))
	{
		return (new Game);
	}
	return this;
}

//=============================================================================
// 描画処理
void Title::Draw()
{
	m_TitleObject.Draw();
}

//=============================================================================
// 終了処理
void Title::Uninit()
{
	//UninitTexture();
	TextureList::GetInstance()->ClearList();

	m_TitleObject.UninitAll();
}
