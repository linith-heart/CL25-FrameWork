//=============================================================================
//
// 3D メッシュ [3D_Mesh.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _3D_MESH_H_
#define _3D_MESH_H_

#include "Object.h"
#include "basic.h"

//=============================================================================
// クラス宣言
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
	// Xファイル読み込みの関数
	HRESULT LoadXFile(LPDIRECT3DDEVICE9 pDevice, LPCSTR pFilename, MESH *mesh)
	{
		if (FAILED(D3DXLoadMeshFromX(pFilename,// モデルデータ
			D3DXMESH_SYSTEMMEM,					// 使用するメモリのオプション
			pDevice,							// デバイス 
			NULL,								// 未使用
			&mesh->BuffMat,						// マテリアルデータへのポインター
			NULL,								// 未使用
			&mesh->NumMat,						// D3DXMATERIAL構造体の数
			&mesh->Mesh)))						// メッシュデータへのポインター
		{
			return E_FAIL;
		}
		return S_OK;
	}
	//=============================================================================
	// メッシュのオブジェクトの描画関数
	void Draw(LPDIRECT3DDEVICE9 pDevice, MESH *mesh, LPDIRECT3DTEXTURE9 *tex)
	{
		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;	// スケール、回転、平行移動
		D3DXMATERIAL *pD3DXMat;
		D3DMATERIAL9 matDef;

		// ワールドマトリクス初期化
		D3DXMatrixIdentity(&mesh->mtxWorld);

		// スケールを反映	(S)
		D3DXMatrixScaling(&mtxScl, mesh->Scl.x, mesh->Scl.y, mesh->Scl.z);
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxScl); 	// &mesh->mtxWorld = &mesh->mtxWorld * &mtxScl
																		// 回転を反映		(R)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, mesh->Rot.y, mesh->Rot.x, mesh->Rot.z);
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxRot);	// &mesh->mtxWorld = &mesh->mtxWorld * &mtxRot
																		// 平行移動を反映	(T)
		D3DXMatrixTranslation(&mtxTranslate, mesh->Pos.x, mesh->Pos.y, mesh->Pos.z);
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxTranslate);

		// ワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &mesh->mtxWorld);

		// 現在のマテリアルを保存
		pDevice->GetMaterial(&matDef);

		// マテリアル情報へのポインタを
		pD3DXMat = (D3DXMATERIAL*)mesh->BuffMat->GetBufferPointer();

		int i;
		for (i = 0; i < (int)mesh->NumMat; i++)
		{

			pDevice->SetMaterial(&pD3DXMat[i].MatD3D);	// マテリアルの設定

			pDevice->SetTexture(0, *tex);	// テクスチャの設定
			mesh->Mesh->DrawSubset(i);
		}

		// マテリアルに戻す
		pDevice->SetMaterial(&matDef);
	}

protected:
	MESH Mesh;
};
#endif