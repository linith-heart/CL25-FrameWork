//=============================================================================
//
// オブジェクト [Object.h]
// Author : 川井一生
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_


#define OBJECT_MAX	(1024)


enum ObjectType		// 描画順番としての役割がある
{
	Blank_State = -1,
	// 実体のないオブジェクト
	ObjT_BulletBlank,
	ObjT_Buttons,

	// 2Dポリゴンのオブジェクト
	Polygon_Object_Start,
	ObjT_BG,
	ObjT_TitleMenu,

	Polygon_Object_End,
	// 3Dポリゴンのオブジェクト
	Billboard_Object_Start,
	ObjT_Bullet,
	ObjT_BulletGroup,

	Billboard_Object_End,
	// モデルのオブジェクト
	Model_Object_Start,
	ObjT_Player,
	ObjT_Npc,
	ObjT_ZergStar,

	Model_Object_End,
	Object_Type_Max,
};



//=============================================================================
// クラス宣言
class Object
{
private:
	static int IdxCnt;	// インデックスのカウンター
public:

	int Idx;
	ObjectType ObjectType = Blank_State;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;


	Object()
	{
		Idx = IdxCnt;
		IdxCnt++;
	}
	~Object()
	{

	}
};


#endif


