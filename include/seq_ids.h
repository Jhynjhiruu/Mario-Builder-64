#ifndef SEQ_IDS_H
#define SEQ_IDS_H

// Sometimes a sequence id is represented as one of the below ids (the base id),
// optionally OR'd with SEQ_VARIATION.
#define SEQ_BASE_ID 0x7f
#define SEQ_VARIATION 0x80
#define SEQUENCE_NONE 0xFF

#define SEQ_MENU_GAME_OVER (SEQ_MENU_TITLE_SCREEN | SEQ_VARIATION)

enum SeqId {
    SEQ_SOUND_PLAYER,                 // 0x00
    SEQ_EVENT_CUTSCENE_COLLECT_STAR,  // 0x01
    SEQ_MENU_TITLE_SCREEN,            // 0x02
    SEQ_LEVEL_GRASS,                  // 0x03
    SEQ_LEVEL_INSIDE_CASTLE,          // 0x04
    SEQ_LEVEL_WATER,                  // 0x05
    SEQ_LEVEL_HOT,                    // 0x06
    SEQ_LEVEL_BOSS_KOOPA,             // 0x07
    SEQ_LEVEL_SNOW,                   // 0x08
    SEQ_LEVEL_SLIDE,                  // 0x09
    SEQ_LEVEL_SPOOKY,                 // 0x0A
    SEQ_EVENT_PIRANHA_PLANT,          // 0x0B
    SEQ_LEVEL_UNDERGROUND,            // 0x0C
    SEQ_MENU_STAR_SELECT,             // 0x0D
    SEQ_EVENT_POWERUP,                // 0x0E
    SEQ_EVENT_METAL_CAP,              // 0x0F
    SEQ_EVENT_KOOPA_MESSAGE,          // 0x10
    SEQ_LEVEL_KOOPA_ROAD,             // 0x11
    SEQ_EVENT_HIGH_SCORE,             // 0x12
    SEQ_EVENT_MERRY_GO_ROUND,         // 0x13
    SEQ_EVENT_RACE,                   // 0x14
    SEQ_EVENT_CUTSCENE_STAR_SPAWN,    // 0x15
    SEQ_EVENT_BOSS,                   // 0x16
    SEQ_EVENT_CUTSCENE_COLLECT_KEY,   // 0x17
    SEQ_EVENT_ENDLESS_STAIRS,         // 0x18
    SEQ_LEVEL_BOSS_KOOPA_FINAL,       // 0x19
    SEQ_EVENT_CUTSCENE_CREDITS,       // 0x1A
    SEQ_EVENT_SOLVE_PUZZLE,           // 0x1B
    SEQ_EVENT_TOAD_MESSAGE,           // 0x1C
    SEQ_EVENT_PEACH_MESSAGE,          // 0x1D
    SEQ_EVENT_CUTSCENE_INTRO,         // 0x1E
    SEQ_EVENT_CUTSCENE_VICTORY,       // 0x1F
    SEQ_EVENT_CUTSCENE_ENDING,        // 0x20
    SEQ_MENU_FILE_SELECT,             // 0x21
    SEQ_EVENT_CUTSCENE_LAKITU,        // 0x22 (not in JP)
    SEQ_LEVEL_INSIDE_CASTLE2,         // 0x23
    SEQ_STREAMED_BONEARENA,           // 0x24
    SEQ_FARM,                         // 0x25
    SEQ_PIRATE,                       // 0x26
    SEQ_JUNGLE,                       // 0x27
    SEQ_REDHOT,                       // 0x28
    SEQ_STREAMED_RAIN_OUTSIDE,        // 0x29
    SEQ_STREAMED_RAIN_INSIDE,         // 0x2A
    SEQ_SHOWRUNNER,                   // 0x2B

    SEQ_COSMIC_SEED_COLLECT,          // 0x2C
    SEQ_COSMIC_SEED_LEVEL,            // 0x2D
    SEQ_COSMIC_SEED_BOSS,             // 0x2E

    SEQ_SMB1_OVERWORLD,               // 0x2F
    SEQ_SMB2_OVERWORLD,               // 0x30
    SEQ_SMB3_CASTLE,                  // 0x31
    SEQ_NSMB_CASTLE,                  // 0x32

    SEQ_FINAL_BOSS,                   // 0x33
    SEQ_SHOWRUNNER_BOSS,              // 0x34
    SEQ_BIG_HOUSE,                    // 0x35
    SEQ_LEVEL_KOOPA_ROAD_2,           // 0x36

    SEQ_BK_BUBBLEGLOOP_SWAMP,         // 0x37
    SEQ_BK_GOBI_VALLEY,               // 0x38
    SEQ_BM_BLACK_FORTRESS,            // 0x39
    SEQ_DK64_FRANTIC_FACTORY,         // 0x3A
    SEQ_DK64_HIDEOUT_HELM,            // 0x3B
    SEQ_K64_SHIVER_STAR,              // 0x3C
    SEQ_KSS_RACE,                     // 0x3D
    SEQ_MLPIT_BEHIND_YOSHI_VILLAGE,   // 0x3E
    SEQ_MP_DANGEROUS_GAME,            // 0x3F
    SEQ_NSMB_OVERWORLD,               // 0x40
    SEQ_TTYD_EIGHT_KEY_DOMAIN,        // 0x41
    SEQ_TTYD_ROGUEPORT_SEWERS,        // 0x42
    SEQ_PIKMIN_FOREST_OF_HOPE,        // 0x43
    SEQ_PKMN_SKY_TOWER,               // 0x44

    SEQ_SMB3,                         // 0x45
    SEQ_SMRPG_MARIOS_PAD,             // 0x46
    SEQ_SMRPG_SUNKEN_SHIP,            // 0x47
    SEQ_SMG_BUOY_BASE,                // 0x48
    SEQ_SC_TROPICAL_RESORT,           // 0x49
    SEQ_OOT_LOST_WOODS,               // 0x4A
    SEQ_SMB_BOWSER_REMIX,             // 0x4B
    SEQ_SMG_MELTY_MOLTEN,             // 0x4C
    SEQ_SMG_GUSTY_GARDEN,             // 0x4D
    SEQ_SMW_ATHLETIC,                 // 0x4E
    SEQ_SPM_FLIPSIDE,                 // 0x4F
    SEQ_SPM_FLORO_CAVERNS,            // 0x50
    SEQ_YS_TITLE,                     // 0x51
    SEQ_OOT_GERUDO_VALLEY,            // 0x52
    SEQ_TP_LAKE_HYLIA,                // 0x53

    SEQ_FRAPPE_SNOWLAND,              // 0x54
    SEQ_FOREST_MAZE,                  // 0x55
    SEQ_DK64_GLOOMY_GALLEON,          // 0x56
    SEQ_MK64_BOWSERS_CASTLE,          // 0x57
    SEQ_KOOPA_BEACH,                  // 0x58
    SEQ_MK64_RAINBOW_ROAD,            // 0x59
    SEQ_SAMMER_KINGDOM,               // 0x5A
    SEQ_SMG_PURPLE_COMET,             // 0x5B
    SEQ_SMS_SKY_AND_SEA,              // 0x5C
    SEQ_STONE_TOWER_TEMPLE,           // 0x5D

    SEQ_COUNT
};

#endif // SEQ_IDS_H
