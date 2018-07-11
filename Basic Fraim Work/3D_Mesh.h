//=============================================================================
//
// 3D ���b�V�� [3D_Mesh.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _3D_MESH_H_
#define _3D_MESH_H_

#include "Object.h"
#include "basic.h"

//=============================================================================
// �N���X�錾
class D3DMesh : public Object
{
public:

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;

	D3DMesh():Object()
	{

	}

	//=========================================================================
	// X�t�@�C���ǂݍ��݂̊֐�
	HRESULT LoadXFile(LPDIRECT3DDEVICE9 pDevice, LPCSTR pFilename, MESH *mesh)
	{
		if (FAILED(D3DXLoadMeshFromX(pFilename,// ���f���f�[�^
			D3DXMESH_SYSTEMMEM,					// �g�p���郁�����̃I�v�V����
			pDevice,							// �f�o�C�X 
			NULL,								// ���g�p
			&mesh->BuffMat,						// �}�e���A���f�[�^�ւ̃|�C���^�[
			NULL,								// ���g�p
			&mesh->NumMat,						// D3DXMATERIAL�\���̂̐�
			&mesh->Mesh)))						// ���b�V���f�[�^�ւ̃|�C���^�[
		{
			return E_FAIL;
		}
		return S_OK;
	}
	//=============================================================================
	// ���b�V���̃I�u�W�F�N�g�̕`��֐�
	void Draw(LPDIRECT3DDEVICE9 pDevice, MESH *mesh, LPDIRECT3DTEXTURE9 *tex)
	{
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// �X�P�[���A��]�A���s�ړ�
		D3DXMATERIAL *pD3DXMat;
		D3DMATERIAL9 matDef;

		// ���[���h�}�g���N�X������
		D3DXMatrixIdentity(&mesh->mtxWorld);

		// �X�P�[���𔽉f	(S)
		D3DXMatrixScaling(&mtxScl, mesh->Scl.x, mesh->Scl.y, mesh->Scl.z);
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxScl); 	// &mesh->mtxWorld = &mesh->mtxWorld * &mtxScl
																		// ��]�𔽉f		(R)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, mesh->Rot.y, mesh->Rot.x, mesh->Rot.z);
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxRot);	// &mesh->mtxWorld = &mesh->mtxWorld * &mtxRot
																		// ���s�ړ��𔽉f	(T)
		D3DXMatrixTranslation(&mtxTranslate, mesh->Pos.x, mesh->Pos.y, mesh->Pos.z);
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mesh->mtxWorld);

		// ���݂̃}�e���A����ۑ�
		pDevice->GetMaterial(&matDef);

		// �}�e���A�����ւ̃|�C���^��
		pD3DXMat = (D3DXMATERIAL*)mesh->BuffMat->GetBufferPointer();

		int i;
		for (i = 0; i < (int)mesh->NumMat; i++)
		{

			pDevice->SetMaterial(&pD3DXMat[i].MatD3D);	// �}�e���A���̐ݒ�

			pDevice->SetTexture(0, *tex);	// �e�N�X�`���̐ݒ�
			mesh->Mesh->DrawSubset(i);
		}

		// �}�e���A���ɖ߂�
		pDevice->SetMaterial(&matDef);
	}

protected:
	MESH Mesh;
};
#endif