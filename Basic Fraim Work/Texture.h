//=============================================================================
//
// テクスチャー [Texture.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"


//=============================================================================
// ファイルパス
// タイトル
#define TEXTURE_FILE_PATH_TITLE_BG			"data/texture/title bg.png"
#define TEXTURE_FILE_PATH_TITLE_START		"data/texture/Start_Game.png"
#define TEXTURE_FILE_PATH_TITLE_EXIT		"data/texture/Exit_Game.png"
#define TEXTURE_FILE_PATH_TITLE_HIGHLIGHT	"data/texture/Select_Highlight.png"

// ゲーム
#define TEXTURE_FILE_PATH_GAME_BG			"data/texture/game bg.png"
#define TEXTURE_FILE_PATH_PLAYER_MODEL		"data/texture/mech000.png"
#define TEXTURE_FILE_PATH_BASIC_BULLET		"data/texture/bullet000.png"

// リザルト
#define TEXTURE_FILE_PATH_RESULT_BG		"data/texture/result bg.png"

//=============================================================================
// テクスチャーのインデックス番号

enum TEXTURE_IDX
{
	// タイトルのテクスチャー
	TITLE_BG_IDX = 0,
	TITLE_START_IDX,
	TITLE_EXIT_IDX,
	TITLE_HIGHLIGHT_IDX,
	TITLE_TEXTURE_MAX,

	// ゲームのテクスチャー
	GAME_BG_IDX = 0,
	PLAYER_MODEL_TEXTURE_IDX,
	BASIC_BULLET_TEXTURE_IDX,
	GAME_TEXTURE_MAX,

	// リザルトのテクスチャー
	RESULT_BG_IDX = 0,
	RESULT_TEXTURE_MAX,
};


#define TEXTURE_MAX (TITLE_TEXTURE_MAX)


//=============================================================================
// クラス定義
class TextureList
{
private:
	struct List
	{
		TEXTURE_IDX Idx;
		LPDIRECT3DTEXTURE9 m_Texture = nullptr;
		struct List *next = nullptr;
	};

	List *Head;
public:
	// コンストラクタ
	TextureList()
	{
		Head = nullptr;
	}
	// デストラクタ
	~TextureList()
	{
		List *NodePtr;
		List *NextNode;

		NodePtr = Head;

		while (NodePtr != nullptr)
		{
			NextNode = NodePtr->next;
			delete NodePtr;
			NodePtr = NextNode;
		}
	}

	void Append(LPCSTR FilePath, TEXTURE_IDX Idx);
	void ClearList();

	// テクスチャーのゲット関数
	LPDIRECT3DTEXTURE9 GetTexture(int Idx)
	{
		List *NodePtr;

		// リストの中が空っぽではないか
		if (Head == nullptr)
		{
		}
		else
		{
			NodePtr = Head;

			while (NodePtr != nullptr && NodePtr->Idx < Idx)
			{
				NodePtr = NodePtr->next;
			}

			if (NodePtr->Idx == Idx)
			{
				return NodePtr->m_Texture;
			}
		}
	}

	// リストのゲット関数
	static TextureList *GetInstance()
	{
		if (m_TextureList == nullptr)
		{
			m_TextureList = new TextureList;
		}
		return	m_TextureList;
	}



private:
protected:
	static TextureList *m_TextureList;
};

//=============================================================================
// プロトタイプ宣言
void InitTexture(int no);

#endif
