//=============================================================================
//
// シーン [Scene.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
// クラス宣言
class Scene
{
public:

	int CurrentScene;

	virtual void Init() = 0;
	virtual Scene* Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;

private:

};
#endif