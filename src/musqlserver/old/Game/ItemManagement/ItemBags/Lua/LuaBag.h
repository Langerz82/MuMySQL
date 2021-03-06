////////////////////////////////////////////////////////////////////////////////
// LuaBag.h
#ifndef _LUABAG_H
#define _LUABAG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "BaseBagClass/Bag.h"
#include "MuLua.h"
#include "ItemObject.h"
#include "GremoryCase.h"

#define MAX_ITEM_VARIABLES 29
#define ITEMBAG_SCRIPT_FILE "\\Scripts\\ItemBags\\ItemBagScript.lua"

static struct ItemMapInt
{
	std::string		Name;
	int				Variable;
};

class CLuaBag
{
public:
	CLuaBag();
	virtual ~CLuaBag();

	void Init();

	void InsertItemMap(BAG_ITEM * m_Item);
	static BOOL	GetVariableItem(lua_State * Lua);
	static BOOL	SetVariableItem(lua_State * Lua);

	bool DropCommonBag(CGameObject &Obj, BYTE MapNumber, BYTE DropX, BYTE DropY, BAG_ITEM * m_Item);
	bool DropMonsterBag(CGameObject &Obj, int iMonsterIndex, BYTE MapNumber, BYTE DropX, BYTE DropY, BAG_ITEM * m_Item);
	bool DropEventBag(CGameObject &Obj, int iMonsterIndex, BYTE MapNumber, BYTE DropX, BYTE DropY, BAG_ITEM * m_Item);
	bool MakeItemFromBag(CGameObject &Obj, BAG_ITEM * m_Item, CItemObject & Item, time_t & Duration);
	bool MakeItemFromBagForGremoryCase(CGameObject &Obj, BAG_ITEM* m_Item, _stGremoryCaseItem &Item);

	void LoadItemBag();

	ItemMapInt			m_ItemInfo[MAX_ITEM_VARIABLES];
	MULua				m_Lua;
};

extern CLuaBag gLuaBag;

const struct luaL_Reg RegisterItemInfo[] =
{
	{ "__index",		CLuaBag::GetVariableItem },
	{ "__newindex",		CLuaBag::SetVariableItem },
	{ NULL,				NULL },
};

#endif


////////////////////////////////////////////////////////////////////////////////
//  vnDev.Games - MuServer S12EP2 IGC v12.0.1.0 - Trong.LIVE - DAO VAN TRONG  //
////////////////////////////////////////////////////////////////////////////////

