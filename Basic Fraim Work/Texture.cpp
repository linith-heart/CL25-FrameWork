//=============================================================================
//
// �e�N�X�`���[ [Texture.h]
// Author : ���ꐶ
//
//=============================================================================
#include "Texture.h"


//LPDIRECT3DTEXTURE9 D3D_Texture[TEXTURE_MAX];

TextureList *TextureList::m_TextureList = nullptr;

//=============================================================================
// ���X�g�ɒǉ�
void TextureList::Append(const LPCSTR FilePath, TEXTURE_IDX Idx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	List *NewTexture;
	List *NodePtr;
	List *PrevNode = nullptr;

	NewTexture = new List;
	D3DXCreateTextureFromFile(pDevice, FilePath, &NewTexture->m_Texture);	//	�e�N�X�`���[�̓ǂݍ���
	NewTexture->Idx = Idx;		// �e�N�X�`���[�̃C���f�b�N�X�ԍ�

	if (Head == nullptr)
	{
		Head = NewTexture;
	}
	else
	{
		NodePtr = Head;

		// �C���f�b�N�X�ԍ��ɂ������ꏊ������
		while (NodePtr != nullptr && NodePtr->Idx < Idx)
		{
			PrevNode = NodePtr;
			NodePtr = NodePtr->next;
		}
		// �O�̃m�[�h��NULL�Ȃ瓪�ɓ����
		if (PrevNode == nullptr)
		{
			Head = NewTexture;
			NewTexture->next = NodePtr;
		}
		// �O�Ƀm�[�h�Ƃ��̎��̃m�[�h������������
		else
		{
			PrevNode->next = NewTexture;
			NewTexture->next = NodePtr;
		}
	}
}


//=============================================================================
// ���X�g�������
void TextureList::ClearList()
{
	List *NodePtr;
	List *NextNode;
	// ���X�g�̒�������ۂł͂Ȃ���
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// ���X�g�̏I���܂Ń��X�g��i�߂�
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
// �e�N�X�`���[�̓ǂݍ��ݏ���
void InitTexture(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	switch (no)
	{
	case Title_Scene_Idx:

		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_TITLE_BG, TITLE_BG_IDX);				// �^�C�g���w�i
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_TITLE_START, TITLE_START_IDX);			// �X�^�[�g�{�^��
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_TITLE_EXIT, TITLE_EXIT_IDX);			// �G�O�W�b�g�{�^��
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_TITLE_HIGHLIGHT, TITLE_HIGHLIGHT_IDX);	// �I���n�C���C�g


		break;
	case Game_Scene_Idx:
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_GAME_BG, GAME_BG_IDX);						// �Q�[���w�i
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_PLAYER_MODEL, PLAYER_MODEL_TEXTURE_IDX);	// �v���C���[���f���̃e�N�X�`���[
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_BASIC_BULLET, BASIC_BULLET_TEXTURE_IDX);	// �o���b�g

		break;
	case Result_Scene_Idx:
		TextureList::GetInstance()->Append(TEXTURE_FILE_PATH_RESULT_BG, RESULT_BG_IDX);			// ���U���g�w�i

		break;

	}

}