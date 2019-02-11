#ifndef _GENERALSTRUCTS_H
#define _GENERALSTRUCTS_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "MuDefines.h"
#include "ServerEngine.h"

#include <string>
#include <map>

struct STR_ITEM_LEVEL_RATE;
struct STR_LUCKY_ITEM_EQUIPMENT;
struct STR_SMELT_RATE;
struct STR_LUCKY_ITEM_INFO;
struct STR_USER_SHOP_REBUY_ITEM;
struct STR_ITEMPERIOD_DATEINFO;
struct STR_GUILD_MEMBER;
struct STR_GUILD_INFO_STRUCT;
struct STR_UNION_MEMBER_DATA;
struct PARTYMATCHING_PARTYUSERDATA;
struct STR_sellItemPrice;
struct STR_PARTY_MEMBER_WAIT_LIST;
struct STR_PSHOP_ITEMVALUE_INFO_DS;
struct STR_STAT_BONUS;
struct STR_PARTYMATCHING_PARTYUSERDATA;


typedef struct STR_STRINGCOMPARE
{
	bool operator()(const std::string s1, const std::string s2) const
	{
		return strcmp(s1.data(), s2.data()) < 0;
	}
} strCmp;

typedef std::map<std::string, STR_GUILD_MEMBER*, strCmp> MAP_GUILD_MEMBER;
typedef std::map<std::string, STR_GUILD_INFO_STRUCT*, strCmp> MAP_GUILD_INFO;
typedef std::map<int, STR_UNION_MEMBER_DATA*> MAP_MEMBER_DATA;



struct STR_ITEM_LEVEL_RATE
{
	int iLevel;
	int	iRate;

	STR_ITEM_LEVEL_RATE::STR_ITEM_LEVEL_RATE()
	{
		this->iLevel		= 0;
		this->iRate			= 0;
	}
};

struct STR_LUCKY_ITEM_EQUIPMENT
{
	int	iItemNum;
	int	iSkill;
	int	iLuckOption;
	int	iAddOption;
	int	iClass;

	STR_LUCKY_ITEM_EQUIPMENT::STR_LUCKY_ITEM_EQUIPMENT()
	{
		this->iItemNum		= -1;
		this->iSkill		= 0;
		this->iLuckOption	= 0;
		this->iAddOption	= 0;
		this->iClass		= -1;
	}
};

struct STR_SMELT_RATE
{
	int	iMinDurab;
	int	iMaxDurab;
	int	iSmeltRate;

	STR_SMELT_RATE::STR_SMELT_RATE()
	{
		this->iMinDurab		= 0;
		this->iMaxDurab		= 0;
		this->iSmeltRate	= 0;
	}
};

struct STR_LUCKY_ITEM_INFO
{
	int						iItemNum;
	int						iItemKind;
	int						iAddOpt3Rate[7];
	int						iAddSetOptRate[2];
	STR_ITEM_LEVEL_RATE		ItemLevelRate[MAX_LUCKYINFO_LEVELRATE];
	STR_LUCKY_ITEM_EQUIPMENT	LuckyItemEquipment[MAX_LUCKYINFO_ITEMEQUIPMENT];
	STR_SMELT_RATE				SmeltRate[MAX_LUCKYINFO_SMELTRATE];

	STR_LUCKY_ITEM_INFO::STR_LUCKY_ITEM_INFO()
	{
		this->iItemNum	= -1;
		this->iItemKind	= -1;
		memset(this->iAddOpt3Rate, 0, sizeof(iAddOpt3Rate));
	}
};

struct STR_USER_SHOP_REBUY_ITEM
{
	STR_USER_SHOP_REBUY_ITEM()
	{
		this->Clear();
	}

	void Clear()
	{
		this->btUsed = FALSE;
		this->wItemCode = 0xFFFF;
		this->iLeftTime = 0;
		memset(this->btItemInfo, 0x00, MAX_ITEM_INFO);
		this->wItemCount = 0;
		this->dwItemPrice = 0;
		this->btItemNumber = 0;
	}

	BYTE btUsed;
	WORD wItemCode;
	int iLeftTime;
	BYTE btItemInfo[MAX_ITEM_INFO];
	WORD wItemCount;
	DWORD dwItemPrice;
	BYTE btItemNumber;
};

struct stArcaBattleMarkTopRankDS {
	BYTE btRank;
	char szGuildNames[MAX_GUILD_LEN + 1];
	DWORD dwMarkCnt;
};

struct stCancelGuildNames {
	char szGuildNames[9];
};

struct stCCFRankingInfo {
	stCCFRankingInfo() {
		memset(this->szCharName, 0x00, sizeof(this->szCharName));
		this->byRank = 0;
		this->nPoint = 0;
	}
	char szCharName[MAX_ACCOUNT_LEN + 1];
	BYTE byRank;
	int nPoint;
};

struct stGuildMatchingAllowList {
	char szName[MAX_ACCOUNT_LEN + 1];
	BYTE btClass;
	int nLevel;
};

struct stGuildMatchingAllowListDB {
	int nGuildNumber;
	char szApplicantName[MAX_ACCOUNT_LEN + 1];
	BYTE btApplicantClass;
	int nApplicantLevel;
	BYTE btState;
};

struct stGuildMatchingList {
	char szMemo[41];
	char szRegistrant[MAX_ACCOUNT_LEN + 1];
	char szGuildName[MAX_GUILD_LEN + 1];
	BYTE btGuildMemberCnt;
	BYTE btGuildMasterClass;
	BYTE btInterestType;
	BYTE btLevelRange;
	BYTE btClassType;
	int nGuildMasterLevel;
	int nBoardNumber;
	int nGuildNumber;
	BYTE btGensType;
};

struct stGuildUnderMember {
	BYTE btGuildMemberCnt;
	char szGuildNames[9];
};

struct ITL_REWARDLIST {
	BYTE byRank;
	BYTE byEnteredCnt;
	BYTE byPoint;
	bool bGotReward;
	char szCharName[MAX_ACCOUNT_LEN + 1];
	char szGuildName[MAX_GUILD_LEN + 1];
};

struct MuRummyCardInfoDS {
	MuRummyCardInfoDS() {
		this->btColor = -1;
		this->btNumber = -1;
		this->btSlotNum = -1;
		this->btSeq = -1;
		this->btStatus = -1;
	}
	BYTE btColor;
	BYTE btNumber;
	BYTE btSlotNum;
	BYTE btSeq;
	BYTE btStatus;
};

struct MuRummyCardUpdateDS {
	MuRummyCardUpdateDS() {
		this->btSlotNum = -1;
		this->btSeq = -1;
		this->btStatus = -1;
	}
	BYTE btSlotNum;
	BYTE btSeq;
	BYTE btStatus;
};

struct MuunRideViewPortInfo {
	BYTE NumberH;
	BYTE NumberL;
	BYTE MuunRideItemH;
	BYTE MuunRideItemL;
};

struct STR_QUESTEXP_INFO {
	STR_QUESTEXP_INFO::STR_QUESTEXP_INFO() {
		this->dwQuestIndexID = 0;
		this->wProgState = 0;
		this->lStartDate = 0;
		this->lEndDate = 0;
		memset(this->btAskIndex, 0, 5);
		memset(this->btAskValue, 0, 5);
		memset(this->btAskState, 0, 5);
	}
	DWORD dwQuestIndexID;
	WORD wProgState;
	BYTE btAskIndex[5];
	BYTE btAskValue[5];
	BYTE btAskState[5];
	time_t lStartDate;
	time_t lEndDate;
};

struct SEND_PARTYMEMBER_INFO {
	SEND_PARTYMEMBER_INFO() {
		this->bUse = FALSE;
	}
	int bUse;
	int bFlag;
	char Name[MAX_ACCOUNT_LEN + 1];
	int nUserIndex;
	int nServerChannel;
};

struct stABAllGuildMark {
	char szGuildName[MAX_GUILD_LEN + 1];
	DWORD dwMarkCnt;
};

struct stABJoinUserInfoDS {
	char szGuildName[MAX_GUILD_LEN + 1];
	DWORD dwGuild;
	char szUserName[MAX_ACCOUNT_LEN + 1];
};

struct stABWinGuildInfoDS {
	char szGuildName[9];
	DWORD dwGuild;
	WORD wOccupyObelisk;
	WORD wObeliskGroup;
};

struct STR_GENS_RANKING_DATA
{
	int GensClass;
	int ContributePoint;
	int RankingPosition;
	BYTE RewardItemGroup;
	WORD RewardItemNumber;
	int RewardItemCount;
};

struct _ITL_GUILD_RANK {
	char szGuildName[MAX_GUILD_LEN + 1];
	BYTE byRank;
	BYTE byITLType;
	BYTE byWin;
	BYTE byLose;
};

struct STR_GUILD_MEMBER {
	char m_szMemberName[11];
	BYTE m_btStatus;
	BYTE m_btConnected;
	int m_iUserIndex;
	STR_GUILD_MEMBER() {
		ZeroMemory(m_szMemberName, sizeof(m_szMemberName));
		m_btStatus = 0;
		m_btConnected = -1;
		m_iUserIndex = -1;
	}
};


struct PARTY_INFO_LIST {
	char szLeaderName[MAX_ACCOUNT_LEN + 1];
	char szTitle[41];
	WORD nMinLevel;
	WORD nMaxLevel;
	WORD nHuntingGround;
	int nLeaderLevel;
	BYTE btLeaderClass;
	BYTE btWantedClass;
	BYTE btCurPartyMemberCnt;
	BYTE btUsePassword;
	BYTE btWantedClassDetailInfo[7];
	int nServerChannel;
	BYTE btGensType;
};

struct PARTY_INFO_LISTDB {
	char szLeaderName[MAX_ACCOUNT_LEN + 1];
	char szTitle[41];
	char szPassword[5];
	WORD nMinLevel;
	WORD nMaxLevel;
	WORD nHuntingGround;
	int nLeaderLevel;
	BYTE btLeaderClass;
	BYTE btWantedClass;
	BYTE btCurPartyMemberCnt;
	BYTE btUsePassword;
	BYTE btWantedClassDetailInfo[7];
	BYTE btGensType;
	BYTE btApprovalType;
};

struct STR_PARTY_MEMBER_WAIT_LIST
{
	char szName[MAX_ACCOUNT_LEN + 1];
	BYTE btClass;
	int nLevel;
};

struct NAME {
	char m_szName[11];
	NAME() {
		std::ZeroMemory(this, sizeof(*this));
	}
	NAME(char * szName) {
		std::ZeroMemory(this, sizeof(*this));
		std::strncpy(m_szName, szName, 10);
	}
};

struct P_ADD_NEWS {
	BYTE day;
	BYTE month;
	WORD year;
	DWORD dateColor;
	DWORD titleColor;
	DWORD textColor;
	char title[40];
	WORD textLen;
	char Text[2048];
};

struct PARTYMATCHING_PARTYDATA {
	PARTYMATCHING_PARTYDATA() {
		this->m_PartyMatchingIndex = -1;
		this->m_UserCount = 0;
	}
	int m_PartyMatchingIndex;
	int m_UserCount;
	char szLeaderName[MAX_ACCOUNT_LEN + 1];
	//STR_PARTYMATCHING_PARTYUSERDATA m_UserData[5];
	STR_PARTYMATCHING_PARTYUSERDATA* m_UserData;
};

struct STR_PARTYMATCHING_PARTYUSERDATA {
	STR_PARTYMATCHING_PARTYUSERDATA() {
		this->iUsedInfo = FALSE;
		this->iUserConnected = FALSE;
		this->iUserIndex = -1;
		this->iServerNumber = -1;
		this->iServerIndex = -1;
	}
	int iUsedInfo;
	int iUserConnected;
	int iUserIndex;
	int iServerNumber;
	int iServerIndex;
	char szUserName[MAX_ACCOUNT_LEN + 1];
};

struct PERIOD_EXPIRED_ITEM {
	WORD wItemCode;
	UINT64 Serial;
};

struct PERIOD_EXPIRED_ITEMLIST {
	BYTE btItemCount;
	PERIOD_EXPIRED_ITEM ExpiredItem[90];
};

struct PERIOD_ITEMLIST {
	DWORD dwUserGuid;
	BYTE btItemCount;
	char chCharacterName[MAX_ACCOUNT_LEN + 1];
	//STR_ITEMPERIOD_DATEINFO ItemData[100];
	STR_ITEMPERIOD_DATEINFO* ItemData;
};

struct STR_sellItem {
	DWORD dwItemGuid;
	DWORD dwItemCODE;
	DWORD dwCategoryID;
	DWORD dwUseType;
	DWORD dwBuyType;
	DWORD dwCoolTime;
	double dbVarEndDate;
	DWORD dwLimitSellCount;
	DWORD dwState;
	char szItemName[64];
	char szItemDesc[128];
	DWORD dwPriceCount;
	//STR_sellItemPrice itemPrice[8];
	STR_sellItemPrice* itemPrice;
};

struct STR_sellItemPrice {
	DWORD dwPriceGuid;
	DWORD dwItemGuid;
	DWORD dwUseTime;
	DWORD dwAmount;
	DWORD dwPrice;
	DWORD dwSellRate;
};

struct sellPackage {
	DWORD dwPackageGuid;
	STR_sellItemPrice itemPrice;
	DWORD dwImageCode;
	DWORD dwCategory;
	DWORD dwBuyType;
	DWORD dwLimitSellCount;
	DWORD dwInItemCount;
	double dbVarEndDate;
	DWORD dwState;
	STR_sellItemPrice inItemPrices[16];
	char szPackageName[64];
	char szPackageDesc[128];
};

struct ServerInfo {
	WORD UserCount;
	WORD MaxUserCount;
	WORD Percent;
	DWORD TickCount;
};

struct ServerList {
	ServerList() {
		this->btServerCode = 0;
		this->wServerPort = 0;
		memset(this->cIp, 0, 16);
	}
	BYTE btServerCode;
	WORD wServerPort;
	char cIp[16];
};

struct STAT_BONUS {
	WORD BonusOptionID;
	WORD BonusOptionVal1;
	WORD BonusOptionVal2;
};

struct stMemberPosInfo {
	char szName[MAX_ACCOUNT_LEN + 1];
	BYTE btMapNumber;
	BYTE btPosX;
	BYTE btPosY;
};

struct STR_GUILD_INFO_STRUCT {
	int m_iNumber;
	char m_szGuildName[9];
	char m_szGuildMaster[11];
	BYTE m_btGuildType;
	MAP_GUILD_MEMBER m_mapGuildMember;
	int m_iRivalGuild;
	int m_iUnionGuild;
	BYTE m_Mark[32];
	int m_Score;
	char m_Notice[128];
	BOOL m_bGSHasData;
	STR_GUILD_INFO_STRUCT() {
		m_iNumber = -1;
		memset(m_szGuildName, 0, sizeof(m_szGuildName));
		memset(m_szGuildMaster, 0, sizeof(m_szGuildMaster));
		m_btGuildType = -1;
		memset(m_Mark, 0, sizeof(m_Mark));
		memset(m_Notice, 0, sizeof(m_Notice));
		m_iRivalGuild = 0;
		m_iUnionGuild = 0;
		m_Score = 0;
		m_mapGuildMember.clear();
		m_bGSHasData = FALSE;
	}
};

struct JOIN_SERVER_SERVER_DATA {
	int m_ServerIndex;
	char m_szServerName[50];
	WORD m_wServerCode;
	WORD m_wPort;
	WORD m_wCurrentUser;
	WORD m_wMaxUser;
	BYTE m_VipServer;
	WORD m_MaxHWIDUseCount;
};

struct JOIN_SERVER_CUserData {
	char m_AccoundID[11];
	char m_HWID[100];
	WORD m_ServerCode;
	WORD m_ServerGroup;
	bool m_bRequestMapSvrMove;
	int iUserNumber;
	DWORD dwPlayTime;
	char m_Ip[17];
	int iPayCode;
	int iUsedTime;
	char szEndDays[9];
	DWORD dwCheckTime;
	int iIndex;
	bool m_bOffTrade;
	char IpAddr[17];
};

typedef struct STR_UNION_MEMBER_DATA {
	std::vector<int> m_vecUnionMember;
} STR_UNION_MEMBER_DATA, *LP_STR_UNION_MEMBER_DATA;

struct USERWAREHOUSE_DATA {
	char szAccountID[MAX_ACCOUNT_LEN + 1];
	int WarehouseID;
	DWORD LastChangeTick;
	int ChangeIDEnableState;
	bool WarehouseOpenState;
};

struct STR_ITEMPERIOD_DATEINFO
{
	BYTE btUsedInfo;
	BYTE btItemType;
	WORD wItemCode;
	BYTE btEffectCategory;
	BYTE btEffectType1;
	BYTE btEffectType2;
	UINT64 Serial;
	time_t lItemBuyDate;
	time_t lItemExpireDate;
};

struct STR_STAT_BONUS
{
	WORD BonusOptionID;
	WORD BonusOptionVal1;
	WORD BonusOptionVal2;
};

struct STR_SERVER_ENGINE
{
	int m_Index;
	SOCKET m_Socket;
	eSERVER_STATE m_State;
	eSERVER_TYPE m_Type;
	char m_ServerIp[16];
	struct _PER_SOCKET_CONTEXT * PerSocketContext;
	WsProtocolCore m_ProtocolCore;
	WORD m_ServerCode;
	WORD m_ServerGroup;
	unsigned short m_ConnectPort;
};

struct IPList
{
	char m_IP[16];
};

struct STR_CS_USER
{
	STR_CS_USER() {}
	int Index;
	int ConnectionState;
	char IP[20];
	unsigned int Port;
	unsigned char Type;
	SOCKET socket;
	_PER_SOCKET_CONTEXT * PerSocketContext;
	bool News;
	int PacketCount;
	ULONGLONG i64PacketTime;
};

struct _PER_IO_CONTEXT
{
	MU_WSAOVERLAPPED Overlapped; // 0
	MU_WSABUF wsabuf;
	unsigned char Buffer[MAX_IO_BUFFER_SIZE]; // 1C
	unsigned char BufferSecond[MAX_IO_BUFFER_SIZE]; // 178C
	int nSecondOfs; // 2EFC
	int nTotalBytes;	// 2F00
	int nSentBytes; // 2F04
	int IOOperation; // 2F08
	int nWaitIO; // 2F0C

};

typedef struct tagIocpServerParameter
{
	DWORD dwServerCount;
	eSERVER_TYPE eServerType;

} IocpServerParameter;

struct _PER_SOCKET_CONTEXT
{
	SOCKET m_socket;	// 0
	int nIndex;	// 4
	_PER_IO_CONTEXT IOContext[2];	// 8
	int dwIOCount;	// 5E28
};

struct PacketQueue
{
	PacketQueue()
	{
		this->nSize = 0;
		this->headcode = 0;
		this->uindex = -1;
		this->iSessionId = -1;
	}

	boost::shared_ptr<unsigned char[]> pData;
	unsigned short nSize;
	unsigned char headcode;
	int uindex;
	int iSessionId;
};


// USER STRUCTS

typedef union tagPATHTABLE
{
	short sPathTable[16];
	char cPathTable[32];
} PATHTABLE, *LPPATHTABLE;

typedef struct tagActionState
{
	unsigned long Rest : 1;	// 0
	unsigned long Attack : 1;	// 1
	unsigned long Move : 1;	// 2
	unsigned long Escape : 1;	// 3
	unsigned long Emotion : 4;	// 4
	unsigned long EmotionCount : 8;	// 8

} ACTION_STATE, *LPACTION_STATE;

typedef struct tagInterfaceState
{
	DWORD use : 2;
	DWORD state : 4;
	DWORD type : 10;

} INTERFACE_STATE, *LPINTERFACE_STATE;

extern short RoadPathTable[MAX_ROAD_PATH_TABLE];
extern BOOL g_EnergyCheckOff;

struct HITDAMAGE_STRUCT
{
	short number;	// 0
	int HitDamage;	// 4
	ULONGLONG LastHitTime;	// 8
};

struct VIEWPORT_STRUCT
{
	char state;	// 0
	short number;	// 2
	unsigned char type;	// 4
	short index;	// 6
	int dis;	// 8
};

struct VIEWPORT_PLAYER_STRUCT
{
	char state;	// 0
	short number;	// 2
	unsigned char type;	// 4
	short index;	// 6
	int dis;	// 8

};

struct MessageStateMachine
{
	int MsgCode;	// 0
	int SendUser;	// 4
	ULONGLONG MsgTime;	// 8
	int SubCode;	// C

	MessageStateMachine()
	{
		this->MsgCode = -1;
	}

};

struct ExMessageStateMachine
{
	int MsgCode;	// 0
	int SendUser;	// 4
	ULONGLONG MsgTime;	// 8
	int SubCode;	// C
	int SubCode2;	// 10

	ExMessageStateMachine()
	{
		this->MsgCode = -1;
	}
};

struct WHISPER_STRUCT
{
	bool iWhisperSent;
	WORD wResponseCount;
};
struct SKILL_INFO
{
	void Clear()
	{
		this->GhostPhantomX = 0;
		this->GhostPhantomY = 0;
		this->RemedyOfLoveEffect = 0;
		this->RemedyOfLoveTime = 0;
		this->LordSummonTime = 0;
		this->LordSummonMapNumber = 0;
		this->LordSummonX = 0;
		this->LordSummonY = 0;
		this->SoulBarrierDefence = 0;
		this->SoulBarrierManaRate = 0;
		this->PoisonType = 0;
		this->IceType = 0;
		this->fInfinityArrowIncRate = 0.0;
		this->fCircleShieldRate = 0.0;
	}

	BYTE	GhostPhantomX;
	BYTE	GhostPhantomY;
	short	RemedyOfLoveEffect;
	short	RemedyOfLoveTime;
	WORD	LordSummonTime;
	BYTE	LordSummonMapNumber;
	BYTE	LordSummonX;
	BYTE	LordSummonY;
	int		SoulBarrierDefence;
	int		SoulBarrierManaRate;
	BYTE	PoisonType;
	BYTE	IceType;
	float	fInfinityArrowIncRate;
	float	fCircleShieldRate;
};

struct _MASTERLEVEL_PASSIVE_SKILL_OPTION
{
	_MASTERLEVEL_PASSIVE_SKILL_OPTION()
	{
		this->Clear();
	}

	void Clear()
	{
		iMpsAttackSuccessRate = 0.0;
		iMpsIncDefenseSuccessRate = 0.0;
		iMpsIncreasePvPAttackRate = 0.0;
		iMpsIncreasePvPDefenseRate = 0.0;
		iMpsDurabilityReduction1 = 0.0;
		btMpsDownDur1Level = 0.0;
		iMpsDurabilityReduction2 = 0.0;
		iMpsDurabilityReduction3 = 0.0;
		iMpsResistancePoison = 0.0;
		iMpsResistanceThunder = 0.0;
		iMpsResistanceIce = 0.0;
		iMpsAutoRecoverLife = 0.0;
		iMpsAutoRecoverMana = 0.0;
		iMpsAutoRecoverAG = 0.0;
		iMpsAddPhysicDamage = 0.0;
		iMpsAddDamage = 0.0;
		iMpsTwoHandSwordAddDamage = 0.0;
		iMpsSwordAddDamage = 0.0;
		iMpsMaceStrength = 0.0;
		iMpsSpearAddDamage = 0.0;
		iMpsTwoHandsPvPAttack = 0.0;
		iMpsAddAttackSpeed = 0.0;
		iMpsIgnoreEnemyDefence = 0.0;
		iMpsAddDoubleDamage = 0.0;
		iMpsAddSturn = 0.0;
		iMpsMaxManaRate = 0.0;
		iMpsAddMagicDamage = 0.0;
		iMpsTwoHandsMagicPower = 0.0;
		iMpsStaffMagicPower = 0.0;
		iMpsIncShield = 0.0;
		iMpsStaffAttackSpeed = 0.0;
		iMpsTwoHandsStaffManAttack = 0.0;
		iMpsShieldBlockRate = 0.0;
		iMpsBowAddDamage = 0.0;
		iMpsBowAddAttackSpeed = 0.0;
		iMpsTwoHandsBowAddDamage = 0.0;
		iMpsTwoHandsBowManAttack = 0.0;
		iMpsElfAddShield = 0.0;
		iMpsElfShieldBlockRate = 0.0;
		iMpsElfAddPhysicDamage = 0.0;
		iMpsCallMonHp = 0.0;
		iMpsCallMonDefense = 0.0;
		iMpsCallMonAttack = 0.0;
		iMpsIncMagicPower = 0.0;
		iMpsIncDamageFireProper = 0.0;
		iMpsIncDamageWindProper = 0.0;
		iMpsIncDamageThunderProper = 0.0;
		iMpsIncDotDamage = 0.0;
		iMpsAddSturn2 = 0.0;
		iMpsAddSpring = 0.0;
		iMpsAddMagicPowerStick = 0.0;
		iMpsAddCurseMagicBook = 0.0;
		iMpsAddManAttackStick = 0.0;
		iMpsAddAttackSpeedMagicBook = 0.0;
		iMpsIncPercentBerserker1 = 0.0;
		iMpsIncPercentBerserker2 = 0.0;
		iMpsIncValueBerserker3 = 0.0;
		iMpsIncMinMagicDamage = 0.0;
		iMpsIncDarkHorseDefense = 0.0;
		iMpsAddForceWaveDamage = 0.0;
		iMpsAddDarkSpiritDamage = 0.0;
		iMpsAddCriticalDamageRate = 0.0;
		iMpsAddExcellentDamageRate = 0.0;
		iMpsAddCeptorDamage = 0.0;
		iMpsIncCeptorManAttack = 0.0;
		iMpsAddShieldDefense = 0.0;
		iMpsAddShieldBlockingRage = 0.0;
		iMpsAddPetAttack = 0.0;
		iMpsAddControlAttack = 0.0;
		iMpsAddMinAttack = 0.0;
		iMpsAddMaxAttack = 0.0;
		iMpsCriticalRateInc = 0.0;
		iMpsAddBlockingRate = 0.0;
		iMpsMonkWeaponDamage = 0.0;
		iMpsMonkDoubleDamage = 0.0;
		iMpsMonkAddVitalToDefense = 0.0;
		iMpsPlusZen = 0.0;
		iMpsDefence = 0.0;
		iMpsMaxHP = 0.0;
		iMpsMaxBP = 0.0;
		iMpsMaxMana = 0.0;
		iMpsMonsterDieGetMana = 0.0;
		iMpsMonsterDieGetLife = 0.0;
		iMpsMonsterDieGetSD = 0.0;
		iMpsPlusExp = 0.0;
		iMpsMaxSD = 0.0;
		iMpsSDSpeed = 0.0;
		iMpsMaxAttackDamage = 0.0;
		iMpsMinAttackDamage = 0.0;
		iMpsDecreaseMana = 0.0;
		iMpsMaxMagicDamage = 0.0;
		iMpsMinMagicDamage = 0.0;
		iMpsPetDurDownSpeed = 0.0;
		iMpsMaxAttackMagicDamage = 0.0;
		iMpsMinAttackMagicDamage = 0.0;
		iMpsImmuneRate = 0.0;
		iMpsIncSetItemDefense = 0.0;
		iMpsReturnEnemyAttack = 0.0;
		iMpsIncEnergyStat = 0.0;
		iMpsIncVitalStat = 0.0;
		iMpsIncDexStat = 0.0;
		iMpsIncPowerStat = 0.0;
		iMpsAddWingDamageBlock = 0.0;
		iMpsAddWingDefense = 0.0;
		iMpsAddWingDamage = 0.0;
		iMpsIncLeadershipStat = 0.0;
		iMpsIncCriticalDamageRate = 0.0;
		iMpsRecoverManaRate = 0.0;
		iMpsRecoverHPRate = 0.0;
		iMpsIncExcellentDamageRate = 0.0;
		iMpsIncDoubleDamageRate = 0.0;
		iMpsIncIgnoreEnemyBlock = 0.0;
		iMpsRecoverSDRate = 0.0;
		iMpsIncTripleDamageRate = 0.0;
		iMpsComboDamage = 0.0;
		iMpsIncMaxBP = 0.0;
		iMpsMasManaRate_Wizard = 0.0;
		iMpsIncMaxMagicDamage = 0.0;
		iMpsIncExcellentDamageRate_Darklord = 0.0;
		iMpsIncDamageBloodHowling = 0.0;
		iMpsIncDarkSpiritAttackSpeed = 0.0;
		iMpsIncDarkSpiritDoubleDamageRate = 0.0;
		iMpsDarkSpiritIgnoreEnemyDefense = 0.0;
		iMpsIncSteelArmor = 0.0;
		iMpsShieldBlock = 0.0;
		iMpsRageDamage = 0.0;
	}

	float	iMpsAttackSuccessRate; // done
	float	iMpsIncDefenseSuccessRate; // done
	float	iMpsIncreasePvPAttackRate; // done
	float	iMpsIncreasePvPDefenseRate; // done
	float	iMpsDurabilityReduction1; // done
	BYTE	btMpsDownDur1Level; // done
	float	iMpsDurabilityReduction2; // done
	float	iMpsDurabilityReduction3; // done
	float	iMpsResistancePoison; // done
	float	iMpsResistanceThunder; // done
	float	iMpsResistanceIce; // done
	float	iMpsAutoRecoverLife; // done
	float	iMpsAutoRecoverMana; // done
	float	iMpsAutoRecoverAG; // done
	float	iMpsAddPhysicDamage; // done
	float	iMpsAddDamage; // not used?
	float	iMpsTwoHandSwordAddDamage; // done
	float	iMpsSwordAddDamage; // done
	float	iMpsMaceStrength; // done
	float	iMpsSpearAddDamage; // done
	float	iMpsTwoHandsPvPAttack; // done
	float	iMpsAddAttackSpeed; // done
	float	iMpsIgnoreEnemyDefence; // done, but no reference in CMasterLevelSkillTreeSystem class
	float	iMpsAddDoubleDamage; // done
	float	iMpsAddSturn; // done
	float	iMpsMaxManaRate; // done
	float	iMpsAddMagicDamage; // done
	float	iMpsTwoHandsMagicPower; // done
	float	iMpsStaffMagicPower; // done
	float	iMpsIncShield; // done
	float	iMpsStaffAttackSpeed; // done
	float	iMpsTwoHandsStaffManAttack;  // done
	float	iMpsShieldBlockRate; // done
	float	iMpsBowAddDamage; // done
	float	iMpsBowAddAttackSpeed; // done
	float	iMpsTwoHandsBowAddDamage; // done
	float	iMpsTwoHandsBowManAttack; // done
	float	iMpsElfAddShield; // done
	float	iMpsElfShieldBlockRate; // done
	float	iMpsElfAddPhysicDamage; // done
	float	iMpsCallMonHp; // done
	float	iMpsCallMonDefense; // done
	float	iMpsCallMonAttack; // done
	float	iMpsIncMagicPower; // done
	float	iMpsIncDamageFireProper; // done
	float	iMpsIncDamageWindProper; // done
	float	iMpsIncDamageThunderProper; // done
	float	iMpsIncDotDamage; // done
	float	iMpsAddSturn2; // done
	float	iMpsAddSpring; // done
	float	iMpsAddMagicPowerStick; // done
	float	iMpsAddCurseMagicBook; // done
	float	iMpsAddManAttackStick; // done
	float	iMpsAddAttackSpeedMagicBook; // done
	float	iMpsIncPercentBerserker1; // done
	float	iMpsIncPercentBerserker2; // done
	float	iMpsIncValueBerserker3; // done
	float	iMpsIncMinMagicDamage; // done
	float	iMpsIncDarkHorseDefense; // done
	float	iMpsAddForceWaveDamage; // not used
	float	iMpsAddDarkSpiritDamage; // done
	float	iMpsAddCriticalDamageRate; // done
	float	iMpsAddExcellentDamageRate; // done
	float	iMpsAddCeptorDamage; // done
	float	iMpsIncCeptorManAttack; // done
	float	iMpsAddShieldDefense; // done
	float	iMpsAddShieldBlockingRage; // done
	float	iMpsAddPetAttack; // done
	float	iMpsAddControlAttack; // done
	float	iMpsAddMinAttack; // done
	float	iMpsAddMaxAttack; // done
	float	iMpsCriticalRateInc; // done
	float	iMpsAddBlockingRate; // done
	float	iMpsMonkWeaponDamage; // done
	float	iMpsMonkDoubleDamage; // done
	float	iMpsMonkAddVitalToDefense; // done
	float	iMpsPlusZen; // done, but no reference in CMasterLevelSkillTreeSystem class
	float	iMpsDefence; // done
	float	iMpsMaxHP; // done
	float	iMpsMaxBP; // done
	float	iMpsMaxMana; // done
	float	iMpsMonsterDieGetMana; // done
	float	iMpsMonsterDieGetLife; // done
	float	iMpsMonsterDieGetSD; // done
	float	iMpsPlusExp; // not used
	float	iMpsMaxSD; // done
	float	iMpsSDSpeed; // done
	float	iMpsMaxAttackDamage; // done
	float	iMpsMinAttackDamage; // done
	float	iMpsDecreaseMana; // done
	float	iMpsMaxMagicDamage; // done
	float	iMpsMinMagicDamage; // done
	float	iMpsPetDurDownSpeed; // done
	float	iMpsMaxAttackMagicDamage; // done, but no reference in CMasterLevelSkillTreeSystem class
	float	iMpsMinAttackMagicDamage; // done, but no reference in CMasterLevelSkillTreeSystem class
	float	iMpsImmuneRate; // done
	float	iMpsIncSetItemDefense; // done
	float	iMpsReturnEnemyAttack; // done
	float	iMpsIncEnergyStat; // done
	float	iMpsIncVitalStat; // done
	float	iMpsIncDexStat; // done
	float	iMpsIncPowerStat; // done
	float	iMpsAddWingDamageBlock; // done
	float	iMpsAddWingDefense; // done
	float	iMpsAddWingDamage; // done
	float	iMpsIncLeadershipStat; // done
	float	iMpsIncCriticalDamageRate; // done
	float	iMpsRecoverManaRate; // done
	float	iMpsRecoverHPRate; // done
	float	iMpsIncExcellentDamageRate; // done
	float	iMpsIncDoubleDamageRate; // done
	float	iMpsIncIgnoreEnemyBlock; // done
	float	iMpsRecoverSDRate; // done
	float	iMpsIncTripleDamageRate; // done
	float	iMpsComboDamage; // done
	float	iMpsIncMaxBP; // done
	float	iMpsMasManaRate_Wizard; // done
	float	iMpsIncMaxMagicDamage; // done
	float	iMpsIncExcellentDamageRate_Darklord; // done
	float	iMpsIncDamageBloodHowling; // done
	float	iMpsIncDarkSpiritAttackSpeed; // done
	float	iMpsIncDarkSpiritDoubleDamageRate; // done
	float	iMpsDarkSpiritIgnoreEnemyDefense; // done
	float	iMpsIncSteelArmor; // done
	float	iMpsShieldBlock; // done
	float	iMpsRageDamage; // done
};

struct EFFECTLIST
{
	BYTE BuffIndex;
	BYTE EffectCategory;
	BYTE EffectType1;
	BYTE EffectType2;
	int EffectValue1;
	int EffectValue2;
	ULONGLONG EffectSetTime;
	int EffectDuration;
};

#pragma pack (1)
struct PENTAGRAMJEWEL_INFO
{
	BYTE btJewelPos;
	BYTE btJewelIndex;
	BYTE btMainAttribute;
	BYTE btItemType;
	WORD wItemIndex;
	BYTE btLevel;
	BYTE btRank1OptionNum;
	BYTE btRank1Level;
	BYTE btRank2OptionNum;
	BYTE btRank2Level;
	BYTE btRank3OptionNum;
	BYTE btRank3Level;
	BYTE btRank4OptionNum;
	BYTE btRank4Level;
	BYTE btRank5OptionNum;
	BYTE btRank5Level;

	void Clear()
	{
		this->btJewelPos = -1;
		this->btJewelIndex = -1;
		this->btMainAttribute = -1;
		this->btItemType = -1;
		this->wItemIndex = -1;
		this->btLevel = 0;
		this->btRank1OptionNum = -1;
		this->btRank1Level = -1;
		this->btRank2OptionNum = -1;
		this->btRank2Level = -1;
		this->btRank3OptionNum = -1;
		this->btRank3Level = -1;
		this->btRank4OptionNum = -1;
		this->btRank4Level = -1;
		this->btRank5OptionNum = -1;
		this->btRank5Level = -1;
	}
};
#pragma pack ()

struct PENTAGRAM_OPTION
{
	int m_iRuby_1RankAddDamage;
	int m_iRuby_2RankOptionNum;
	int m_iRuby_2RankAddAttackRelationshipRate;
	int m_iRuby_3RankOptionNum;
	int m_iRuby_3RankAddDamage;
	int m_iRuby_4RankOptionNum;
	int m_iRuby_4RankAddDamage;
	int m_iRuby_5RankOptionNum;
	int m_iRuby_5RankCriticalDamageRate;
	int m_iSapph_1RankAddDefense;
	int m_iSapph_2RankOptionNum;
	int m_iSapph_2RankAddDefenseRelationshipRate;
	int m_iSapph_3RankOptionNum;
	int m_iSapph_3RankAddDefense;
	int m_iSapph_4RankOptionNum;
	int m_iSapph_4RankAddDefense;
	int m_iSapph_5RankOptionNum;
	int m_iSapph_5RankMinusTargetDamageRate;
	int m_iEme_1RankAddAttackRate;
	int m_iEme_2RankOptionNum;
	int m_iEme_2RankAddAttackRelationshipRate;
	int m_iEme_3RankOptionNum;
	int m_iEme_3RankAddDamage;
	int m_iEme_4RankOptionNum;
	int m_iEme_4RankAddDamage;
	int m_iEme_5RankOptionNum;
	int m_iEme_5RankAddDamageRate;
	int m_iTopa_1RankOptionNum;
	int m_iTopa_1RankAddDefenseSuccessRate;
	int m_iTopa_2RankOptionNum;
	int m_iTopa_2RankAddDefenseRelationshipRate;
	int m_iTopa_3RankOptionNum;
	int m_iTopa_3RankAddDefense;
	int m_iTopa_4RankOptionNum;
	int m_iTopa_4RankAddDefense;
	int m_iTopa_5RankOptionNum;
	int m_iTopa_5RankDamageAbsorbRate;
	int m_iOnyx_1RankSlowMoveSkillRate;
	int m_iOnyx_2RankAddStrength;
	int m_iOnyx_2RankAddDexterity;
	int m_iOnyx_2RankAddEnergy;
	int m_iOnyx_2RankAddVitality;
	int m_iOnyx_3RankAddMaxLife;
	int m_iOnyx_3RankAddMaxMana;
	int m_iOnyx_3RankAddMaxAG;
	int m_iOnyx_3RankAddMaxSD;
	int m_iOnyx_4RankOptionNum;
	int m_iOnyx_4RankAddExllentDamageRate;
	int m_iOnyx_5RankHalfValueSkillRate;
	bool m_isAddPentaAttack;
	bool m_isAddPentaDefense;
	bool m_isAddCriPentaDamage;
	bool m_isChangePentaDefense;
	bool m_isChangePentaAttack;
	bool m_isAddResistByStrongRelationShip;
	bool m_isAddResistByPentaAttack;
};

struct _BOT_BUFF_LIST
{
	WORD wBuffId;
	WORD wDuration;
	int iEffect;
	WORD wEffectType;
};

struct EXC_WING_OPTION
{
	EXC_WING_OPTION()
	{
		this->Clear();
	}

	void Clear()
	{
		this->iWingOpIgnoreEnemyDefense = 0;
		this->iWingOpReturnEnemyDamage = 0;
		this->iWingOpRecoveryHP = 0;
		this->iWingOpRecoveryMana = 0;
		this->iWingOpAddDoubleDamage = 0;
	}

	int iWingOpIgnoreEnemyDefense;
	int iWingOpReturnEnemyDamage;
	int iWingOpRecoveryHP;
	int iWingOpRecoveryMana;
	int iWingOpAddDoubleDamage;
};

struct STAT_USER_OPTION
{
	STAT_USER_OPTION()
	{
		this->Clear();
	}

	void Clear()
	{
		this->StatOptionID = 0;
		this->StatOptionValMin = 0;
		this->StatOptionValMax = 0;
	}

	WORD StatOptionID;
	WORD StatOptionValMin;
	WORD StatOptionValMax;
};

struct _tagMUUN_EFFECT_LIST
{
	_tagMUUN_EFFECT_LIST()
	{
		this->Clear();
	}

	void Clear()
	{
		this->nIndex = 0;
		this->nMuunItemNum = 0;
		this->nCategory = 0;
		this->bOptEnable = 0;
		this->nOptType = 0;
		this->nOptValue = 0;
		this->bAddOptEnable = 0;
		this->nAddOptType = 0;
		this->nAddOptValue = 0;
		this->nSetTime = 0;
		this->nDuration = 0;
		this->pCMuunInfo = NULL;
		this->nTotalVal = 0;
		this->nSkillDelayTime = 0;
		this->bSkillUsed = false;
		this->nTargetIndex = -1;
		this->nTickTime = 0;
	}

	int nIndex;
	int nMuunItemNum;
	char nCategory;
	bool bOptEnable;
	char nOptType;
	int nOptValue;
	bool bAddOptEnable;
	char nAddOptType;
	int nAddOptValue;
	DWORD nSetTime;
	int nDuration;
	CMuunInfo *pCMuunInfo;
	int nTotalVal;
	int nSkillDelayTime;
	int nTickTime;
	bool bSkillUsed;
	int nTargetIndex;
};

struct _tagMOVE_MAPSERVER_AUTHINFO
{
	char szCharName[MAX_ACCOUNT_LEN + 2];
	int iJA1;
	int iJA2;
	int iJA3;
	int iJA4;
};

struct CharacterNameOfUBF
{
	void Clear()
	{
		memset(this->szCharacterName, 0, MAX_ACCOUNT_LEN + 1);
		memset(this->szCharacterNameOfUBF, 0, MAX_ACCOUNT_LEN + 1);
		this->nServerCodeOfHomeWorld = 0;
	}

	char szCharacterName[MAX_ACCOUNT_LEN + 1];
	char szCharacterNameOfUBF[MAX_ACCOUNT_LEN + 1];
	WORD nServerCodeOfHomeWorld;
};

typedef struct MU_WSAOVERLAPPED {
	DWORD    Internal;
	DWORD    InternalHigh;
	DWORD    Offset;
	DWORD    OffsetHigh;
	DWORD	 hEvent;
} FAR * LPMU_WSAOVERLAPPED;

typedef struct MU_WSABUF {
	ULONG len;
	CHAR* buf;
} *LPMU_WSABUF;

// END USER STRUCTS


#endif