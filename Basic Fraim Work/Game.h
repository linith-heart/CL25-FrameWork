//=============================================================================
//
// �Q�[�� [Game.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "Scene.h"
#include "GameObject.h"
#include "Player.h"

//=============================================================================
// �N���X�錾
class Game :public Scene
{
public:

	void Init();
	
	Scene* Update();
	
	void Draw();
	
	void Uninit();

private:
	static GameObject m_GameObject;
};
#endif