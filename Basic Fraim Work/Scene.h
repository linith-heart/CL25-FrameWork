//=============================================================================
//
// �V�[�� [Scene.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
// �N���X�錾
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