//=============================================================================
//
// 2D‚Ì”wŒi [BG.cpp]
// Author : ìˆäˆê¶
//
//=============================================================================
#include "BG.h"
#include "Texture.h"
#include "Scene.h"

//=============================================================================
// ‰Šú‰»ˆ—
void BackGround::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BackGround::Poly.Pos = D3DXVECTOR2(0.0f, 0.0f);
	BackGround::Poly.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	BackGround::Poly.TexId = 0;
	Polygon::SetVtxdata(pDevice,&Poly);
}

//=============================================================================
// ÅVˆ—
void BackGround::Update()
{

}

//=============================================================================
// •`‰æˆ—
void BackGround::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 Texture = TextureList::GetInstance()->GetTexture(Poly.TexId);

	Polygon::Draw(pDevice, &Poly, &Texture);
}

//=============================================================================
// I—¹ˆ—
void BackGround::Uninit()
{

}

//=============================================================================
// ”wŒi‚Ì•ÏŠ·
void BackGround::SetBG(int TextureIdx)
{

	//search
	//	return obj*
	//	onj->poly.texid = TextureIdx;

	BackGround::Poly.TexId = TextureIdx;
}
