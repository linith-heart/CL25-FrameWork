//=============================================================================
//
// ゲームオブジェクト [GameObject.h]
// Author : 川井一生
//
// このクラスは無駄
// 以降作る時は省くこと
//=============================================================================
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_
//=============================================================================
// インクルードファイル
#include "Object.h"
#include "ObjectList.h"

//=============================================================================
// クラス宣言
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