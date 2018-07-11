//=============================================================================
//
// タイトル [Title.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "Scene.h"
#include "BG.h"
#include "TitleMenu.h"
#include "TitleObject.h"

//=============================================================================
// クラス宣言
class Title :public Scene
{
public:

	void Init();

	Scene* Update();

	void Draw();

	void Uninit();
private:
	static TitleObject m_TitleObject;
};
#endif