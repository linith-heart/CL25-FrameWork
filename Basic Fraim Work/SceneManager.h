//=============================================================================
//
// �V�[���}�l�[�W�� [SceneManager.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_
//=============================================================================
// �C���N���[�h�t�@�C��
#include "Scene.h"

//=============================================================================
// �N���X�錾
class SceneManager
{
public:

	Scene *m_Scene;

	void Init(Scene *pgs);
	void Update();
	void Draw();
	void Uninit();

};
#endif