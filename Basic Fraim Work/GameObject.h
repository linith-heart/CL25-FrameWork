//=============================================================================
//
// �Q�[���I�u�W�F�N�g [GameObject.h]
// Author : ���ꐶ
//
// ���̃N���X�͖���
// �ȍ~��鎞�͏Ȃ�����
//=============================================================================
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_
//=============================================================================
// �C���N���[�h�t�@�C��
#include "Object.h"
#include "ObjectList.h"

//=============================================================================
// �N���X�錾
class GameObject
{
protected:
	static ObjectList *m_List;

public:
	static ObjectList *GetList()
	{
		if (m_List == nullptr)
		{
			m_List = new ObjectList;
		}
		return m_List;
	}

	void Create();


	void Init();
	void Update();
	void Draw();
	void UninitAll();
};

#endif