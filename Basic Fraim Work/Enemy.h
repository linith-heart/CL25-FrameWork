//=============================================================================
//
// エネミー [Enemy.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "3D_Mesh.h"
#include "Character.h"
#include "Bullet.h"

//#define PLAYER_MODEL_FILE_PATH	"data/model/ZergStar.x"


//=============================================================================
// クラス宣言
class Enemy :public D3DMesh, public Character
{
private:
#define BULLET_MAX		(50)	// プレイヤーが使うバレットの数
#define BULLET_SIZE		(10.0f)	// 初期化の時の大きさ
#define BULLET_TEXTURE	(BASIC_BULLET_TEXTURE_IDX) // バレットがるかうテクスチャー
#define BULLET_CD		(20)		// バレットを打つ速度
#define BULLET_SPEED	(5)	// バレットが飛ぶ速度
#define BULLET_AIR_TIME	(180)	// バレットの滞空時間

#define MOVE_VAL_MAX	(2.0f)	// 移動量のマックス
#define MOVE_VAL		(0.02f)	// 加速量
#define TRACTION		(0.25f)	// 慣性・摩擦

#define BASE_ANGLE		(1.0f * D3DX_PI)	// 初期化角度
#define ROT_VALUE		(0.02f * D3DX_PI)	// 角度の変換度

public:
	// バレットに使うもの
	class Bullet *m_Bullet[BULLET_MAX];
	int			m_BullCD;		// バレットの打つ速度

	// 移動に使うもの
	D3DXVECTOR3	m_Dir;			// direction方向
	float		m_Vel;			// velocity	移動量

	// ギミック
	CameraState m_CameraState;	// 移動軸を設定


	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;

	virtual void Move() = 0;
	virtual void Action() = 0;


	Enemy() :D3DMesh()
	{
		ObjectType = ObjT_Npc;
	}
};
#endif