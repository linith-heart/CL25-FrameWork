//=============================================================================
//
// 2D ポリゴン [2D_Polygon.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _2D_POLYGON_H_
#define _2D_POLYGON_H_

#include "main.h"
#include "Object.h"
#include "basic.h"

//=============================================================================
// クラス宣言
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
	// 位置変換
	// poly	: ポリゴンの構造体
	//=========================================================================
	void SetPos(POLY *poly)
	{
		//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].vtx = D3DXVECTOR3(poly->Pos.x - (poly->Size.x / 2), poly->Pos.y - (poly->Size.y / 2), 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(poly->Pos.x + (poly->Size.x / 2), poly->Pos.y - (poly->Size.y / 2), 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(poly->Pos.x - (poly->Size.x / 2), poly->Pos.y + (poly->Size.y / 2), 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(poly->Pos.x + (poly->Size.x / 2), poly->Pos.y + (poly->Size.y / 2), 0.0f);

		// 頂点データをアンロックする
		poly->VtxBuff->Unlock();
	}

	//=========================================================================
	// 色の変換処理
	// poly	: ポリゴンの構造体
	// r	: 赤
	// g	: 緑
	// b	: 青
	// a	: α(透明度)
	//=========================================================================
	void SetCol(POLY *poly, float r, float g, float b, float a)
	{
		//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[1].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[2].diffuse = D3DXCOLOR(r, g, b, a);
		pVtx[3].diffuse = D3DXCOLOR(r, g, b, a);

		// 頂点データをアンロックする
		poly->VtxBuff->Unlock();
	}


	//=========================================================================
	// 2次元のオブジェクトの描画関数
	// pDevice	: デバイス
	// poly		: ポリゴンの構造体
	// tex		: 表示したいテクスチャー
	//=========================================================================
	void Draw(LPDIRECT3DDEVICE9 pDevice, POLY *poly, LPDIRECT3DTEXTURE9 *tex)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, poly->VtxBuff, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, *tex);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


	//=========================================================================
	// ヴァーテックスバッファの設定
	// pDevice	: デバイス
	// poly		: ポリゴンの構造体
	//=========================================================================
	HRESULT SetVtxdata(LPDIRECT3DDEVICE9 pDevice, POLY *poly)
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_2D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&poly->VtxBuff,		// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{//頂点バッファの中身を埋める
			VERTEX_2D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			poly->VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(poly->Pos.x, poly->Pos.y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(poly->Pos.x + poly->Size.x, poly->Pos.y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(poly->Pos.x, poly->Pos.y + poly->Size.y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(poly->Pos.x + poly->Size.x, poly->Pos.y + poly->Size.y, 0.0f);

			// テクスチャのパースペクティブコレクト用
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

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
			poly->VtxBuff->Unlock();
		}
	}
protected:
	POLY Poly;
};
#endif