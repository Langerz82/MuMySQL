// KanturuBattleUserMng.cpp: implementation of the CKanturuBattleUserMng class.
//	GS-N	1.00.18	JPN	0x00580A30	-	Completed
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "KanturuBattleUserMng.h"
#include "KanturuUtil.h"
#include "Main.h"
#include "Logging/Log.h"
#include "configread.h"

CKanturuBattleUserMng g_KanturuBattleUserMng;
static CKanturuUtil KANTURU_UTIL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKanturuBattleUserMng::CKanturuBattleUserMng()
{
	this->ResetAllData();
}

CKanturuBattleUserMng::~CKanturuBattleUserMng()
{
	return;
}


void CKanturuBattleUserMng::ResetAllData()
{
	this->m_iBattleUserCount = 0;
	this->SetMaxUser(MAX_KANTURU_BATTLE_USER);

	for ( int iCount=0;iCount<MAX_KANTURU_BATTLE_USER;iCount++)
	{
		this->m_BattleUser[iCount].ResetData();
	}
}


BOOL CKanturuBattleUserMng::AddUserData(CGameObject &Obj)
{
	if ( !gObjIsConnected(Obj.m_Index))
	{
		return FALSE;
	}

	if ( this->IsOverMaxUser() )
	{
		return FALSE;
	}

	for ( int iCount=0;iCount<MAX_KANTURU_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == FALSE )
		{
			this->m_BattleUser[iCount].SetIndex(Obj.m_Index);
			this->m_iBattleUserCount++;
			
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CKanturuBattleUserMng::DeleteUserData(CGameObject &Obj)
{
	if ( iIndex < 0 || iIndex > g_ConfigRead.server.GetObjectMax()-1)
	{
		return FALSE;
	}

	for ( int iCount=0;iCount<MAX_KANTURU_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == TRUE )
		{
			if ( this->m_BattleUser[iCount].GetIndex() == iIndex )
			{
				this->m_BattleUser[iCount].ResetData();
				this->m_iBattleUserCount--;
				
				if (g_ConfigRead.server.GetServerType() != SERVER_CASTLE)
				{
					Obj.m_PlayerData->m_bKanturuEntranceByNPC = FALSE;
				}
				return TRUE;
			}
		}
	}

	return FALSE;
}


void CKanturuBattleUserMng::CheckUserState()
{
	int iIndex;

	for ( int iCount=0;iCount<MAX_KANTURU_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == TRUE )
		{
			iIndex = this->m_BattleUser[iCount].GetIndex();

			if ( !gObjIsConnected(Obj.m_Index))
			{
				this->DeleteUserData(Obj.m_Index);

			}

			if ( Obj.MapNumber != MAP_INDEX_KANTURU_BOSS &&
				 Obj.m_State == 2 &&
				 Obj.Live == 1 )
			{
				this->DeleteUserData(Obj.m_Index);

			}
		}
	}
}


BOOL CKanturuBattleUserMng::MoveAllUser(int iGateNumber)
{
	int iIndex;
	BOOL bMoveGateSuccess = FALSE;

	for ( int iCount=0;iCount<MAX_KANTURU_BATTLE_USER;iCount++)
	{
		iIndex = this->m_BattleUser[iCount].GetIndex();

		if ( this->m_BattleUser[iCount].IsUseData()  )
		{
			bMoveGateSuccess = gObjMoveGate(iIndex, iGateNumber);

			if ( bMoveGateSuccess == TRUE )
			{
			}
			else
			{
				this->DeleteUserData(Obj.m_Index);

				gObjMoveGate(iIndex, 137);
			}
		}
	}

	return TRUE;
}


void CKanturuBattleUserMng::SetMaxUser(int iMaxUser)
{
	this->m_iBattleMaxUser = iMaxUser;

	if ( iMaxUser > MAX_KANTURU_BATTLE_USER )
	{
		this->m_iBattleMaxUser = MAX_KANTURU_BATTLE_USER;

	}
}


int CKanturuBattleUserMng::GetMaxUser()
{
	return this->m_iBattleMaxUser;
}

int CKanturuBattleUserMng::GetUserCount()
{
	return this->m_iBattleUserCount;
}

BOOL CKanturuBattleUserMng::IsEmpty()
{
	if ( this->m_iBattleUserCount <= 0 )
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CKanturuBattleUserMng::IsOverMaxUser()
{
	if ( this->m_iBattleUserCount >=  MAX_KANTURU_BATTLE_USER )
	{
		return TRUE;
	}

	return FALSE;
}


void CKanturuBattleUserMng::LogBattleWinnerUserInfo(BYTE btFlag, int iElapsedTime)
{
	int iIndex = -1;
	float fTime = iElapsedTime / 1000.0f;

	for ( int iCount=0;iCount<MAX_KANTURU_BATTLE_USER;iCount++)
	{
		if ( this->m_BattleUser[iCount].IsUseData() == TRUE )
		{
			iIndex = this->m_BattleUser[iCount].GetIndex();
			
			KANTURU_UTIL.SendDataKanturuTimeAttackEvent(iIndex, btFlag, fTime);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//  vnDev.Games - MuServer S12EP2 IGC v12.0.1.0 - Trong.LIVE - DAO VAN TRONG  //
////////////////////////////////////////////////////////////////////////////////

