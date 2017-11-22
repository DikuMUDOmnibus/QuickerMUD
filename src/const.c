/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik Strfeldt, Tom Madsen, and Katja Nyboe.    *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 **************************************************************************/

/***************************************************************************
 *   ROM 2.4 is copyright 1993-1998 Russ Taylor                            *
 *   ROM has been brought to you by the ROM consortium                     *
 *       Russ Taylor (rtaylor@hypercube.org)                               *
 *       Gabrielle Taylor (gtaylor@hypercube.org)                          *
 *       Brian Moore (zump@rom.org)                                        *
 *   By using this code, you have agreed to follow the terms of the        *
 *   ROM license, in the file Rom24/doc/rom.license                        *
 **************************************************************************/

#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <time.h>
#include "merc.h"
#include "magic.h"
#include "interp.h"


/* item type list */
const struct item_type item_table[] = {
    {ITEM_LIGHT, "light"},
    {ITEM_WEAPON, "weapon"},
    {ITEM_TREASURE, "treasure"},
    {ITEM_ARMOR, "armor"},
    {ITEM_CLOTHING, "clothing"},
    {ITEM_FURNITURE, "furniture"},
    {ITEM_TRASH, "trash"},
    {ITEM_CONTAINER, "container"},
    {ITEM_DRINK_CON, "drink"},
    {ITEM_KEY, "key"},
    {ITEM_FOOD, "food"},
    {ITEM_MONEY, "money"},
    {ITEM_BOAT, "boat"},
    {ITEM_CORPSE_NPC, "npc_corpse"},
    {ITEM_CORPSE_PC, "pc_corpse"},
    {ITEM_FOUNTAIN, "fountain"},
    {ITEM_PROTECT, "protect"},
    {ITEM_MAP, "map"},
    {ITEM_PORTAL, "portal"},
    {ITEM_WARP_STONE, "warp_stone"},
    {ITEM_ROOM_KEY, "room_key"},
    {ITEM_GEM, "gem"},
    {ITEM_JEWELRY, "jewelry"},
    {ITEM_JUKEBOX, "jukebox"},
    {0, NULL}
};


/* weapon selection table */
const struct weapon_type weapon_table[] = {
    {"sword", OBJ_VNUM_SCHOOL_SWORD, WEAPON_SWORD, &gsn_sword},
    {"mace", OBJ_VNUM_SCHOOL_MACE, WEAPON_MACE, &gsn_mace},
    {"dagger", OBJ_VNUM_SCHOOL_DAGGER, WEAPON_DAGGER, &gsn_dagger},
    {"axe", OBJ_VNUM_SCHOOL_AXE, WEAPON_AXE, &gsn_axe},
    {"staff", OBJ_VNUM_SCHOOL_STAFF, WEAPON_SPEAR, &gsn_spear},
    {"flail", OBJ_VNUM_SCHOOL_FLAIL, WEAPON_FLAIL, &gsn_flail},
    {"whip", OBJ_VNUM_SCHOOL_WHIP, WEAPON_WHIP, &gsn_whip},
    {"polearm", OBJ_VNUM_SCHOOL_POLEARM, WEAPON_POLEARM, &gsn_polearm},
    {NULL, 0, 0, NULL}
};



/* wiznet table and prototype for future flag setting */
const struct wiznet_type wiznet_table[] = {
    {"on", WIZ_ON, IM},
    {"prefix", WIZ_PREFIX, IM},
    {"ticks", WIZ_TICKS, IM},
    {"logins", WIZ_LOGINS, IM},
    {"sites", WIZ_SITES, L4},
    {"links", WIZ_LINKS, L7},
    {"newbies", WIZ_NEWBIE, IM},
    {"spam", WIZ_SPAM, L5},
    {"deaths", WIZ_DEATHS, IM},
    {"resets", WIZ_RESETS, L4},
    {"mobdeaths", WIZ_MOBDEATHS, L4},
    {"flags", WIZ_FLAGS, L5},
    {"penalties", WIZ_PENALTIES, L5},
    {"saccing", WIZ_SACCING, L5},
    {"levels", WIZ_LEVELS, IM},
    {"load", WIZ_LOAD, L2},
    {"restore", WIZ_RESTORE, L2},
    {"snoops", WIZ_SNOOPS, L2},
    {"switches", WIZ_SWITCHES, L2},
    {"secure", WIZ_SECURE, L1},
    {NULL, 0, 0}
};

/*
 * Liquid properties.
 * Used in world.obj.
 */
const struct liq_type liq_table[] = {
/*    name            color    proof, full, thirst, food, ssize */
    {"water", "clear", {0, 1, 10, 0, 16}},
    {"beer", "amber", {12, 1, 8, 1, 12}},
    {"red wine", "burgundy", {30, 1, 8, 1, 5}},
    {"ale", "brown", {15, 1, 8, 1, 12}},
    {"dark ale", "dark", {16, 1, 8, 1, 12}},

    {"whisky", "golden", {120, 1, 5, 0, 2}},
    {"lemonade", "pink", {0, 1, 9, 2, 12}},
    {"firebreather", "boiling", {190, 0, 4, 0, 2}},
    {"local specialty", "clear", {151, 1, 3, 0, 2}},
    {"slime mold juice", "green", {0, 2, -8, 1, 2}},

    {"milk", "white", {0, 2, 9, 3, 12}},
    {"tea", "tan", {0, 1, 8, 0, 6}},
    {"coffee", "black", {0, 1, 8, 0, 6}},
    {"blood", "red", {0, 2, -1, 2, 6}},
    {"salt water", "clear", {0, 1, -2, 0, 1}},

    {"coke", "brown", {0, 2, 9, 2, 12}},
    {"root beer", "brown", {0, 2, 9, 2, 12}},
    {"elvish wine", "green", {35, 2, 8, 1, 5}},
    {"white wine", "golden", {28, 1, 8, 1, 5}},
    {"champagne", "golden", {32, 1, 8, 1, 5}},

    {"mead", "honey-colored", {34, 2, 8, 2, 12}},
    {"rose wine", "pink", {26, 1, 8, 1, 5}},
    {"benedictine wine", "burgundy", {40, 1, 8, 1, 5}},
    {"vodka", "clear", {130, 1, 5, 0, 2}},
    {"cranberry juice", "red", {0, 1, 9, 2, 12}},

    {"orange juice", "orange", {0, 2, 9, 3, 12}},
    {"absinthe", "green", {200, 1, 4, 0, 2}},
    {"brandy", "golden", {80, 1, 5, 0, 4}},
    {"aquavit", "clear", {140, 1, 5, 0, 2}},
    {"schnapps", "clear", {90, 1, 5, 0, 2}},

    {"icewine", "purple", {50, 2, 6, 1, 5}},
    {"amontillado", "burgundy", {35, 2, 8, 1, 5}},
    {"sherry", "red", {38, 2, 7, 1, 5}},
    {"framboise", "red", {50, 1, 7, 1, 5}},
    {"rum", "amber", {151, 1, 4, 0, 2}},

    {"cordial", "clear", {100, 1, 5, 0, 2}},
    {NULL, NULL, {0, 0, 0, 0, 0}}
};
