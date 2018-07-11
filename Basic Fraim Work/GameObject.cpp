//=============================================================================
//
// �Q�[���I�u�W�F�N�g [GameObject.cpp]
// Author : ���ꐶ
//
//=============================================================================
// �C���N���[�h�t�@�C��
#include "main.h"
#include "GameObject.h"


//=============================================================================
// �O���[�o��
ObjectList *GameObject::m_List;

//=============================================================================
// �Q�[���I�u�W�F�N�g�}�l�[�W���̐���
void GameObject::Create()
{
	m_List = new ObjectList;
}

//=============================================================================
// ����������
void GameObject::Init()
{
	m_List->Init();
}

//=============================================================================
// �ŐV����
void GameObject::Update()
{
	m_List->Update();
}

//=============================================================================
// �`�揈��
void GameObject::Draw()
{
	m_List->Draw();

}

//=============================================================================
// �S�ă����[�X���鏈��
void GameObject::UninitAll()
{
	m_List->Uninit();
}

//=============================================================================
// �I�u�W�F�N�g�̒��g�����������Ԗڂɂ��邩�߂�
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