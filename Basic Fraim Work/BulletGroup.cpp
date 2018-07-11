//=============================================================================
//
// �o���b�g�̔z�� [BulletGroup.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "Bullet.h"



//=============================================================================
// �o���b�g�̐���
void BulletGroup::Create()
{
	for (int i = 0; i < BULLET_IN_GROUP; i++)
	{
		m_Bullet[i] = new Bullet;
	}
}
//=============================================================================
// �o���b�g�̏���������
void BulletGroup::Init()
{
	Create();
	for (int i = 0; i < BULLET_IN_GROUP; i++)
	{
		m_Bullet[i]->Init();
	}
}

//=============================================================================
// �o���b�g�̍ŐV����
void BulletGroup::Update()
{
	for (int i = 0; i < BULLET_IN_GROUP; i++)
	{
		if (m_Bullet[i]->use)
			m_Bullet[i]->Update();
	}
}

//=============================================================================
// �o���b�g�̕`�揈��
void BulletGroup::Draw()
{
	for (int i = 0; i < BULLET_IN_GROUP; i++)
	{
		if (m_Bullet[i]->use)
			m_Bullet[i]->Draw();
	}
}

//=============================================================================
// �o���b�g�̏I������
void BulletGroup::Uninit()
{
	for (int i = 0; i < BULLET_IN_GROUP; i++)
	{
		if (m_Bullet[i]->use)
			m_Bullet[i]->Update();
	}
}

//=============================================================================
// �o���b�g�̃|�b�v����
void BulletGroup::Set(D3DXVECTOR3 Pos, D3DXVECTOR3 Vel, int Time)
{
	for (int i = 0; i < BULLET_IN_GROUP; i++)
	{
		if (!m_Bullet[i]->use)
		{
			m_Bullet[i]->Set(Pos, Vel, Time);
			break;
		}
	}
}