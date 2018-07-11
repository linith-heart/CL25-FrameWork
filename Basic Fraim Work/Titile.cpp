//=============================================================================
//
// �^�C�g�� [Title.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "main.h"
#include "Title.h"
#include "Game.h"
#include "input.h"
#include "TitleObject.h"
#include "BG.h"


//=============================================================================
// �O���[�o��
TitleObject Title::m_TitleObject;

//=============================================================================
// ����������
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
// �ŐV����
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
// �`�揈��
void Title::Draw()
{
	m_TitleObject.Draw();
}

//=============================================================================
// �I������
void Title::Uninit()
{
	//UninitTexture();
	TextureList::GetInstance()->ClearList();

	m_TitleObject.UninitAll();
}
