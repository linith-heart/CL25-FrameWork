#ifdef _DEBUG
//=============================================================================
//
// �f�o�b�O�f�[�^�\������ [DebugData.cpp]
// Author : ���ꐶ
/*
�f�o�b�O�̃f�[�^���Ǘ�

hub for debug data
*/
//=============================================================================
#include "main.h"
#include "DebugData.h"

#include "camera.h"

//=============================================================================
// �}�N����`

//=============================================================================
// �v���g�^�C�v�錾
int Line(int no);

//=============================================================================
// �O���[�o���ϐ�

LPD3DXFONT		g_pD3DXFont = NULL;		// �t�H���g�ւ̃|�C���^

int				g_LineCnt;

//=============================================================================
void InitDBD(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pD3DXFont);

}

void DrawDBD(int no)
{
	RECT	rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	char	str[256];

	D3DXVECTOR3 temp = Camera::GetInstance()->m_Eye - Camera::GetInstance()->m_At;
	float	CamLenSq = D3DXVec3LengthSq(&temp);

	// �J�����̊p�x
	temp.y = 0.0f;
	float tAng = atan2(temp.z, temp.x);





	g_LineCnt = 1;
	// FPS
	sprintf(str, "FPS:%d\n", no);
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// �J�����̈ʒu�@camera Eye	
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "cam x:%f z:%f y:%f\n", Camera::GetInstance()->m_Eye.x, Camera::GetInstance()->m_Eye.z, Camera::GetInstance()->m_Eye.y);
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// �J������Eye����At�̒����@distance between camEye and camAt
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "cam len sq%f\n", CamLenSq);
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// �Q�[���ֈړ�
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "�^�C�g���̎��@B�@�������Ă�������\n");
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));

	// ����\��
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "�ړ� W,A,S,D\n");
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// ����\���Q
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "�o���b�g Space\n");
	g_pD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// ����\��
	rect = { 0,Line(g_LineCnt),SCREEN_WIDTH,SCREEN_HEIGHT };		// bg x and y
	sprintf(str, "�J������]�@NUM 1, NUM 2, NUM 3\n");
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
	{// ���\���p�t�H���g�̊J��
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
}
#endif
