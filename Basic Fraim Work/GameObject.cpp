//=============================================================================
//
// ゲームオブジェクト [GameObject.cpp]
// Author : 川井一生
//
//=============================================================================
// インクルードファイル
#include "main.h"
#include "GameObject.h"


//=============================================================================
// グローバル
ObjectList *GameObject::m_List;

//=============================================================================
// ゲームオブジェクトマネージャの制作
void GameObject::Create()
{
	m_List = new ObjectList;
}

//=============================================================================
// 初期化処理
void GameObject::Init()
{
	m_List->Init();
}

//=============================================================================
// 最新処理
void GameObject::Update()
{
	m_List->Update();
}

//=============================================================================
// 描画処理
void GameObject::Draw()
{
	m_List->Draw();

}

//=============================================================================
// 全てリリースする処理
void GameObject::UninitAll()
{
	m_List->Uninit();
}

//=============================================================================
// オブジェクトの中身を検索し何番目にあるか戻す
// enum ObjectType
//		Blank_State = -1,
//		ObjT_Player = 0,
//		ObjT_BulletBlank,
//		ObjT_BulletBill,
//		ObjT_BG,
//		Object_Type_Max,
//=============================================================================
//void GameObject::SearchObject(int ObjectIdx)
//{
//	bool isSearchObject[GAME_OBJECT_MAX];
//	for (int i = 0; i < GAME_OBJECT_MAX; i++)
//	{
//		isSearchObject[i] = false;
//	}
//	for (int i = 0; i < GAME_OBJECT_MAX; i++)
//	{
//		if (m_Object[i] != nullptr)
//		{
//			if (m_Object[i]->ObjectType == ObjectIdx)
//			{
//				isSearchObject[i] = true;
//			}
//		}
//	}
//}