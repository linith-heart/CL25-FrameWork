//=============================================================================
//
// 2D ビルボード [2D_Billboard.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _2D_BILLBOARD_H_
#define _2D_BILLBOARD_H_

#include "Object.h"
#include "basic.h"

//=============================================================================
// クラス宣言
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
	// 色の変換処理
	// Bill	: ビルボードの構造体
	// r	: 赤
	// g	: 緑
	// b	: 青
	// a	: α(透明度)
	//=========================================================================
	void SetCol(BILL *Bill, float r, float g, float b, float a)
	{
		//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		Bill->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[1].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[2].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[3].diffuse = D3DXCOLOR(r, g, b, a);

		// 頂点データをアンロックする
		Bill->VtxBuff->Unlock();
	}

	//=============================================================================
	// ビルボードオブジェクトの描画関数
	// pDevice	: デバイス
	// Bill		: ビルボードの構造体
	// tex		: 表示したいテクスチャー
	// mtxView	: カメラのビューマトリックス
	//=========================================================================
	void Draw(LPDIRECT3DDEVICE9 pDevice, BILL *Bill, LPDIRECT3DTEXTURE9 *tex, D3DMATRIX mtxView)
	{
		D3DXMATRIX mtxScl, mtxTranslate;	// スケール、平行移動

		// ワールドマトリクス初期化
		D3DXMatrixIdentity(&Bill->mtxWorld);


		//ポリゴンを正面に向ける(逆行列)

		// 直交行列の正方行列にとる逆行列
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


		// スケールを反映	(S)
		D3DXMatrixScaling(&mtxScl, Bill->Scl.x, Bill->Scl.y, Bill->Scl.z);
		D3DXMatrixMultiply(&Bill->mtxWorld, &Bill->mtxWorld, &mtxScl);
		// 平行移動を反映	(T)
		D3DXMatrixTranslation(&mtxTranslate, Bill->Pos.x, Bill->Pos.y, Bill->Pos.z);
		D3DXMatrixMultiply(&Bill->mtxWorld, &Bill->mtxWorld, &mtxTranslate);


		// ワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &Bill->mtxWorld);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, Bill->VtxBuff, 0, sizeof(VERTEX_3D));

		// 頂点フォーマット設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// クスチャの設定
		pDevice->SetTexture(0, *tex);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	}


	//=============================================================================
	// 頂点の作成
	// pDevice	:デバイス
	// Bill		:ビルボードの構造体
	//=============================================================================
	HRESULT SetVexData(LPDIRECT3DDEVICE9 pDevice,BILL* Bill)
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_3D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&Bill->VtxBuff,			// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_3D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			Bill->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-Bill->Size.x, Bill->Size.y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(Bill->Size.x, Bill->Size.y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-Bill->Size.x, -Bill->Size.y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(Bill->Size.x, -Bill->Size.y, 0.0f);

			// 法線ベクトルの設定
			pVtx[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			// 頂点データをアンロックする
			Bill->VtxBuff->Unlock();
		}
		return S_OK;
	}


protected:
	BILL Bill;
};
#endif