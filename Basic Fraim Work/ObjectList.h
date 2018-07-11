//=============================================================================
//
// オブジェクトリスト [ObjectList.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _OBJECT_LIST_H_
#define _OBJECT_LIST_H_

#include "Object.h"


//=============================================================================
// クラス宣言
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


	void Append(Object *ojp);	// オブジェクトをリストに追加
	void Delete(Object *ojp);	// オブジェクトをリストから消去

	Object *Search(ObjectType TypeIdx);

	void Init();
	void Update();
	void Draw();
	void Uninit();
protected:

};
#endif


