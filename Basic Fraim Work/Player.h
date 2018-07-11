//=============================================================================
//
// プレイヤー [Player.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "3D_Mesh.h"
#include "Character.h"
#include "Bullet.h"
#include "camera.h"

#define PLAYER_MODEL_FILE_PATH	"data/model/mech_body.x"


//=============================================================================
// クラス宣言
class Player :public D3DMesh, public Character
{
private:
#define BULLET_MAX		(100)	// プレイヤーが使うバレットの数
#define BULLET_SIZE		(5.0f)	// 初期化の時の大きさ
#define BULLET_TEXTURE	(BASIC_BULLET_TEXTURE_IDX) // バレットがるかうテクスチャー
#define BULLET_CD		(3)		// バレットを打つ速度
#define BULLET_SPEED	(15)	// バレットが飛ぶ速度
#define BULLET_AIR_TIME	(90)	// バレットの滞空時間

#define ANGLE_VAL_MAX	(5)		// 角度のマックス
#define ANGLE_VAL		(1)		// 角度の変換量

#define MOVE_VAL_MAX	(5.0f)	// 移動量のマックス
#define MOVE_VAL		(0.5f)	// 加速量
#define TRACTION		(0.25f)	// 慣性・摩擦

#define BASE_ANGLE		(1.0f * D3DX_PI)	// 初期化角度
#define ROT_VALUE		(0.02f * D3DX_PI)	// 角度の変換度

#define RECENTER_FRAME	(90)	// 真ん中に戻すフレーム数
public:
	// バレットに使うもの
	class Bullet *m_Bullet[BULLET_MAX];
	int			m_BullCD;		// バレットの打つ速度


	// 移動に使うもの
	D3DXVECTOR3	m_Dir;			// direction方向
	float		m_Vel;			// velocity	移動量

	// ギミック
	CameraState m_CameraState;	// 移動軸を設定
	bool		m_isFaceRot;	// プレイヤーを移動方向にROT値を合わせるか
	bool		m_isReCenter;	// プレイヤーを真ん中に戻す
	bool		m_isAxisCenter;	// 軸をゼロに戻す

	int			m_ReCenterCnt;	// 真ん中に戻すフレーム数
	D3DXVECTOR3 m_ReCenterVec;	// 真ん中に戻す移動量

	int			m_AxisCenterCnt; // 軸をゼロに戻すフレーム数
	D3DXVECTOR3 m_AxisCenterVec; // 軸をゼロに戻す移動量

	void Init();
	void Update();
	void Draw();
	void Uninit();

	void Move();
	void Action();


	void ReCenter();
	void AxisCenter();
	Player():D3DMesh()
	{
		ObjectType = ObjT_Player;
	}
};
#endif