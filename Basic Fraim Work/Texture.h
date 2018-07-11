//=============================================================================
//
// �e�N�X�`���[ [Texture.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"


//=============================================================================
// �t�@�C���p�X
// �^�C�g��
#define TEXTURE_FILE_PATH_TITLE_BG			"data/texture/title bg.png"
#define TEXTURE_FILE_PATH_TITLE_START		"data/texture/Start_Game.png"
#define TEXTURE_FILE_PATH_TITLE_EXIT		"data/texture/Exit_Game.png"
#define TEXTURE_FILE_PATH_TITLE_HIGHLIGHT	"data/texture/Select_Highlight.png"

// �Q�[��
#define TEXTURE_FILE_PATH_GAME_BG			"data/texture/game bg.png"
#define TEXTURE_FILE_PATH_PLAYER_MODEL		"data/texture/mech000.png"
#define TEXTURE_FILE_PATH_BASIC_BULLET		"data/texture/bullet000.png"

// ���U���g
#define TEXTURE_FILE_PATH_RESULT_BG		"data/texture/result bg.png"

//=============================================================================
// �e�N�X�`���[�̃C���f�b�N�X�ԍ�

enum TEXTURE_IDX
{
	// �^�C�g���̃e�N�X�`���[
	TITLE_BG_IDX = 0,
	TITLE_START_IDX,
	TITLE_EXIT_IDX,
	TITLE_HIGHLIGHT_IDX,
	TITLE_TEXTURE_MAX,

	// �Q�[���̃e�N�X�`���[
	GAME_BG_IDX = 0,
	PLAYER_MODEL_TEXTURE_IDX,
	BASIC_BULLET_TEXTURE_IDX,
	GAME_TEXTURE_MAX,

	// ���U���g�̃e�N�X�`���[
	RESULT_BG_IDX = 0,
	RESULT_TEXTURE_MAX,
};


#define TEXTURE_MAX (TITLE_TEXTURE_MAX)


//=============================================================================
// �N���X��`
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
	// �R���X�g���N�^
	TextureList()
	{
		Head = nullptr;
	}
	// �f�X�g���N�^
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

	// �e�N�X�`���[�̃Q�b�g�֐�
	LPDIRECT3DTEXTURE9 GetTexture(int Idx)
	{
		List *NodePtr;

		// ���X�g�̒�������ۂł͂Ȃ���
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

	// ���X�g�̃Q�b�g�֐�
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
// �v���g�^�C�v�錾
void InitTexture(int no);

#endif
