//=============================================================================
//
// 2DÇÃîwåi [BG.h]
// Author : êÏà‰àÍê∂
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "2D_Polygon.h"
#include "Texture.h"

//=============================================================================
// ÉNÉâÉXêÈåæ
class BackGround :public Polygon
{
public:

	void Init();
	void Update();
	void Draw();
	void Uninit();

	//static BackGround* Create()
	//{
	//	if (m_BackGround == nullptr)
	//	{
	//		m_BackGround = new BackGround;
	//	}
	//	return m_BackGround;
	//}

	BackGround() :Polygon()
	{
		ObjectType = ObjT_BG;
	}

	void SetBG(int TextureIdx);

};
#endif