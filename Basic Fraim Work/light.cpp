//=============================================================================
//
// ライト処理 [field.cpp]
// Author : 川井一生
//
//=============================================================================
#include "input.h"

//=============================================================================
// マクロ定義
#define	NUM_LIGHT		(1)							// ライトの数


//=============================================================================
// プロトタイプ宣言

//=============================================================================
// グローバル変数
D3DLIGHT9				g_aLight[NUM_LIGHT];		// ライト情報


//=============================================================================
// ライトの初期化処理
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	// ライト0のタイプの設定
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ライト0の拡散光の設定
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト0の鏡面反射光の設定
//	g_aLight[0].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト0の環境光の設定
//	g_aLight[0].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト0の方向の設定
	vecDir = D3DXVECTOR3(-0.0f, -0.6f, -1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

	// ライト0をレンダリングパイプラインに設定
	pDevice->SetLight(0, &g_aLight[0]);

	// ライト0を使用使用状態に
	pDevice->LightEnable(0, TRUE);


	// ライティングモードをON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

