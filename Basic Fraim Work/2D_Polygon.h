//=============================================================================
//
// 2D �|���S�� [2D_Polygon.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _2D_POLYGON_H_
#define _2D_POLYGON_H_

#include "main.h"
#include "Object.h"
#include "basic.h"

//=============================================================================
// �N���X�錾
class Polygon : public Object
{
public:

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;

	Polygon():Object()
	{

	}


	//=========================================================================
	// �ʒu�ϊ�
	// poly	: �|���S���̍\����
	//=========================================================================
	void SetPos(POLY *poly)
	{
		//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(poly->Pos.x - (poly->Size.x / 2), poly->Pos.y - (poly->Size.y / 2), 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(poly->Pos.x + (poly->Size.x / 2), poly->Pos.y - (poly->Size.y / 2), 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(poly->Pos.x - (poly->Size.x / 2), poly->Pos.y + (poly->Size.y / 2), 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(poly->Pos.x + (poly->Size.x / 2), poly->Pos.y + (poly->Size.y / 2), 0.0f);

		// ���_�f�[�^���A�����b�N����
		poly->VtxBuff->Unlock();
	}

	//=========================================================================
	// �F�̕ϊ�����
	// poly	: �|���S���̍\����
	// r	: ��
	// g	: ��
	// b	: ��
	// a	: ��(�����x)
	//=========================================================================
	void SetCol(POLY *poly, float r, float g, float b, float a)
	{
		//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[1].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[2].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[3].diffuse = D3DXCOLOR(r, g, b, a);

		// ���_�f�[�^���A�����b�N����
		poly->VtxBuff->Unlock();
	}


	//=========================================================================
	// 2�����̃I�u�W�F�N�g�̕`��֐�
	// pDevice	: �f�o�C�X
	// poly		: �|���S���̍\����
	// tex		: �\���������e�N�X�`���[
	//=========================================================================
	void Draw(LPDIRECT3DDEVICE9 pDevice, POLY *poly, LPDIRECT3DTEXTURE9 *tex)
	{
		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, poly->VtxBuff, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, *tex);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


	//=========================================================================
	// ���@�[�e�b�N�X�o�b�t�@�̐ݒ�
	// pDevice	: �f�o�C�X
	// poly		: �|���S���̍\����
	//=========================================================================
	HRESULT SetVtxdata(LPDIRECT3DDEVICE9 pDevice, POLY *poly)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&poly->VtxBuff,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_2D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(poly->Pos.x, poly->Pos.y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(poly->Pos.x + poly->Size.x, poly->Pos.y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(poly->Pos.x, poly->Pos.y + poly->Size.y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(poly->Pos.x + poly->Size.x, poly->Pos.y + poly->Size.y, 0.0f);

			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// ���_�f�[�^���A�����b�N����
			poly->VtxBuff->Unlock();
		}
	}
protected:
	POLY Poly;
};
#endif