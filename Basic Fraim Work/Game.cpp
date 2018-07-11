//=============================================================================
//
// �Q�[�� [Game.cpp]
// Author : ���ꐶ
//
//=============================================================================
#include "main.h"
#include "Game.h"
#include "Result.h"
#include "input.h"

#include "GameObject.h"
#include "camera.h"
#include "light.h"
#include "Player.h"

#include "BG.h"

#include "meshwater.h"

// ���b�V���̐��̏����ݒ�
#define WATER_POS		(D3DXVECTOR3(0.0f, -100.0f, 0.0f))
#define WATER_ROT		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
#define WATER_B_CNT_X	(250)
#define WATER_B_CNT_Z	(250)
#define WATER_B_SCL_X	(75.0f)
#define WATER_B_SCL_Z	(75.0f)


//=============================================================================
// �O���[�o��
GameObject Game::m_GameObject;

//=============================================================================
// ����������
void Game::Init()
{
	CurrentScene = Game_Scene_Idx;
	InitTexture(Game_Scene_Idx);

	InitLight();
	Camera::GetInstance()->Init();
	
	InitMeshWater(WATER_POS, WATER_ROT, WATER_B_CNT_X, WATER_B_CNT_Z, WATER_B_SCL_X, WATER_B_SCL_Z);


	m_GameObject.GetList()->Append(new Player);

	m_GameObject.Init();
}

//=============================================================================
// �ŐV����
Scene* Game::Update()
{
	Camera::GetInstance()->Update();
	UpdateMeshWater();
	m_GameObject.Update();


	if (GetKeyboardTrigger(DIK_B))
	{
		//return (new Result);
	}
	return this;
}

//=============================================================================
// �`�揈��
void Game::Draw()
{
	m_GameObject.Draw();

	DrawMeshWater();


}

//=============================================================================
// �I������
void Game::Uninit()
{
	//UninitTexture();
	TextureList::GetInstance()->ClearList();

	UninitMeshWater();

	m_GameObject.UninitAll();
}
