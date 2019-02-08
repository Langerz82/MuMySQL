
#if !defined(AFX_COREDSPROTOCOL_H__2BBE1FF8_64DE_46AC_8344_13E7059DCBE3__INCLUDED_)
#define AFX_COREDSPROTOCOL_H__2BBE1FF8_64DE_46AC_8344_13E7059DCBE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "ProtocolStructs.h"
#include "Shop.h"
#include "CryWolf/Crywolf.h"
#include "Database/Query.h"

/*
 *	MAP OF DB ITEMS
 *
 *  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
 *	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
 *
 *  1 - Type (0..4) bits
 *  2 - Level(3..6)-Luck(2)-Option(0..1)-Skill(7)
 *  3 - Dur
 *  4,5,6,7 - Serial
 *  8 - NewOption(0..5)-Option16(6)-(Type(7)
 *	9 - SetOption
 * 10 - ItemType(4..7) and ItemEffectEx(0..3)
 * 11 - JOH
 *  
 */
/*
 *	CHAR SET
 *	
 *	It Contains the Character Settings
 *	CS_CLASS(0)	Contains the Class and the ChangeUP
 *				You can use CS_GET_CLASS and CS_GET_CHANGEUP
 *	MAP of CHAR SET
 *
 *	    0         1	        2	      3	        4	      5	  	    6	      7
 *	0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
 *	AAAB   CC EEEE EEEE GGGG GGGG JJJJ MMMM PPPP SSSS VVVV WWWW XXXX XXXX YYYY YYYY
 *
 *	    8         9		    10	      11	    12	      13	    14	      15
 *	0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
 *	ZZZZ ZZZZ ILOR Uhhh aaaa aaad bbbb bbbc DDDD  i e FFFF HHHH KKKK NNNN QQQQ TTTT
 *
 *	    16	      17
 *	0000 0000 0000 0000
 *	       gf         
 *
 *	AAA Contain Class Character Definition (DK:1 DW:0 ELF:2 MG:3 DL:4)
 *	B Contains the Change UP (0:Normal 1:Evolved)
 *	CC Contains a value Acording m_ActionNumber fron gObj
 *
 *	DDDD Contains the 8..11 bits of Rigth Hand Item Index
 *	EEEE EEEE Contains the 0..7 bits Rigth Hand Item Index
 *
 *	FFFF Contains the 8..11 bits of Left Hand Item Index
 *	GGGG GGGG Contains the 0..7 bits of Left Hand Item Index
 *
 *	HHHH Contains the 5..8 Bits from Helmet Item Index
 *	I Contains the 4 bit from Helmet Item Index
 *	JJJJ Contains the 0..3 bits from Helmet Item Index
 *
 *	KKKK Contains the 5..8 Bits from Armor Item Index
 *	L Contains the 4 bit from Armor Item Index
 *	MMMM Contains the 0..3 bits from Armor Item Index
 *
 *	NNNN Contains the 5..8 Bits from Pants Item Index
 *	O Contains the 4 bit from Pants Item Index
 *	PPPP Contains the 0..3 bits from Pants Item Index
 *
 *	QQQQ Contains the 5..8 Bits from Gloves Item Index
 *	R Contains the 4 bit from Gloves Item Index
 *	SSSS Contains the 0..3 bits from Gloves Item Index
 *
 *	TTTT Contains the 5..8 Bits from Boots Item Index
 *	U Contains the 4 bit from Boots Item Index
 *	VVVV Contains the 0..3 bits from Boots Item Index
 *
 *	WW-WW Contains Wings and Helper(0..1, 0..1 bits) for Wings2 is set 0x0C
 *
 *	XXXX XXXX Contains Levels (Shine Levels) from Wings and Boots
 *	YYYY YYYY Contains Levels (Shine Levels) from Gloves and Pants and Armor
 *	ZZZZ ZZZZ Contains Levels (Shine Levels) from Helmet , Right and Left HAnd
 *
 *	aaaa aaa Contains the If the item is Excellent
 *
 *	bbbb bbb Contains the If the item is SetItem
 *	c	1 if the Char have the Full Set Item
 *
 *	d Unkown
 *
 *	e Have Dark Horse?
 *
 *	f	Fenrir Inc Attack Damage
 *	g	Fenrir Dec Attack Damage
 *	hhh Wing2 Types (m_Type - 2) Cape Of Lord 101(5)
 *	i Is Fenrir?
 */


#define CHAR_SET_SIZE		18

	#define CS_CLASS		0

	#define CS_WEAPON1_TYPE	1
	#define CS_WEAPON2_TYPE	2

	#define CS_WEAPON1_DATA	12
	#define CS_WEAPON2_DATA	13

	#define CS_HELMET1		13
	#define CS_HELMET2		9
	#define CS_HELMET3		3

	#define CS_ARMOR1		14
	#define CS_ARMOR2		9
	#define CS_ARMOR3		3

	#define CS_PANTS1		14
	#define CS_PANTS2		9
	#define CS_PANTS3		4

	#define CS_GLOVES1		15
	#define CS_GLOVES2		9
	#define CS_GLOVES3		4

	#define CS_BOOTS1		15
	#define CS_BOOTS2		9
	#define CS_BOOTS3		5


#define CHECK_CLASS(value, type) ( ((value)!=(type))?FALSE:TRUE )

#define CS_GET_CLASS(x) ( (((x)>>4)<<5)&(0xE0) )
#define CS_GET_CHANGEUP(x) ( ((x)&0x07) )
#define CS_SET_CLASS(x) ( ((x)<<5)& 0xE0 )
#define CS_SET_CHANGEUP(x) ( ((x) << 4) & 0x10 )

#define CS_SET_HELMET1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_HELMET2(x) ( ((x) & 0x10 ) << 3 )
#define CS_SET_HELMET3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_ARMOR1(x) ( ((x) & 0x1E0) >> 1 )
#define CS_SET_ARMOR2(x) ( ((x) & 0x10 ) << 2 )
#define CS_SET_ARMOR3(x) ( ((x) & 0x0F )      )

#define CS_SET_PANTS1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_PANTS2(x) ( ((x) & 0x10 ) << 1 )
#define CS_SET_PANTS3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_GLOVES1(x) ( ((x) & 0x1E0) >> 1 )
#define CS_SET_GLOVES2(x) ( ((x) & 0x10 )      )
#define CS_SET_GLOVES3(x) ( ((x) & 0x0F )      )

#define CS_SET_BOOTS1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_BOOTS2(x) ( ((x) & 0x10 ) >> 1 )
#define CS_SET_BOOTS3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_WING1(x)  ( ((x) & 0x03 ) << 2 )
#define CS_SET_HELPER(x) ( ((x) & 0x03 )      )

#define CS_SET_SMALLLEVEL_RH(x)		( (x)       )
#define CS_SET_SMALLLEVEL_LH(x)		( (x) << 3  ) 
#define CS_SET_SMALLLEVEL_HELMET(x)	( (x) << 6  )
#define CS_SET_SMALLLEVEL_ARMOR(x)	( (x) << 9  )
#define CS_SET_SMALLLEVEL_PANTS(x)	( (x) << 12 )
#define CS_SET_SMALLLEVEL_GLOVES(x)	( (x) << 15 )
#define CS_SET_SMALLLEVEL_BOOTS(x)	( (x) << 18 )

#define CS_SET_SMALLLEVEL1(x)		( ((x) >> 16) & 0xFF )
#define CS_SET_SMALLLEVEL2(x)		( ((x) >> 8 ) & 0xFF )
#define CS_SET_SMALLLEVEL3(x)		((x) & 0xFF )

#define DBI_GET_TYPE(x) ( ((x)&((MAX_TYPE_ITEMS-1)<<8))>>4 )
#define DBI_GET_INDEX(x) ( (x) & 0xFF )

#ifndef DBI_GET_LEVEL
#define DBI_GET_LEVEL(x)  ( ((x)>>3)& MAX_ITEM_LEVEL )
#endif

#define DBI_GET_SKILL(x)  ( ((x) >> 7) & 0x01)
#define DBI_GET_LUCK(x)  ( ((x) >> 2) & 0x01)
#define DBI_GET_OPTION(x)  ( ( (x) ) & 0x03 )
#define DBI_GET_OPTION16(x) ( (x) & 0x40  )
#define DBI_GET_DINO_OPTION(x)  ( DBI_GET_OPTION16((x)) >> 4 )
#define DBI_GET_NOPTION(x)  ( (x) & 0x3F  )
#define DBI_GET_380OPTION(x) ( ((x) & 0x08) << 4  )
#define ITEM_GET_TYPE(x)  ( (x)/MAX_SUBTYPE_ITEMS  )
#define ITEM_GET_INDEX(x) ( (x)%MAX_SUBTYPE_ITEMS  )

#define CHAR_SET_SIZE 18
#define MAX_ITEM_INFO 12
#define INVENTORY_BINARY_SIZE 7584
#define MAX_DBITEM_INFO 32
#define CHAOS_BOX_SIZE 32

// Struct Declarations.
struct _PMSG_QUESTEXP_INFO;
struct _QUESTEXP_INFO;
struct BAN_REQ_USER;
struct CSP_ANS_ALLGUILDREGINFO;
struct CSP_ANS_CALCREGGUILDLIST;
struct CSP_ANS_CASTLEOWNERCHANGE;
struct CSP_ANS_CASTLESIEGEEND;
struct CSP_ANS_CASTLESTATESYNC;
struct CSP_ANS_CASTLETRIBUTEMONEY;
struct CSP_ANS_CSGUILDUNIONINFO;
struct CSP_ANS_CSINITDATA;
struct CSP_ANS_CSLOADTOTALGUILDINFO;
struct CSP_ANS_CSSAVETOTALGUILDINFO;
struct CSP_ANS_GUILDREGINFO;
struct CSP_ANS_GUILDREGMARK;
struct CSP_ANS_GUILDRESETMARK;
struct CSP_ANS_GUILDSETGIVEUP;
struct CSP_ANS_MAPSVRMULTICAST;
struct CSP_ANS_MONEYCHANGE;
struct CSP_ANS_NPCBUY;
struct CSP_ANS_NPCREMOVE;
struct CSP_ANS_NPCREPAIR;
struct CSP_ANS_NPCSAVEDATA;
struct CSP_ANS_NPCUPDATEDATA;
struct CSP_ANS_NPCUPGRADE;
struct CSP_ANS_OWNERGUILDMASTER;
struct CSP_ANS_REGATTACKGUILD;
struct CSP_ANS_RESETCASTLETAXINFO;
struct CSP_ANS_RESETREGSIEGEINFO;
struct CSP_ANS_RESETSIEGEGUILDINFO;
struct CSP_ANS_SDEDCHANGE;
struct CSP_ANS_SIEGEENDCHANGE;
struct CSP_ANS_TAXINFO;
struct CSP_ANS_TAXRATECHANGE;
struct CSP_CALCREGGUILDLIST;
struct CSP_CSGUILDUNIONINFO;
struct CSP_CSINITDATA;
struct CSP_CSLOADTOTALGUILDINFO;
struct CSP_CSSAVETOTALGUILDINFO;
struct CSP_GLOBALPOST_MULTICAST;
struct CSP_GUILDREGINFO;
struct CSP_NPCSAVEDATA;
struct CSP_NPCUPDATEDATA;
struct CSP_REQ_ALLGUILDREGINFO;
struct CSP_REQ_CALCREGGUILDLIST;
struct CSP_REQ_CASTLEOWNERCHANGE;
struct CSP_REQ_CASTLESIEGEEND;
struct CSP_REQ_CASTLESTATESYNC;
struct CSP_REQ_CASTLETRIBUTEMONEY;
struct CSP_REQ_CSGUILDUNIONINFO;
struct CSP_REQ_CSINITDATA;
struct CSP_REQ_CSLOADTOTALGUILDINFO;
struct CSP_REQ_CSSAVETOTALGUILDINFO;
struct CSP_REQ_GUILDREGINFO;
struct CSP_REQ_GUILDREGMARK;
struct CSP_REQ_GUILDRESETMARK;
struct CSP_REQ_GUILDSETGIVEUP;
struct CSP_REQ_MAPSVRMULTICAST;
struct CSP_REQ_MONEYCHANGE;
struct CSP_REQ_NPCBUY;
struct CSP_REQ_NPCREMOVE;
struct CSP_REQ_NPCREPAIR;
struct CSP_REQ_NPCSAVEDATA;
struct CSP_REQ_NPCUPDATEDATA;
struct CSP_REQ_NPCUPDATEDATA;
struct CSP_REQ_NPCUPGRADE;
struct CSP_REQ_OWNERGUILDMASTER;
struct CSP_REQ_REGATTACKGUILD;
struct CSP_REQ_RESETCASTLETAXINFO;
struct CSP_REQ_RESETREGSIEGEINFO;
struct CSP_REQ_RESETSIEGEGUILDINFO;
struct CSP_REQ_SDEDCHANGE;
struct CSP_REQ_SIEGEENDCHANGE;
struct CSP_REQ_TAXINFO;
struct CSP_REQ_TAXRATECHANGE;
struct CWP_ANS_CRYWOLFINFOLOAD;
struct CWP_ANS_CRYWOLFINFOSAVE;
struct CWP_ANS_CRYWOLFSYNC;
struct CWP_REQ_CRYWOLFINFOLOAD;
struct CWP_REQ_CRYWOLFINFOSAVE;
struct CWP_REQ_CRYWOLFSYNC;
struct DS_SAVE_MONSTERCNT;
struct DS_SAVE_PLAYERKILLER;
struct DSF_GO_FINAL_PARTY;
struct DSMSG_ANS_SUBSERVER_COUNT;
struct DSMSG_ANS_WHISPER_RESULT;
struct DSMSG_CHAOSMACHINE_LOSTITEMS;
struct DSMSG_GS_WHISPER_RESULT;
struct DSMSG_REQ_SUBSERVER_COUNT;
struct ISHOP_ANS_ITEMLIST;
struct ISHOP_ANS_POINT;
struct ISHOP_CHARCARD_BUY;
struct ISHOP_ITEM_BUY;
struct ISHOP_ITEM_BUY_PACKAGE;
struct ISHOP_ITEM_BUYANS;
struct ISHOP_ITEM_DELETE;
struct ISHOP_ITEM_GIFT;
struct ISHOP_ITEM_GIFT_PACKAGE;
struct ISHOP_ITEM_GIFTANS;
struct ISHOP_ITEM_PACKAGE;
struct ISHOP_ITEM_ROLLBACK;
struct ISHOP_ITEM_USE;
struct ISHOP_ITEM_USEANS;
struct ISHOP_ITEMLIST;
struct ISHOP_POINT_ADD;
struct ISHOP_REQ_ITEMLIST;
struct ISHOP_REQ_POINT;
struct MAX_CS_GUILDLIST;
struct MAX_CS_NPC;
struct MAX_IDSTRING;
struct MUBOT_SETTINGS_REQ_SAVE;
struct MUBOT_SETTINGS_SEND;
struct PENTAGRAMJEWEL_INFO;
struct PMSG_ANS_2ANIV_SERIAL;
struct PMSG_ANS_AB_ALL_JOIN_USER_DS;
struct PMSG_ANS_AB_JOIN_CANCEL_DS;
struct PMSG_ANS_AB_JOIN_MEMBER_UNDER_DS;
struct PMSG_ANS_AB_PROC_STATE_DS;
struct PMSG_ANS_AB_REG_MEMBER_CNT_DS;
struct PMSG_ANS_AB_WIN_GUILD_INFO_DS;
struct PMSG_ANS_AE_PLAY_DS;
struct PMSG_ANS_ALL_GUILD_MARK_CNT_DS;
struct PMSG_ANS_ARCA_BATTLE_ENTER_DS;
struct PMSG_ANS_ARCA_BATTLE_GUILD_JOIN_DS;
struct PMSG_ANS_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS;
struct PMSG_ANS_ARCA_BATTLE_MARK_CNT_DS;
struct PMSG_ANS_ARCA_BATTLE_MARK_RANK_DS;
struct PMSG_ANS_ARCA_BATTLE_MARK_REG_DS;
struct PMSG_ANS_BLOODCASTLE_ENTERCOUNT;
struct PMSG_ANS_BLOODCASTLESCORE_5TH;
struct PMSG_ANS_CCF_RANK;
struct PMSG_ANS_CHAOSCASTLE_RANKING;
struct PMSG_ANS_CLASSDEF;
struct PMSG_ANS_DELETE_STONES;
struct PMSG_ANS_DSF_CAN_PARTY_ENTER;
struct PMSG_ANS_DSF_GO_FINAL_PARTY;
struct PMSG_ANS_DSF_PARTYRANKRENEW;
struct PMSG_ANS_EVENTENTRY_INFO;
struct PMSG_ANS_EVENTUSERSCORE;
struct PMSG_ANS_EVOMON_MAXSCORE;
struct PMSG_ANS_GET_DSF_REWARD;
struct PMSG_ANS_GET_UBF_REAL_NAME;
struct PMSG_ANS_ILLUSIONTEMPLE_RANKING;
struct PMSG_ANS_LUCKYCOIN;
struct PMSG_ANS_LUCKYITEM_SELECT;
struct PMSG_ANS_MURUMMY_SELECT_DS;
struct PMSG_ANS_PENTAGRAMJEWEL;
struct PMSG_ANS_PERIODBUFF_SELECT;
struct PMSG_ANS_PERIODITEMEX_DELETE;
struct PMSG_ANS_PERIODITEMEX_EXPIRED_ITEMLIST;
struct PMSG_ANS_PERIODITEMEX_INSERT;
struct PMSG_ANS_PERIODITEMEX_LIST;
struct PMSG_ANS_PERIODITEMEX_LIST_COUNT;
struct PMSG_ANS_PSHOPITEMVALUE_INFO;
struct PMSG_ANS_QUESTEXP_INFO;
struct PMSG_ANS_REG_CC_OFFLINE_GIFT;
struct PMSG_ANS_REG_DL_OFFLINE_GIFT;
struct PMSG_ANS_REG_HT_OFFLINE_GIFT;
struct PMSG_ANS_REG_LUCKYCOIN;
struct PMSG_ANS_REGISTER_EVENTCHIP;
struct PMSG_ANS_REGISTER_STONES;
struct PMSG_ANS_REMOVE_ALL_GUILD_BUFF_DS;
struct PMSG_ANS_RESET_EVENTCHIP;
struct PMSG_ANS_SANTACHECK;
struct PMSG_ANS_SANTAGIFT;
struct PMSG_ANS_SWITCHWARE;
struct PMSG_ANS_UBF_ACCOUNT_USERINFO;
struct PMSG_ANS_UBF_GET_REWARD;
struct PMSG_ANS_UBF_SET_RECEIVED_REWARD;
struct PMSG_ANS_VIEW_EC_MN;
struct PMSG_ANS_VIEW_STONES;
struct PMSG_ANS_WARESAVE;
struct PMSG_DEL_PENTAGRAMJEWEL;
struct PMSG_DEL_PSHOPITEM;
struct PMSG_INSERT_PENTAGRAMJEWEL;
struct PMSG_LUCKYITME_DB_INFO;
struct PMSG_MOVE_PSHOPITEM;
struct PMSG_RECV_CHATDATA_WHISPER;
struct PMSG_RECV_DC_OTHER_CHANNEL;
struct PMSG_REQ_AB_ALL_JOIN_USER_DS;
struct PMSG_REQ_AB_JOIN_CANCEL_DS;
struct PMSG_REQ_AB_JOIN_MEMBER_UNDER_DS;
struct PMSG_REQ_AB_MARK_REG_UPDATE_DS;
struct PMSG_REQ_AB_PROC_INSERT_DS;
struct PMSG_REQ_AB_PROC_STATE_DS;
struct PMSG_REQ_AB_REG_MEMBER_CNT_DS;
struct PMSG_REQ_AB_WIN_GUILD_INFO_DS;
struct PMSG_REQ_AB_WIN_GUILD_INFO_INSERT_DS;
struct PMSG_REQ_AE_PLAY_DS;
struct PMSG_REQ_ARCA_BATTLE_ENTER_DS;
struct PMSG_REQ_ARCA_BATTLE_GUILD_JOIN_DS;
struct PMSG_REQ_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS;
struct PMSG_REQ_ARCA_BATTLE_IS_TOP_RANK;
struct PMSG_REQ_ARCA_BATTLE_MARK_CNT_DS;
struct PMSG_REQ_ARCA_BATTLE_MARK_RANK_DS;
struct PMSG_REQ_ARCA_BATTLE_MARK_REG_DEL_DS;
struct PMSG_REQ_ARCA_BATTLE_MARK_REG_DS;
struct PMSG_REQ_BLOODCASTLE_ENTERCOUNT;
struct PMSG_REQ_CCF_PERMISSION;
struct PMSG_REQ_DELETE_STONES;
struct PMSG_REQ_DSF_CAN_PARTY_ENTER;
struct PMSG_REQ_DSF_GO_FINAL_PARTY;
struct PMSG_REQ_DSF_PARTYRANKRENEW;
struct PMSG_REQ_EVENTENTRY_INFO;
struct PMSG_REQ_EVOMON_MAXSCORE;
struct PMSG_REQ_GET_DSF_REWARD;
struct PMSG_REQ_GET_UBF_REAL_NAME;
struct PMSG_REQ_GUILD_REG_INIT;
struct PMSG_REQ_LUCKYCOIN;
struct PMSG_REQ_LUCKYITEM_DELETE;
struct PMSG_REQ_LUCKYITEM_INSERT;
struct PMSG_REQ_LUCKYITEM_SELECT;
struct PMSG_REQ_MURUMMY_DELETE_DS;
struct PMSG_REQ_MURUMMY_INFO_UPDATE_DS;
struct PMSG_REQ_MURUMMY_INSERT_DS;
struct PMSG_REQ_MURUMMY_LOG_INSERT_DS;
struct PMSG_REQ_MURUMMY_SCORE_UPDATE_DS;
struct PMSG_REQ_MURUMMY_SELECT_DS;
struct PMSG_REQ_MURUMMY_SLOTUPDATE_DS;
struct PMSG_REQ_MURUMMY_UPDATE_DS;
struct PMSG_REQ_PENTAGRAMJEWEL;
struct PMSG_REQ_PERIODBUFF_DELETE;
struct PMSG_REQ_PERIODBUFF_INSERT;
struct PMSG_REQ_PERIODBUFF_SELECT;
struct PMSG_REQ_PERIODITEMEX_DELETE;
struct PMSG_REQ_PERIODITEMEX_INSERT;
struct PMSG_REQ_PERIODITEMEX_SELECT;
struct PMSG_REQ_PSHOPITEMVALUE_INFO;
struct PMSG_REQ_QUESTEXP_INFO;
struct PMSG_REQ_REG_CC_OFFLINE_GIFT;
struct PMSG_REQ_REG_DL_OFFLINE_GIFT;
struct PMSG_REQ_REG_HT_OFFLINE_GIFT;
struct PMSG_REQ_REGISTER_EVENTCHIP;
struct PMSG_REQ_REGISTER_LUCKYCOIN;
struct PMSG_REQ_REGISTER_STONES;
struct PMSG_REQ_REMOVE_ALL_GUILD_BUFF_DS;
struct PMSG_REQ_RESET_EVENTCHIP;
struct PMSG_REQ_SANTACHECK;
struct PMSG_REQ_SANTAGIFT;
struct PMSG_REQ_SAVE_CCF_RESULT;
struct PMSG_REQ_SAVE_DSF_PARTYPOINT;
struct PMSG_REQ_SAVE_DSF_REWARD_USER;
struct PMSG_REQ_SAVE_EVOMON_RESULT;
struct PMSG_REQ_SET_DSF_WINNER_INFO;
struct PMSG_REQ_SETPENTAGRAMJEWEL;
struct PMSG_REQ_SWITCHWARE;
struct PMSG_REQ_UBF_ACCOUNT_USERINFO;
struct PMSG_REQ_UBF_GET_REWARD;
struct PMSG_REQ_UBF_SET_RECEIVED_REWARD;
struct PMSG_REQ_VIEW_EC_MN;
struct PMSG_SEND_CCF_INFO_ALL_SVR;
struct PMSG_UBF_ACCOUNT_USER_COPY;
struct PMSG_UBF_ACCOUNT_USER_COPY_PETITEM;
struct PMSG_UBF_ACCOUNT_USER_COPY_RESULT;
struct PMSG_UBF_ANS_CANCEL_REGISTER_USER;
struct PMSG_UBF_REGISTER_ACCOUNT_USER;
struct PMSG_UBF_REGISTER_ACCOUNT_USER_RESULT;
struct PMSG_UBF_REQ_CANCEL_REGISTER_USER;
struct PMSG_UPDATE_PSHOPITEMVALUE_INFO;
struct Recv_PetItem_Info;
struct Request_PetItem_Info;
struct Save_PetItem_Info;
struct SDHP_ANS_CCF_GETPERMISSION;
struct SDHP_ANS_CCF_INFO_NOTIFY;
struct SDHP_ANS_DBEVENT_INVEN_LOAD;
struct SDHP_ANS_DBMUUN_INVEN_LOAD;
struct SDHP_ANS_LOAD_MINESYSTEM_UPT_USERINFO;
struct SDHP_ANS_MINESYSTEM_UPT_USERINFO;
struct SDHP_ANS_SHOP_REBUY_GET_ITEM;
struct SDHP_ANS_SHOP_REBUY_LIST;
struct SDHP_CHARACTER_TRANSFER;
struct SDHP_CHARDELETE;
struct SDHP_CHARDELETERESULT;
struct SDHP_CHARLIST;
struct SDHP_CHARLISTCOUNT;
struct SDHP_CHARLISTCOUNT;
struct SDHP_CREATECHAR;
struct SDHP_CREATECHARRESULT;
struct SDHP_DBCHAR_INFORESULT;
struct SDHP_DBCHAR_INFOSAVE;
struct SDHP_DBCHAR_ITEMSAVE;
struct SDHP_DBCHARINFOREQUEST;
struct SDHP_DELETE_TEMPUSERINFO;
struct SDHP_DELETE_TEMPUSERINFO_RESULT;
struct SDHP_EXPANDEDWAREHOUSE_SET;
struct SDHP_GETCHARLIST;
struct SDHP_GETWAREHOUSEDB;
struct SDHP_GETWAREHOUSEDB_RESULT;
struct SDHP_GETWAREHOUSEDB_SAVE;
struct SDHP_ITEMCREATE;
struct SDHP_ITEMCREATERECV;
struct SDHP_RECV_PETITEM_INFO;
struct SDHP_RENEW_RANKING;
struct SDHP_REQ_CCF_RANKING;
struct SDHP_REQ_DBEVENT_INVEN_LOAD;
struct SDHP_REQ_DBEVENT_INVEN_SAVE;
struct SDHP_REQ_DBMUUN_INVEN_LOAD;
struct SDHP_REQ_DBMUUN_INVEN_SAVE;
struct SDHP_REQ_LOAD_MINESYSTEM_UPT_USERINFO;
struct SDHP_REQ_MINESYSTEM_UPT_USERINFO;
struct SDHP_REQ_SET_CC_WINNER_INFO_UBF;
struct SDHP_REQ_SET_CCF_WINNER_INFO;
struct SDHP_REQ_SHOP_REBUY_ADD_ITEM;
struct SDHP_REQ_SHOP_REBUY_DELETE_ITEM;
struct SDHP_REQ_SHOP_REBUY_GET_ITEM;
struct SDHP_REQ_SHOP_REBUY_LIST;
struct SDHP_REQUEST_PETITEM_INFO;
struct SDHP_RESULT;
struct SDHP_SAVE_PETITEM_INFO;
struct SDHP_SERVERINFO;
struct SDHP_SHOP_REBUY_ITEM;
struct SDHP_SKILLKEYDATA;
struct SDHP_SKILLKEYDATA_SEND;
struct SDHP_WAREHOUSEMONEY_SAVE;
struct SECLOCK_REQ_SAVE;
struct USERWAREHOUSE_DATA;


class CWarehouseUserData
{
public:

	CWarehouseUserData();
	~CWarehouseUserData();

	void Init();

	void AddUserData(char * szAccountID);
	void DelUserData(char * szAccountID);

	int SwitchWarehouse(char * szAccountID, int WarehouseID);
	void SetChangeEnableState(char * szAccountID, int State);
	void SetWarehouseOpenState(char * szAccountID, bool bState);

	int GetWarehouseID(char * szAccountID);
	bool GetWarehouseOpenState(char * szAccountID);

	void DGGetWarehouseList(int aIndex, SDHP_GETWAREHOUSEDB * aRecv);
	void GDSetWarehouseList(int aIndex, SDHP_GETWAREHOUSEDB_SAVE * aRecv);
	void GDSetWarehouseMoney(int aIndex, SDHP_WAREHOUSEMONEY_SAVE * aRecv);
	void GDReqSwitchWarehouse(int aIndex, PMSG_REQ_SWITCHWARE * aRecv);

private:
	std::vector<USERWAREHOUSE_DATA*> m_vtWarehouseData;
	CRITICAL_SECTION m_WareDataCriti;
	CQuery m_WareDB;
};

#define MAX_CS_GUILDLIST 100
#define MAX_CS_NPC 200
#define PMHC_WORD 0xC2
#define MAX_IDSTRING 10

class CDataServerProtocol
{
public:

	CDataServerProtocol();
	~CDataServerProtocol();
	BOOL Init();
	static void ProtocolCore(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize);

private:

	void DataServerLogin(int aIndex, SDHP_SERVERINFO * lpMsg);
	void JGPGetCharList(int aIndex, SDHP_GETCHARLIST * aRecv);
	void JGCharacterCreateRequest(int aIndex, SDHP_CREATECHAR * aRecv);
	void JGCharDelRequest(int aIndex, SDHP_CHARDELETE * aRecv);
	void JGGetCharacterInfo(int aIndex, SDHP_DBCHARINFOREQUEST * aRecv);
	void GJSetCharacterInfo(int aIndex, SDHP_DBCHAR_INFOSAVE * aRecv);
	void GDUserItemSave(int aIndex, SDHP_DBCHAR_ITEMSAVE * aRecv);
	void ItemSerialCreateRecv(int aIndex, SDHP_ITEMCREATE * aRecv);
	void PetItemSerialCreateRecv(int aIndex, SDHP_ITEMCREATE * aRecv);
	void DGRecvPetItemInfo(int aIndex, SDHP_REQUEST_PETITEM_INFO * aRecv);
	void GDSavePetItemInfo(int aIndex, SDHP_SAVE_PETITEM_INFO * aRecv);
	void DGOptionDataRecv(int aIndex, SDHP_SKILLKEYDATA * aRecv);
	void DGMoveOtherServer(int aIndex, SDHP_CHARACTER_TRANSFER * aRecv);
	void GDDeleteTempUserInfo(int aIndex, SDHP_DELETE_TEMPUSERINFO * aRecv);
	void GS_DGAnsCastleInitData(int aIndex,CSP_REQ_CSINITDATA * aRecv);
	void GS_DGAnsOwnerGuildMaster(int aIndex,CSP_REQ_OWNERGUILDMASTER * aRecv);
	void GS_DGAnsCastleNpcBuy(int aIndex,CSP_REQ_NPCBUY * aRecv);
	void GS_DGAnsCastleNpcRepair(int aIndex,CSP_REQ_NPCREPAIR * aRecv);
	void GS_DGAnsCastleNpcUpgrade(int aIndex,CSP_REQ_NPCUPGRADE * aRecv);
	void GS_DGAnsTaxInfo(int aIndex,CSP_REQ_TAXINFO * aRecv);
	void GS_DGAnsTaxRateChange(int aIndex,CSP_REQ_TAXRATECHANGE * aRecv);
	void GS_DGAnsCastleMoneyChange(int aIndex,CSP_REQ_MONEYCHANGE * aRecv);
	void GS_DGAnsSiegeDateChange(int aIndex,CSP_REQ_SDEDCHANGE * aRecv);
	void GS_DGAnsGuildMarkRegInfo(int aIndex,CSP_REQ_GUILDREGINFO * aRecv);
	void GS_DGAnsSiegeEndedChange(int aIndex,CSP_REQ_SIEGEENDCHANGE * aRecv);
	void GS_DGAnsCastleOwnerChange(int aIndex,CSP_REQ_CASTLEOWNERCHANGE * aRecv);
	void GS_DGAnsRegAttackGuild(int aIndex,CSP_REQ_REGATTACKGUILD * aRecv);
	void GS_DGAnsRestartCastleState(int aIndex,CSP_REQ_CASTLESIEGEEND * aRecv);
	void GS_DGAnsMapSvrMsgMultiCast(int aIndex,CSP_REQ_MAPSVRMULTICAST * aRecv);
	void GS_DGAnsGlobalPostMultiCast(int aIndex, CSP_GLOBALPOST_MULTICAST * aRecv);
	void GS_DGAnsRegGuildMark(int aIndex,CSP_REQ_GUILDREGMARK * aRecv);
	void GS_DGAnsGuildMarkReset(int aIndex,CSP_REQ_GUILDRESETMARK * aRecv);
	void GS_DGAnsGuildSetGiveUp(int aIndex,CSP_REQ_GUILDSETGIVEUP * aRecv);
	void GS_DGAnsNpcRemove(int aIndex,CSP_REQ_NPCREMOVE * aRecv);
	void GS_DGAnsCastleStateSync(int aIndex,CSP_REQ_CASTLESTATESYNC * aRecv);
	void GS_DGAnsCastleTributeMoney(int aIndex,CSP_REQ_CASTLETRIBUTEMONEY * aRecv);
	void GS_DGAnsResetCastleTaxInfo(int aIndex,CSP_REQ_RESETCASTLETAXINFO * aRecv);
	void GS_DGAnsResetSiegeGuildInfo(int aIndex,CSP_REQ_RESETSIEGEGUILDINFO * aRecv);
	void GS_DGAnsResetRegSiegeInfo(int aIndex,CSP_REQ_RESETREGSIEGEINFO * aRecv);
	void GS_DGAnsAllGuildMarkRegInfo(int aIndex,CSP_REQ_ALLGUILDREGINFO * aRecv);
	void GS_DGAnsFirstCreateNPC(int aIndex,CSP_REQ_NPCSAVEDATA * aRecv);
	void GS_DGAnsCalcRegGuildList(int aIndex,CSP_REQ_CALCREGGUILDLIST * aRecv);
	void GS_DGAnsCsGulidUnionInfo(int aIndex,CSP_REQ_CSGUILDUNIONINFO * aRecv);
	void GS_DGAnsCsSaveTotalGuildInfo(int aIndex,CSP_REQ_CSSAVETOTALGUILDINFO * aRecv);
	void GS_DGAnsCsLoadTotalGuildInfo(int aIndex,CSP_REQ_CSLOADTOTALGUILDINFO * aRecv);
	void GS_DGAnsCastleNpcUpdate(int aIndex,CSP_REQ_NPCUPDATEDATA * aRecv);
	void DGAnsCrywolfSync(int aIndex,CWP_REQ_CRYWOLFSYNC * aRecv);
	void DGAnsCrywolfInfoLoad(int aIndex,CWP_REQ_CRYWOLFINFOLOAD * aRecv);
	void DGAnsCrywolfInfoSave(int aIndex,CWP_REQ_CRYWOLFINFOSAVE * aRecv);
	void DGAnsPeriodItemExInsert(int aIndex,PMSG_REQ_PERIODITEMEX_INSERT * aRecv);
	void DGAnsPeriodItemExSelect(int aIndex,PMSG_REQ_PERIODITEMEX_SELECT * aRecv);
	void DGAnsPeriodItemExDelete(int aIndex,PMSG_REQ_PERIODITEMEX_DELETE * aRecv);
	void ReqInGameShopItemList(short aIndex, ISHOP_REQ_ITEMLIST *aRecv);
	void ReqInGameShopPoint(short aIndex, ISHOP_REQ_POINT *aRecv);
	void ReqInGameShopAddPoint(short aindex, ISHOP_POINT_ADD *aRecv);
	void ReqInGameShopItemBuy(short aIndex, ISHOP_ITEM_BUY *aRecv);
	void ReqInGameShopPackageBuy(short aIndex, LPBYTE aRecv);
	void ReqInGameShopPackageGift(short aIndex, LPBYTE aRecv);
	void ReqInGameShopItemGift(short aIndex, ISHOP_ITEM_GIFT *aRecv);
	void ReqInGameShopItemUse(short aIndex, ISHOP_ITEM_USE *aRecv);
	void ReqInGameShopCharacterCardBuy(short aIndex, ISHOP_CHARCARD_BUY *aRecv);
	void ReqSetExpandedWarehouse(short aIndex, SDHP_EXPANDEDWAREHOUSE_SET *aRecv);
	void ReqInGameShopItemDelete(short aIndex, ISHOP_ITEM_DELETE *aRecv);
	void ReqInGameShopItemRollbackUse(short aIndex, ISHOP_ITEM_ROLLBACK *aRecv);
	void ReqLuckyCoinInfo(int aIndex,PMSG_REQ_LUCKYCOIN * lpMsg);
	void ReqRegLuckyCoin(int aIndex,PMSG_REQ_REGISTER_LUCKYCOIN * lpMsg);
	void DevilSqureScore(PMSG_ANS_EVENTUSERSCORE * pMsg);
	void GDReqBloodCastleEnterCount(int aIndex,PMSG_REQ_BLOODCASTLE_ENTERCOUNT * lpMsg);
	void BloodCastleScore_5TH(PMSG_ANS_BLOODCASTLESCORE_5TH * lpMsg);
	void IllusionTempleScore(PMSG_ANS_ILLUSIONTEMPLE_RANKING * lpMsg);
	void ChaosCastleScore(PMSG_ANS_CHAOSCASTLE_RANKING * lpMsg);
	void EGAnsEventChipInfo(int aIndex,PMSG_REQ_VIEW_EC_MN * lpMsg);
	void EGAnsRegEventChipInfo(int aIndex,PMSG_REQ_REGISTER_EVENTCHIP * lpMsg);
	void EGAnsResetEventChip(int aIndex,PMSG_REQ_RESET_EVENTCHIP * lpMsg);
	void EGAnsEventStoneInfo(int aIndex,PMSG_REQ_VIEW_EC_MN * lpMsg);
	void EGAnsRegEventStoneInfo(int aIndex,PMSG_REQ_REGISTER_STONES * lpMsg);
	void EGAnsResetStoneInfo(int aIndex,PMSG_REQ_RESET_EVENTCHIP * lpMsg);
	void EGAns2AnivRegSerial(int aIndex,PMSG_REQ_2ANIV_SERIAL * lpMsg);
	void EGAnsDeleteStones(int aIndex,PMSG_REQ_DELETE_STONES * lpMsg);
	void EGAnsRegCCOfflineGift(int aIndex,PMSG_REQ_REG_CC_OFFLINE_GIFT * lpMsg);
	void EGAnsRegDLOfflineGift(int aIndex,PMSG_REQ_REG_DL_OFFLINE_GIFT * lpMsg);
	void EGAnsRegHTOfflineGift(int aIndex,PMSG_REQ_REG_HT_OFFLINE_GIFT * lpMsg);
	void EGAnsLuckyCoinInfo(int aIndex,PMSG_REQ_LUCKYCOIN * lpMsg);
	void EGAnsRegLuckyCoin(int aIndex,PMSG_REQ_REGISTER_LUCKYCOIN * lpMsg);
	void EGReqSantaCheck(short aIndex, PMSG_REQ_SANTACHECK * aRecv);
	void EGReqSantaGift(short aIndex, PMSG_REQ_SANTAGIFT * aRecv);
	void ReqBanUser(short aIndex, BAN_REQ_USER * aRecv);
	void ReqSecLock(short aIndex, SECLOCK_REQ_SAVE *aRecv);
	void ReqSaveMonsterCount(short aIndex,DS_SAVE_MONSTERCNT * aRecv);
	void ReqSavePlayerKiller(short aIndex,DS_SAVE_PLAYERKILLER * aRecv);
	void GDReqArcaBattleGuildJoin(int aIndex, PMSG_REQ_ARCA_BATTLE_GUILD_JOIN_DS *aRecv);
	void GDReqArcaBattleGuildMemberJoin(int aIndex, PMSG_REQ_ARCA_BATTLE_GUILD_MEMBER_JOIN_DS *aRecv);
	void GDReqArcaBattleEnter(int aIndex, PMSG_REQ_ARCA_BATTLE_ENTER_DS *aRecv);
	void GDReqArcaBattleWinGuildInfoInsert(int aIndex, PMSG_REQ_AB_WIN_GUILD_INFO_INSERT_DS *aRecv);
	void GDReqArcaBattleWinGuildInfo(int aIndex, PMSG_REQ_AB_WIN_GUILD_INFO_DS *aRecv);
	void GDReqDeleteArcaBattleInfo(int aIndex);
	void GDReqArcaBattleProcMultiCast(int aIndex, PMSG_REQ_AB_PROC_INSERT_DS *aRecv);
	void GDReqArcaBattleProcState(int aIndex, PMSG_REQ_AB_PROC_STATE_DS *aRecv);
	void GDReqArcaBattleJoinMemberUnder(int aIndex, PMSG_REQ_AB_JOIN_MEMBER_UNDER_DS *aRecv);
	void GDReqArcaBattleJoinMemberUnderReq(int aIndex, PMSG_REQ_AB_JOIN_CANCEL_DS *aRecv);
	void GDReqArcaBattleRegisteredMemberCnt(int aIndex, PMSG_REQ_AB_REG_MEMBER_CNT_DS *aRecv);
	void GDReqRemoveAllGuildBuffMultiCast(int aIndex, PMSG_REQ_REMOVE_ALL_GUILD_BUFF_DS *aRecv);
	void GDReqArcaBattleMarkCnt(int aIndex, PMSG_REQ_ARCA_BATTLE_MARK_CNT_DS *aRecv);
	void GDReqArcaBattleMarkReg(int aIndex, PMSG_REQ_ARCA_BATTLE_MARK_REG_DS *aRecv);
	void GDReqArcaBattleMarkRank(int aIndex, PMSG_REQ_ARCA_BATTLE_MARK_RANK_DS *aRecv);
	void GDReqArcaBattleMarkRegDel(int aIndex, PMSG_REQ_ARCA_BATTLE_MARK_REG_DEL_DS *aRecv);
	void GDReqArcaBattleIsTopRank(int aIndex, PMSG_REQ_ARCA_BATTLE_IS_TOP_RANK *aRecv);
	void GDReqArcaBattleMarkRegAllDel(int aIndex);
	void GDReqArcaBattleAllGuildMarkCnt(int aIndex);
	void GDReqArcaBattleMarkRegSet(int aIndex, PMSG_REQ_AB_MARK_REG_UPDATE_DS *aRecv);
	void GDReqArcaBattleGuildRegInit(int aIndex, PMSG_REQ_GUILD_REG_INIT *aRecv);
	void GDReqArcaBattleAllJoinUser(int aIndex, PMSG_REQ_AB_ALL_JOIN_USER_DS *aRecv);
	void GDReqGetPentagramJewel(int aIndex, PMSG_REQ_PENTAGRAMJEWEL *lpMsg);
	void GDReqSetPentagramJewel(int aIndex, LPBYTE lpRecv);
	void GDReqDelPentagramJewel(int aIndex, PMSG_DEL_PENTAGRAMJEWEL *lpMsg);
	void GDReqInsertPentagramJewel(int aIndex, PMSG_INSERT_PENTAGRAMJEWEL *lpMsg);
	void GDReqPeriodBuffInsert(int aIndex, PMSG_REQ_PERIODBUFF_INSERT *aRecv);
	void GDReqPeriodBuffDelete(int aIndex, PMSG_REQ_PERIODBUFF_DELETE *aRecv);
	void GDReqPeriodBuffSelect(int aIndex, PMSG_REQ_PERIODBUFF_SELECT *aRecv);
	void GDReqQuestExpInfoLoad(int aIndex, PMSG_REQ_QUESTEXP_INFO *aRecv);
	void GDReqQuestExpInfoSave(int aIndex, LPBYTE lpRecv);
	void GDReqLuckyItemInsert(int aIndex, PMSG_REQ_LUCKYITEM_INSERT* lpMsg);
	void GDReqLuckyItemInsert2nd(int aIndex, PMSG_REQ_LUCKYITEM_INSERT_2ND* lpMsg);
	void GDReqLuckyItemDelete(int aIndex, PMSG_REQ_LUCKYITEM_DELETE* lpMsg);
	void GDReqLuckyItemSelect(int aIndex, PMSG_REQ_LUCKYITEM_SELECT* lpMsg);
	void GDReqChaosCastleFinalSave(int aIndex, PMSG_REQ_SAVE_CCF_RESULT* lpMsg);
	void GDReqChaosCastleFinalPermission(int aIndex, PMSG_REQ_CCF_PERMISSION* lpMsg);
	void GDReqChaosCastleFinalLoad(int aIndex, SDHP_REQ_CCF_RANKING* lpMsg);
	void GDReqChaosCastleFinalRenew(int aIndex, SDHP_RENEW_RANKING* lpMsg);
	void GDReqChaosCastleFinalSendMsgAllSvr(int aIndex, PMSG_SEND_CCF_INFO_ALL_SVR* lpMsg);
	void GDReqLoadMuunInvenItem(int aIndex, SDHP_REQ_DBMUUN_INVEN_LOAD* lpMsg);
	void GDReqSaveMuunInvenItem(int aIndex, SDHP_REQ_DBMUUN_INVEN_SAVE * aRecv);
	void GDReqLoadEventInvenItem(int aIndex, SDHP_REQ_DBEVENT_INVEN_LOAD * aRecv);
	void GDReqSaveEventInvenItem(int aIndex, SDHP_REQ_DBEVENT_INVEN_SAVE * aRecv);
	void GDReqCardInfo(int aIndex, PMSG_REQ_MURUMMY_SELECT_DS * aRecv);
	void GDReqCardInfoInsert(int aIndex, PMSG_REQ_MURUMMY_INSERT_DS * aRecv);
	void GDReqScoreUpdate(int aIndex, PMSG_REQ_MURUMMY_SCORE_UPDATE_DS * aRecv);
	void GDReqCardInfoUpdate(int aIndex, PMSG_REQ_MURUMMY_UPDATE_DS * aRecv);
	void GDReqScoreDelete(int aIndex, PMSG_REQ_MURUMMY_DELETE_DS * aRecv);
	void GDReqSlotInfoUpdate(int aIndex, PMSG_REQ_MURUMMY_SLOTUPDATE_DS * aRecv);
	void GDReqMuRummyInfoUpdate(int aIndex, PMSG_REQ_MURUMMY_INFO_UPDATE_DS * aRecv);
	void GDReqMuRummyDBLog(int aIndex, PMSG_REQ_MURUMMY_LOG_INSERT_DS * aRecv);
	void GDReqMineModifyUPTUserInfo(int aIndex, SDHP_REQ_MINESYSTEM_UPT_USERINFO * aRecv);
	void GDReqMineCheckIsUPTWhenUserConnect(int aIndex, SDHP_REQ_LOAD_MINESYSTEM_UPT_USERINFO * aRecv);
	void GDReqPShopItemValue(int aIndex, PMSG_REQ_PSHOPITEMVALUE_INFO * aRecv);
	void GDAllSavePShopItemValue(int aIndex, PMSG_UPDATE_PSHOPITEMVALUE_INFO * aRecv);
	void GDDelPShopItemValue(int aIndex, PMSG_DEL_PSHOPITEM * aRecv);
	void GDMovePShopItem(int aIndex, PMSG_MOVE_PSHOPITEM * aRecv);
	void GDReqAcheronGuardianProcMultiCast(int aIndex, PMSG_REQ_AE_PLAY_DS * aRecv);
	void GDReqClassDefData(int aIndex);
	void GDReqReBuyItemList(int aIndex, SDHP_REQ_SHOP_REBUY_LIST * aRecv);
	void GDReqReBuyAddItem(int aIndex, SDHP_REQ_SHOP_REBUY_ADD_ITEM * aRecv);
	void GDReqReBuyGetItem(int aIndex, SDHP_REQ_SHOP_REBUY_GET_ITEM * aRecv);
	void GDReqDeleteSoldItem(int aIndex, SDHP_REQ_SHOP_REBUY_DELETE_ITEM * aRecv);
	void GDReqGremoryCaseItemList(int aIndex, _stReqGremoryCaseItemList * aRecv);
	void GDReqGremoryCaseAddItem(int aIndex, _stReqAddItemToGremoryCase * aRecv);
	void GDReqCheckUseItemGremoryCase(int aIndex, _stReqCheckUseItemGremoryCase * aRecv);
	void GDReqGremoryCaseDeleteItem(int aIndex, _stReqDeleteItemFromGremoryCase * aRecv);
	void GDReqUBFCheckIsJoinedUser(int aIndex, PMSG_REQ_UBF_ACCOUNT_USERINFO * aRecv);
	void GDReqUBFJoinUser(int aIndex, PMSG_UBF_REGISTER_ACCOUNT_USER * aRecv);
	void GDReqUBFCopyCharacter(int aIndex, PMSG_UBF_ACCOUNT_USER_COPY * aRecv);
	void GDReqUBFCancelUser(int aIndex, PMSG_UBF_REQ_CANCEL_REGISTER_USER * aRecv);
	void GDReqUBFGetRealName(int aIndex, PMSG_REQ_GET_UBF_REAL_NAME * aRecv);
	void GDReqUBFCopyPetItem(int aIndex, LPBYTE lpRecv);
	void GDReqUBFGetReward(int aIndex, PMSG_REQ_UBF_GET_REWARD * aRecv);
	void GDReqUBFSetGainReward(int aIndex, PMSG_REQ_UBF_SET_RECEIVED_REWARD * aRecv);
	void GDReqUBFSetCCFReward(int aIndex, SDHP_REQ_SET_CCF_WINNER_INFO * aRecv);
	void GDReqUBFSetCCBattleReward(int aIndex, SDHP_REQ_SET_CC_WINNER_INFO_UBF * aRecv);
	void GDReqUBFSetDSFReward(int aIndex, PMSG_REQ_SET_DSF_WINNER_INFO * aRecv);
	void GDReqDSFCanPartyEnter(int aIndex, PMSG_REQ_DSF_CAN_PARTY_ENTER * aRecv);
	void GDReqDSFSavePartyPoint(int aIndex, PMSG_REQ_SAVE_DSF_PARTYPOINT * aRecv);
	void GDReqDSFPartyRankRenew(int aIndex, PMSG_REQ_DSF_PARTYRANKRENEW * aRecv);
	void GDReqDSFGoFinalParty(int aIndex, PMSG_REQ_DSF_GO_FINAL_PARTY * aRecv);
	void GDReqDSFInsertRewardUser(int aIndex, PMSG_REQ_SAVE_DSF_REWARD_USER * aRecv);
	void GDReqDSFGetReward(int aIndex, PMSG_REQ_GET_DSF_REWARD * aRecv);
	void GDReqWishperOtherChannel(int aIndex, PMSG_RECV_CHATDATA_WHISPER * aRecv);
	void GDReqMapSrvGroupServerCount(int aIndex, DSMSG_REQ_SUBSERVER_COUNT * aRecv);
	void DGWhisperResponseRecv(int aIndex, DSMSG_ANS_WHISPER_RESULT * aRecv);
	void DGChaosMachineLogLostItems(int aIndex, DSMSG_CHAOSMACHINE_LOSTITEMS * aRecv);
	void GDDisconnectOtherChannel(int aIndex, PMSG_RECV_DC_OTHER_CHANNEL * aRecv);
	void GDReqEventEntryCount(int aIndex, PMSG_REQ_EVENTENTRY_INFO * aRecv);
	void GDReqEvoMonMaxScore(int aIndex, PMSG_REQ_EVOMON_MAXSCORE * aRecv);
	void GDReqEvoMonSaveScore(int aIndex, PMSG_REQ_SAVE_EVOMON_RESULT * aRecv);

	void DGMuBotOptionRecv(MUBOT_SETTINGS_REQ_SAVE* lpMsg, int aIndex);
	void MuBotSaveOption(char* szName, MUBOT_SETTINGS_REQ_SAVE* lpMsg);
	void GetMuBotData(char* szName, MUBOT_SETTINGS_SEND* lpMsg);

	CQuery m_CharDB;
	CQuery m_AccDB;
	CQuery m_GSDB;
	CQuery m_PetDB;
	CQuery m_CastleDB;
	CQuery m_CrywolfDB;
	CQuery m_PentagramDB;
	CQuery m_EventDB;
	CQuery m_RankingDB;
	CQuery m_ItemShopDB;
	CQuery m_PeriodItemDB;
	CQuery m_CharMiscDB;
	CQuery m_ArcaDB;
	CQuery m_QuestExpDB;
	CQuery m_LuckyItemDB;
	CQuery m_CCFinalDB;
	CQuery m_RummyDB;
	CQuery m_MineDB;
	CQuery m_PShopDB;
	CQuery m_EventInvDB;
	CQuery m_MuunDB;
	CQuery m_OptionDataDB;
	CQuery m_ReBuyDB;
	CQuery m_GremoryCaseDB;
	CQuery m_BattleCoreDB;
	CQuery m_DSFinalDB;
	CQuery m_EvoMonDB;
	CQuery m_Survivor;

public:
	CQuery m_MembStatDB;

private:
	CRITICAL_SECTION m_QuestExpDBCriti;
	CWarehouseUserData m_WareUserData;

	int m_iConnectionCount;
	int m_iItemCount;
};

#endif // !defined(AFX_DSPROTOCOL_H__2BBE1FF8_64DE_46AC_8344_13E7059DCBE3__INCLUDED_)