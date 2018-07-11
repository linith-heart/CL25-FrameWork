//=============================================================================
//
// バレットの配列 [BulletGroup.cpp]
// Author : 川井一生
//
//=============================================================================
#include "Bullet.h"



//=============================================================================
// バレットの制作
void BulletGroup::Create()
{
	for (int i = 0; i < BULLET_IN_GROUP; i++)
	{
		m_Bullet[i] = new Bullet;
	}
}
//=============================================================================
// バレットの初期化処理
void BulletGroup::Init()
{
	Create();
	for (int i = 0; i < BULLET_IN_GROUP; i++)
	{
		m_Bullet[i]->Init();
	}
}

//=============================================================================
// バレットの最新処理
void BulletGroup::Update()
{
	for (int i = 0; i < BULLET_IN_GROUP; i++)
	{
		if (m_Bullet[i]->use)
			m_Bullet[i]->Update();
	}
}

//=============================================================================
// バレットの描画処理
void BulletGroup::Draw()
{
	for (int i = 0; i < BULLET_IN_GROUP; i++)
	{
		if (m_Bullet[i]->use)
			m_Bullet[i]->Draw();
	}
}

//=============================================================================
// バレットの終了処理
void BulletGroup::Uninit()
{
	for (int i = 0; i < BULLET_IN_GROUP; i++)
	{
		if (m_Bullet[i]->use)
			m_Bullet[i]->Update();
	}
}

//=============================================================================
// バレットのポップ処理
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