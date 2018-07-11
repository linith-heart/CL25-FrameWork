//=============================================================================
//
// �G�l�~�[ [Enemy.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "3D_Mesh.h"
#include "Character.h"
#include "Bullet.h"

//#define PLAYER_MODEL_FILE_PATH	"data/model/ZergStar.x"


//=============================================================================
// �N���X�錾
class Enemy :public D3DMesh, public Character
{
private:
#define BULLET_MAX		(50)	// �v���C���[���g���o���b�g�̐�
#define BULLET_SIZE		(10.0f)	// �������̎��̑傫��
#define BULLET_TEXTURE	(BASIC_BULLET_TEXTURE_IDX) // �o���b�g���邩���e�N�X�`���[
#define BULLET_CD		(20)		// �o���b�g��ł��x
#define BULLET_SPEED	(5)	// �o���b�g����ԑ��x
#define BULLET_AIR_TIME	(180)	// �o���b�g�̑؋󎞊�

#define MOVE_VAL_MAX	(2.0f)	// �ړ��ʂ̃}�b�N�X
#define MOVE_VAL		(0.02f)	// ������
#define TRACTION		(0.25f)	// �����E���C

#define BASE_ANGLE		(1.0f * D3DX_PI)	// �������p�x
#define ROT_VALUE		(0.02f * D3DX_PI)	// �p�x�̕ϊ��x

public:
	// �o���b�g�Ɏg������
	class Bullet *m_Bullet[BULLET_MAX];
	int			m_BullCD;		// �o���b�g�̑ł��x

	// �ړ��Ɏg������
	D3DXVECTOR3	m_Dir;			// direction����
	float		m_Vel;			// velocity	�ړ���

	// �M�~�b�N
	CameraState m_CameraState;	// �ړ�����ݒ�


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