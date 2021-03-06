////////////////////////////////////////////////////////////////////////////////
// ChangeCmd.cpp
#include "StdAfx.h"
#include "ChangeCmd.h"
#include "ItemObject.h"
#include "Logging/Log.h"
#include "User/CUserData.h"


// joinmu private custom
// expiry date: 14/12/2016
CChangeCmd g_ChangeCmd;

CChangeCmd::CChangeCmd()
{
	this->m_bSystemEnable = false;
}

CChangeCmd::~CChangeCmd()
{
}

void CChangeCmd::LoadFile(char * szFile)
{
	this->m_mapChangeData.clear();

	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(szFile);

	if (res.status != pugi::status_ok)
	{
		this->m_bSystemEnable = false;
		return;
	}

	pugi::xml_node mainXML = file.child("JoinMu");
	 
	this->m_bSystemEnable = mainXML.attribute("Enable").as_bool();

	CHANGE_ITEM_DATA m_ChangeData;

	for (pugi::xml_node change = mainXML.child("Change"); change; change = change.next_sibling())
	{
		BYTE ItemCat = change.attribute("ItemCat").as_int();
		WORD ItemIndex = change.attribute("ItemIndex").as_int();

		m_ChangeData.ItemID = ITEMGET(ItemCat, ItemIndex);

		if (m_ChangeData.ItemID == (WORD)-1)
		{
			sLog->outError("Change Item Cmd - Wrong item found (System disabled) (%d/%d)", ItemCat, ItemIndex);
			this->m_bSystemEnable = false;
			return;
		}

		m_ChangeData.CoinType = change.attribute("CoinType").as_int();

		if (m_ChangeData.CoinType < 0 || m_ChangeData.CoinType > 3)
		{
			sLog->outError("Change Item Cmd - Wrong Coin Type (System disabled) (%d/%d) (%d)", ItemCat, ItemIndex, m_ChangeData.CoinType);
			this->m_bSystemEnable = false;
			return;
		}

		m_ChangeData.CoinValue = change.attribute("CoinValue").as_int();

		if (this->m_mapChangeData.find(m_ChangeData.ItemID) != this->m_mapChangeData.end())
		{
			sLog->outError("Change Item Cmd - Already Exist item (System disabled) (%d/%d)", ItemCat, ItemIndex);
			this->m_bSystemEnable = false;
			return;
		}

		this->m_mapChangeData.insert(std::pair<int, CHANGE_ITEM_DATA>(m_ChangeData.ItemID, m_ChangeData));
	}
}

char * szCoinNames[] = { "Zen", "WCoinC", "WCoinP", "GoblinPoint" };

int CChangeCmd::DoChange(CGameObject &Obj) // -1 - system off, 0 - no change made, > 0 - count of items changed
{
	if (this->m_bSystemEnable == false)
	{
		return -1;
	}

	if (!ObjectMaxRange(Obj.m_Index))
	{
		return -1;
	}

	if (Obj.Type != OBJ_USER)
	{
		return -1;
	}

	
	Obj.ChaosLock = TRUE; // Lock Inventory

	int iItemChangeCnt = 0;

	for (int i = INVETORY_WEAR_SIZE; i < INVENTORY_SIZE - 1; i++) // Pentagram excluded, so -1
	{
		if (PSHOP_RANGE(i) == TRUE)
		{
			continue;
		}

		if (Obj.pntInventory[i]->IsItem() == false)
		{
			continue;
		}

		std::map<int, CHANGE_ITEM_DATA>::iterator It = this->m_mapChangeData.find(Obj.pntInventory[i]->m_Type);

		if (It == this->m_mapChangeData.end())
		{
			continue;
		}

		if (It->second.CoinType == 0)
		{
			if (Obj.m_PlayerData->Money + It->second.CoinValue > MAX_ZEN)
			{
				MsgOutput(Obj.m_Index, Lang.GetText(0,637));
				Obj.ChaosLock = FALSE;
				return iItemChangeCnt;
			}

			Obj.m_PlayerData->Money += It->second.CoinValue;
			GSProtocol.GCMoneySend(Obj.m_Index, Obj.m_PlayerData->Money);
		}

		else
		{
			GDReqInGameShopPointAdd(Obj.m_Index, It->second.CoinType - 1, It->second.CoinValue);
		}

		MsgOutput(Obj.m_Index, Lang.GetText(0, 638), Obj.pntInventory[i]->GetName(), It->second.CoinValue, szCoinNames[It->second.CoinType]);

		gObjInventoryDeleteItem(Obj.m_Index, i);
		GSProtocol.GCInventoryItemDeleteSend(Obj.m_Index, i, 1);

		iItemChangeCnt++;
	}

	Obj.ChaosLock = FALSE;
	return iItemChangeCnt;
}


////////////////////////////////////////////////////////////////////////////////
//  vnDev.Games - MuServer S12EP2 IGC v12.0.1.0 - Trong.LIVE - DAO VAN TRONG  //
////////////////////////////////////////////////////////////////////////////////

