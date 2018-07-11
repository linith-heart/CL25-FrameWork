//=============================================================================
//
// ゲームオブジェクト [GameObject.cpp]
// Author : 川井一生
//
//=============================================================================
// インクルードファイル
#include "ObjectList.h"
#include "main.h"

//=============================================================================
// マクロ宣言

// 描画タイプ
enum RenderState
{
	Polygon_Render_State,
	Billboard_Render_State,
	Model_Render_State,
};

//=============================================================================
// グローバル
RenderState g_RenderState;

//=============================================================================
// プロトタイプ宣言
void CheangeRenderState(RenderState State);

//=============================================================================
// オブジェクトをリストに追加
void ObjectList::Append(Object *ojp)
{
	List *newObject;
	List *NodePtr;
	List *PrevNode = nullptr;

	newObject = new List;
	newObject->m_Object = ojp;

	// リストの頭に何か入っているか
	if (Head == nullptr)
	{
		Head = newObject;
	}
	else
	{
		NodePtr = Head;

		// 追加すべき場所をリストの中から検索
		while (NodePtr != nullptr && NodePtr->m_Object->ObjectType < ojp->ObjectType)
		{
			PrevNode = NodePtr;
			NodePtr = NodePtr->next;
		}
		// リストの頭に入れるべきか
		if (PrevNode == nullptr)
		{
			Head = newObject;
			newObject->next = NodePtr;
		}
		// リストに追加して次のものをつなげなおす
		else
		{
			PrevNode->next = newObject;
			newObject->next = NodePtr;
		}
	}
}

//=============================================================================
// オブジェクトをリストから消去する処理
// ＊＊＊デバッグ必要＊＊＊
// オブジェクトクラスの中に(Idx)インデックス番号と(ObjectType)オブジェクト種類
// これによってどのオブジェクトを消滅したいか判断する
//=============================================================================
void ObjectList::Delete(Object *ojp)
{
	List *NodePtr;
	List *PrevNode = nullptr;

	// リストの中が空っぽではないか
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// ＊＊＊デバッグ必要＊＊＊
		// 消去するオブジェクトの検索
		while (NodePtr != nullptr && NodePtr->m_Object->Idx < ojp->Idx)
		{
			PrevNode = NodePtr;
			NodePtr = NodePtr->next;
		}
		// 消したい位置がNULLでないか
		// 消去してリストをつなげなおす
		if (NodePtr != nullptr)
		{
			PrevNode->next = NodePtr->next;
			delete NodePtr;
		}
	}
}

//=============================================================================
// リストの中の検索
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
// 初期化処理
void ObjectList::Init()
{
	List *NodePtr;

	// リストの中が空っぽではないか
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// リストの終わりまでリストを進める
		while (NodePtr != nullptr)
		{
			NodePtr->m_Object->Init();
			NodePtr = NodePtr->next;
		}
	}

}

//=============================================================================
// 最新処理
void ObjectList::Update()
{
	List *NodePtr;

	// リストの中が空っぽではないか
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// リストの終わりまでリストを進める
		while (NodePtr != nullptr)
		{
			NodePtr->m_Object->Update();
			NodePtr = NodePtr->next;
		}
	}
}

//=============================================================================
// 描画処理
void ObjectList::Draw()
{
	List * NodePtr;

	// リストの中が空っぽではないか
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// リストの終わりまでリストを進める
		while (NodePtr != nullptr)
		{
			// 描画タイプをポリゴンに変換するか
			if (NodePtr->m_Object->ObjectType > Polygon_Object_Start
				&& NodePtr->m_Object->ObjectType < Polygon_Object_End)
			{
				CheangeRenderState(Polygon_Render_State);
			}
			// 描画タイプをビルボードに変換するか
			if (NodePtr->m_Object->ObjectType > Billboard_Object_Start
				&& NodePtr->m_Object->ObjectType < Billboard_Object_End)
			{
				CheangeRenderState(Billboard_Render_State);
			}
			// 描画タイプをモデルに変換するか
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
// 終了処理
void ObjectList::Uninit()
{
	List *NodePtr;
	List *NextNode;
	// リストの中が空っぽではないか
	if (Head == nullptr)
	{
		return;
	}
	else
	{
		NodePtr = Head;

		// リストの終わりまでリストを進める
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
// 描画タイプを班関する処理
void CheangeRenderState(RenderState State)
{
	if (State == g_RenderState)
	{
		return;
	}

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 描画タイプを設定
	g_RenderState = State;

	switch (State)
	{
	case Polygon_Render_State:
		break;
	case Billboard_Render_State:
		// αテストを有効にする
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		// ラインティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		break;
	case Model_Render_State:
		// αテストを無効にする
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		// ラインティングを有効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		break;
	default:
		// αテストを無効にする
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		// ラインティングを有効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		break;
	}

	return;
}