////////////////////////////////////////////////////////////////////////////////
// CustomMichi.h
#pragma once

#include "configread.h"

#define FILE_CUSTOM_HACKPOTION "Custom\\AutoPotionHack.ini"

struct AutoPotion
{
	short m_CheckHealingAutoPotionHack;
	short m_CheckAutoHealingPotionHackTolerance;
	
	short m_LifePotionMultiplyCount;
	short m_LifePotionMultiplyRate;

	int Potion0;
	int Potion1;
	int Potion2;
	int Potion3;
};

class CConfigMichi
{
public:

	CConfigMichi();
	virtual ~CConfigMichi();

	void LoadPotionHack();
	void UseHealingPotion(CItemObject* ObjItem, int pos, CGameObject &Obj);
	void GCFireworksSend(CGameObject *lpObj, int x, int y);
	bool IsEventItem(int ItemIndex);
	bool Ex_IsBadFileLine(char *FileLine, int *Flag);
	int GetNumberByPercent(int Proc, int Min, int Max);
	int ExcOpt(int amount);
	BYTE IsNewOptionRand(int level);
	/*------------------------------*/
	AutoPotion FixHackPotions;

}; extern CConfigMichi g_Michi;


////////////////////////////////////////////////////////////////////////////////
//  vnDev.Games - MuServer S12EP2 IGC v12.0.1.0 - Trong.LIVE - DAO VAN TRONG  //
////////////////////////////////////////////////////////////////////////////////

