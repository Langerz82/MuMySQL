////////////////////////////////////////////////////////////////////////////////
// PeriodItemEx.h
#ifndef PERIODITEMEX_H
#define PERIODITEMEX_H

#include "StdAfx.h"


#define MAX_PERIOD_ITEMS 30

enum PERIODITEM_TYPE
{
	PERIODITEM_BUFF = 1,
	PERIODITEM_NORMAL = 2
};

struct PMSG_ANS_PERIODITEMEX_INSERT
{
	PBMSG_HEAD2 head;
	DWORD dwUserGuid;
	WORD wUserIndex;
	BYTE btResultCode;
	BYTE btItemtype;
	WORD wItemCode;
	BYTE btEffectCategory;
	BYTE btEffectType1;
	BYTE btEffectType2;
	UINT64 Serial;
	DWORD dwDuration;
	time_t lBuyDate;
	time_t lExpireDate;
};

struct PMSG_REQ_PERIODITEMEX_INSERT
{
	PBMSG_HEAD2 head;
	DWORD dwUserGuid;
	WORD wUserIndex;
	char chCharacterName[MAX_ACCOUNT_LEN + 1];
	BYTE btItemType;
	WORD wItemCode;
	BYTE btEffectCategory;
	BYTE btEffectType1;
	BYTE btEffectType2;
	UINT64 Serial;
	DWORD dwDuration;
	time_t lBuyDate;
	time_t lExpireDate;
};

struct PMSG_ANS_PERIODITEMEX_DELETE
{
	PBMSG_HEAD2 head;
	DWORD dwUserGuid;
	WORD wUserIndex;
	BYTE btResultCode;
};

struct PMSG_REQ_PERIODITEMEX_DELETE
{
	PBMSG_HEAD2 head;
	DWORD dwUserGuid;
	WORD wUserIndex;
	UINT64 Serial;
	WORD wItemCode;
	BYTE btItemType;
	char chCharacterName[MAX_ACCOUNT_LEN + 1];
};

struct ITEMPERIOD_DATEINFO
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

typedef struct
{
	DWORD dwUserGuid;
	BYTE btItemCount;
	char chCharacterName[MAX_ACCOUNT_LEN + 1];
	ITEMPERIOD_DATEINFO ItemData[100];
}PERIOD_ITEMLIST, *LPPERIOD_ITEMLIST;

struct PMSG_ANS_PERIODITEMEX_LIST
{
	PBMSG_HEAD2 head;
	DWORD dwUserGuid;
	WORD wUserIndex;
	BYTE btUsedInfo;
	BYTE btItemType;
	UINT64 Serial;
	time_t lItemBuyDate;
	time_t lItemExpireDate;
	WORD wItemCode;
	BYTE btEffectCategory;
	BYTE btEffectType1;
	BYTE btEffectType2;
};

struct PMSG_REQ_PERIODITEMEX_SELECT
{
	PBMSG_HEAD2 head;
	DWORD dwUserGuid;
	WORD wUserIndex;
	char chCharacterName[MAX_ACCOUNT_LEN + 1];
};

struct PMSG_ANS_PERIODITEMEX_EXPIRED_ITEMLIST
{
	PWMSG_HEAD2 head;
	WORD wUserIndex;
	BYTE btExpiredItemCount;
	WORD wItemCode[90];
	UINT64 Serial[90];
};

struct PMSG_ANS_PERIODITEMEX_LIST_COUNT
{
	PBMSG_HEAD2 head;
	WORD wUserIndex;
	BYTE btResult;
	BYTE btListCount;
	DWORD dwUserGuid;
};

struct PERIOD_EXPIRED_ITEM
{
	WORD wItemCode;
	UINT64 Serial;
};

typedef struct
{
	BYTE btItemCount;
	PERIOD_EXPIRED_ITEM ExpiredItem[90];
}PERIOD_EXPIRED_ITEMLIST, *LPPERIOD_EXPIRED_ITEMLIST;

struct ITEM_DATA
{
	BYTE btUsedInfo;
	BYTE btItemType; // used
	WORD wItemCode; // used
	BYTE btEffectCategory;
	BYTE btEffectType1;
	BYTE btEffectType2;
	UINT64 Serial; // used
	time_t lItemBuyDate; // used
	time_t lItemExpireDate; // used
	DWORD dwDuration; // used

	void Clear()
	{
		this->btUsedInfo = FALSE;
		this->btItemType = FALSE;
		this->wItemCode = 0;
		this->Serial = 0;
	}
};

struct PERIOD_DATA
{
	BYTE btUsedInfo;
	BYTE btItemCount;
	WORD wUserIndex;
	DWORD dwUserGuid;
	CGameObject* lpObj; // lol
	char szAccountID[MAX_ACCOUNT_LEN + 1];
	char szCharacterName[MAX_ACCOUNT_LEN + 1];
	ITEM_DATA m_ItemInfo[30];

	void Clear()
	{
		this->btUsedInfo = FALSE;
		this->btItemCount = FALSE;
		this->wUserIndex = 0;
		this->dwUserGuid = 0;
		this->lpObj = nullptr;
		this->szAccountID[0] = 0;
		this->szCharacterName[0] = 0;

		for (int i = 0; i<30; i++)
		{
			this->m_ItemInfo[i].Clear();
		}
	}
};

class CPeriodItemEx
{
public:
	CPeriodItemEx(void);
	virtual ~CPeriodItemEx(void);

	void Initialize();

	int AddPeriodInfo(CGameObject &Obj);
	BOOL RemovePeriodInfo(CGameObject &Obj);
	BOOL IsCorrectUser(CGameObject &Obj);

	int AddPeriodItemData(CGameObject &Obj, WORD ItemType, UINT64 Serial, DWORD Duration, time_t ExpireDate);
	int AddPeriodItemData(CGameObject &Obj, WORD ItemType, UINT64 Serial, DWORD Duration);
	int RemovePeriodItemData(CGameObject &Obj, BYTE ItemUseType, WORD ItemType, UINT64 Serial);
	int RemovePeriodItemDataByForce(CGameObject &Obj, WORD ItemType, UINT64 Serial);

	BOOL CheckExpireDate(time_t ExpireDate);
	void CheckPeriodData();
	time_t GetExpireDate(DWORD Duration);
	time_t GetLeftDate(time_t ExpireDate);
	int GetItemFromInventory(CGameObject &Obj, WORD ItemType, UINT64 Serial);

	time_t GetCurrentDate();

	void OnRequestPeriodItemList(CGameObject &Obj);
	void OnRequestPeriodItemListOnce(CGameObject &Obj, ITEM_DATA * lpItemData);

	void RequestPeriodItemInfo(CGameObject &Obj);
	void RequestPeriodItemInsert(CGameObject &Obj, ITEM_DATA * lpItemData, DWORD dwDuration);
	void RequestPeriodItemDelete(CGameObject &Obj, ITEM_DATA * lpItemData);

	void DGPeriodItemExInsert(PMSG_ANS_PERIODITEMEX_INSERT * lpMsg);
	void DGPeriodItemExDelete(PMSG_ANS_PERIODITEMEX_DELETE * lpMsg);
	void DGPeriodItemExExpiredItemList(PMSG_ANS_PERIODITEMEX_EXPIRED_ITEMLIST * lpMsg);
	void DGPeriodItemExListCount(PMSG_ANS_PERIODITEMEX_LIST_COUNT * lpMsg);
	void DGPeriodItemExList(PMSG_ANS_PERIODITEMEX_LIST * lpMsg);
	
	BOOL SendPeriodItemInfoOnce(CGameObject &Obj, CItemObject * Item);
	BOOL SendPeriodItemInfoOnce(CGameObject &Obj, UINT64 Serial);

	BOOL SetPeriodItemInfo(CGameObject &Obj, WORD wItemCode, UINT64 Serial, DWORD dwDuration);
	BOOL SetDisableItemToExpire(CGameObject &Obj, int pos);
	void SetExpireNotMatchedData(CGameObject &Obj);

	PERIOD_DATA * m_PeriodData;

};

extern CPeriodItemEx g_PeriodItemEx;

#endif

////////////////////////////////////////////////////////////////////////////////
//  vnDev.Games - MuServer S12EP2 IGC v12.0.1.0 - Trong.LIVE - DAO VAN TRONG  //
////////////////////////////////////////////////////////////////////////////////

