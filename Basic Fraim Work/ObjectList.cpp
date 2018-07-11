//=============================================================================
//
// �Q�[���I�u�W�F�N�g [GameObject.cpp]
// Author : ���ꐶ
//
//=============================================================================
// �C���N���[�h�t�@�C��
#include "ObjectList.h"
#include "main.h"

//=============================================================================
// �}�N���錾

// �`��^�C�v
enum RenderState
{
	Polygon_Render_State,
	Billboard_Render_State,
	Model_Render_State,
};

//=============================================================================
// �O���[�o��
RenderState g_RenderState;

//=============================================================================
// �v���g�^�C�v�錾
void CheangeRenderState(RenderState State);

//=============================================================================
// �I�u�W�F�N�g�����X�g�ɒǉ�
void ObjectList::Append(Object *ojp)
{
	List *newObject;
	List *NodePtr;
	List *PrevNode = nullptr;

	newObject = new List;
	newObject->m_Object = ojp;

	// ���X�g�̓��ɉ��������Ă��邩
	if (Head == nullptr)
	{
		Head = newObject;
	}
	else
	{
		NodePtr = Head;

		// �ǉ����ׂ��ꏊ�����X�g�̒����猟��
		while (NodePtr != nullptr && NodePtr->m_Object->ObjectType < ojp->ObjectType)
		{
			PrevNode = NodePtr;
			NodePtr = NodePtr->next;
		}
		// ���X�g�̓��ɓ����ׂ���
		if (PrevNode == nullptr)
		{
			Head = newObject;
			newObject->next = NodePtr;
		}
		// ���X�g�ɒǉ����Ď��̂��̂��Ȃ��Ȃ���
		else
		{
			PrevNode->next = newObject;
			newObject->next = NodePtr;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�����X�g����������鏈��
// �������f�o�b�O�K�v������
// �I�u�W�F�N�g�N���X�̒���(Idx)�C���f�b�N�X�ԍ���(ObjectType)�I�u�W�F�N�g���
// ����ɂ���Ăǂ̃I�u�W�F�N�g�����ł����������f����
//=============================================================================
void ObjectList::Delete(Object *ojp)
{
	List *NodePtr;
	List *PrevNode = nullptr;

	// ���X�g�̒�������ۂł͂Ȃ���
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// �������f�o�b�O�K�v������
		// ��������I�u�W�F�N�g�̌���
		while (NodePtr != nullptr && NodePtr->m_Object->Idx < ojp->Idx)
		{
			PrevNode = NodePtr;
			NodePtr = NodePtr->next;
		}
		// ���������ʒu��NULL�łȂ���
		// �������ă��X�g���Ȃ��Ȃ���
		if (NodePtr != nullptr)
		{
			PrevNode->next = NodePtr->next;
			delete NodePtr;
		}
	}
}

//=============================================================================
// ���X�g�̒��̌���
Object *ObjectList::Search(ObjectType TypeIdx)
{
	List *NodePtr;

	if (Head == nullptr)
	{
		return nullptr;
	}
	else
	{
		NodePtr = Head;

		while (NodePtr != nullptr)
		{
			if (NodePtr->m_Object->ObjectType == TypeIdx)
			{
				return NodePtr->m_Object;
			}
			NodePtr = NodePtr->next;
		}
	}

}

//=============================================================================
// ����������
void ObjectList::Init()
{
	List *NodePtr;

	// ���X�g�̒�������ۂł͂Ȃ���
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// ���X�g�̏I���܂Ń��X�g��i�߂�
		while (NodePtr != nullptr)
		{
			NodePtr->m_Object->Init();
			NodePtr = NodePtr->next;
		}
	}

}

//=============================================================================
// �ŐV����
void ObjectList::Update()
{
	List *NodePtr;

	// ���X�g�̒�������ۂł͂Ȃ���
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// ���X�g�̏I���܂Ń��X�g��i�߂�
		while (NodePtr != nullptr)
		{
			NodePtr->m_Object->Update();
			NodePtr = NodePtr->next;
		}
	}
}

//=============================================================================
// �`�揈��
void ObjectList::Draw()
{
	List * NodePtr;

	// ���X�g�̒�������ۂł͂Ȃ���
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// ���X�g�̏I���܂Ń��X�g��i�߂�
		while (NodePtr != nullptr)
		{
			// �`��^�C�v���|���S���ɕϊ����邩
			if (NodePtr->m_Object->ObjectType > Polygon_Object_Start
				&& NodePtr->m_Object->ObjectType < Polygon_Object_End)
			{
				CheangeRenderState(Polygon_Render_State);
			}
			// �`��^�C�v���r���{�[�h�ɕϊ����邩
			if (NodePtr->m_Object->ObjectType > Billboard_Object_Start
				&& NodePtr->m_Object->ObjectType < Billboard_Object_End)
			{
				CheangeRenderState(Billboard_Render_State);
			}
			// �`��^�C�v�����f���ɕϊ����邩
			if (NodePtr->m_Object->ObjectType > Model_Object_Start
				&& NodePtr->m_Object->ObjectType < Model_Object_End)
			{
				CheangeRenderState(Model_Render_State);
			}

			NodePtr->m_Object->Draw();
			NodePtr = NodePtr->next;
		}
	}
}

//=============================================================================
// �I������
void ObjectList::Uninit()
{
	List *NodePtr;
	List *NextNode;
	// ���X�g�̒�������ۂł͂Ȃ���
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// ���X�g�̏I���܂Ń��X�g��i�߂�
		while (NodePtr != nullptr)
		{
			NodePtr->m_Object->Uninit();
			delete NodePtr->m_Object;
			NextNode = NodePtr->next;
			delete NodePtr;
			NodePtr = NextNode;
		}
	}
}


//=============================================================================
// �`��^�C�v��Ǌւ��鏈��
void CheangeRenderState(RenderState State)
{
	if (State == g_RenderState)
	{
		return;
	}

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �`��^�C�v��ݒ�
	g_RenderState = State;

	switch (State)
	{
	case Polygon_Render_State:
		break;
	case Billboard_Render_State:
		// ���e�X�g��L���ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		// ���C���e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		break;
	case Model_Render_State:
		// ���e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		// ���C���e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		break;
	default:
		// ���e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		// ���C���e�B���O��L���ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		break;
	}

	return;
}