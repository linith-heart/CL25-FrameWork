//=============================================================================
//
// タイトルオブジェクト [TitleObject.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _TITLE_OBJECT_H_
#define _TITLE_OBJECT_H_
//=============================================================================
// タイトルで使うオブジェクトのインクルード
#include "BG.h"
#include "TitleMenu.h"
#include "ObjectList.h"


//=============================================================================
// クラス宣言
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