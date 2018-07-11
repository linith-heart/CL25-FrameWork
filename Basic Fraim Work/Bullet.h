//=============================================================================
//
// バレット [Bullet.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "Object.h"
#include "Game.h"
#include "2D_Billboard.h"
#include "Texture.h"
#include "Character.h"

//=============================================================================
// マクロ宣言
#define BULLET_IN_GROUP	(50)

//=============================================================================
// クラス宣言
// バレットクラス
class Bullet : public Billboard
{
public:

	bool		use;		// 使っているか
	/*
	ゲームの中で常に表示したりしなかったりするものなので
	useフラグを設定し処理するかしないを管理
	newとdeleteの使用をゲームプレイ中は避ける目的
	*/

	D3DXVECTOR3	m_Vel;	// 移動量
	int			m_Time;	// 滞空時間
	Character::Team m_Team;

	void Init(float Size, TEXTURE_IDX Texture);
	void Update();
	void Draw();
	void Uninit();

	void Set(D3DXVECTOR3 Pos, D3DXVECTOR3 Vel, int Time , Character::Team Team);

	Bullet():Billboard()
	{
		ObjectType = ObjT_Bullet;
	}

private:
	void Init()	{}
};
#endif