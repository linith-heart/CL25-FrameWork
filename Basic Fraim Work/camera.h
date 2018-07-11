//=============================================================================
//
// �J�������� [camera.h]
// Author : ���ꐶ
/*
���̃Q�[�����ł̓J������������g��Ȃ��̂�
�V���O���g���Ƃ��Ē�`
*/
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//=============================================================================
// �}�N����`
enum CameraState
{
	TopDown_State,
	LeftRight_State,
	BackFront_State,
};

//=============================================================================
// �\���̐錾

//=============================================================================
// �N���X��`
class Camera
{
private:

#define TOP_DOWN_POS	(D3DXVECTOR3(0.0f,480.0f,-45.0f))
#define LEFT_RIGHT_POS	(D3DXVECTOR3(480.0f,0.0f,0.0f))
#define BACK_FRONT_POS	(D3DXVECTOR3(0.0f,15.0f,-480.0f))
#define MOVE_TIME		(120)
public:
	CameraState				m_CurrentState;		// �J����������ׂ��ꏊ

	D3DXVECTOR3				m_Eye;				// �J�����̎��_				position of camera
	D3DXVECTOR3				m_At;				// �J�����̒����_			position of cameras view point
	D3DXVECTOR3				m_Up;				// �J�����̏�����x�N�g��	direction of up

	D3DXMATRIX				m_mtxView;			// �r���[�}�g���b�N�X		view matrix
	
	bool					m_isMove;

	D3DXVECTOR3				m_RotAxis;
	float					m_RotVal;
	int						m_MoveTime;


	// �J�����̃Q�b�g�֐�
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
