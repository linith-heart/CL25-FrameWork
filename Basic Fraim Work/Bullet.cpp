//=============================================================================
//
// バレットの配列 [BulletBillGroup.cpp]
// Author : 川井一生
//
//=============================================================================
#include "Bullet.h"
#include "Texture.h"
#include "camera.h"


//=============================================================================
// 初期化処理
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
// 最新処理
void Bullet::Update()
{
	if (!use)
		return;

	// 移動
	Bill.Pos += m_Vel;

	// 滞空時間
	m_Time--;

	// 時間が無くなったら消滅させる
	if (m_Time <= 0)
		use = false;
}

//=============================================================================
// 描画処理
void Bullet::Draw()
{
	if (!use)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 Texture = TextureList::GetInstance()->GetTexture(Bill.TexId);

	Billboard::Draw(pDevice, &Bill, &Texture, Camera::GetInstance()->m_mtxView);
}

//=============================================================================
// 終了処理
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
