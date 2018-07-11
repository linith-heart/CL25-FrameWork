//=============================================================================
//
// �o���b�g [Bullet.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "Object.h"
#include "Game.h"
#include "2D_Billboard.h"
#include "Texture.h"
#include "Character.h"

//=============================================================================
// �}�N���錾
#define BULLET_IN_GROUP	(50)

//=============================================================================
// �N���X�錾
// �o���b�g�N���X
class Bullet : public Billboard
{
public:

	bool		use;		// �g���Ă��邩
	/*
	�Q�[���̒��ŏ�ɕ\�������肵�Ȃ������肷����̂Ȃ̂�
	use�t���O��ݒ肵�������邩���Ȃ����Ǘ�
	new��delete�̎g�p���Q�[���v���C���͔�����ړI
	*/

	D3DXVECTOR3	m_Vel;	// �ړ���
	int			m_Time;	// �؋󎞊�
	Character::Team m_Team;

	void Init(float Size, TEXTURE_IDX Texture);
	void Update();
	void Draw();
	void Uninit();

	void Set(D3DXVECTOR3 Pos, D3DXVECTOR3 Vel, int Time , Character::Team Team);

	Bullet():Billboard()
	{
		ObjectType = ObjT_Bullet;
	}

private:
	void Init()	{}
};
#endif