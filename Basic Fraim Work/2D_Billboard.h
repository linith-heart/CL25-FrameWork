//=============================================================================
//
// 2D �r���{�[�h [2D_Billboard.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _2D_BILLBOARD_H_
#define _2D_BILLBOARD_H_

#include "Object.h"
#include "basic.h"

//=============================================================================
// �N���X�錾
class Billboard: public Object
{
public:

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;

	Billboard()
	{

	}


	//=============================================================================
	// �F�̕ϊ�����
	// Bill	: �r���{�[�h�̍\����
	// r	: ��
	// g	: ��
	// b	: ��
	// a	: ��(�����x)
	//=========================================================================
	void SetCol(BILL *Bill, float r, float g, float b, float a)
	{
		//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		Bill->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[1].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[2].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[3].diffuse = D3DXCOLOR(r, g, b, a);

		// ���_�f�[�^���A�����b�N����
		Bill->VtxBuff->Unlock();
	}

	//=============================================================================
	// �r���{�[�h�I�u�W�F�N�g�̕`��֐�
	// pDevice	: �f�o�C�X
	// Bill		: �r���{�[�h�̍\����
	// tex		: �\���������e�N�X�`���[
	// mtxView	: �J�����̃r���[�}�g���b�N�X
	//=========================================================================
	void Draw(LPDIRECT3DDEVICE9 pDevice, BILL *Bill, LPDIRECT3DTEXTURE9 *tex, D3DMATRIX mtxView)
	{
		D3DXMATRIX mtxScl, mtxTranslate;	// �X�P�[���A���s�ړ�

		// ���[���h�}�g���N�X������
		D3DXMatrixIdentity(&Bill->mtxWorld);


		//�|���S���𐳖ʂɌ�����(�t�s��)

		// �����s��̐����s��ɂƂ�t�s��
		Bill->mtxWorld._11 = mtxView._11;
		Bill->mtxWorld._12 = mtxView._21;
		Bill->mtxWorld._13 = mtxView._31;

		Bill->mtxWorld._21 = mtxView._12;
		Bill->mtxWorld._22 = mtxView._22;
		Bill->mtxWorld._23 = mtxView._32;

		Bill->mtxWorld._31 = mtxView._13;
		Bill->mtxWorld._32 = mtxView._23;
		Bill->mtxWorld._33 = mtxView._33;


		//D3DXMatrixInverse(&Bill->mtxWorld, NULL, &mtxView);
		//Bill->mtxWorld._41 = 0.0f;
		//Bill->mtxWorld._42 = 0.0f;
		//Bill->mtxWorld._43 = 0.0f;


		// �X�P�[���𔽉f	(S)
		D3DXMatrixScaling(&mtxScl, Bill->Scl.x, Bill->Scl.y, Bill->Scl.z);
		D3DXMatrixMultiply(&Bill->mtxWorld, &Bill->mtxWorld, &mtxScl);
		// ���s�ړ��𔽉f	(T)
		D3DXMatrixTranslation(&mtxTranslate, Bill->Pos.x, Bill->Pos.y, Bill->Pos.z);
		D3DXMatrixMultiply(&Bill->mtxWorld, &Bill->mtxWorld, &mtxTranslate);


		// ���[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &Bill->mtxWorld);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, Bill->VtxBuff, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �N�X�`���̐ݒ�
		pDevice->SetTexture(0, *tex);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	}


	//=============================================================================
	// ���_�̍쐬
	// pDevice	:�f�o�C�X
	// Bill		:�r���{�[�h�̍\����
	//=============================================================================
	HRESULT SetVexData(LPDIRECT3DDEVICE9 pDevice,BILL* Bill)
	{
		// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
			D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
			FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
			D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
			&Bill->VtxBuff,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
			NULL)))						// NULL�ɐݒ�
		{
			return E_FAIL;
		}

		{//���_�o�b�t�@�̒��g�𖄂߂�
			VERTEX_3D *pVtx;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			Bill->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-Bill->Size.x, Bill->Size.y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(Bill->Size.x, Bill->Size.y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-Bill->Size.x, -Bill->Size.y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(Bill->Size.x, -Bill->Size.y, 0.0f);

			// �@���x�N�g���̐ݒ�
			pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
			Bill->VtxBuff->Unlock();
		}
		return S_OK;
	}


protected:
	BILL Bill;
};
#endif