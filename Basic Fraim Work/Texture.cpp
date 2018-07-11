//=============================================================================
//
// テクスチャー [Texture.h]
// Author : 川井一生
//
//=============================================================================
#include "Texture.h"


//LPDIRECT3DTEXTURE9 D3D_Texture[TEXTURE_MAX];

TextureList *TextureList::m_TextureList = nullptr;

//=============================================================================
// リストに追加
void TextureList::Append(const LPCSTR FilePath, TEXTURE_IDX Idx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	List *NewTexture;
	List *NodePtr;
	List *PrevNode = nullptr;

	NewTexture = new List;
	D3DXCreateTextureFromFile(pDevice, FilePath, &NewTexture->m_Texture);	//	テクスチャーの読み込み
	NewTexture->Idx = Idx;		// テクスチャーのインデックス番号

	if (Head == nullptr)
	{
		Head = NewTexture;
	}
	else
	{
		NodePtr = Head;

		// インデックス番号により入れる場所を検索
		while (NodePtr != nullptr && NodePtr->Idx < Idx)
		{
			PrevNode = NodePtr;
			NodePtr = NodePtr->next;
		}
		// 前のノードがNULLなら頭に入れる
		if (PrevNode == nullptr)
		{
			Head = NewTexture;
			NewTexture->next = NodePtr;
		}
		// 前にノードとその次のノードを結合させる
		else
		{
			PrevNode->next = NewTexture;
			NewTexture->next = NodePtr;
		}
	}
}


//=============================================================================
// リストから消去
void TextureList::ClearList()
{
	List *NodePtr;
	List *NextNode;
	// リストの中が空っぽではないか
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// リストの終わりまでリストを進める
		while (NodePtr != nullptr)
		{

			SAFE_RELEASE(NodePtr->m_Texture);
			NextNode = NodePtr->next;
			delete NodePtr;
			NodePtr = NextNode;
		}

		Head = nullptr;
	}
}
//=============================================================================
// テクスチャーの読み込み処理
void InitTexture(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	switch (no)
	{
	case Title_Scene_Idx:

		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_TITLE_BG, TITLE_BG_IDX);				// タイトル背景
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_TITLE_START, TITLE_START_IDX);			// スタートボタン
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_TITLE_EXIT, TITLE_EXIT_IDX);			// エグジットボタン
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_TITLE_HIGHLIGHT, TITLE_HIGHLIGHT_IDX);	// 選択ハイライト


		break;
	case Game_Scene_Idx:
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_GAME_BG, GAME_BG_IDX);						// ゲーム背景
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_PLAYER_MODEL, PLAYER_MODEL_TEXTURE_IDX);	// プレイヤーモデルのテクスチャー
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_BASIC_BULLET, BASIC_BULLET_TEXTURE_IDX);	// バレット

		break;
	case Result_Scene_Idx:
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_RESULT_BG, RESULT_BG_IDX);			// リザルト背景

		break;

	}

}