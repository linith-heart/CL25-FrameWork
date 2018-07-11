//=============================================================================
//
// ���C������ [main.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~

//=============================================================================
// �C���N���[�h�t�@�C��
#include <windows.h>
#include "d3dx9.h"
#include <stdio.h>
#include <time.h>
#include "Texture.h"

#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"

//=============================================================================
// ���C�u�����̃����N
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")

//=============================================================================
// �}�N����`

#define SCREEN_WIDTH	(1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)	// �E�C���h�E�̍���

#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����

// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[�RD] / �@���x�N�g�� / ���ˌ� / �e�N�X�`�����W )
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// ���x�̐ݒ�
#define	ALPHA			(170)

// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;	// ���_���W
	float		rhw;	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;	// ���ˌ�
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

//3D�|���S�����_�t�H�[�}�b�g�ɍ��킹���\����
typedef struct
{
	D3DXVECTOR3	vtx;		// ���_���W
	D3DXVECTOR3	normal;		// �����x�N�g��
	D3DCOLOR	diffuse;	// ���ˌ�
	D3DXVECTOR2	tex;		// �e�N�X�`���[���W
}VERTEX_3D;


enum SceneIdx
{
	Title_Scene_Idx,
	Game_Scene_Idx,
	Result_Scene_Idx,
};


// �I�������̃`�[�g
/*
�����[�X���������������̂��킽��
NULL�ł��邩�ǂ������m�F
NULL�łȂ���΃f�[�^�������[�X��NULL�ɕύX
*/
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) {if (p!=NULL){(p)->Release();(p)=NULL;}}
#endif // !SAFE_RELEASE

// �x�N�g������������Ƃ��̃`�[�g
#define VEC3CLEAR	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))

// �x�N�g�������ׂē����l�ɃZ�b�g���鎞�̃`�[�g
#define VEC3NUM(f)	(D3DXVECTOR3(f,f,f))


//=============================================================================
// �v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void Uninit(void);
#endif