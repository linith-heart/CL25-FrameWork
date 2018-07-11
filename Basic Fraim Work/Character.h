//=============================================================================
//
// キャラクター[Character.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_


//=============================================================================
// マクロ定義

//=============================================================================
// クラス宣言
class Character
{
public:
	enum Team
	{
		Team_1,
		Team_2,
		Team_Max
	};
protected:
	struct CHARACTER
	{
		int		m_HP;
		float	m_Spd;
		int		m_AtkSpd;
		int		m_Dmg;
		Team	m_Team;
	};
	CHARACTER Chara;
};
#endif