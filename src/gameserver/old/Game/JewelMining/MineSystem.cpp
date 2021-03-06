////////////////////////////////////////////////////////////////////////////////
// MineSystem.cpp
#include "MineSystem.h"
#include "LargeRand.h"
#include "Main.h"
#include "MapServerManager.h"
#include "GameProtocol.h"

CMineSystem g_MineSystem;

CMineSystem::CMineSystem()
{
}

CMineSystem::~CMineSystem()
{
}

void CMineSystem::LoadMineingDropScript()
{
	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(g_ConfigRead.GetPath("IGC_MiningSystem.xml"));

	if (res.status != pugi::status_ok)
	{
		sLog->outError("Failed to load IGC_MiningSystem.xml file! (%s)", res.description());
		return;
	}

	this->m_mapMineSuccessInfo.clear();
	this->m_vecRewardValue.clear();
	this->m_vecMiracleSuccessInfo.clear();
	this->m_vecMiracleRewardValue.clear();
	this->m_mapMapName.clear();
	this->m_vecRepairValue.clear();
	this->m_mapTwinkleSpawn.clear();

	pugi::xml_node mainXML_section = file.child("MiningSystem");
	pugi::xml_node successinfo = main_section.child("SuccessInfo");
	pugi::xml_node rewardinfo = main_section.child("RewardInfo");
	pugi::xml_node pandorainfo = main_section.child("PandoraSuccessInfo");
	pugi::xml_node pandorareward = main_section.child("PandoraRewardInfo");
	pugi::xml_node mapname = main_section.child("MapName");
	pugi::xml_node repairvalue = main_section.child("RepairValue");
	pugi::xml_node spot = main_section.child("Spot");

	this->m_iChanceStartValue = successinfo.attribute("ChanceStartValue").as_int();
	this->m_iChanceStartValue_Copy = this->m_iChanceStartValue;

	for (pugi::xml_node twinkle = successinfo.child("Twinkle"); twinkle; twinkle = twinkle.next_sibling())
	{
		_ST_MINESYSTEM_MINE_SUCCESS_INFO stMineSuccessInfo;

		stMineSuccessInfo.wTwinkleType = twinkle.attribute("Type").as_int();
		stMineSuccessInfo.iDurabilityDecrement = twinkle.attribute("DurabilityDec").as_int();
		stMineSuccessInfo.iSuccessRate[0] = twinkle.attribute("Rate1").as_int();
		stMineSuccessInfo.iSuccessRate[1] = twinkle.attribute("Rate2").as_int();
		stMineSuccessInfo.iSuccessRate[2] = twinkle.attribute("Rate3").as_int();
		stMineSuccessInfo.iSuccessRate[3] = twinkle.attribute("Rate4").as_int();
		stMineSuccessInfo.iSuccessRate[4] = twinkle.attribute("Rate5").as_int();

		if (stMineSuccessInfo.wTwinkleType < 605 || stMineSuccessInfo.wTwinkleType > 607)
		{
			sLog->outError("[Mining System] Invalid Monster Index");
		}

		this->m_mapMineSuccessInfo.insert(std::pair<int, _ST_MINESYSTEM_MINE_SUCCESS_INFO>(stMineSuccessInfo.wTwinkleType, stMineSuccessInfo));
	}

	for (pugi::xml_node twinkle = rewardinfo.child("Twinkle"); twinkle; twinkle = twinkle.next_sibling())
	{
		_ST_MINESYSTEM_REWARD_VALUE stRewardValue;

		stRewardValue.wTwinkleType = twinkle.attribute("Type").as_int();
		stRewardValue.iStage = twinkle.attribute("Stage").as_int();
		stRewardValue.wType = twinkle.attribute("NotifyItemCat").as_int();
		stRewardValue.wIndex = twinkle.attribute("NotifyItemIndex").as_int();
		stRewardValue.iTotalJewelNumber = twinkle.attribute("JewelCount").as_int();

		for (pugi::xml_node rewarditem = twinkle.child("Reward"); rewarditem; rewarditem = rewarditem.next_sibling())
		{
			_ST_MINESYSTEM_DROP_ITEM stDropItem;
			stDropItem.iItemType = rewarditem.attribute("ItemCat").as_int();
			stDropItem.iItemIndex = rewarditem.attribute("ItemIndex").as_int();
			stDropItem.iLevel = rewarditem.attribute("ItemLevel").as_int();
			stDropItem.iNumber = rewarditem.attribute("ItemCount").as_int();

			stRewardValue.vecDropItem.push_back(stDropItem);
		}

		if (stRewardValue.wTwinkleType < 605 || stRewardValue.wTwinkleType > 607)
		{
			sLog->outError("[Mining System] Invalid Monster Index");
		}

		this->m_vecRewardValue.push_back(stRewardValue);
	}

	for (pugi::xml_node twinkle = pandorainfo.child("Twinkle"); twinkle; twinkle = twinkle.next_sibling())
	{
		_ST_MINESYSTEM_MINE_MIRACLE_SUCCESS_INFO stMiracleSuccessInfo;

		stMiracleSuccessInfo.wTwinkleType = twinkle.attribute("Type").as_int();
		stMiracleSuccessInfo.iStage = twinkle.attribute("Stage").as_int();
		stMiracleSuccessInfo.iSuccessRate = twinkle.attribute("Rate").as_int();

		this->m_vecMiracleSuccessInfo.push_back(stMiracleSuccessInfo);
	}

	for (pugi::xml_node twinkle = pandorareward.child("Twinkle"); twinkle; twinkle = twinkle.next_sibling())
	{
		_ST_MINESYSTEM_REWARD_VALUE stRewardValue;

		stRewardValue.wTwinkleType = twinkle.attribute("Type").as_int();
		stRewardValue.iStage = twinkle.attribute("Stage").as_int();
		stRewardValue.wType = twinkle.attribute("NotifyItemCat").as_int();
		stRewardValue.wIndex = twinkle.attribute("NotifyItemIndex").as_int();
		stRewardValue.iTotalJewelNumber = twinkle.attribute("JewelCount").as_int();

		for (pugi::xml_node rewarditem = twinkle.child("Reward"); rewarditem; rewarditem = rewarditem.next_sibling())
		{
			_ST_MINESYSTEM_DROP_ITEM stDropItem;
			stDropItem.iItemType = rewarditem.attribute("ItemCat").as_int();
			stDropItem.iItemIndex = rewarditem.attribute("ItemIndex").as_int();
			stDropItem.iLevel = rewarditem.attribute("ItemLevel").as_int();
			stDropItem.iNumber = rewarditem.attribute("ItemCount").as_int();

			stRewardValue.vecDropItem.push_back(stDropItem);
		}

		if (stRewardValue.wTwinkleType < 605 || stRewardValue.wTwinkleType > 607)
		{
			sLog->outError("[Mining System] Invalid Monster Index");
		}

		this->m_vecMiracleRewardValue.push_back(stRewardValue);
	}

	for (pugi::xml_node map = mapname.child("Map"); map; map = map.next_sibling())
	{
		int iMapNumber = map.attribute("Number").as_int();
		std::string szMapName = map.attribute("Name").as_string();

		this->m_mapMapName.insert(std::pair<int, std::string>(iMapNumber, szMapName));
	}

	int iMaxRepairValue = repairvalue.attribute("MaxValue").as_int();

	for (pugi::xml_node repair = repairvalue.child("Repair"); repair; repair = repair.next_sibling())
	{
		_ST_MINESYSTEM_REPAIR_VALUE stRepairValue;

		stRepairValue.sItemType = repair.attribute("ItemCat").as_int();
		stRepairValue.sItemIndex = repair.attribute("ItemIndex").as_int();
		stRepairValue.sLevel = repair.attribute("ItemLevel").as_int();
		stRepairValue.sRepairValue = repair.attribute("Value").as_int();

		if (iMaxRepairValue < stRepairValue.sRepairValue)
		{
			sLog->outError("[Mining System] The repair value is over the max repair value");
		}

		this->m_vecRepairValue.push_back(stRepairValue);
	}

	int iCount = 0;
	for (pugi::xml_node spawn = spot.child("Spawn"); spawn; spawn = spawn.next_sibling())
	{
		_ST_MINESYSTEM_TWINKLE_SPAWN stTwinkleSpawn;

		stTwinkleSpawn.wType = spawn.attribute("Index").as_int();
		stTwinkleSpawn.byMapNumber = spawn.attribute("MapNumber").as_int();
		stTwinkleSpawn.byDistance = spawn.attribute("Distance").as_int();
		stTwinkleSpawn.byX = spawn.attribute("StartX").as_int();
		stTwinkleSpawn.byY = spawn.attribute("StartY").as_int();
		stTwinkleSpawn.byDir = spawn.attribute("Dir").as_int();

		this->m_mapTwinkleSpawn.insert(std::pair<int, _ST_MINESYSTEM_TWINKLE_SPAWN>(iCount, stTwinkleSpawn));
		iCount++;
	}
}

void CMineSystem::CheckIsUPTUserWhenDisconnected(CGameObject &Obj)
{ 
	std::map<int, _ST_MINESYSTEM_TWINKLE>::iterator it = this->m_mapTwinkle.begin();

	while (true)
	{
		if (it == this->m_mapTwinkle.end())
		{
			return;
		}

		if (it->second.wUserIndex == Obj.m_Index)
		{
			break;
		}

		it++;
	}

	if (it->second.iCurrentStage > 0)
	{
		sLog->outBasic("[MineSystem][CheckIsUPTUserWhenDisconnect][Request Insert Reward][%s][%s][Type:%d][Index:%d][Stage:%d]",
			Obj.AccountID, Obj.Name, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

		this->RequestDBToModifyUPTUserInfo(Obj.m_Index, Obj.Name, it->second.wTwinkleType, it->second.iCurrentStage, 0);
	}

	this->ResetTwinkleInfo(Obj.m_Index, it->second.wTwinkleIndex, 0);
}

void CMineSystem::CheckIsUPTUserWhenConnect(CGameObject &Obj)
{
	if (g_ConfigRead.server.GetServerType() == SERVER_BATTLECORE)
	{
		return;
	}

	SDHP_REQ_LOAD_MINESYSTEM_UPT_USERINFO pMsg;
	PHeadSubSetB((BYTE*)&pMsg, 0x4C, 0x01, sizeof(pMsg));
	
	std::memcpy(pMsg.szCharName, Obj.Name, MAX_ACCOUNT_LEN + 1);
	pMsg.wUserIndex = Obj.m_Index;

	wsDataCli.DataSend((char *)&pMsg, pMsg.h.size);
}

void CMineSystem::GiveRewardItemToUPTUser(CGameObject &Obj, WORD wTwinkleType, int iStage)
{
	if (!ObjectMaxRange(Obj.m_Index))
	{
		return;
	}

	sLog->outBasic("[MineSystem][GiveRewardItemToUPTUser][START][%s][%s][Type:%d][Stage:%d]",
		Obj.AccountID, Obj.Name, wTwinkleType, iStage);

	if (this->GiveRewardItem(Obj.m_Index, wTwinkleType, iStage, 0))
	{
		sLog->outBasic("[MineSystem][GiveRewardItemToUPTUser][END][%s][%s][Type:%d][Stage:%d]",
			Obj.AccountID, Obj.Name, wTwinkleType, iStage);

		this->RequestDBToModifyUPTUserInfo(Obj.m_Index, Obj.Name, 0, 0, 1);
	}

	else
	{
		sLog->outBasic("[MineSystem][GiveRewardItemToUPTUser][ERROR][%s][%s][Type:%d][Stage:%d]",
			Obj.AccountID, Obj.Name, wTwinkleType, iStage);
	}
}

void CMineSystem::MineTwinkle(PMSG_REQ_MINETWINKLE *lpMsg, CGameObject &Obj)
{
	if (Obj.Type != OBJ_USER)
	{
		return;
	}

	if (Obj.m_PlayerData->m_ReqWarehouseOpen || Obj.CloseType != -1)
	{
		return;
	}

	int iRewardJewelNumber = 0;
	int iMineResult;

	if (this->CheckValidationMineState(Obj.m_Index, lpMsg->wTwinkleIndex, lpMsg->wTwinkleType, lpMsg->byMapNumber, lpMsg->wUserIndex, &iMineResult, 0))
	{
		std::map<int, _ST_MINESYSTEM_TWINKLE>::iterator it = this->m_mapTwinkle.find(lpMsg->wTwinkleIndex);
		std::map<int, _ST_MINESYSTEM_MINE_SUCCESS_INFO>::iterator itMineSuccessInfo = this->m_mapMineSuccessInfo.find(lpMsg->wTwinkleType);

		if (Obj.pntInventory[0]->m_Durability >= itMineSuccessInfo->second.iDurabilityDecrement)
		{
			Obj.pntInventory[0]->m_Durability -= itMineSuccessInfo->second.iDurabilityDecrement;
			GSProtocol.GCItemDurSend(Obj.m_Index, 0, Obj.pntInventory[0]->m_Durability, 0);

			if (this->SuccessOrFailure(it->second.wTwinkleType, it->second.iCurrentStage))
			{
				it->second.bIsDominated = true;
				it->second.wUserIndex = lpMsg->wUserIndex;

				Obj.m_PlayerData->m_bIsMining = true;

				it->second.iCurrentStage++;

				if (it->second.iCurrentStage == 5)
				{
					iMineResult = 1;
				}

				else
				{
					iMineResult = 0;
					std::vector<_ST_MINESYSTEM_REWARD_VALUE>::iterator itDropInformation = this->m_vecRewardValue.begin();

					while (true)
					{
						if (itDropInformation == this->m_vecRewardValue.end())
						{
							break;
						}

						if (it->second.wTwinkleType == itDropInformation->wTwinkleType)
						{
							if (itDropInformation->iStage == it->second.iCurrentStage)
							{
								iRewardJewelNumber = itDropInformation->iTotalJewelNumber;
								break;
							}
						}

						itDropInformation++;
					}
				}
			}

			else
			{
				iMineResult = 2;
				int iTotalUseDurability = itMineSuccessInfo->second.iDurabilityDecrement * (it->second.iCurrentStage + 1);

				sLog->outBasic("[MineSystem][MineTwinkle][FAIL][%s][%s][Type:%d][Index:%d][Stage:%d][TotalDecrementDur:%d]",
					Obj.AccountID, Obj.Name, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage, iTotalUseDurability);

				this->ResetTwinkleInfo(Obj.m_Index, it->second.wTwinkleIndex, 1);
			}

			PMSG_ANS_MINETWINKLE pMsg;
			PHeadSubSetB((BYTE*)&pMsg, 0x4C, 0x00, sizeof(pMsg));

			pMsg.wUserIndex = it->second.wUserIndex;
			pMsg.wTwinkleIndex = it->second.wTwinkleIndex;
			pMsg.wTwinkleType = it->second.wTwinkleType;
			pMsg.byMapNumber = it->second.byMapNumber;
			pMsg.byCurrentStage = it->second.iCurrentStage;
			pMsg.iRewardJewelNumber = iRewardJewelNumber;
			pMsg.iResult = iMineResult;

			IOCP.DataSend(Obj.m_Index, (BYTE*)&pMsg, pMsg.h.size);
		}

		else
		{
			sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_LACK_OF_PICKAX_DURABILITY][%s][%s][Type:%d][Index:%d][Stage:%d]",
				Obj.AccountID, Obj.Name, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

			PMSG_ANS_MINETWINKLE pMsg;
			PHeadSubSetB((BYTE*)&pMsg, 0x4C, 0x00, sizeof(pMsg));

			pMsg.wUserIndex = it->second.wUserIndex;
			pMsg.wTwinkleIndex = it->second.wTwinkleIndex;
			pMsg.wTwinkleType = it->second.wTwinkleType;
			pMsg.byMapNumber = it->second.byMapNumber;
			pMsg.byCurrentStage = it->second.iCurrentStage;
			pMsg.iRewardJewelNumber = iRewardJewelNumber;
			pMsg.iResult = 18;

			IOCP.DataSend(Obj.m_Index, (BYTE*)&pMsg, pMsg.h.size);
		}
	}

	else
	{
		if (iMineResult != 20 && iMineResult != 7 && iMineResult != 14)
		{
			PMSG_ANS_MINETWINKLE pMsg;
			PHeadSubSetB((BYTE*)&pMsg, 0x4C, 0x00, sizeof(pMsg));

			std::map<int, _ST_MINESYSTEM_TWINKLE>::iterator itError = this->m_mapTwinkle.find(lpMsg->wTwinkleIndex);

			if (itError != this->m_mapTwinkle.end())
			{
				pMsg.wUserIndex = itError->second.wUserIndex;
				pMsg.wTwinkleIndex = itError->second.wTwinkleIndex;
				pMsg.wTwinkleType = itError->second.wTwinkleType;
				pMsg.byMapNumber = itError->second.byMapNumber; 
				pMsg.byCurrentStage = itError->second.iCurrentStage;
			}

			else
			{
				pMsg.wUserIndex = 0;
				pMsg.wTwinkleIndex = 0;
				pMsg.wTwinkleType = 0;
				pMsg.byMapNumber = 0;
				pMsg.byCurrentStage = 0;
			}

			pMsg.iRewardJewelNumber = iRewardJewelNumber;
			pMsg.iResult = iMineResult;

			IOCP.DataSend(Obj.m_Index, (BYTE*)&pMsg, pMsg.h.size);
		}
	}
}

void CMineSystem::RewardMineTwinkle(PMSG_REQ_MINETWINKLE_REWARD *lpMsg, CGameObject &Obj)
{
	int iRewardResult = 0;

	if (!this->CheckValidationMineState(Obj.m_Index, lpMsg->wTwinkleIndex, lpMsg->wTwinkleType, lpMsg->byMapNumber, lpMsg->wUserIndex, &iRewardResult, true))
	{
		if (iRewardResult == 20 || iRewardResult == 7 || iRewardResult == 14)
			return;

		PMSG_ANS_MINETWINKLE_REWARD pMsg;
		PHeadSubSetB((BYTE*)&pMsg, 0x4C, 0x01, sizeof(pMsg));

		pMsg.iResult = iRewardResult;
		IOCP.DataSend(Obj.m_Index, (BYTE*)&pMsg, pMsg.h.size);
	}

	std::map<int, _ST_MINESYSTEM_TWINKLE>::iterator it = this->m_mapTwinkle.find(lpMsg->wTwinkleIndex);

	if (lpMsg->byIsStopMine)
	{
		if (this->GiveRewardItem(Obj.m_Index, it->second.wTwinkleType, it->second.iCurrentStage, 1))
		{
			if (it->second.iCurrentStage == 5)
			{
				PMSG_SERVERCMD ServerCmd;
				PHeadSubSetB((BYTE*)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));

				ServerCmd.CmdType = 0;
				ServerCmd.X = Obj.X;
				ServerCmd.Y = Obj.Y;
				GSProtocol.MsgSendV2(getGameObject(Obj.m_Index), (BYTE*)&ServerCmd, sizeof(ServerCmd));
				IOCP.DataSend(Obj.m_Index, (BYTE*)&ServerCmd, sizeof(ServerCmd));
			}

			iRewardResult = 3;
			sLog->outBasic("[MineSystem][RewardMineTwinkle][GiveRewardItem][END][%s][%s][Type:%d][Index:%d][Stage:%d]",
				Obj.AccountID, Obj.Name, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);
		}

		else
		{
			iRewardResult = 4;
			sLog->outBasic("[MineSystem][RewardMineTwinkle][GiveRewardItem][ERROR][%s][%s][Type:%d][Index:%d][Stage:%d]",
				Obj.AccountID, Obj.Name, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);
		}
	}

	PMSG_ANS_MINETWINKLE_REWARD pMsg;
	PHeadSubSetB((BYTE*)&pMsg, 0x4C, 0x01, sizeof(pMsg));

	pMsg.wUserIndex = it->second.wUserIndex;
	pMsg.wTwinkleIndex = it->second.wTwinkleIndex;
	pMsg.wTwinkleType = it->second.wTwinkleType;
	pMsg.byMapNumber = it->second.byMapNumber;
	pMsg.byCurrentStage = it->second.iCurrentStage;
	pMsg.iResult = iRewardResult;

	IOCP.DataSend(Obj.m_Index, (BYTE*)&pMsg, pMsg.h.size);
	this->ResetTwinkleInfo(Obj.m_Index, lpMsg->wTwinkleIndex, 0);
}

void CMineSystem::FailMineTwinkle(PMSG_ANS_MINETWINKLE_END_ANIMATION *lpMsg, CGameObject &Obj, bool bError)
{
	std::map<int, _ST_MINESYSTEM_TWINKLE>::iterator it = this->m_mapTwinkle.find(lpMsg->wTwinkleIndex);

	if (it == this->m_mapTwinkle.end())
	{
		return;
	}

	if (!ObjectMaxRange(lpMsg->wTwinkleIndex))
	{
		return;
	}

	if (this->IsTwinkle(it->second.wTwinkleType) == TRUE)
	{
		return;
	}

	if (getGameObject(lpMsg->wTwinkleIndex]->Life == 0.0 && getGameObject(lpMsg->wTwinkleIndex)->MapNumber == lpMsg->byMapNumber)
	{
		gObjLifeCheck(getGameObject(lpMsg->wTwinkleIndex], getGameObject(Obj.m_Index), 0, 1, 0, 0, 0, 0, 0);
	}
}

void CMineSystem::RequestDBToModifyUPTUserInfo(CGameObject &Obj, char *szCharName, WORD wTwinkleType, int iCurrentStage, BYTE byRequestType)
{
	SDHP_REQ_MINESYSTEM_UPT_USERINFO pMsg;
	PHeadSubSetB((BYTE*)&pMsg, 0x4C, 0x00, sizeof(pMsg));

	std::memcpy(pMsg.szCharName, szCharName, MAX_ACCOUNT_LEN + 1);
	pMsg.wUserIndex = Obj.m_Index;
	pMsg.wTwinkleType = wTwinkleType;
	pMsg.iCurrentStage = iCurrentStage;
	pMsg.byRequestType = byRequestType;

	wsDataCli.DataSend((char *)&pMsg, pMsg.h.size);
}

void CMineSystem::GDAnsModifyMineSystemUPTUserInfo(SDHP_ANS_MINESYSTEM_UPT_USERINFO *lpMsg)
{
	if (!ObjectMaxRange(lpMsg->wUserIndex))
	{
		return;
	}

	if (lpMsg->Result == 0)
	{
		sLog->outBasic("[MineSystem][UPT Info][DELETE/INSERT][ERROR][ID:%s][Name:%s]",
			getGameObject(lpMsg->wUserIndex]->AccountID, getGameObject(lpMsg->wUserIndex)->Name);
	}

	else if (lpMsg->Result == 1)
	{
		if (lpMsg->byRequestType == 0)
		{
			sLog->outBasic("[MineSystem][UPT Info][INSERT][SUCCESS][%d]", lpMsg->wUserIndex);
		}

		else if (lpMsg->byRequestType == 1)
		{
			sLog->outBasic("[MineSystem][UPT Info][DELETE][SUCCESS][ID:%s][Name:%s]",
				getGameObject(lpMsg->wUserIndex]->AccountID, getGameObject(lpMsg->wUserIndex)->Name);
		}

		else
		{
			sLog->outBasic("[MineSystem][UPT Info][DELETE][ERROR][Undefined Request Type][ID:%s][Name:%s]",
				getGameObject(lpMsg->wUserIndex]->AccountID, getGameObject(lpMsg->wUserIndex)->Name);
		}
	}
}

void CMineSystem::GDAnsLoadMineSystemUPTUserInfo(SDHP_ANS_LOAD_MINESYSTEM_UPT_USERINFO *lpMsg)
{
	if (lpMsg->byResult == TRUE)
	{
		this->GiveRewardItemToUPTUser(lpMsg->wUserIndex, lpMsg->wTwinkleType, lpMsg->iCurrentStage);
	}
}

BOOL CMineSystem::CheckMoveMapWhileMining(CGameObject &Obj)
{
	std::map<int, _ST_MINESYSTEM_TWINKLE>::iterator it = this->m_mapTwinkle.begin();

	while (true)
	{
		if (it == this->m_mapTwinkle.end())
		{
			break;
		}

		if (it->second.wUserIndex == Obj.m_Index)
		{
			PMSG_ANS_MINETWINKLE_CANCEL pMsg;
			PHeadSubSetB((BYTE*)&pMsg, 0x4C, 0x02, sizeof(pMsg));
			pMsg.wUserIndex = it->second.wUserIndex;
			pMsg.wTwinkleIndex = it->second.wTwinkleIndex;
			pMsg.wTwinkleType = it->second.wTwinkleType;
			pMsg.byMapNumber = it->second.byMapNumber;
			pMsg.byCurrentStage = it->second.iCurrentStage;

			IOCP.DataSend(Obj.m_Index, (BYTE*)&pMsg, pMsg.h.size);

			this->GiveRewardItem(Obj.m_Index, it->second.wTwinkleType, it->second.iCurrentStage, 1);
			this->ResetTwinkleInfo(Obj.m_Index, it->second.wTwinkleIndex, 0);

			return TRUE;
		}
		
		it++;
	}

	return FALSE;
}

void CMineSystem::SetTwinklesInfo()
{
	this->m_mapTwinkle.clear();

	for (std::map<int, _ST_MINESYSTEM_TWINKLE_SPAWN>::iterator It = this->m_mapTwinkleSpawn.begin(); It != this->m_mapTwinkleSpawn.end(); It++)
	{
		if (g_MapServerManager.CheckMapCanMove(It->second.byMapNumber) == FALSE)
		{
			continue;
		}

		int result = gObjAddMonster(It->second.byMapNumber);

		if (result == -1)
		{
			sLog->outError( "[MineSystem][SetTwinkleInfo][ERROR] Cannot add Twinkle [Type:%d][Map:%d]", It->second.wType, It->second.byMapNumber);
			return;
		}

		getGameObject(result)->m_PosNum = It->first;
		getGameObject(result)->X = It->second.byX;
		getGameObject(result)->Y = It->second.byY;
		getGameObject(result)->MapNumber = It->second.byMapNumber;
		getGameObject(result)->TX = getGameObject(result)->X;
		getGameObject(result)->TY = getGameObject(result)->Y;
		getGameObject(result)->m_OldX = getGameObject(result)->X;
		getGameObject(result)->m_OldY = getGameObject(result)->Y;
		getGameObject(result)->Dir = It->second.byDir;
		getGameObject(result)->StartX = getGameObject(result)->X;
		getGameObject(result)->StartY = getGameObject(result)->Y;

		if (getGameObject(result)->Dir == (BYTE)-1)
		{
			getGameObject(result)->Dir = rand() % 8;
		}

		gObjSetMonster(result, It->second.wType);

		_ST_MINESYSTEM_TWINKLE stTwinkle;
		stTwinkle.wTwinkleIndex = result;
		stTwinkle.wTwinkleType = getGameObject(result)->Class;
		stTwinkle.byMapNumber = getGameObject(result)->MapNumber;
		stTwinkle.wUserIndex = 0;
		stTwinkle.bIsDominated = false;

		this->m_mapTwinkle.insert(std::pair<int, _ST_MINESYSTEM_TWINKLE>(result, stTwinkle));
		//sLog->outBasic("[MineSystem][SetTwinkleInfo][SUCCESS][Type:%d][Index:%d]", getGameObject(result)->Class, result);
	}
}

void CMineSystem::SetTwinkleInfo(CGameObject &Obj)
{
	if (!ObjectMaxRange(Obj.m_Index))
	{
		sLog->outBasic("[MineSystem][SetTwinkleInfo][ERROR][Invalid TwinkleIndex]");
	}

	std::map<int, _ST_MINESYSTEM_TWINKLE>::iterator it = this->m_mapTwinkle.find(Obj.m_Index);

	if (it == this->m_mapTwinkle.end())
	{
		return;
	}

	//sLog->outBasic("[MineSystem][SetTwinkleInfo][SUCCESS][Type:%d][Index:%d]",	Obj.Class, Obj.m_Index);

	memset(&it->second, 0, sizeof(it->second));
	it->second.wTwinkleIndex = Obj.m_Index;
	it->second.wTwinkleType = Obj.Class;
	it->second.byMapNumber = Obj.MapNumber;
}

BOOL CMineSystem::SuccessOrFailure(WORD wType, int iStage)
{
	BOOL IsSuccess = FALSE;

	if (iStage >= 0 && iStage <= 5)
	{
		std::map<int, _ST_MINESYSTEM_MINE_SUCCESS_INFO>::iterator it = this->m_mapMineSuccessInfo.find(wType);

		if (it == this->m_mapMineSuccessInfo.end())
		{
			sLog->outBasic("[MineSystem][SuccessOrFailure][ERROR][MINESYSTEM_RESULT_INVALID_TWINKLE_TYPE][Type:%d][Stage:%d]",
				wType, iStage);
		}

		else
		{
			if (it->second.wTwinkleType == wType)
			{
				if ((GetLargeRand() % this->m_iChanceStartValue) < it->second.iSuccessRate[iStage])
				{
					IsSuccess = TRUE;
				}
			}

			else
			{
				sLog->outBasic("[MineSystem][SuccessOrFailure][ERROR][MINESYSTEM_RESULT_NOT_MATCH_TWINKLE_TYPE][Type:%d][Stage:%d]",
					wType, iStage);
			}
		}
	}

	else
	{
		return FALSE;
	}

	return IsSuccess;
}

BOOL CMineSystem::IsTwinkle(WORD wClass)
{
	return wClass >= 605 && wClass <= 607;
}

BOOL CMineSystem::IsEquipPickax(CGameObject &Obj)
{
	return Obj.pntInventory[0]->m_Type == ITEMGET(0, 41);
}

BOOL CMineSystem::IsPickax(WORD wItemType)
{
	return wItemType == ITEMGET(0, 41);
}

void CMineSystem::ResetTwinkleInfo(CGameObject &Obj, WORD wTwinkleIndex, bool bFailMining)
{
	std::map<int, _ST_MINESYSTEM_TWINKLE>::iterator it = this->m_mapTwinkle.find(wTwinkleIndex);

	if (it == this->m_mapTwinkle.end())
	{
		return;
	}

	sLog->outBasic("[MineSystem][ResetTwinkleInfo][Type:%d][Index:%d][Map:%d][UserIndex:%d]",
		it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.byMapNumber, it->second.wUserIndex);

	memset(&it->second, 0, sizeof(it->second));

	getGameObject(wTwinkleIndex)->Life = 0.0;

	if (!bFailMining)
	{
		gObjLifeCheck(getGameObject(wTwinkleIndex), getGameObject(Obj.m_Index), 0, 1, 0, 0, 0, 0, 0);
	}

	Obj.m_PlayerData->m_bIsMining = false;
}

BOOL CMineSystem::CheckValidationMineState(CGameObject &Obj, WORD wTwinkleIndex, WORD wTwinkleType, BYTE byMapNumber, WORD wUserIndex, int *iResult, bool bRewardCheck)
{
	int iEmptyInvenSize = 0;

	if (!ObjectMaxRange(Obj.m_Index))
	{
		*iResult = 20;
		return FALSE;
	}

	if (!ObjectMaxRange(wUserIndex) || Obj.m_Index != wUserIndex)
	{
		sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_INVALID_USERINDEX][%s][%s][Map:%d][Type:%d]",
			Obj.AccountID, Obj.Name, byMapNumber, wTwinkleIndex);

		*iResult = 20;
		GSProtocol.GCSendDisableReconnect(Obj.m_Index);
		//IOCP.CloseClient(Obj.m_Index);
		return FALSE;
	}

	std::map<int, _ST_MINESYSTEM_TWINKLE>::iterator it = this->m_mapTwinkle.find(wTwinkleIndex);

	if (it == this->m_mapTwinkle.end())
	{
		sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_INVALID_TWINKLE_INDEX][%s][%s][Map:%d][Index:%d][Type:%d]",
			Obj.AccountID, Obj.Name, byMapNumber, wTwinkleIndex, wTwinkleType);

		*iResult = 14;
		GSProtocol.GCSendDisableReconnect(Obj.m_Index);
		//IOCP.CloseClient(Obj.m_Index);
		return FALSE;
	}

	if (bRewardCheck == false)
	{
		if (!this->IsEquipPickax(Obj.m_Index))
		{
			sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_NOT_EQUIPT_PICKAX][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
				Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

			*iResult = 7;
			GSProtocol.GCSendDisableReconnect(Obj.m_Index);
			//IOCP.CloseClient(Obj.m_Index);
			return FALSE;
		}

		if (Obj.pntInventory[10]->IsItem() == TRUE)
		{
			LPITEM_ATTRIBUTE p = &ItemAttribute[Obj.pntInventory[10]->m_Type];

			if (p->ItemKindB == 33)
			{
				sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_EQUIP_TRANSFORM_RING][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
					Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

				*iResult = 10;
				return FALSE;
			}
		}

		if (Obj.pntInventory[11]->IsItem() == TRUE)
		{
			LPITEM_ATTRIBUTE p = &ItemAttribute[Obj.pntInventory[11]->m_Type];

			if (p->ItemKindB == 33)
			{
				sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_EQUIP_TRANSFORM_RING][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
					Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

				*iResult = 10;
				return FALSE;
			}
		}
	}

	if (Obj.pTransaction == 1 || Obj.m_bPShopTransaction == true || Obj.m_bPShopWantDeal == true)
	{
		sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_REQUEST_TRADE][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
			Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

		*iResult = 12;

		if (it->second.wUserIndex == Obj.m_Index)
		{
			if (it->second.iCurrentStage > 0)
			{
				this->GiveRewardItem(Obj.m_Index, it->second.wTwinkleType, it->second.iCurrentStage, 1);
				this->ResetTwinkleInfo(Obj.m_Index, it->second.wTwinkleIndex, false);
			}
		}

		return FALSE;
	}

	if (Obj.m_bPShopOpen == true)
	{
		sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_OPEN_PSHOP][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
			Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

		*iResult = 13;

		if (it->second.wUserIndex == Obj.m_Index)
		{
			if (it->second.iCurrentStage > 0)
			{
				this->GiveRewardItem(Obj.m_Index, it->second.wTwinkleType, it->second.iCurrentStage, 1);
				this->ResetTwinkleInfo(Obj.m_Index, it->second.wTwinkleIndex, false);
			}
		}

		return FALSE;
	}

	int iTotalInvenCount = 8 * (4 * Obj.m_PlayerData->m_InventoryExpansion + 8);

	for (int x = 0; x < iTotalInvenCount; x++)
	{
		if (Obj.pInventoryMap[x] == 0xFF)
		{
			iEmptyInvenSize++;
		}
	}

	if (iEmptyInvenSize < 40)
	{
		sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_LACK_OF_INVENTORY][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
			Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

		*iResult = 11;
		return FALSE;
	}

	if (it->second.bIsDominated == true && Obj.m_Index != it->second.wUserIndex)
	{
		sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_DOMINATED_OTHER_USER][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
			Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

		*iResult = 8;
		return FALSE;
	}

	int iDominateTwinkleCount = 0;

	std::map<int, _ST_MINESYSTEM_TWINKLE>::iterator itTwinkle = this->m_mapTwinkle.begin();

	while (true)
	{
		if (itTwinkle == this->m_mapTwinkle.end())
		{
			break;
		}

		if (itTwinkle->second.bIsDominated == true && itTwinkle->second.wUserIndex == Obj.m_Index)
		{
			iDominateTwinkleCount++;
		}

		if (iDominateTwinkleCount > 1)
		{
			sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_DOMINATED_OTHER_TWINKLE][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
				Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

			*iResult = 9;

			std::map<int, _ST_MINESYSTEM_TWINKLE>::iterator itError = this->m_mapTwinkle.begin();

			while (true)
			{
				if (itError == this->m_mapTwinkle.end())
				{
					break;
				}

				if (itError->second.bIsDominated == true && itError->second.wUserIndex == Obj.m_Index)
				{
					this->GiveRewardItem(Obj.m_Index, itError->second.wTwinkleType, itError->second.iCurrentStage, 1);
					this->ResetTwinkleInfo(Obj.m_Index, itError->second.wTwinkleIndex, false);
				}

				itError++;
			}

			return FALSE;
		}

		itTwinkle++;
	}

	if (wTwinkleType != it->second.wTwinkleType)
	{
		sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_NOT_MATCH_TWINKLE_TYPE][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
			Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

		*iResult = 17;

		if (it->second.wTwinkleType && it->second.wTwinkleIndex)
		{
			if (it->second.iCurrentStage > 0)
			{
				this->GiveRewardItem(Obj.m_Index, it->second.wTwinkleType, it->second.iCurrentStage, 1);
				this->ResetTwinkleInfo(Obj.m_Index, it->second.wTwinkleIndex, false);
			}
		}

		else
		{
			PMSG_ANS_MINETWINKLE_END_ANIMATION stTempMsg;
			memset(&stTempMsg, 0x00, sizeof(stTempMsg));

			stTempMsg.byMapNumber = byMapNumber;
			stTempMsg.wTwinkleIndex = wTwinkleIndex;
			stTempMsg.wUserIndex = wUserIndex;

			this->FailMineTwinkle(&stTempMsg, Obj.m_Index, true);
		}

		return FALSE;
	}

	if (it->second.iCurrentStage < 0 || it->second.iCurrentStage > 5)
	{
		sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_INVALID_STAGE][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
			Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

		*iResult = 19;

		if (it->second.iCurrentStage > 0)
		{
			this->GiveRewardItem(Obj.m_Index, it->second.wTwinkleType, it->second.iCurrentStage, 1);
			this->ResetTwinkleInfo(Obj.m_Index, it->second.wTwinkleIndex, false);
		}

		return FALSE;
	}

	if (byMapNumber != it->second.byMapNumber || Obj.MapNumber != it->second.byMapNumber)
	{
		sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_NOT_MATCH_MAPNUMBER][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
			Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

		*iResult = 16;

		if (it->second.iCurrentStage > 0)
		{
			this->GiveRewardItem(Obj.m_Index, it->second.wTwinkleType, it->second.iCurrentStage, 1);
			this->ResetTwinkleInfo(Obj.m_Index, it->second.wTwinkleIndex, false);
		}

		return FALSE;
	}

	if (abs(Obj.X - getGameObject(wTwinkleIndex)->X) > 3 ||
		abs(Obj.Y - getGameObject(wTwinkleIndex)->Y) > 3)
	{
		sLog->outBasic("[MineSystem][CheckValidationMineState][ERROR][MINESYSTEM_RESULT_INVALID_DISTANCE][%s][%s][Map:%d][Type:%d][Index:%d][Stage:%d]",
			Obj.AccountID, Obj.Name, byMapNumber, it->second.wTwinkleType, it->second.wTwinkleIndex, it->second.iCurrentStage);

		*iResult = 21;

		if (it->second.iCurrentStage > 0)
		{
			this->GiveRewardItem(Obj.m_Index, it->second.wTwinkleType, it->second.iCurrentStage, 1);
			this->ResetTwinkleInfo(Obj.m_Index, it->second.wTwinkleIndex, false);
		}

		return FALSE;
	}

	return TRUE;
}

BOOL CMineSystem::GiveRewardItem(CGameObject &Obj, WORD wTwinkleType, int iStage, int bNotify)
{
	if (Obj.Type != OBJ_USER || Obj.Connected != PLAYER_PLAYING)
	{
		return FALSE;
	}

	std::vector<_ST_MINESYSTEM_REWARD_VALUE>::iterator itDropInformation;
	std::vector<_ST_MINESYSTEM_REWARD_VALUE>::iterator itDropInformation_end;
	bool bIsNotifyAllUser = false;
	bool bGaveReward = false;

	if (this->MiracleSuccessOrFailure(wTwinkleType, iStage) == TRUE)
	{
		itDropInformation = this->m_vecMiracleRewardValue.begin();
		itDropInformation_end = this->m_vecMiracleRewardValue.end();
		bIsNotifyAllUser = true;

		sLog->outBasic("[MineSystem][GiveRewardItem][Miracle][TwinkleType:%d][Stage:%d][%s][%s]",
			wTwinkleType, iStage, Obj.AccountID, Obj.Name);
	}

	else
	{
		itDropInformation = this->m_vecRewardValue.begin();
		itDropInformation_end = this->m_vecRewardValue.end();
	}

	while (itDropInformation != itDropInformation_end)
	{
		if (itDropInformation->wTwinkleType == wTwinkleType && itDropInformation->iStage == iStage)
		{
			sLog->outBasic("[MineSystem][GiveRewardItem][START][%s][%s][Type:%d][Stage:%d][ItemType:%d][ItemIndex:%d][Count:%d]",
				Obj.AccountID, Obj.Name, wTwinkleType, iStage, itDropInformation->wType, itDropInformation->wIndex, itDropInformation->iTotalJewelNumber);
			
			bGaveReward = true;

			std::vector<_ST_MINESYSTEM_DROP_ITEM>::iterator itDropItem = itDropInformation->vecDropItem.begin();

			while (true)
			{
				if (itDropItem == itDropInformation->vecDropItem.end())
				{
					break;
				}

				for (int i = 0; i < itDropItem->iNumber; i++)
				{
					ItemCreate(Obj.m_Index, 223, 0, 0, ITEMGET(itDropItem->iItemType, itDropItem->iItemIndex), itDropItem->iLevel, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0);
					sLog->outBasic("[MineSystem][GiveRewardItem][%s][%s][Item Type:%d][Index:%d][Level:%d]",
						Obj.AccountID, Obj.Name, itDropItem->iItemType, itDropItem->iItemIndex, itDropItem->iLevel);
				}

				itDropItem++;
			}
		}

		itDropInformation++;
	}

	if (bIsNotifyAllUser == true && bNotify == true)
	{
		std::map<int, std::string>::iterator itMapName = this->m_mapMapName.find(Obj.MapNumber);

		if (itMapName != this->m_mapMapName.end())
		{
			char szTemp[256];
			sprintf(Lang.GetText(0,588), Obj.Name, ItemAttribute[ITEMGET(itDropInformation->wType, itDropInformation->wIndex)].Name,
				itDropInformation->iTotalJewelNumber, g_ConfigRead.server.GetGameServerCode() % 20 + 1, itMapName->second.c_str());

			GS_GDReqMapSvrMsgMultiCast(g_MapServerManager.GetMapSvrGroup(), szTemp);
		}
	}

	return bGaveReward;
}

BOOL CMineSystem::MiracleSuccessOrFailure(WORD wType, int iStage)
{
	if (iStage < 0 || iStage > 5)
	{
		return FALSE;
	}
	
	BOOL IsSuccess = FALSE;

	std::vector<_ST_MINESYSTEM_MINE_MIRACLE_SUCCESS_INFO>::iterator it = this->m_vecMiracleSuccessInfo.begin();

	while (true)
	{
		if (it == this->m_vecMiracleSuccessInfo.end())
		{
			break;
		}

		if (it->wTwinkleType == wType && it->iStage == iStage)
		{
			if ((GetLargeRand() % this->m_iChanceStartValue) < it->iSuccessRate)
			{
				IsSuccess = TRUE;
			}

			break;
		}

		it++;
	}

	return IsSuccess;
}

void CMineSystem::ChangeUnconditionalSuccess(int iIsSuccess)
{
	if (iIsSuccess == TRUE)
		this->m_iChanceStartValue = 1;
	else
		this->m_iChanceStartValue = this->m_iChanceStartValue_Copy;

}

short CMineSystem::GetRepairValueOfJewel(WORD sItemType, WORD sLevel)
{
	std::vector<_ST_MINESYSTEM_REPAIR_VALUE>::iterator it = this->m_vecRepairValue.begin();

	while (true)
	{
		if (it == this->m_vecRepairValue.end())
		{
			break;
		}

		if (sItemType == ITEMGET(it->sItemType, it->sItemIndex) && sLevel == it->sLevel)
		{
			return it->sRepairValue;
		}

		it++;
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////////
//  vnDev.Games - MuServer S12EP2 IGC v12.0.1.0 - Trong.LIVE - DAO VAN TRONG  //
////////////////////////////////////////////////////////////////////////////////

