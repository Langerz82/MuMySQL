// KanturuUtil.h: interface for the CKanturuUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KANTURUUTIL_H__F4F5A116_190C_42DA_9D05_982E6BCD73D5__INCLUDED_)
#define AFX_KANTURUUTIL_H__F4F5A116_190C_42DA_9D05_982E6BCD73D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKanturuUtil  
{

public:

	CKanturuUtil();
	virtual ~CKanturuUtil();

	void NotifyKanturuChangeState(int iState, int iDetailState);
	void NotifyKanturuEntranceReqResult(CGameObject &Obj, int iResult);
	void NotifyKanturuSuccessValue(int iSuccessValue);
	void NotifyKanturuCurrentState(CGameObject &Obj, int iState, int iDetailState);
	void NotifyKanturuBattleTime(int iBattleTime);
	void NotifyKanturuWideAreaAttack(CGameObject &Obj, int iTargetIndex, int iSkillType);
	void NotifyKanturuUserMonsterCount(int iMonsterCount, int iUserCount);
	void __cdecl SendMsgKanturuBattleUser(LPSTR lpszMsg, ...);
	void SendDataKanturuBattleUser(LPBYTE lpMsg, int iSize);
	void __cdecl SendMsgKauturuBossMapUser(LPSTR lpszMsg, ...);
	void SendDataKanturuBossMapUser(BYTE* lpMsg, int iSize);
	void __cdecl SendMsgKauturuMapUser(char* lpszMsg, ...);
	void SendDataKanturuMapUser(BYTE* lpMsg, int iSize);
	void __cdecl SendMsgAllUser(LPSTR lpszMsg, ...);
	void SendDataAllUser(BYTE* lpMsg, int iSize);
	void __cdecl SendMsgToUser(CGameObject &Obj, char* lpszMsg, ...);
	void SendDataToUser(CGameObject &Obj, BYTE* lpMsg, int iSize);
	void __cdecl SendKanturuChattingMsg(CGameObject &Obj, char* lpszMsg, ...);
	void SendDataKanturuTimeAttackEvent(CGameObject &Obj, BYTE btFlag, int iClearTime);

};

#endif // !defined(AFX_KANTURUUTIL_H__F4F5A116_190C_42DA_9D05_982E6BCD73D5__INCLUDED_)


////////////////////////////////////////////////////////////////////////////////
//  vnDev.Games - MuServer S12EP2 IGC v12.0.1.0 - Trong.LIVE - DAO VAN TRONG  //
////////////////////////////////////////////////////////////////////////////////

