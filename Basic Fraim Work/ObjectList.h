//=============================================================================
//
// �I�u�W�F�N�g���X�g [ObjectList.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _OBJECT_LIST_H_
#define _OBJECT_LIST_H_

#include "Object.h"


//=============================================================================
// �N���X�錾
class ObjectList
{
private:
	struct List
	{
		Object *m_Object;
		struct List *next = nullptr;
	};

	List *Head;
public:


	ObjectList()
	{
		Head = nullptr;
	}

	~ObjectList()
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


	void Append(Object *ojp);	// �I�u�W�F�N�g�����X�g�ɒǉ�
	void Delete(Object *ojp);	// �I�u�W�F�N�g�����X�g�������

	Object *Search(ObjectType TypeIdx);

	void Init();
	void Update();
	void Draw();
	void Uninit();
protected:

};
#endif


