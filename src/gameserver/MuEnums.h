#ifndef _MU_MUENUMS_H_
#define _MU_MUENUMS_H_

enum
{
	CS_SERVER_SELECT = 0x03,
	CS_CLIENT_CONNECT = 0x06
};

enum eSERVER_TYPE
{
	ST_NONE = 0,
	ST_JOINSERVER = 1,
	ST_DATASERVER = 2,
	ST_EXDATASERVER = 3,
};

enum eSERVER_STATE
{
	SS_CLOSED,
	SS_CONNECTED,
	SS_LOGGED,
	SS_GUILD,
	SS_CHAT,
};

enum eMasterSkillType
{
	// DK MSKILL
	AT_MSKILL_DK_CYCLONE1 = 326,
	AT_MSKILL_DK_SLASH1 = 327,
	AT_MSKILL_DK_FALLINGSLASH1 = 328,
	AT_MSKILL_DK_LUNGE1 = 329,
	AT_MSKILL_DK_TWISTINGSLASH1 = 330,
	AT_MSKILL_DK_RAGEFULBLOW1 = 331,
	AT_MSKILL_DK_TWISTINGSLASH2 = 332,
	AT_MSKILL_DK_RAGEFULBLOW2 = 333,
	AT_MSKILL_DK_DEATHSTAB1 = 336,
	AT_MSKILL_DK_DEATHSTAB2 = 339,
	AT_MSKILL_DK_DEATHSTAB3 = 342,
	AT_MSKILL_DK_DESTRUCTION1 = 337,
	AT_MSKILL_DK_DESTRUCTION2 = 340,
	AT_MSKILL_DK_BLOODSTORM = 344,
	AT_MSKILL_DK_BLOODSTORM1 = 346,
	AT_MSKILL_DK_DESTRUCTION3 = 343,
	AT_MSKILL_MACE_STRENGTHENER = 350,
	AT_MSKILL_DK_SWELLLIFE1 = 356,
	AT_MSKILL_DK_SWELLLIFE2 = 360,
	AT_MSKILL_DK_SWELLLIFE3 = 363,
	AT_MSKILL_DK_IRONDEFENSE = 632,
	AT_MSKILL_DK_IRONDEFENSE1 = 633,
	// DW MSKILL
	AT_MSKILL_DW_FLAME1 = 378,
	AT_MSKILL_DW_LIGHTNING1 = 379,
	AT_MSKILL_DW_EXPWIZARDRY1 = 380,
	AT_MSKILL_DW_INFERNO1 = 381,
	AT_MSKILL_DW_BLAST1 = 382,
	AT_MSKILL_DW_EXPWIZARDRY2 = 383,
	AT_MSKILL_DW_POISON1 = 384,
	AT_MSKILL_DW_EVILSPIRIT1 = 385,
	AT_MSKILL_DW_DECAY1 = 387,
	AT_MSKILL_DW_HELLFIRE1 = 388,
	AT_MSKILL_DW_ICE1 = 389,
	AT_MSKILL_DW_METEORIT1 = 390,
	AT_MSKILL_DW_ICESTORM1 = 391,
	AT_MSKILL_DW_NOVA1 = 392,
	AT_MSKILL_DW_ICESTORM2 = 393,
	AT_MSKILL_DW_METEORIT2 = 394,
	AT_MSKILL_DW_MANASHIELD1 = 403,
	AT_MSKILL_DW_MANASHIELD2 = 404,
	AT_MSKILL_DW_MANASHIELD3 = 406,
	AT_MSKILL_DW_EARTHPRISON = 495,
	AT_MSKILL_DW_EARTHPRISON1 = 497,
	// FE MSKILL
	AT_MSKILL_FE_HEAL1 = 413,
	AT_MSKILL_FE_TRIPLESHOT1 = 414,
	AT_MSKILL_FE_PENETRATION1 = 416,
	AT_MSKILL_FE_DEFENSEBUFF1 = 417,
	AT_MSKILL_FE_TRIPLESHOT2 = 418,
	AT_MSKILL_FE_ATTACKBUFF1 = 420,
	AT_MSKILL_FE_ATTACKBUFF2 = 422,
	AT_MSKILL_FE_DEFENSEBUFF2 = 423,
	AT_MSKILL_FE_ICEARROW1 = 424,
	AT_MSKILL_FE_CURE = 425,
	AT_MSKILL_FE_PARTYHEAL = 426,
	AT_MSKILL_FE_PARTYHEAL1 = 429,
	AT_MSKILL_FE_POISONARROW = 427,
	AT_MSKILL_FE_POISONARROW1 = 434,
	AT_MSKILL_FE_BLESS = 430,
	AT_MSKILL_FE_BLESS1 = 433,
	AT_MSKILL_FE_MULTISHOT1 = 411,
	AT_MSKILL_FE_MULTISHOT2 = 431,
	AT_MSKILL_FE_SUMMONSATYROS = 432,
	AT_MSKILL_FE_INFINITY1 = 441,
	// SUM MSKILL
	AT_MSKILL_SUM_SLEEP1 = 454,
	AT_MSKILL_SUM_CHAINLIGHTNING1 = 455,
	AT_MSKILL_SUM_LIGHTNSHOCK1 = 456,
	AT_MSKILL_SUM_DRAINLIFE1 = 458,
	AT_MSKILL_SUM_DRAINLIFE2 = 462,
	AT_MSKILL_SUM_WEAKNESS1 = 459,
	AT_MSKILL_SUM_INNOVATION1 = 460,
	AT_MSKILL_SUM_BLIND = 461,
	AT_MSKILL_SUM_BLIND1 = 463,
	AT_MSKILL_SUM_BERSERK1 = 469,
	AT_MSKILL_SUM_BERSERK2 = 470,
	AT_MSKILL_SUM_BERSERK3 = 472,
	// MG MSKILL
	AT_MSKILL_MG_CYCLONE1 = 479,
	AT_MSKILL_MG_LIGHTNING1 = 480,
	AT_MSKILL_MG_TWISTINGSLASH1 = 481,
	AT_MSKILL_MG_POWERSLASH1 = 482,
	AT_MSKILL_MG_FLAME1 = 483,
	AT_MSKILL_MG_BLAST1 = 484,
	AT_MSKILL_MG_INFERNO1 = 486,
	AT_MSKILL_MG_EVILSPIRIT1 = 487,
	AT_MSKILL_MG_ICE1 = 489,
	AT_MSKILL_MG_ICE2 = 491,
	AT_MSKILL_MG_FIRESLASH1 = 490,
	AT_MSKILL_MG_FIRESLASH2 = 493,
	AT_MSKILL_MG_FLAMESTRIKE1 = 492,
	AT_MSKILL_MG_FLAMESTRIKE2 = 494,
	AT_MSKILL_MG_GIGANTICSTORM1 = 496,
	// DL MSKILL
	AT_MSKILL_DL_504 = 504, //Emperor Cape Absorption PowUp
	AT_MSKILL_DL_505 = 505, //Emperor Cape Defense PowUp
	AT_MSKILL_DL_506 = 506, //Adds Command Stat
	AT_MSKILL_DL_507 = 507, //Emperor Cape Attack PowUp
	AT_MSKILL_DL_FIREBURST1 = 508,
	AT_MSKILL_DL_FORCEWAVE1 = 509,
	AT_MSKILL_DL_CRITICALDAMAGE1 = 511,
	AT_MSKILL_DL_EARTHSHAKE1 = 512,
	AT_MSKILL_DL_FIREBURST2 = 514,
	AT_MSKILL_DL_CRITICALDAMAGE2 = 515,
	AT_MSKILL_DL_EARTHSHAKE2 = 516,
	AT_MSKILL_DL_CRITICALDAMAGE3 = 517,
	AT_MSKILL_DL_FIRESCREAM1 = 518,
	AT_MSKILL_DL_ELECTRICSPARK1 = 519,
	AT_MSKILL_DL_FIRESCREAM2 = 520,
	AT_MSKILL_DL_IRONDEFENSE = 521,
	AT_MSKILL_DL_IRONDEFENSE1 = 524,
	AT_MSKILL_DL_CRITICALDAMAGE4 = 522,
	AT_MSKILL_DL_CHAOTICDESEAR1 = 523,
	// DL SKILL 2
	AT_MSKILL_DL_524 = 524, //Iron Defense Strengthener
	AT_MSKILL_DL_526 = 526, //Dark Spirit Strengthener
	AT_MSKILL_DL_527 = 527, //Scepter Strengthener
	AT_MSKILL_DL_528 = 528, //Shield Strengthener
	AT_MSKILL_DL_529 = 529, //Use Scepter : Pet Strengthener
	AT_MSKILL_DL_530 = 530, //Dark Spirit Strengthener (2)
	AT_MSKILL_DL_531 = 531, //Scepter Mastery
	AT_MSKILL_DL_532 = 532, //Shield Mastery
	AT_MSKILL_DL_533 = 533, //Command Attack Increase
	AT_MSKILL_DL_534 = 534, //Dark Spirit Strengthener (3)
	AT_MSKILL_DL_535 = 535, //Pet Durability Strengthener
	AT_MSKILL_DL_536 = 536, //Dark Spirit Strengthener (4)
	AT_MSKILL_DL_538 = 538, //Dark Spirit Strengthener (5)
	AT_MSKILL_DL_539 = 539, //Spirit Lord
	// RF SKILL
	AT_MSKILL_RF_CLOAKABSPOWUP = 548,
	AT_MSKILL_RF_CLOAKDEFPOWUP = 549,
	AT_MSKILL_RF_CLOAKATTAPOWUP = 550,
	AT_MSKILL_RF_KILLBLOW1 = 551,
	AT_MSKILL_RF_KILLBLOW2 = 554,
	AT_MSKILL_RF_UPERCUT1 = 552,
	AT_MSKILL_RF_UPERCUT2 = 555,
	AT_MSKILL_RF_CHAINDRIVE1 = 558,
	AT_MSKILL_RF_CHAINDRIVE2 = 562,
	AT_MSKILL_RF_DARKSIDE1 = 559,
	AT_MSKILL_RF_DARKSIDE2 = 563,
	AT_MSKILL_RF_DRAGONRORE1 = 560,
	AT_MSKILL_RF_DRAGONRORE2 = 561,
	AT_MSKILL_RF_DRAGONSLASH1 = 564,
	AT_MSKILL_RF_DRAGONSLASH2 = 565,
	AT_MSKILL_RF_DEFRATE1 = 569,
	AT_MSKILL_RF_DEFRATE2 = 572,
	AT_MSKILL_RF_FITNESS1 = 573,
	// rf skill 2
	AT_MSKILL_RF_574 = 574, //Defense Switch
	AT_MSKILL_RF_578 = 578, //Durability Reduction (1)
	AT_MSKILL_RF_579 = 579, //Increase PvP Defense Rate
	AT_MSKILL_RF_580 = 580, //Increase Maximum SD
	AT_MSKILL_RF_581 = 581, //Increase Mana Recovery Rate
	AT_MSKILL_RF_582 = 582, //Increase Poison Resistance
	AT_MSKILL_RF_583 = 583, //Durability Reduction (2)
	AT_MSKILL_RF_584 = 584, //Increase SD Recovery Rate
	AT_MSKILL_RF_585 = 585, //Increase HP Recovery Rate
	AT_MSKILL_RF_586 = 586, //Increase Lightning Resistance
	AT_MSKILL_RF_587 = 587, //Increases Defense
	AT_MSKILL_RF_588 = 588, //Increases AG Recovery Rate
	AT_MSKILL_RF_589 = 589, //Increase Ice Resistance
	AT_MSKILL_RF_590 = 590, //Durability Reduction(3)
	AT_MSKILL_RF_591 = 591, //Increase Defense Success Rate
	AT_MSKILL_RF_592 = 592, //Cast Invincibility
	AT_MSKILL_RF_593 = 593, //Increase Set Defense
	AT_MSKILL_RF_594 = 594, //Vengeance
	AT_MSKILL_RF_595 = 595, //Increase Energy
	AT_MSKILL_RF_596 = 596, //Stamina Increases
	AT_MSKILL_RF_597 = 597, //Increase Agility
	AT_MSKILL_RF_598 = 598, //Increase Strength
	AT_MSKILL_RF_599 = 599, //Increase Attack Success Rate
	AT_MSKILL_RF_600 = 600, //Increase Maximum HP
	AT_MSKILL_RF_601 = 601, //Increase Maximum Mana
	AT_MSKILL_RF_602 = 602, //Increase Maximum AG
	AT_MSKILL_RF_603 = 603, //Increase PvP Attack Rate
	AT_MSKILL_RF_604 = 604, //Decrease Mana
	AT_MSKILL_RF_605 = 605, //Recover SD from Monster Kills
	AT_MSKILL_RF_606 = 606, //Recover HP from Monster Kills
	AT_MSKILL_RF_607 = 607, //Increase Minimum Attack Power
	AT_MSKILL_RF_608 = 608, //Recover Mana from Monster Kills
	AT_MSKILL_RF_609 = 609, //Increase Maximum Attack Power
	AT_MSKILL_RF_610 = 610, //Increases Critical DMG Chance
	AT_MSKILL_RF_611 = 611, //Recover Mana Fully
	AT_MSKILL_RF_612 = 612, //Recovers HP Fully
	AT_MSKILL_RF_613 = 613, //Increase Excellent DMG Chance
	AT_MSKILL_RF_614 = 614, //Increase Double Damage Chance
	AT_MSKILL_RF_615 = 615, //Increase Ignore Def Chance
	AT_MSKILL_RF_616 = 616, //Recovers SD Fully
	AT_MSKILL_RF_617 = 617, //Increase Triple Damage Chance
	AT_MSKILL_ILLUSION = 642, // Illusion
	AT_MSKILL_RF_677 = 677, //Shield Block
	AT_MSKILL_RF_678 = 678, //Weapon Block
	AT_MSKILL_RF_679 = 679, //Protection Shield
	AT_MSKILL_RF_680 = 680, //Steel Armor
	AT_MSKILL_RF_681 = 681, //Strong Mind
	AT_MSKILL_RF_682 = 682, //Absorb Life
	AT_MSKILL_RF_683 = 683, //Absorb Shield
	// LANCER SKILL
	AT_MSKILL_GL_684 = 684, //Cloak of Transcendence Absorption PowUp
	AT_MSKILL_GL_685 = 685, //Cloak of Transcendence Defense PowUp
	AT_MSKILL_GL_686 = 686, //Cloak of Transcendence Attack PowUp
	AT_MSKILL_GL_687 = 687, //Spin Step PowUpHarsh Strike PowUp
	AT_MSKILL_GL_688 = 688, //Harsh Strike PowUp
	AT_MSKILL_GL_689 = 689, //Weapon Mastery
	AT_MSKILL_GL_690 = 690, //Spin Step Mastery
	AT_MSKILL_GL_691 = 691, //Harsh Strike Mastery
	AT_MSKILL_GL_692 = 692, //Magic Pin PowUp
	AT_MSKILL_OBSIDIAN_POWUP = 693, //Obsidian PowUp
	AT_MSKILL_GL_694 = 694, //Magic Pin Proficiency
	AT_MSKILL_GL_695 = 695, //Magic Pin Mastery
	AT_MSKILL_GL_696 = 696, //Breche PowUp
	AT_MSKILL_GL_697 = 697, //Breche Proficiency
	AT_MSKILL_GL_698 = 698, //Breche Mastery
	AT_MSKILL_GL_699 = 699, //Shining Peak PowUp
	AT_MSKILL_BURST = 700, //Burst
	AT_MSKILL_BURST_POWUP = 701, //Burst PowUp
	AT_MSKILL_GL_702 = 702, //Lance PowUp
	AT_MSKILL_CIRCLE_SHIELD_POWUP = 703, //Circle Shield PowUp
	AT_MSKILL_GL_704 = 704, //Shield PowUp
	AT_MSKILL_GL_705 = 705, //Lance Mastery
	AT_MSKILL_CIRCLE_SHIELD_MASTERY = 706, //Circle Shield Mastery
	AT_MSKILL_GL_707 = 707, //Shield Mastery
	AT_MSKILL_WRATH_POWUP = 708, //Wrath PowUp
	AT_MSKILL_WRATH_PROFICIENCY = 709, //Wrath Proficiency
	AT_MSKILL_WRATH_MASTERY = 710, //Wrath Mastery
	AT_MSKILL_GL_711 = 711, //Increases Retaliation DMG
	AT_MSKILL_GL_712 = 712, //Increases Rage DMG
	AT_MSKILL_GL_713 = 713, //Shield Block
	AT_MSKILL_GL_714 = 714, //Weapon Block
	AT_MSKILL_GL_715 = 715, //Protection Shield
	AT_MSKILL_GL_716 = 716, //Steel Armor
	AT_MSKILL_GL_717 = 717, //Strong Mind
	AT_MSKILL_GL_718 = 718, //Absorb Life
	AT_MSKILL_GL_719 = 719, //Absorb Shield
	// skills
	AT_MSKILL_GL_720 = 720, //Immune I
	AT_MSKILL_GL_721 = 721, //Immune II
	AT_MSKILL_GL_722 = 722, //Berserker I
};


enum COMMON_EXC_OPTIONS
{
	OPTION_INC_MANA_MONSTER_DIE = 0,
	OPTION_INC_LIFE_MONSTER_DIE = 1,
	OPTION_INC_ATTACK_SPEED = 2,
	OPTION_INC_ATTACK_PERCENT = 3,
	OPTION_INC_ATTACK_LEVEL = 4,
	OPTION_INC_EXCELLENT_DAMAGE = 5,
	OPTION_INC_ZEN_MONSTER_DIE = 6,
	OPTION_INC_DEFENSE_RATE = 7,
	OPTION_INC_DAMAGE_REFLECT = 8,
	OPTION_DEC_VICTIM_DAMAGE = 9,
	OPTION_INC_MAXIMUM_MANA = 10,
	OPTION_INC_MAXIMUM_LIFE = 11
};

enum EXC_OPTION_OPERATORS
{
	EXC_OPERATOR_NORMAL = 1,
	EXC_OPERATOR_PERCENT = 2,
	EXC_OPERATOR_DIVIDE_BY_LEVEL_20 = 3,
	EXC_OPERATOR_DIVIDE_BY_LIFE = 4,
	EXC_OPERATOR_DIVIDE_BY_MANA = 5,
	EXC_OPERATOR_INC_PER_LEVEL = 6,
	EXC_OPERATOR_FORMULA = 100
};

enum EXC_OPTION_EFFECTS
{
	EXC_EFFECT_ETC = 0,
	EXC_EFFECT_RATE = 1,
	EXC_EFFECT_ATTACK = 2,
	EXC_EFFECT_DEFENSE = 3,
	EXC_EFFECT_LIFE = 4,
	EXC_EFFECT_MANA = 5,
	EXC_EFFECT_SKILL = 6
};


enum eJewelOfHarmonySystem_ItemType {
	JEWELOFHARMONY_ITEM_TYPE_NULL = 0x0,
	JEWELOFHARMONY_ITEM_TYPE_WEAPON = 0x1,
	JEWELOFHARMONY_ITEM_TYPE_STAFF = 0x2,
	JEWELOFHARMONY_ITEM_TYPE_DEFENSE = 0x3,
};

enum eJewelOfHarmonyItemOption {
	AT_JEWELOFHARMONY_NOT_STRENGTHEN_ITEM = 0x0,
	AT_JEWELOFHARMONY_WEAPON_IMPROVE_MINATTACKDAMAGE = 0x1,
	AT_JEWELOFHARMONY_WEAPON_IMPROVE_MAXATTACKDAMAGE = 0x2,
	AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_STR = 0x3,
	AT_JEWELOFHARMONY_WEAPON_DECREASE_REQUIRE_DEX = 0x4,
	AT_JEWELOFHARMONY_WEAPON_IMPROVE_ATTACKDAMAGE_BOTH = 0x5,
	AT_JEWELOFHARMONY_WEAPON_IMPROVE_CRITICALDAMAGE = 0x6,
	AT_JEWELOFHARMONY_WEAPON_IMPROVE_SKILLDAMAGE = 0x7,
	AT_JEWELOFHARMONY_WEAPON_IMPROVE_ATTACKSUCCESRATE_PVP = 0x8,
	AT_JEWELOFHARMONY_WEAPON_DECREASE_SD_RATE = 0x9,
	AT_JEWELOFHARMONY_WEAPON_IMPROVE_IGNORE_SD_RATE = 0xa,
	AT_JEWELOFHARMONY_STAFF_IMPROVE_MAGICDAMAGE = 0x1,
	AT_JEWELOFHARMONY_STAFF_DECREASE_REQUIRE_STR = 0x2,
	AT_JEWELOFHARMONY_STAFF_DECREASE_REQUIRE_DEX = 0x3,
	AT_JEWELOFHARMONY_STAFF_IMPROVE_SKILLDAMAGE = 0x4,
	AT_JEWELOFHARMONY_STAFF_IMPROVE_CRITICALDAMAGE = 0x5,
	AT_JEWELOFHARMONY_STAFF_DECREASE_SD_RATE = 0x6,
	AT_JEWELOFHARMONY_STAFF_IMPROVE_ATTACKSUCCESRATE_PVP = 0x7,
	AT_JEWELOFHARMONY_STAFF_IMPROVE_IGNORE_SD_RATE = 0x8,
	AT_JEWELOFHARMONY_DEFENSE_IMPROVE_DEFENSE = 0x1,
	AT_JEWELOFHARMONY_DEFENSE_IMPROVE_MAX_AG = 0x2,
	AT_JEWELOFHARMONY_DEFENSE_IMPROVE_MAX_HP = 0x3,
	AT_JEWELOFHARMONY_DEFENSE_IMPROVE_AUTO_REFILL_HP = 0x4,
	AT_JEWELOFHARMONY_DEFENSE_IMPROVE_AUTO_REFILL_MP = 0x5,
	AT_JEWELOFHARMONY_DEFENSE_IMPROVE_BLOCKSUCCESRATE_PVP = 0x6,
	AT_JEWELOFHARMONY_DEFENSE_IMPROVE_DAMAGE_DECREASE = 0x7,
	AT_JEWELOFHARMONY_DEFENSE_IMPROVE_SD_RATE = 0x8,
};


enum GREMORYCASE_STORAGE_TYPE
{
	GC_STORAGE_SERVER = 1,
	GC_STORAGE_CHARACTER = 2
};

enum GREMORYCASE_REWARD_SOURCES
{
	GC_REWARD_CHAOS_CASTLE = 1,
	GC_REWARD_BLOOD_CASTLE = 2,
	GC_REWARD_ILLUSION_TEMPLE = 3,
	GC_REWARD_DOPPELGANGER = 4,
	GC_REWARD_CHAOS_CASTLE_SURVIVAL = 5,
	GC_REWARD_TORMENTED_SQUARE = 6,
	GC_REWARD_ILLUSION_TEMPLE_LEAGUE = 7,
	GC_REWARD_CHAOS_CASTLE_SURVIVAL_2 = 8,
	GC_REWARD_TORMENTED_SQUARE_LEAGUE = 9,
	GC_REWARD_CHAOS_CASTLE_UBF = 10,
	GC_REWARD_TORMENTED_SQUARE_UBF = 11,
	GC_REWARD_EVOMON = 12,
	GC_REWARD_DEVIL_SQUARE = 13,
	GC_REWARD_IMPERIAL_FORT = 14,
	GC_REWARD_PENTAGRAM_UNKNOWN = 15,
	GC_REWARD_PENTAGRAM_MIX = 16,
	GC_REWARD_GM_REWARD = 100
};

enum GREMORYCASE_MESSAGE_CODES
{
	GC_MESSAGE_ITEM_SENT_TO_STORAGE = 0,
	GC_MESSAGE_ITEM_RECEIVED_TO_INVENTORY = 1,
	GC_MESSAGE_ERROR_1 = 2,
	GC_MESSAGE_ERROR_2 = 3,
	GC_MESSAGE_ITEM_WILL_EXPIRE_SOON = 4,
	GC_MESSAGE_STORAGE_NEARLY_FULL = 5,
	GC_MESSAGE_FULL_NOTICE = 6,
	GC_MESSAGE_MUUN_INVENTORY_FULL = 7,
	GC_MESSAGE_EVENT_INVENTORY_FULL = 8,
	GC_MESSAGE_NORMAL_INVENTORY_FULL = 9,
	GC_MESSAGE_HOLDING_ALREADY_ITEM = 10,
	GC_MESSAGE_NO_DATA_ERROR = 11,
	GC_MESSAGE_DB_ERROR = 12,
	GC_MESSAGE_INVENTORY_FULL = 13,
	GC_MESSAGE_CLOSING_GC_WINDOW = 14
};

enum MAP_INDEX
{
	MAP_INDEX_EMPTY = -1,
	MAP_INDEX_RORENCIA = 0x0,
	MAP_INDEX_DUNGEON = 0x1,
	MAP_INDEX_DEVIAS = 0x2,
	MAP_INDEX_NORIA = 0x3,
	MAP_INDEX_LOSTTOWER = 0x4,
	MAP_INDEX_RESERVED = 0x5,
	MAP_INDEX_ARENA = 0x6,
	MAP_INDEX_ATHLANSE = 0x7,
	MAP_INDEX_TARKAN = 0x8,
	MAP_INDEX_DEVILSQUARE = 0x9,
	MAP_INDEX_ICARUS = 0xa,
	MAP_INDEX_BLOODCASTLE1 = 0xb,
	MAP_INDEX_BLOODCASTLE2 = 0xc,
	MAP_INDEX_BLOODCASTLE3 = 0xd,
	MAP_INDEX_BLOODCASTLE4 = 0xe,
	MAP_INDEX_BLOODCASTLE5 = 0xf,
	MAP_INDEX_BLOODCASTLE6 = 0x10,
	MAP_INDEX_BLOODCASTLE7 = 0x11,
	MAP_INDEX_CHAOSCASTLE1 = 0x12,
	MAP_INDEX_CHAOSCASTLE2 = 0x13,
	MAP_INDEX_CHAOSCASTLE3 = 0x14,
	MAP_INDEX_CHAOSCASTLE4 = 0x15,
	MAP_INDEX_CHAOSCASTLE5 = 0x16,
	MAP_INDEX_CHAOSCASTLE6 = 0x17,
	MAP_INDEX_KALIMA1 = 0x18,
	MAP_INDEX_KALIMA2 = 0x19,
	MAP_INDEX_KALIMA3 = 0x1a,
	MAP_INDEX_KALIMA4 = 0x1b,
	MAP_INDEX_KALIMA5 = 0x1c,
	MAP_INDEX_KALIMA6 = 0x1d,
	MAP_INDEX_CASTLESIEGE = 0x1e,
	MAP_INDEX_CASTLEHUNTZONE = 0x1f,
	MAP_INDEX_DEVILSQUARE2 = 0x20,
	MAP_INDEX_AIDA = 0x21,
	MAP_INDEX_CRYWOLF_FIRSTZONE = 0x22,
	MAP_INDEX_CRYWOLF_SECONDZONE = 0x23,
	MAP_INDEX_KALIMA7 = 0x24,
	MAP_INDEX_KANTURU1 = 0x25,
	MAP_INDEX_KANTURU2 = 0x26,
	MAP_INDEX_KANTURU_BOSS = 0x27,
	MAP_INDEX_GAMEMASTER_MAP = 0x28, //0x28 OK
	MAP_INDEX_BARRACKS = 0x29, //0x29 OK
	MAP_INDEX_REFUGEE = 0x2a, //0x2a OK
	MAP_INDEX_ILLUSIONTEMPLE1 = 0x2d, //0x2d OK
	MAP_INDEX_ILLUSIONTEMPLE2 = 0x2e, //0x2e OK
	MAP_INDEX_ILLUSIONTEMPLE3 = 0x2f, //0x32 OK
	MAP_INDEX_ILLUSIONTEMPLE4 = 0x30, //0x30 OK
	MAP_INDEX_ILLUSIONTEMPLE5 = 0x31, //0x31 OK
	MAP_INDEX_ILLUSIONTEMPLE6 = 0x32, //0x32 OK
	MAP_INDEX_ELBELAND = 0x33, // 0x33 OK
	MAP_INDEX_BLOODCASTLE8 = 0x34,
	MAP_INDEX_CHAOSCASTLE7 = 0x35,
	MAP_INDEX_CALMNESS = 0x38,
	MAP_INDEX_RAKLION = 0x39,
	MAP_INDEX_HATCHERY = 0x3A,
	MAP_INDEX_SANTAVILLAGE = 0x3E,
	MAP_INDEX_VULCAN = 0x3F,
	MAP_INDEX_VULCANROOM = 0x40,
	MAP_INDEX_DOUBLE_GOER1 = 0x41,
	MAP_INDEX_DOUBLE_GOER2 = 0x42,
	MAP_INDEX_DOUBLE_GOER3 = 0x43,
	MAP_INDEX_DOUBLE_GOER4 = 0x44,
	MAP_INDEX_IMPERIAL1 = 0x45,
	MAP_INDEX_IMPERIAL2 = 0x46,
	MAP_INDEX_IMPERIAL3 = 0x47,
	MAP_INDEX_IMPERIAL4 = 0x48,
	MAP_INDEX_LORENMARKET = 0x4f,
	MAP_INDEX_KALRUTAN1 = 0x50,
	MAP_INDEX_KALRUTAN2 = 0x51,

	MAP_INDEX_DOPPELGANGER1 = 0x52,
	MAP_INDEX_DOPPELGANGER2 = 0x53,
	MAP_INDEX_DOPPELGANGER3 = 0x54,
	MAP_INDEX_DOPPELGANGER4 = 0x55,

	MAP_INDEX_ACHERON = 0x5b,
	MAP_INDEX_ARCA_WAR = 0x5c,
	MAP_INDEX_DEBENTER = 0x5F,
	MAP_INDEX_DEBENTER_ARCA_WAR = 0x60,
	MAP_INDEX_CHAOSCASTLE_SURVIVAL = 0x61,
	MAP_INDEX_ILLUSIONTEMPLE7 = 0x62,
	MAP_INDEX_ILLUSIONTEMPLE8 = 0x63,
	MAP_INDEX_URUK_MOUNTAIN = 0x64,
	MAP_INDEX_URUK_MOUNTAIN_ARCA_WAR = 0x65,
	MAP_INDEX_DEVILSQUARE_FINAL = 0x66,
	MAP_INDEX_TORMENTED_SQUARE1 = 103,
	MAP_INDEX_TORMENTED_SQUARE2 = 104,
	MAP_INDEX_TORMENTED_SQUARE3 = 105,
	MAP_INDEX_TORMENTED_SQUARE4 = 106,
	MAP_INDEX_NARS = 110,
	MAP_INDEX_FEREA = 112,
	MAP_INDEX_NIXIE_LAKE = 113
};

enum EVENT_NOTIFICATION
{
	EVENT_NOTIFICATION_CHAOS_CASTLE = 1,
	EVENT_NOTIFICATION_BLOOD_CASTLE = 2,
	EVENT_NOTIFICATION_DEVIL_SQUARE = 3,
	EVENT_NOTIFICATION_ILLUSION_TEMPLE = 6,
	EVENT_NOTIFICATION_DOPPELGANGER = 7,
	EVENT_NOTIFICATION_MAX,
};

enum EXP_GETTING_EVENT_TYPE {
	EVENT_TYPE_NONE = 0x0,
	EVENT_TYPE_PARTY = 0x1,
	EVENT_TYPE_DEVILSQUARE = 0x2,
	EVENT_TYPE_CHAOSCASTLE = 0x3,
	EVENT_TYPE_BLOODCASTLE = 0x4,
	EVENT_TYPE_CRYWOLF = 0x5,
	EVENT_TYPE_ILLUSIONTEMPLE = 0x6,
};

enum WING_CHECK_FLAG
{
	WCF_ITEMNUMBER = 100,
	WCF_ITEMTYPE = 101,
};

enum WING_TYPE
{
	NONE_WING = 10,
	FIRST_WING = 11,
	SECOND_WING = 12,
	THIRD_WING = 13,
	LITTLE_WING = 14,
	MONSTER_WRING = 15,
	CHAOSCASTLE_WING = 16,
	GOODANDDEVIL_WING = 17,
};

enum EVENTENTRY_TYPE
{
	EVENT_ENTRY_BC = 0,
	EVENT_ENTRY_CC = 1,
	EVENT_ENTRY_DS = 2,
	EVENT_ENTRY_DG = 3,
	EVENT_ENTRY_IF = 4,
	EVENT_ENTRY_IT = 5,
};


enum NPC_TYPES
{
	NPC_NONE = 0,
	NPC_SHOP = 1,
	NPC_WAREHOUSE = 2,
	NPC_CHAOSMIX = 3,
	NPC_GOLDARCHER = 4,
	NPC_PENTAGRAMMIX = 5,
};

enum GM_SYSTEM_FLAGS
{
	GM_EVENT_MODIFY = 0x01,
	GM_COMMAND_FIRECRACKER = 0x02,
	GM_COMMAND_DC_MOVE = 0x04,
	GM_COMMAND_GUILD = 0x08,
	GM_COMMAND_BATTLESOCCER = 0x10,
	GM_COMMAND_ITEM_CREATE = 0x20,
	GM_COMMAND_PK_MODIFY = 0x40,
	GM_COMMAND_INVISIBLE = 0x80,
	GM_COMMAND_SKIN = 0x100,
	GM_COMMAND_BAN = 0x200,
	GM_USE_GMSHOP = 0x400,
	GM_MONSTERS_INVISIBLE = 0x800
};

enum DISABLE_MSB_DAMAGE_EFFECT
{
	MSB_DISABLE_MONSTER = 0,
	MSB_DISABLE_CHARACTER = 1,
	MSB_DISABLE_CHARACTER_FENRIR = 2
};

enum SERVER_TYPE
{
	SERVER_NORMAL = 0,
	SERVER_CASTLE = 1,
	SERVER_ARCA = 2,
	SERVER_BATTLECORE = 3
};

enum MU_EVENT_TABLE
{
	EV_TABLE_BC = 0,
	EV_TABLE_DS = 1,
	EV_TABLE_CC = 2,
	EV_TABLE_IT = 3,
	EV_TABLE_CS = 4,
	EV_TABLE_DEEP = 5,
	EV_TABLE_CW = 6,
	EV_TABLE_KANTURU = 7,
	EV_TABLE_RAKLION = 8,
	EV_TABLE_DG = 9,
	EV_TABLE_IF = 10,
	EV_TABLE_RING = 11,
	EV_TABLE_XMAS = 12,
	EV_TABLE_ARCA = 13,
	EV_TABLE_ACHERON = 14,
	EV_TABLE_CCF = 15,
	EV_TABLE_DSF = 16,
	EV_TABLE_LMS = 17
};

enum eCustomEventDropState
{
	CUSTOM_EVENT_DROP_STATE_BLANK = 0,
	CUSTOM_EVENT_DROP_STATE_EMPTY = 1,
	CUSTOM_EVENT_DROP_STATE_START = 2,
};


#endif
