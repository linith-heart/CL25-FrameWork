//=============================================================================
//
// �^�C�g���I�u�W�F�N�g [TitleObject.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _TITLE_OBJECT_H_
#define _TITLE_OBJECT_H_
//=============================================================================
// �^�C�g���Ŏg���I�u�W�F�N�g�̃C���N���[�h
#include "BG.h"
#include "TitleMenu.h"
#include "ObjectList.h"


//=============================================================================
// �N���X�錾
class TitleObject
{
protected:
	static ObjectList  *m_List;

public:
	ObjectList *GetList()
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