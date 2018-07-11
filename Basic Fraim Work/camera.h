//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 川井一生
/*
このゲーム内ではカメラを一つしか使わないので
シングルトンとして定義
*/
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//=============================================================================
// マクロ定義
enum CameraState
{
	TopDown_State,
	LeftRight_State,
	BackFront_State,
};

//=============================================================================
// 構造体宣言

//=============================================================================
// クラス定義
class Camera
{
private:

#define TOP_DOWN_POS	(D3DXVECTOR3(0.0f,480.0f,-45.0f))
#define LEFT_RIGHT_POS	(D3DXVECTOR3(480.0f,0.0f,0.0f))
#define BACK_FRONT_POS	(D3DXVECTOR3(0.0f,15.0f,-480.0f))
#define MOVE_TIME		(120)
public:
	CameraState				m_CurrentState;		// カメラがいるべき場所

	D3DXVECTOR3				m_Eye;				// カメラの視点				position of camera
	D3DXVECTOR3				m_At;				// カメラの注視点			position of cameras view point
	D3DXVECTOR3				m_Up;				// カメラの上方向ベクトル	direction of up

	D3DXMATRIX				m_mtxView;			// ビューマトリックス		view matrix
	
	bool					m_isMove;

	D3DXVECTOR3				m_RotAxis;
	float					m_RotVal;
	int						m_MoveTime;


	// カメラのゲット関数
	static Camera *GetInstance()
	{
		if (m_Camera == nullptr)
		{
			m_Camera = new Camera;
		}
		return m_Camera;
	}
	void Init();
	void Update();

	D3DXVECTOR3 QuaternionRot(D3DXVECTOR3 AxisVec, float RotVal);

	void Set();
	void Move();
	void ResetCam();
protected:
	static Camera *m_Camera;
private:
	Camera() {}
};
#endif
