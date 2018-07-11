#ifdef _DEBUG
//=============================================================================
//
// デバッグデータ表示処理 [DebugData.cpp]
// Author : 川井一生
/*
デバッグのデータを管理

hub for debug data
*/
//=============================================================================
#include "main.h"
#include "DebugData.h"

#include "camera.h"

//=============================================================================
// マクロ定義

//=============================================================================
// プロトタイプ宣言
int Line(int no);

//=============================================================================
// グローバル変数

LPD3DXFONT		g_pD3DXFont = NULL;		// フォントへのポインタ

int				g_LineCnt;

//=============================================================================
void InitDBD(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 情報表示用フォントを設定
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);

}

void DrawDBD(int no)
{
	RECT	rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	char	str[256];

	D3DXVECTOR3 temp = Camera::GetInstance()->m_Eye - Camera::GetInstance()->m_At;
	float	CamLenSq = D3DXVec3LengthSq(&temp);

	// カメラの角度
	temp.y = 0.0f;
	float tAng = atan2(temp.z, temp.x);





	g_LineCnt = 1;
	// FPS
	sprintf(str, "FPS:%d\n", no);
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// カメラの位置　camera Eye	
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "cam x:%f z:%f y:%f\n", Camera::GetInstance()->m_Eye.x, Camera::GetInstance()->m_Eye.z, Camera::GetInstance()->m_Eye.y);
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// カメラのEyeからAtの長さ　distance between camEye and camAt
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "cam len sq%f\n", CamLenSq);
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// ゲームへ移動
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "タイトルの時　B　を押してください\n");
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));

	// 操作表示
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "移動 W,A,S,D\n");
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// 操作表示２
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "バレット Space\n");
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// 操作表示
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "カメラ回転　NUM 1, NUM 2, NUM 3\n");
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

}

int Line(int no)
{
	g_LineCnt++;
	return (no * 15);
}


void UninitDBD(void)
{
	if (g_pD3DXFont != NULL)
	{// 情報表示用フォントの開放
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
}
#endif
