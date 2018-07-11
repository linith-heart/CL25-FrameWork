//=============================================================================
//
// �o���b�g�̔z�� [BulletBillGroup.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "Bullet.h"
#include "Texture.h"
#include "camera.h"


//=============================================================================
// ����������
void Bullet::Init(float Size, TEXTURE_IDX Texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	use = false;
	m_Vel = VEC3CLEAR;
	m_Time = 0;
	Bill.Pos = VEC3CLEAR;
	Bill.Scl = VEC3NUM(1.0f);
	Bill.Size = D3DXVECTOR2(Size, Size);
	Bill.TexId = Texture;
	SetVexData(pDevice, &Bill);
}

//=============================================================================
// �ŐV����
void Bullet::Update()
{
	if (!use)
		return;

	// �ړ�
	Bill.Pos += m_Vel;

	// �؋󎞊�
	m_Time--;

	// ���Ԃ������Ȃ�������ł�����
	if (m_Time <= 0)
		use = false;
}

//=============================================================================
// �`�揈��
void Bullet::Draw()
{
	if (!use)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 Texture = TextureList::GetInstance()->GetTexture(Bill.TexId);

	Billboard::Draw(pDevice, &Bill, &Texture, Camera::GetInstance()->m_mtxView);
}

//=============================================================================
// �I������
void Bullet::Uninit()
{
	SAFE_RELEASE(Bill.VtxBuff);
}


void Bullet::Set(D3DXVECTOR3 Pos, D3DXVECTOR3 Vel, int Time , Character::Team Team)
{
	use = true;
	Bill.Pos = Pos;
	m_Vel = Vel;
	m_Time = Time;
	m_Team = Team;
	//Bill.TexId = 
}
