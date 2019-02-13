#ifndef __MU_USER_H__
#define __MU_USER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

#include "ViewPortGuild.h"
#include "ItemSystemFor380.h"
#include "SkillDelay.h"
#include "EvolutionMonsterInfo.h"
#include "QuestExpUserInfo.h"

class CAttackQueue;
class CUserData;
struct MessageStateMachine;
struct ExMessageStateMachine;
struct _GUILD_INFO_STRUCT;



extern int MaxViewportMonster;

class CNameConvert
{
public:
	void InitData();
	void InputData(int cnt, const char *name, const char *realNameOfUBF, WORD serverCode, int Length);
	char * ConvertNameToRealName(const char *name);
	char * ConvertRealNameToName(const char *realName);
	WORD FindServerCodeAtRealName(const char *realName);
	WORD FindServerCodeAtCharacterName(const char *Name);
	char * ConvertSlotIndexToName(int slotindex);
	int IsDuplicationOfName();

private:
	CharacterNameOfUBF m_perCharacterInfo[5];
};

extern ExMessageStateMachine ** gSMAttackProcMsg;
extern MessageStateMachine ** gSMMsg;


class CUserData
{
public:
	CUserData(int IDNumber);
	virtual ~CUserData();

	void Init(bool VipReset = true);

public:
	int IDNumber;
	char Ip_addr[16];	// 18
	char HWID[100];
	UINT64 Experience;	// AC
	UINT64 NextExp; // B0
	UINT64 MasterExperience;
	UINT64 MasterNextExp;
	short MasterLevel;
	int LevelUpPoint; // A4
	int	MasterPoint;
	int	MasterPointUsed;
	int   iFruitPoint;	// A8
	int   Money; // B4
	WORD Strength; // B8
	WORD Dexterity;	// BA
	WORD Vitality;	// BC
	WORD Energy;	// BE
	BYTE  DbClass;	// 9E
	BYTE  ChangeUP; // 9F
	_GUILD_INFO_STRUCT *lpGuild;	// 2D4
	char GuildName[11]; // 2D8
	int GuildStatus;	// 2E4
	int iGuildUnionTimeStamp;	// 2E8
	int GuildNumber;	// 2D0
	DWORD LastMoveTime;
	int m_iResets;
	BYTE VipType;
	char VipEffect;
	BYTE SantaCount;
	DWORD m_GoblinTime;
	bool m_bSecurityCheck;
	int m_iSecurityCode;
	BYTE RegisterdLMS;
	BYTE RegisteredLMSRoom;
	JEWELOFHARMONY_ITEM_EFFECT m_JewelOfHarmonyEffect;	// 1914
	ITEMOPTION_FOR380ITEM_EFFECT m_ItemOptionExFor380;	// 193A
	BOOL	m_bKanturuEntranceByNPC;
	bool m_iGensInfoLoad;
	bool m_iQuestInfoLoad;
	int m_WCoinP;
	int m_WCoinC;
	int m_GoblinPoint;
	int m_iPeriodItemEffectIndex;	// 195C
	SOCKET_OPTION_LIST m_SeedOptionList[35]; // Size=210 Offset=9392
	SOCKET_OPTION_LIST m_BonusOptionList[7]; // Size=42 Offset=9602
	SOCKET_OPTION_LIST m_SetOptionList[2]; // Size=12 Offset=9644
	unsigned short m_btRefillHPSocketOption; // Size=2 Offset=9656
	unsigned short m_btRefillMPSocketOption; // Size=2 Offset=9658
	unsigned short m_wSocketOptionMonsterDieGetHp; // Size=2 Offset=9660
	unsigned short m_wSocketOptionMonsterDieGetMana; // Size=2 Offset=9662
	unsigned char m_btAGReduceRate; // Size=1 Offset=9664
	//=========
	BYTE m_InventoryExpansion;
	BYTE m_WarehouseExpansion;
	DWORD LastAuthTime;
	BYTE LastXorKey1[4];
	BYTE LastXorKey2[4];
	bool ISBOT;
	WORD wBotIndex;
	BYTE SkillHellFire2State;	// FA4
	BYTE SkillHellFire2Count;	// FA5
	DWORD SkillHellFire2Time;	// FA8
	BYTE SkillStrengthenHellFire2State;	// FA4
	BYTE SkillStrengthenHellFire2Count;	// FA5
	DWORD SkillStrengthenHellFire2Time;	// FA8
	unsigned char m_ReqWarehouseOpen;	// FAC
	short SetOpAddSkillAttack;	// FB4
	short SetOpAddExDamage;	// FB6
	short SetOpAddExDamageSuccessRate;	// FB8
	short SetOpAddCriticalDamage;	// FBA
	short SetOpAddCriticalDamageSuccessRate;	// FBC
	short SetOpIncAGValue;	// FBE
	short SetOpAddDamage;	// FC0
	short SetOpAddMinAttackDamage;	// FC2
	short SetOpAddMaxAttackDamage;	// FC4
	short SetOpAddAttackDamage;	// FC6
	short SetOpAddDefence;	// FC8
	short SetOpAddDefenceRate;	// FCA
	short SetOpAddMagicPower;	// FCC
	short SetOpAddMinMagicDamage;
	short SetOpAddMaxMagicDamage;
	BYTE SetOpIgnoreDefense;	// FCE
	BYTE SetOpDoubleDamage;	// FCF
	BYTE SetOpTwoHandSwordImproveDamage;	// FD0
	BYTE SetOpImproveSuccessAttackRate;	// FD1
	BYTE SetOpReflectionDamage;	// FD2
	BYTE SetOpImproveSheldDefence;	// FD3
	BYTE SetOpDecreaseAG;	// FD4
	BYTE SetOpImproveItemDropRate;	// FD5
	bool IsFullSetItem;	// FD6
	DWORD PotionTime;
	int PacketsPerSecond;
	DWORD PacketTime;
	DWORD LivePacketTime;
	BYTE bt_BotType;
	BYTE LiveCheckDetectCount;
	char  Password[20];	// 7E
	bool  PlusStatQuestClear; // 8C
	bool  ComboSkillquestClear;	// 8D
	ComboSkillData comboSkill; // 90
	int m_GensRanking;
	int m_GensClass;
	int m_ContributePoint;
	int m_NextContributePoint;
	int m_GensInfluence;
	int m_UserBattleZoneEnable;
	char KillUserName[11 * MAX_ACCOUNT_LEN];
	int m_KillUserCnt[10];
	int m_KillUserTotCnt;
	ULONGLONG m_GensAbusingTick;
	bool GensReward;
	char SwearWarning;
	BYTE m_Quest[100];	// EE0
	bool m_SendQuestInfo;	// F12
	DWORD AgilityCheckDelay;
	BYTE AgilityCheckCount;
	CRITICAL_SECTION AgiCheckCriti;
	BYTE RFSkillCount;
	WORD DarkSideCount;
	WORD DarkSideTarget[5];
	CRITICAL_SECTION m_DarkSideRFCriti;
	CRITICAL_SECTION m_MasterSkillCriti;
	BYTE m_btSculptPos;
	BYTE m_btCharmPos;
	BYTE m_btArtifactPos;
	BYTE m_btExpUpCharmPos;
	int IGC_KillCount;
	WORD MoveGate;
	BOOL PentagramInfoLoad;
	bool BlessSkillCast;
	DWORD m_dwMSBFlagAttackDisable;
	int m_iMiningLevel;
	int m_iMiningObjectId;
	int m_iMiningJewelId;
	_MASTERLEVEL_PASSIVE_SKILL_OPTION m_MPSkillOpt;
	UserQuestInfo m_UserQuestInfo[MAX_QUESTEXP_USER_INFO];
	int m_bUserQuestInfoSent;
	bool m_bUsePolymorphSkin;
	ULONGLONG LastSkillUseTick;
	DWORD LastSkillUseNumber;
	DWORD LastSkillUseCount;
	PENTAGRAM_OPTION m_PentagramOptions;
	class CItem * pPentagramMixBox;
	unsigned char * pPentagramMixBoxMap;
	int PentagramMixMoney;
	int PentagramMixSuccessRate;
	int m_PentagramMixLock;
	bool m_bIsPentagramMixCompleted;
	PENTAGRAMJEWEL_INFO m_PentagramJewelInfo_Inven[254];
	PENTAGRAMJEWEL_INFO m_PentagramJewelInfo_Warehouse[254];
	DWORD MathAuthenElapsed;
	DWORD AntiHackCheckTime;
	int m_AttackRatePvM;
	double m_AttackRatePvP;
	double m_DefenseRatePvP;
	bool bActiveSetParty;
	char PartyPassword[10];
	bool m_bUseGuildMatching;
	bool m_bUsePartyMatching;
	bool m_bPartyMatchingLeader;
	int m_nServerChannel;
	int m_nPartyMatchingIndex;
	int m_nPartyMatchingMemberCount;
	CMuRummyInfo *m_pCMuRummyInfo;
	bool m_bSendMemberPos;
	bool m_bSendNpcPos;
	int  m_Resistance_Stun;
	int  m_Resistance_Double;
	int  m_Resistance_Perfect;
	int  m_Resistance_SD;
	int  m_Resistance_Excellent;
	int  m_Resistance_Critical;
	bool m_bIsMining;
	bool m_EnableUseChangeSkin;
	DWORD m_dwMapMoveKeyValue;
	EXC_WING_OPTION m_WingExcOption;
	STAT_USER_OPTION m_StatSpecOption[12];
	bool m_IsOffLevelling;
	STR_USER_SHOP_REBUY_ITEM m_CancelItemSaleList[MAX_CANCEL_ITEMS_SALE];
	bool m_bIsCancelItemSale;
	int m_JoinUnityBattle;
	int m_nServerCodeOfHomeWorld;
	char m_RealNameOfUBF[11];
	CNameConvert m_NameConvertOfUBF;
	bool m_bGremoryCaseDBInfo;
	GREMORYCASE_ITEM_DATA m_GremoryCaseData[MAX_GREMORYCASE_STORAGE_TYPES][MAX_GREMORYCASE_STORAGE_ITEMS];
	CSkillDelay SkillDelay;
	DWORD m_dwGensHitTeleportDelay; // Private custom for joinmu
	DWORD dwOpenWareCnt;
	DWORD dwCloseWareCnt;
	bool bHasSameSerialItem;
	DWORD dwHitHackCounter1;
	DWORD dwLastHitHackValue1[7];
	DWORD dwHitHackCounter2;
	DWORD dwLastHitHackValue2[7];
	DWORD64 dwLastHitHackTick;
	int Ruud;
	BYTE EventEntryCount[6];
	CEvolutionMonsterInfo * m_pCEvoMonInfo;
	//Antihack related (move speed)
	short MovingDistance;
	BYTE  MovingIgnore;
	int RageDMG;
	CAttackQueue* m_AttackQueue;
};


#endif
