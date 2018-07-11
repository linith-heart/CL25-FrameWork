//=============================================================================
//
// �v���C���[ [Player.h]
// Author : ���ꐶ
//
//=============================================================================
#include "Player.h"
#include "Texture.h"

#include "camera.h"
#include "input.h"

#include "Bullet.h"
#include "mathWk.h"

//=============================================================================
// ����������
void Player::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���b�V���\���̂̏�����
	Mesh.Pos = VEC3CLEAR;
	Mesh.Rot = D3DXVECTOR3(0.0f, BASE_ANGLE,0.0f);
	Mesh.Scl = VEC3NUM(0.1f);

	Mesh.NumMat = 0;
	Mesh.BuffMat = nullptr;
	Mesh.Mesh = nullptr;

	Mesh.TexId = PLAYER_MODEL_TEXTURE_IDX;

	LoadXFile(pDevice, PLAYER_MODEL_FILE_PATH, &Mesh);

	// �L�����N�^�[�̏�����
	Chara.m_AtkSpd	= BULLET_SPEED;
	Chara.m_Spd		= MOVE_VAL_MAX;
	Chara.m_Team	= Team_1;

	// �ړ��Ɏg�����̂̏�����
	m_Vel = 0;
	m_Dir = VEC3CLEAR;

	// �M�~�b�N�Ɏg�����̂̏�����
	m_isFaceRot = false;
	m_isReCenter = false;
	m_isAxisCenter = false;
	m_CameraState = TopDown_State;

	// �o���b�g�̏�����
	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_Bullet[i] = new Bullet;
		m_Bullet[i]->Init(BULLET_SIZE, BULLET_TEXTURE);
	}
}

//=============================================================================
// �ŐV����
void Player::Update()
{
	Player::Move();		// �ړ��̏���
	Player::Action();	// �A�N�V��������

	if (GetKeyboardTrigger(DIK_NUMPAD1))
	{
		m_CameraState = TopDown_State;
	}
	if (GetKeyboardTrigger(DIK_NUMPAD2))
	{
		m_CameraState = LeftRight_State;
	}
	if (GetKeyboardTrigger(DIK_NUMPAD3))
	{
		m_CameraState = BackFront_State;
	}

	if (m_CameraState != Camera::GetInstance()->m_CurrentState)
	{
		Camera::GetInstance()->m_CurrentState = m_CameraState;
		Camera::GetInstance()->Set();
		Player::AxisCenter();
	}



	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_Bullet[i]->Update();
	}

}

//=============================================================================
// �`�揈��
void Player::Draw()
{
	//=====================================================
	// �v���C���[���f���̕`��
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �e�N�X�`���[���擾
	LPDIRECT3DTEXTURE9 Texture = TextureList::GetInstance()->GetTexture(Mesh.TexId);


	D3DMesh::Draw(pDevice, &Mesh, &Texture);


	//=====================================================
	// �o���b�g�̕`��

	// ���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_Bullet[i]->Draw();
	}

	// ���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// �I������
void Player::Uninit()
{
	SAFE_RELEASE(Mesh.BuffMat);

	SAFE_RELEASE(Mesh.Mesh);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_Bullet[i]->Uninit();
		delete m_Bullet[i];
	}

}

//=============================================================================
// �ړ�����
void Player::Move()
{
	D3DXVECTOR3 OldPos = Mesh.Pos;


	bool VelAdded = false;			// �ړ��ʂ̕ϊ�����������

	bool isUpDwnPress = false;		// ���E�̕ϊ�����������
	bool isLftRgtPress = false;		// �㉺�̕ϊ�����������


	if (GetKeyboardPress(DIK_W))
	{
		float temp = m_Dir.z;			// �ԊґO�̈ړ��p�x

		if (m_Dir.z < ANGLE_VAL_MAX)	// �ړ��p�x++
			m_Dir.z += ANGLE_VAL;
		else
		{
			m_Dir.z = ANGLE_VAL_MAX;	// �}�b�N�X�𒴂��Ȃ��悤��
		}

		if (GetKeyboardPress(DIK_S))
			m_Dir.z = temp;			// ���������Ȃ�ԊґO�ɖ߂�
		else
		{
			VelAdded = true;
			isUpDwnPress = true;

			if (m_Vel < MOVE_VAL_MAX)	// �ړ���++
				m_Vel += MOVE_VAL;
			else
				m_Vel = MOVE_VAL_MAX;	// �}�b�N�X�𒴂��Ȃ��悤��
		}
	}
	else if (GetKeyboardPress(DIK_S))
	{
		VelAdded = true;
		isUpDwnPress = true;
		if (m_Dir.z > -ANGLE_VAL_MAX)
			m_Dir.z -= ANGLE_VAL;
		else
			m_Dir.z = -ANGLE_VAL_MAX;

		if (m_Vel < MOVE_VAL_MAX)		// �ړ���++
			m_Vel += MOVE_VAL;
		else
			m_Vel = MOVE_VAL_MAX;		// �}�b�N�X�𒴂��Ȃ��悤��
	}


	if (!isUpDwnPress)	// �㉺�̕ϊ���������Έړ��p�x���[���ɋ߂Â���
	{
		if (m_Dir.z > TRACTION)
			m_Dir.z -= TRACTION;
		else if (m_Dir.z < -TRACTION)
			m_Dir.z += TRACTION;
		else
			m_Dir.z = 0;
	}



	if (GetKeyboardPress(DIK_D))
	{
		float temp = m_Dir.x;			// �ԊґO�̈ړ��p�x

		if (m_Dir.x < ANGLE_VAL_MAX)	// �ړ��p�x++
			m_Dir.x += ANGLE_VAL;
		else
		{
			m_Dir.x = ANGLE_VAL_MAX;	// �}�b�N�X�𒴂��Ȃ��悤��
		}

		if (GetKeyboardPress(DIK_A))
			m_Dir.x = temp;			// ���������Ȃ�ԊґO�ɖ߂�
		else
		{
			VelAdded = true;
			isLftRgtPress = true;

			if (m_Vel < MOVE_VAL_MAX)	// �ړ���++
				m_Vel += MOVE_VAL;
			else
				m_Vel = MOVE_VAL_MAX;	// �}�b�N�X�𒴂��Ȃ��悤��
		}
	}
	else if (GetKeyboardPress(DIK_A))
	{
		VelAdded = true;
		isLftRgtPress = true;
		if (m_Dir.x > -ANGLE_VAL_MAX)
			m_Dir.x -= ANGLE_VAL;
		else
			m_Dir.x = -ANGLE_VAL_MAX;

		if (m_Vel < MOVE_VAL_MAX)		// �ړ���++
			m_Vel += MOVE_VAL;
		else
			m_Vel = MOVE_VAL_MAX;		// �}�b�N�X�𒴂��Ȃ��悤��
	}


	if (!isLftRgtPress)	// ���E�̕ϊ���������Έړ��p�x���[���ɋ߂Â���
	{
		if (m_Dir.x > TRACTION)
			m_Dir.x -= TRACTION;
		else if (m_Dir.x < -TRACTION)
			m_Dir.x += TRACTION;
		else
			m_Dir.x = 0;
	}

	if (!VelAdded)		// �ړ��ʂ̕ϊ���������΃[���ɋ߂Â���
	{
		if (m_Vel > 0)
			m_Vel -= MOVE_VAL;
		else
			m_Vel = 0;
	}

	D3DXVECTOR3 temp = Camera::GetInstance()->m_At - Camera::GetInstance()->m_Eye;			// �J�����ƃv���C���[�̊p�x�����߂�
	float tCamAng = atan2(temp.x, temp.z);
	float tDirAng = atan2(m_Dir.z, m_Dir.x);
	
	D3DXVECTOR3 MoveVal = VEC3CLEAR;

	//�ړ��ʂ��v�Z
	switch (m_CameraState)
	{
	case TopDown_State:
		MoveVal.x = cosf(tDirAng - tCamAng) * m_Vel;
		MoveVal.z = sinf(tDirAng - tCamAng) * m_Vel;
		break;
	case LeftRight_State:
		MoveVal.y = -cosf(tDirAng - tCamAng) * m_Vel;
		MoveVal.z = sinf(tDirAng - tCamAng) * m_Vel;
		break;
	case BackFront_State:
		MoveVal.x = cosf(tDirAng - tCamAng) * m_Vel;
		MoveVal.y = sinf(tDirAng - tCamAng) * m_Vel;
		break;
	default:
		break;
	}

	Mesh.Pos += MoveVal;


	if (m_isFaceRot)
	{
		float tAng = atan2f(MoveVal.z, MoveVal.x);
		Mesh.Rot.y = -tAng - (0.5 * D3DX_PI);
	}
	else
	{
		if (Mesh.Rot.y != BASE_ANGLE)
		{
			D3DXVECTOR3 tVec = Ang2Vec(Mesh.Rot, 1);
			D3DXVECTOR3 tVec2 = D3DXVECTOR3(0.0f,0.0f,-1.0f);
			if (Vec2Cross(tVec, tVec2) < -ROT_VALUE)
			{
				Mesh.Rot.y -= ROT_VALUE;
			}
			else if (Vec2Cross(tVec, tVec2) > ROT_VALUE)
			{
				Mesh.Rot.y += ROT_VALUE;
			}
			else
			{
				Mesh.Rot.y = BASE_ANGLE;
			}
		}
	}

	// �����[���ɖ߂�����
	if (m_isAxisCenter)
	{
		Mesh.Pos -= m_AxisCenterVec;
		m_AxisCenterCnt--;
		if (m_AxisCenterCnt <= 0)
			m_isAxisCenter = false;
	}

	// �^�񒆂ɖ߂�����
	if (m_isReCenter)
	{
		Mesh.Pos -= m_ReCenterVec;
		m_ReCenterCnt--;
		if (m_ReCenterCnt <= 0)
			m_isReCenter = false;
	}

}

//=============================================================================
// �A�N�V�����̏���
void Player::Action()
{
	// �o���b�g�̃N�[���_�E�����I����Ă����
	if (m_BullCD <= 0)
	{	// �X�y�[�X��������Ă�����
		if (GetKeyboardPress(DIK_SPACE))
		{	// �g�p���Ă��Ȃ��o���b�g���������o���b�g�̃Z�b�g����������
			for (int i = 0; i < BULLET_MAX; i++)
			{
				if (!m_Bullet[i]->use)
				{
					D3DXVECTOR3 BullVel = Ang2Vec(Mesh.Rot, BULLET_SPEED);
					//BullVel.x = cosf(-Mesh.Rot.y - (0.5 * D3DX_PI)) *BULLET_SPEED;
					//BullVel.z = sinf(-Mesh.Rot.y - (0.5 * D3DX_PI)) *BULLET_SPEED;

					m_Bullet[i]->Set(Mesh.Pos, BullVel, BULLET_AIR_TIME, Chara.m_Team);

					// �o���b�g���Z�b�g������o���b�g�̃N�[���_�E�����Z�b�g
					m_BullCD = BULLET_CD;
					break;
				}
			}
		}
	}
	// �o���b�g�̃N�[���_�E����i�߂�
	m_BullCD--;

	// m_isFaceRot�̃I���I�t�X�C�b�`
	if (GetKeyboardTrigger(DIK_N))
	{
		if (m_isFaceRot)
			m_isFaceRot = false;
		else
			m_isFaceRot = true;
	}
}

//=============================================================================
// �v���C���[��^�񒆂ɖ߂�����
void Player::ReCenter()
{
	//=====================================================
	// resetting the player position to the center of the map
	if (!m_isReCenter)
	{
		m_isReCenter = true;

		m_ReCenterVec = Mesh.Pos;
		m_ReCenterVec = m_ReCenterVec / RECENTER_FRAME;

		m_ReCenterCnt = RECENTER_FRAME;
	}


}

//=============================================================================
// m_CameraState����Ď����[���ɖ߂�
void Player::AxisCenter()
{
	//=====================================================
	// setting the axis based on the current camera state to zero
	if (!m_isAxisCenter)
	{
		m_isAxisCenter = true;

		m_AxisCenterVec = VEC3CLEAR;

		switch (m_CameraState)
		{
		case TopDown_State:
			m_AxisCenterVec.y = Mesh.Pos.y;
			break;
		case LeftRight_State:
			m_AxisCenterVec.x = Mesh.Pos.x;
			break;
		case BackFront_State:
			m_AxisCenterVec.z = Mesh.Pos.z;
			break;
		default:
			break;
		}
		m_AxisCenterVec = m_AxisCenterVec / RECENTER_FRAME;

		m_AxisCenterCnt = RECENTER_FRAME;
	}

}
