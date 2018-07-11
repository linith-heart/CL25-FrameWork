//=============================================================================
//
// ���U���g�I�u�W�F�N�g [ResultObject.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _RESULT_OBJECT_H_
#define _RESULT_OBJECT_H_
//=============================================================================
// �C���N���[�h�t�@�C��
#include "Object.h"



#define GAME_OBJECT_MAX	(1024)
#define BULLET_MAX		(500)
#define PLAYER_MAX		(1)
#define ENEMY_MAX		(20)
#define EFFECT_MAX		(4096)

//=============================================================================
// �N���X�錾
class ResultObject
{
public:

	// 


	Object *m_Bullet[BULLET_MAX];
	Object *m_Enemy[ENEMY_MAX];
	Object *m_Effect[EFFECT_MAX];

	void Init(Object *obp);
	void InitBullet(Object *obp);
	void InitPlayer(Object *obp);
	void InitEnemy(Object *obp);
	void InitEffect(Object *obp);
	void Update();
	void Draw();
	void UninitAll();


	void Uninit(Object *obp);
};

#endif