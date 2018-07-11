//=============================================================================
//
// 2D�̔w�i [BG.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "BG.h"
#include "Texture.h"
#include "Scene.h"

//=============================================================================
// ����������
void BackGround::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BackGround::Poly.Pos = D3DXVECTOR2(0.0f, 0.0f);
	BackGround::Poly.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	BackGround::Poly.TexId = 0;
	Polygon::SetVtxdata(pDevice,&Poly);
}

//=============================================================================
// �ŐV����
void BackGround::Update()
{

}

//=============================================================================
// �`�揈��
void BackGround::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPDIRECT3DTEXTURE9 Texture = TextureList::GetInstance()->GetTexture(Poly.TexId);

	Polygon::Draw(pDevice, &Poly, &Texture);
}

//=============================================================================
// �I������
void BackGround::Uninit()
{

}

//=============================================================================
// �w�i�̕ϊ�
void BackGround::SetBG(int TextureIdx)
{

	//search
	//	return obj*
	//	onj->poly.texid = TextureIdx;

	BackGround::Poly.TexId = TextureIdx;
}
