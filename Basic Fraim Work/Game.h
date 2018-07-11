//=============================================================================
//
// ƒQ[ƒ€ [Game.h]
// Author : ìˆäˆê¶
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "Scene.h"
#include "GameObject.h"
#include "Player.h"

//=============================================================================
// ƒNƒ‰ƒXéŒ¾
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