//=============================================================================
//
// �J�������� [camera.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "mathWk.h"

//=============================================================================
// �}�N����`
#define	POS_X_CAM		(0.0f)						// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(400.0f)						// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-400.0f)							// �J�����̏����ʒu(Z���W)


#define	TITLE_EYE_X		(4300.0f)						// �J�����̏����ʒu(X���W)
#define	TITLE_EYE_Y		(880.0f)						// �J�����̏����ʒu(Y���W)
#define	TITLE_EYE_Z		(740.0f)						// �J�����̏����ʒu(Z���W)

#define	TITLE_AT_X		(3900.0f)						// �J�����̏����ʒu(X���W)
#define	TITLE_AT_Y		(710.0f)						// �J�����̏����ʒu(Y���W)
#define	TITLE_AT_Z		(775.0f)						// �J�����̏����ʒu(Z���W)


#define TITLE_ROT		(0.5f * D3DX_PI)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(8500.0f)										// �r���[���ʂ�FarZ�l

#define CAM_HIGHT		(80.0f)						// �J�����̒n�ʂ���̍���

#define MOVE_VALUE		(1)							// �ړ���
#define ROT_VALUE		(D3DX_PI * 0.01f)			// ��]��
#define FLIP_CAM		(D3DX_PI * 0.05f)			// �t���b�v���̉�]��
#define FLIP_TIME		(20)						// ��]����t���[����


#define GAME_CAM_MAX (2)

//=============================================================================
// �v���g�^�C�v�錾
void MoveCamera(int no);

void ResetCam(int no);

//=============================================================================
// �O���[�o���ϐ�
Camera *Camera::m_Camera = nullptr;

D3DXMATRIX				mtxProjection;				// �v���W�F�N�V�����}�g���b�N�X

int						cam_mode = 0;				// �J�����̃��[�h

bool					isFlip = false;
int						FlipCnt = 0;

//=============================================================================
// �J�����̏���������
void Camera::Init()
{
	m_CurrentState = TopDown_State;

	m_Eye = TOP_DOWN_POS;
	m_At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_isMove = false;
}

//=============================================================================
// �J�����̍ŐV����
void Camera::Update()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (m_isMove)
	{
		Camera::Move();
	}


	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_Eye, &m_At, &m_Up);
	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����}�g���b�N�X������
	D3DXMatrixIdentity(&mtxProjection);
	// �v���W�F�N�V�����}�g���b�N�X�쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		VIEW_ANGLE,
		VIEW_ASPECT,
		VIEW_NEAR_Z,	//�r���[���ʂ�NearZ�l
		VIEW_FAR_Z);	//�r���[���ʂ�FarZ�l
						// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//=============================================================================
// �N�H�[�^�j�I���̉�]����
// AxisVec : ��]��
// RotVal  : ��]��
// return  : ��]����������� m_Eye �̈ʒu (m_Eye = this function)
//=============================================================================
D3DXVECTOR3 Camera::QuaternionRot(D3DXVECTOR3 AxisVec, float RotVal)
{
	Vec3Normalize(&AxisVec);// ���K��

	D3DXVECTOR3 tOut = m_Eye - m_At;							// ���݂̃J�����̃x�N�g��
	D3DXVECTOR4 p = D3DXVECTOR4(tOut.x, tOut.y, tOut.z, 0.0f);	// ��]�������o�[�e�b�N�X
	D3DXVECTOR4 q = D3DXVECTOR4(-AxisVec.x*sinf(RotVal / 2), -AxisVec.y*sinf(RotVal / 2), -AxisVec.z*sinf(RotVal / 2), cosf(RotVal / 2));	// ��]�v�Z�p�̃N�I�[�^�j�I��
	D3DXVECTOR4 r = D3DXVECTOR4(AxisVec.x*sinf(RotVal / 2), AxisVec.y*sinf(RotVal / 2), AxisVec.z*sinf(RotVal / 2), cosf(RotVal / 2));		// ��]�v�Z�p�̃N�I�[�^�j�I��
	D3DXVECTOR4 temp4 = QuaternionMulty(QuaternionMulty(r, p), q);	// �N�I�[�^�j�I���̊|���Z�ňړ��ʌv�Z

	tOut = D3DXVECTOR3(temp4.x + m_At.x, temp4.y + m_At.y, temp4.z + m_At.z);

	return tOut;
}

//=============================================================================
// �J�����̈ړ��Z�b�g
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
// �ړ�����
void Camera::Move()
{
	m_Eye = Camera::QuaternionRot(m_RotAxis, m_RotVal);
	m_MoveTime--;
	if (m_MoveTime <= 0)
		m_isMove = false;
}



//=============================================================================
// �J���������Z�b�g
void Camera::ResetCam()
{
	m_Eye = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	m_At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}