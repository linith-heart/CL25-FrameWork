//=============================================================================
//
// �v���C���[ [Player.h]
// Author : ���ꐶ
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
// �N���X�錾
class Player :public D3DMesh, public Character
{
private:
#define BULLET_MAX		(100)	// �v���C���[���g���o���b�g�̐�
#define BULLET_SIZE		(5.0f)	// �������̎��̑傫��
#define BULLET_TEXTURE	(BASIC_BULLET_TEXTURE_IDX) // �o���b�g���邩���e�N�X�`���[
#define BULLET_CD		(3)		// �o���b�g��ł��x
#define BULLET_SPEED	(15)	// �o���b�g����ԑ��x
#define BULLET_AIR_TIME	(90)	// �o���b�g�̑؋󎞊�

#define ANGLE_VAL_MAX	(5)		// �p�x�̃}�b�N�X
#define ANGLE_VAL		(1)		// �p�x�̕ϊ���

#define MOVE_VAL_MAX	(5.0f)	// �ړ��ʂ̃}�b�N�X
#define MOVE_VAL		(0.5f)	// ������
#define TRACTION		(0.25f)	// �����E���C

#define BASE_ANGLE		(1.0f * D3DX_PI)	// �������p�x
#define ROT_VALUE		(0.02f * D3DX_PI)	// �p�x�̕ϊ��x

#define RECENTER_FRAME	(90)	// �^�񒆂ɖ߂��t���[����
public:
	// �o���b�g�Ɏg������
	class Bullet *m_Bullet[BULLET_MAX];
	int			m_BullCD;		// �o���b�g�̑ł��x


	// �ړ��Ɏg������
	D3DXVECTOR3	m_Dir;			// direction����
	float		m_Vel;			// velocity	�ړ���

	// �M�~�b�N
	CameraState m_CameraState;	// �ړ�����ݒ�
	bool		m_isFaceRot;	// �v���C���[���ړ�������ROT�l�����킹�邩
	bool		m_isReCenter;	// �v���C���[��^�񒆂ɖ߂�
	bool		m_isAxisCenter;	// �����[���ɖ߂�

	int			m_ReCenterCnt;	// �^�񒆂ɖ߂��t���[����
	D3DXVECTOR3 m_ReCenterVec;	// �^�񒆂ɖ߂��ړ���

	int			m_AxisCenterCnt; // �����[���ɖ߂��t���[����
	D3DXVECTOR3 m_AxisCenterVec; // �����[���ɖ߂��ړ���

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