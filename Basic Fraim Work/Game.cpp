//=============================================================================
//
// ゲーム [Game.cpp]
// Author : 川井一生
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

// メッシュの水の初期設定
#define WATER_POS		(D3DXVECTOR3(0.0f, -100.0f, 0.0f))
#define WATER_ROT		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
#define WATER_B_CNT_X	(250)
#define WATER_B_CNT_Z	(250)
#define WATER_B_SCL_X	(75.0f)
#define WATER_B_SCL_Z	(75.0f)


//=============================================================================
// グローバル
GameObject Game::m_GameObject;

//=============================================================================
// 初期化処理
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
// 最新処理
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
// 描画処理
void Game::Draw()
{
	m_GameObject.Draw();

	DrawMeshWater();


}

//=============================================================================
// 終了処理
void Game::Uninit()
{
	//UninitTexture();
	TextureList::GetInstance()->ClearList();

	UninitMeshWater();

	m_GameObject.UninitAll();
}
