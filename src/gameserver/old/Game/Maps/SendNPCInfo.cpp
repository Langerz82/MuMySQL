////////////////////////////////////////////////////////////////////////////////
// SendNPCInfo.cpp
#include "StdAfx.h"
#include "SendNPCInfo.h"
#include "Main.h"
#include "Logging/Log.h"
#include "configread.h"

CSendNPCInfo g_SendNPCInfo;

CSendNPCInfo::CSendNPCInfo(void)
{
	this->m_bLoadScript = false;
}

CSendNPCInfo::~CSendNPCInfo(void)
{
}

void CSendNPCInfo::LoadScript(char *lpFileName)
{
	this->m_bLoadScript = false;

	if (!lpFileName)
	{
		sLog->outBasic("[SendNPCInfo] lpFileName is null!!");
		return;
	}

	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(lpFileName);

	if (res.status != pugi::status_ok)
	{
		sLog->outBasic("%s load fail (%s)", lpFileName, res.description());
		return;
	}

	_stSendNPCInfo sendNpcInfo;
	_stSendPortalInfo sendPortalInfo;

	pugi::xml_node mainXMLsection = file.child("MiniMapObjects");
	pugi::xml_node npc = mainsection.child("TypeOne");
	pugi::xml_node portal = mainsection.child("TypeTwo");

	for (pugi::xml_node tag = npc.child("Tag"); tag; tag = tag.next_sibling())
	{
		sendNpcInfo.nIdentNo = tag.attribute("Id").as_int();
		sendNpcInfo.btMapNumber = tag.attribute("MapNumber").as_int();
		sendNpcInfo.nNpcClass = tag.attribute("NPCIndex").as_int();
		sendNpcInfo.btPosX = tag.attribute("X").as_int();
		sendNpcInfo.btPosY = tag.attribute("Y").as_int();
		sendNpcInfo.btTag = tag.attribute("DisplayType").as_int();
		sendNpcInfo.btSync = tag.attribute("SyncType").as_int();
		std::memcpy(sendNpcInfo.szName, tag.attribute("Name").as_string(), 31);

		this->m_vtSendNpcInfo.push_back(sendNpcInfo);
	}

	for (pugi::xml_node tag = portal.child("Tag"); tag; tag = tag.next_sibling())
	{
		sendPortalInfo.nIdentNo = tag.attribute("Id").as_int();
		sendPortalInfo.btMapNumber = tag.attribute("MapNumber").as_int();
		sendPortalInfo.btPosX = tag.attribute("X").as_int();
		sendPortalInfo.btPosY = tag.attribute("Y").as_int();
		std::memcpy(sendPortalInfo.szName, tag.attribute("Name").as_string(), 31);

		this->m_vtSendPortalInfo.push_back(sendPortalInfo);
	}

	this->m_bLoadScript = true;
}

void CSendNPCInfo::SendNpcCoordinate(CGameObject* lpObj, BYTE btMapIndex, BYTE btAddType)
{
	int nSize = this->m_vtSendNpcInfo.size();

	if (ObjectMaxRange(nDestUserIndex) == false)
	{
		sLog->outBasic("error : %s %d", __FILE__, __LINE__);
		return;
	}

	PMSG_ANS_NPC_POSITION pMsg;
	_stSendNPCInfo sendNpcInfo;

	PHeadSubSetB((BYTE*)&pMsg, 0xE7, 0x03, sizeof(pMsg));

	for (int i = 0; i < nSize; i++)
	{
		std::memcpy(&sendNpcInfo, &this->m_vtSendNpcInfo.at(i), sizeof(_stSendNPCInfo));

		if (sendNpcInfo.btSync == 0)
		{
			continue;
		}	
		
		if (sendNpcInfo.btMapNumber != btMapIndex || sendNpcInfo.btSync != 1)
		{
			if (sendNpcInfo.btMapNumber == btMapIndex && sendNpcInfo.btSync == 2)
			{
				for (int n = 0; n < g_ConfigRead.server.GetObjectMaxMonster(); n++)
				{
					if (getGameObject(n)->Type != OBJ_USER && 
						getGameObject(n)->MapNumber == sendNpcInfo.btMapNumber &&
						getGameObject(n)->Class == sendNpcInfo.nNpcClass)
					{
						pMsg.btPosX = getGameObject(n)->X;
						pMsg.btPosY = getGameObject(n)->Y;
						pMsg.btTag = sendNpcInfo.btTag;
						pMsg.btType = btAddType;
						pMsg.btIdentNo = sendNpcInfo.nIdentNo;
						pMsg.btIsNpc = TRUE;
						std::memcpy(pMsg.szName, sendNpcInfo.szName, 31);
						IOCP.DataSend(nDestUserIndex, (BYTE*)&pMsg, pMsg.h.size);
						break;
					}
				}
			}
		}

		else
		{
			pMsg.btPosX = sendNpcInfo.btPosX;
			pMsg.btPosY = sendNpcInfo.btPosY;
			pMsg.btTag = sendNpcInfo.btTag;
			pMsg.btIdentNo = sendNpcInfo.nIdentNo;
			pMsg.btType = btAddType;
			pMsg.btIsNpc = TRUE;
			std::memcpy(pMsg.szName, sendNpcInfo.szName, 31);
			IOCP.DataSend(nDestUserIndex, (BYTE*)&pMsg, pMsg.h.size);
		}
	}
}

void CSendNPCInfo::SendPortalCoordinateMoveNpc(BYTE btBeforeMapNumber, BYTE btAfterMapNumber, BYTE btBeforeX, BYTE btBeforeY, BYTE btX, BYTE btY, int nNpcClass)
{
	int nSize = this->m_vtSendNpcInfo.size();

	PMSG_ANS_NPC_POSITION pInsertMsg;
	PMSG_ANS_NPC_POSITION pDeleteMsg;

	PHeadSubSetB((BYTE*)&pInsertMsg, 0xE7, 0x03, sizeof(pInsertMsg));
	PHeadSubSetB((BYTE*)&pDeleteMsg, 0xE7, 0x03, sizeof(pDeleteMsg));

	_stSendNPCInfo sendNpcInfo;

	for (int i = 0; i < nSize; i++)
	{
		std::memcpy(&sendNpcInfo, &this->m_vtSendNpcInfo.at(i), sizeof(_stSendNPCInfo));

		if (sendNpcInfo.btMapNumber == btBeforeMapNumber && sendNpcInfo.btSync == 2 && sendNpcInfo.nNpcClass == nNpcClass)
		{
			pDeleteMsg.btPosX = btBeforeX;
			pDeleteMsg.btPosY = btBeforeY;
			pDeleteMsg.btTag = sendNpcInfo.btTag;
			pDeleteMsg.btIdentNo = sendNpcInfo.nIdentNo;
			pDeleteMsg.btType = 1;
			pDeleteMsg.btIsNpc = TRUE;
			std::memcpy(pDeleteMsg.szName, sendNpcInfo.szName, 31);
		}

		if (sendNpcInfo.btMapNumber == btAfterMapNumber && sendNpcInfo.btSync == 2 && sendNpcInfo.nNpcClass == nNpcClass)
		{
			pInsertMsg.btPosX = btX;
			pInsertMsg.btPosY = btY;
			pInsertMsg.btTag = sendNpcInfo.btTag;
			pInsertMsg.btType = 0;
			pInsertMsg.btIdentNo = sendNpcInfo.nIdentNo;
			pInsertMsg.btIsNpc = TRUE;
			std::memcpy(pInsertMsg.szName, sendNpcInfo.szName, 31);
		}
	}

	for (int n = g_ConfigRead.server.GetObjectStartUserIndex(); n < g_ConfigRead.server.GetObjectMax(); n++)
	{
		if (getGameObject(n)->Connected == PLAYER_PLAYING)
		{
			if (getGameObject(n)->MapNumber == btBeforeMapNumber)
			{
				IOCP.DataSend(n, (BYTE*)&pDeleteMsg, pDeleteMsg.h.size);
			}

			else if (getGameObject(n)->MapNumber == btAfterMapNumber)
			{
				IOCP.DataSend(n, (BYTE*)&pInsertMsg, pInsertMsg.h.size);
			}
		}
	}
}

void CSendNPCInfo::SendPortalCoordinate(CGameObject* lpObj, BYTE btMapNumber)
{
	int nSize = this->m_vtSendPortalInfo.size();

	if (ObjectMaxRange(nDestUserIndex) == false)
	{
		sLog->outBasic("error : %s %d", __FILE__, __LINE__);
		return;
	}

	PMSG_ANS_NPC_POSITION pMsg;
	_stSendPortalInfo sendPortalInfo;

	PHeadSubSetB((BYTE*)&pMsg, 0xE7, 0x03, sizeof(pMsg));

	for (int i = 0; i < nSize; i++)
	{
		std::memcpy(&sendPortalInfo, &this->m_vtSendPortalInfo.at(i), sizeof(sendPortalInfo));

		if (sendPortalInfo.btMapNumber == btMapNumber)
		{
			pMsg.btPosX = sendPortalInfo.btPosX;
			pMsg.btPosY = sendPortalInfo.btPosY;
			pMsg.btTag = 1;
			pMsg.btType = 0;
			pMsg.btIdentNo = sendPortalInfo.nIdentNo;
			pMsg.btIsNpc = FALSE;
			std::memcpy(pMsg.szName, sendPortalInfo.szName, 31);
			IOCP.DataSend(nDestUserIndex, &pMsg.h.c, pMsg.h.size);
		}
	}
}

void CSendNPCInfo::Find_ITL_Npc(BYTE byMapNumber, WORD wNpcType, BYTE & byMapTagIndex)
{
	int nSize = this->m_vtSendNpcInfo.size();
	_stSendNPCInfo sendNpcInfo;

	for (int i = 0; i < nSize; i++)
	{
		std::memcpy(&sendNpcInfo, &this->m_vtSendNpcInfo.at(i), sizeof(_stSendNPCInfo));

		if (byMapNumber == sendNpcInfo.btMapNumber && wNpcType == sendNpcInfo.nNpcClass)
		{
			byMapTagIndex = sendNpcInfo.nIdentNo;
			return;
		}
	}
}

void CSendNPCInfo::SendITLNpcCoordinate(CGameObject* lpObj, BYTE btMapIndex)
{
	int nSize = this->m_vtSendNpcInfo.size();

	if (ObjectMaxRange(nDestUserIndex) == false)
	{
		sLog->outBasic("error : %s %d", __FILE__, __LINE__);
		return;
	}

	PMSG_ANS_ITL_NPC_POSITION pMsg;
	_stSendNPCInfo sendNpcInfo;

	PHeadSubSetB((BYTE*)&pMsg, 0xE7, 0x04, sizeof(pMsg));

	for (int i = 0; i < nSize; i++)
	{
		std::memcpy(&sendNpcInfo, &this->m_vtSendNpcInfo.at(i), sizeof(_stSendNPCInfo));

		if (sendNpcInfo.btMapNumber == btMapIndex)
		{
			pMsg.btPosX = sendNpcInfo.btPosX;
			pMsg.btPosY = sendNpcInfo.btPosY;
			pMsg.btTag = sendNpcInfo.btTag;
			pMsg.btIdentNo = sendNpcInfo.nIdentNo;
			pMsg.btType = 0;
			pMsg.btIsNpc = TRUE;
			IOCP.DataSend(nDestUserIndex, &pMsg.h.c, pMsg.h.size);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//  vnDev.Games - MuServer S12EP2 IGC v12.0.1.0 - Trong.LIVE - DAO VAN TRONG  //
////////////////////////////////////////////////////////////////////////////////

