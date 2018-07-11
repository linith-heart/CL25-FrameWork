//=============================================================================
//
// �^�C�g���̃��j���[ [TitleMenu.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _TITLE_MENU_H_
#define _TITLE_MENU_H_

#include "2D_Polygon.h"



//=============================================================================
// �N���X�錾


class TitleButton :public Polygon
{
public:
	void Init(int no);
	void Update();
	void Draw();
	void Uninit();

	TitleButton():Polygon()
	{
		ObjectType = ObjT_Buttons;
	}
private:
	void Init(){}

#define SIZE_X	(350)
#define SIZE_Y	(64)
#define POS_X	(SIZE_X / 2)
#define POS_Y	(SCREEN_HEIGHT / 2)

};


class TitleMenu: public Object
{
public:
	enum MenuButtons
	{
		Start_Idx,
		Exit_Idx,
		Menu_Buttons_Max
	};
	TitleButton* Button[Menu_Buttons_Max];
	//TitleButton* Highlight;
	void Init();
	void Update();
	void Draw();
	void Uninit();

	TitleMenu()
	{
		ObjectType = ObjT_TitleMenu;
	}

};

#endif
