//=============================================================================
//
// プレイヤー [Player.h]
// Author : 川井一生
//
//=============================================================================
#include "Player.h"
#include "Texture.h"

#include "camera.h"
#include "input.h"

#include "Bullet.h"
#include "mathWk.h"

//=============================================================================
// 初期化処理
void Player::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// メッシュ構造体の初期化
	Mesh.Pos = VEC3CLEAR;
	Mesh.Rot = D3DXVECTOR3(0.0f, BASE_ANGLE,0.0f);
	Mesh.Scl = VEC3NUM(0.1f);

	Mesh.NumMat = 0;
	Mesh.BuffMat = nullptr;
	Mesh.Mesh = nullptr;

	Mesh.TexId = PLAYER_MODEL_TEXTURE_IDX;

	LoadXFile(pDevice, PLAYER_MODEL_FILE_PATH, &Mesh);

	// キャラクターの初期化
	Chara.m_AtkSpd	= BULLET_SPEED;
	Chara.m_Spd		= MOVE_VAL_MAX;
	Chara.m_Team	= Team_1;

	// 移動に使うものの初期化
	m_Vel = 0;
	m_Dir = VEC3CLEAR;

	// ギミックに使うものの初期化
	m_isFaceRot = false;
	m_isReCenter = false;
	m_isAxisCenter = false;
	m_CameraState = TopDown_State;

	// バレットの初期化
	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_Bullet[i] = new Bullet;
		m_Bullet[i]->Init(BULLET_SIZE, BULLET_TEXTURE);
	}
}

//=============================================================================
// 最新処理
void Player::Update()
{
	Player::Move();		// 移動の処理
	Player::Action();	// アクション処理

	if (GetKeyboardTrigger(DIK_NUMPAD1))
	{
		m_CameraState = TopDown_State;
	}
	if (GetKeyboardTrigger(DIK_NUMPAD2))
	{
		m_CameraState = LeftRight_State;
	}
	if (GetKeyboardTrigger(DIK_NUMPAD3))
	{
		m_CameraState = BackFront_State;
	}

	if (m_CameraState != Camera::GetInstance()->m_CurrentState)
	{
		Camera::GetInstance()->m_CurrentState = m_CameraState;
		Camera::GetInstance()->Set();
		Player::AxisCenter();
	}



	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_Bullet[i]->Update();
	}

}

//=============================================================================
// 描画処理
void Player::Draw()
{
	//=====================================================
	// プレイヤーモデルの描画
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// テクスチャーを取得
	LPDIRECT3DTEXTURE9 Texture = TextureList::GetInstance()->GetTexture(Mesh.TexId);


	D3DMesh::Draw(pDevice, &Mesh, &Texture);


	//=====================================================
	// バレットの描画

	// αテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_Bullet[i]->Draw();
	}

	// αテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// 終了処理
void Player::Uninit()
{
	SAFE_RELEASE(Mesh.BuffMat);

	SAFE_RELEASE(Mesh.Mesh);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		m_Bullet[i]->Uninit();
		delete m_Bullet[i];
	}

}

//=============================================================================
// 移動処理
void Player::Move()
{
	D3DXVECTOR3 OldPos = Mesh.Pos;


	bool VelAdded = false;			// 移動量の変換があったか

	bool isUpDwnPress = false;		// 左右の変換があったか
	bool isLftRgtPress = false;		// 上下の変換があったか


	if (GetKeyboardPress(DIK_W))
	{
		float temp = m_Dir.z;			// 返還前の移動角度

		if (m_Dir.z < ANGLE_VAL_MAX)	// 移動角度++
			m_Dir.z += ANGLE_VAL;
		else
		{
			m_Dir.z = ANGLE_VAL_MAX;	// マックスを超えないように
		}

		if (GetKeyboardPress(DIK_S))
			m_Dir.z = temp;			// 同時押しなら返還前に戻す
		else
		{
			VelAdded = true;
			isUpDwnPress = true;

			if (m_Vel < MOVE_VAL_MAX)	// 移動量++
				m_Vel += MOVE_VAL;
			else
				m_Vel = MOVE_VAL_MAX;	// マックスを超えないように
		}
	}
	else if (GetKeyboardPress(DIK_S))
	{
		VelAdded = true;
		isUpDwnPress = true;
		if (m_Dir.z > -ANGLE_VAL_MAX)
			m_Dir.z -= ANGLE_VAL;
		else
			m_Dir.z = -ANGLE_VAL_MAX;

		if (m_Vel < MOVE_VAL_MAX)		// 移動量++
			m_Vel += MOVE_VAL;
		else
			m_Vel = MOVE_VAL_MAX;		// マックスを超えないように
	}


	if (!isUpDwnPress)	// 上下の変換が無ければ移動角度をゼロに近づける
	{
		if (m_Dir.z > TRACTION)
			m_Dir.z -= TRACTION;
		else if (m_Dir.z < -TRACTION)
			m_Dir.z += TRACTION;
		else
			m_Dir.z = 0;
	}



	if (GetKeyboardPress(DIK_D))
	{
		float temp = m_Dir.x;			// 返還前の移動角度

		if (m_Dir.x < ANGLE_VAL_MAX)	// 移動角度++
			m_Dir.x += ANGLE_VAL;
		else
		{
			m_Dir.x = ANGLE_VAL_MAX;	// マックスを超えないように
		}

		if (GetKeyboardPress(DIK_A))
			m_Dir.x = temp;			// 同時押しなら返還前に戻す
		else
		{
			VelAdded = true;
			isLftRgtPress = true;

			if (m_Vel < MOVE_VAL_MAX)	// 移動量++
				m_Vel += MOVE_VAL;
			else
				m_Vel = MOVE_VAL_MAX;	// マックスを超えないように
		}
	}
	else if (GetKeyboardPress(DIK_A))
	{
		VelAdded = true;
		isLftRgtPress = true;
		if (m_Dir.x > -ANGLE_VAL_MAX)
			m_Dir.x -= ANGLE_VAL;
		else
			m_Dir.x = -ANGLE_VAL_MAX;

		if (m_Vel < MOVE_VAL_MAX)		// 移動量++
			m_Vel += MOVE_VAL;
		else
			m_Vel = MOVE_VAL_MAX;		// マックスを超えないように
	}


	if (!isLftRgtPress)	// 左右の変換が無ければ移動角度をゼロに近づける
	{
		if (m_Dir.x > TRACTION)
			m_Dir.x -= TRACTION;
		else if (m_Dir.x < -TRACTION)
			m_Dir.x += TRACTION;
		else
			m_Dir.x = 0;
	}

	if (!VelAdded)		// 移動量の変換が無ければゼロに近づける
	{
		if (m_Vel > 0)
			m_Vel -= MOVE_VAL;
		else
			m_Vel = 0;
	}

	D3DXVECTOR3 temp = Camera::GetInstance()->m_At - Camera::GetInstance()->m_Eye;			// カメラとプレイヤーの角度を求める
	float tCamAng = atan2(temp.x, temp.z);
	float tDirAng = atan2(m_Dir.z, m_Dir.x);
	
	D3DXVECTOR3 MoveVal = VEC3CLEAR;

	//移動量を計算
	switch (m_CameraState)
	{
	case TopDown_State:
		MoveVal.x = cosf(tDirAng - tCamAng) * m_Vel;
		MoveVal.z = sinf(tDirAng - tCamAng) * m_Vel;
		break;
	case LeftRight_State:
		MoveVal.y = -cosf(tDirAng - tCamAng) * m_Vel;
		MoveVal.z = sinf(tDirAng - tCamAng) * m_Vel;
		break;
	case BackFront_State:
		MoveVal.x = cosf(tDirAng - tCamAng) * m_Vel;
		MoveVal.y = sinf(tDirAng - tCamAng) * m_Vel;
		break;
	default:
		break;
	}

	Mesh.Pos += MoveVal;


	if (m_isFaceRot)
	{
		float tAng = atan2f(MoveVal.z, MoveVal.x);
		Mesh.Rot.y = -tAng - (0.5 * D3DX_PI);
	}
	else
	{
		if (Mesh.Rot.y != BASE_ANGLE)
		{
			D3DXVECTOR3 tVec = Ang2Vec(Mesh.Rot, 1);
			D3DXVECTOR3 tVec2 = D3DXVECTOR3(0.0f,0.0f,-1.0f);
			if (Vec2Cross(tVec, tVec2) < -ROT_VALUE)
			{
				Mesh.Rot.y -= ROT_VALUE;
			}
			else if (Vec2Cross(tVec, tVec2) > ROT_VALUE)
			{
				Mesh.Rot.y += ROT_VALUE;
			}
			else
			{
				Mesh.Rot.y = BASE_ANGLE;
			}
		}
	}

	// 軸をゼロに戻す処理
	if (m_isAxisCenter)
	{
		Mesh.Pos -= m_AxisCenterVec;
		m_AxisCenterCnt--;
		if (m_AxisCenterCnt <= 0)
			m_isAxisCenter = false;
	}

	// 真ん中に戻す処理
	if (m_isReCenter)
	{
		Mesh.Pos -= m_ReCenterVec;
		m_ReCenterCnt--;
		if (m_ReCenterCnt <= 0)
			m_isReCenter = false;
	}

}

//=============================================================================
// アクションの処理
void Player::Action()
{
	// バレットのクールダウンが終わっていれば
	if (m_BullCD <= 0)
	{	// スペースが押されていたら
		if (GetKeyboardPress(DIK_SPACE))
		{	// 使用していないバレットを検索しバレットのセット処理をする
			for (int i = 0; i < BULLET_MAX; i++)
			{
				if (!m_Bullet[i]->use)
				{
					D3DXVECTOR3 BullVel = Ang2Vec(Mesh.Rot, BULLET_SPEED);
					//BullVel.x = cosf(-Mesh.Rot.y - (0.5 * D3DX_PI)) *BULLET_SPEED;
					//BullVel.z = sinf(-Mesh.Rot.y - (0.5 * D3DX_PI)) *BULLET_SPEED;

					m_Bullet[i]->Set(Mesh.Pos, BullVel, BULLET_AIR_TIME, Chara.m_Team);

					// バレットをセットしたらバレットのクールダウンをセット
					m_BullCD = BULLET_CD;
					break;
				}
			}
		}
	}
	// バレットのクールダウンを進める
	m_BullCD--;

	// m_isFaceRotのオンオフスイッチ
	if (GetKeyboardTrigger(DIK_N))
	{
		if (m_isFaceRot)
			m_isFaceRot = false;
		else
			m_isFaceRot = true;
	}
}

//=============================================================================
// プレイヤーを真ん中に戻す処理
void Player::ReCenter()
{
	//=====================================================
	// resetting the player position to the center of the map
	if (!m_isReCenter)
	{
		m_isReCenter = true;

		m_ReCenterVec = Mesh.Pos;
		m_ReCenterVec = m_ReCenterVec / RECENTER_FRAME;

		m_ReCenterCnt = RECENTER_FRAME;
	}


}

//=============================================================================
// m_CameraStateよって軸をゼロに戻す
void Player::AxisCenter()
{
	//=====================================================
	// setting the axis based on the current camera state to zero
	if (!m_isAxisCenter)
	{
		m_isAxisCenter = true;

		m_AxisCenterVec = VEC3CLEAR;

		switch (m_CameraState)
		{
		case TopDown_State:
			m_AxisCenterVec.y = Mesh.Pos.y;
			break;
		case LeftRight_State:
			m_AxisCenterVec.x = Mesh.Pos.x;
			break;
		case BackFront_State:
			m_AxisCenterVec.z = Mesh.Pos.z;
			break;
		default:
			break;
		}
		m_AxisCenterVec = m_AxisCenterVec / RECENTER_FRAME;

		m_AxisCenterCnt = RECENTER_FRAME;
	}

}
