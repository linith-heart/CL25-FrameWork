//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 川井一生
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "mathWk.h"

//=============================================================================
// マクロ定義
#define	POS_X_CAM		(0.0f)						// カメラの初期位置(X座標)
#define	POS_Y_CAM		(400.0f)						// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(-400.0f)							// カメラの初期位置(Z座標)


#define	TITLE_EYE_X		(4300.0f)						// カメラの初期位置(X座標)
#define	TITLE_EYE_Y		(880.0f)						// カメラの初期位置(Y座標)
#define	TITLE_EYE_Z		(740.0f)						// カメラの初期位置(Z座標)

#define	TITLE_AT_X		(3900.0f)						// カメラの初期位置(X座標)
#define	TITLE_AT_Y		(710.0f)						// カメラの初期位置(Y座標)
#define	TITLE_AT_Z		(775.0f)						// カメラの初期位置(Z座標)


#define TITLE_ROT		(0.5f * D3DX_PI)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(8500.0f)										// ビュー平面のFarZ値

#define CAM_HIGHT		(80.0f)						// カメラの地面からの高さ

#define MOVE_VALUE		(1)							// 移動量
#define ROT_VALUE		(D3DX_PI * 0.01f)			// 回転量
#define FLIP_CAM		(D3DX_PI * 0.05f)			// フリップ時の回転量
#define FLIP_TIME		(20)						// 回転するフレーム数


#define GAME_CAM_MAX (2)

//=============================================================================
// プロトタイプ宣言
void MoveCamera(int no);

void ResetCam(int no);

//=============================================================================
// グローバル変数
Camera *Camera::m_Camera = nullptr;

D3DXMATRIX				mtxProjection;				// プロジェクションマトリックス

int						cam_mode = 0;				// カメラのモード

bool					isFlip = false;
int						FlipCnt = 0;

//=============================================================================
// カメラの初期化処理
void Camera::Init()
{
	m_CurrentState = TopDown_State;

	m_Eye = TOP_DOWN_POS;
	m_At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_isMove = false;
}

//=============================================================================
// カメラの最新処理
void Camera::Update()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (m_isMove)
	{
		Camera::Move();
	}


	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_Eye, &m_At, &m_Up);
	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションマトリックス初期化
	D3DXMatrixIdentity(&mtxProjection);
	// プロジェクションマトリックス作成
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		VIEW_ANGLE,
		VIEW_ASPECT,
		VIEW_NEAR_Z,	//ビュー平面のNearZ値
		VIEW_FAR_Z);	//ビュー平面のFarZ値
						// プロジェクションマトリックス設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//=============================================================================
// クォータニオンの回転処理
// AxisVec : 回転軸
// RotVal  : 回転量
// return  : 回転をかけた後の m_Eye の位置 (m_Eye = this function)
//=============================================================================
D3DXVECTOR3 Camera::QuaternionRot(D3DXVECTOR3 AxisVec, float RotVal)
{
	Vec3Normalize(&AxisVec);// 正規化

	D3DXVECTOR3 tOut = m_Eye - m_At;							// 現在のカメラのベクトル
	D3DXVECTOR4 p = D3DXVECTOR4(tOut.x, tOut.y, tOut.z, 0.0f);	// 回転したいバーテックス
	D3DXVECTOR4 q = D3DXVECTOR4(-AxisVec.x*sinf(RotVal / 2), -AxisVec.y*sinf(RotVal / 2), -AxisVec.z*sinf(RotVal / 2), cosf(RotVal / 2));	// 回転計算用のクオータニオン
	D3DXVECTOR4 r = D3DXVECTOR4(AxisVec.x*sinf(RotVal / 2), AxisVec.y*sinf(RotVal / 2), AxisVec.z*sinf(RotVal / 2), cosf(RotVal / 2));		// 回転計算用のクオータニオン
	D3DXVECTOR4 temp4 = QuaternionMulty(QuaternionMulty(r, p), q);	// クオータニオンの掛け算で移動量計算

	tOut = D3DXVECTOR3(temp4.x + m_At.x, temp4.y + m_At.y, temp4.z + m_At.z);

	return tOut;
}

//=============================================================================
// カメラの移動セット
void Camera::Set()
{
	D3DXVECTOR3 temp;

	switch (m_CurrentState)
	{
	case TopDown_State:
		temp = TOP_DOWN_POS;
		break;
	case LeftRight_State:
		temp = LEFT_RIGHT_POS;
		break;
	case BackFront_State:
		temp = BACK_FRONT_POS;
		break;
	}

	m_isMove = true;
	m_MoveTime = MOVE_TIME;
	m_RotAxis = Vec3Cross(&m_Eye, &temp);

	float tdot = dotProduct(&m_Eye, &temp);
	float tAng = (D3DXVec3LengthSq(&m_Eye) * (D3DXVec3LengthSq(&temp)));

	m_RotVal = (acosf(tdot / sqrtf(tAng))) / MOVE_TIME;
}

//=============================================================================
// 移動処理
void Camera::Move()
{
	m_Eye = Camera::QuaternionRot(m_RotAxis, m_RotVal);
	m_MoveTime--;
	if (m_MoveTime <= 0)
		m_isMove = false;
}



//=============================================================================
// カメラをリセット
void Camera::ResetCam()
{
	m_Eye = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	m_At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}