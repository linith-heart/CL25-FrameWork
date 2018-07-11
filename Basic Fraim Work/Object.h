//=============================================================================
//
// �I�u�W�F�N�g [Object.h]
// Author : ���ꐶ
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_


#define OBJECT_MAX	(1024)


enum ObjectType		// �`�揇�ԂƂ��Ă̖���������
{
	Blank_State = -1,
	// ���̂̂Ȃ��I�u�W�F�N�g
	ObjT_BulletBlank,
	ObjT_Buttons,

	// 2D�|���S���̃I�u�W�F�N�g
	Polygon_Object_Start,
	ObjT_BG,
	ObjT_TitleMenu,

	Polygon_Object_End,
	// 3D�|���S���̃I�u�W�F�N�g
	Billboard_Object_Start,
	ObjT_Bullet,
	ObjT_BulletGroup,

	Billboard_Object_End,
	// ���f���̃I�u�W�F�N�g
	Model_Object_Start,
	ObjT_Player,
	ObjT_Npc,
	ObjT_ZergStar,

	Model_Object_End,
	Object_Type_Max,
};



//=============================================================================
// �N���X�錾
class Object
{
private:
	static int IdxCnt;	// �C���f�b�N�X�̃J�E���^�[
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


