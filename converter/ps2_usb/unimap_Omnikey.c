/*
Copyright 2016 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "unimap_trans.h"

enum function_id {
    PROMICRO_RESET,
    PROMICRO_PROGRAM,    
};

#define AC_PROMICRO_PROGRAM ACTION_FUNCTION(PROMICRO_PROGRAM)
#define AC_PROMICRO_RESET ACTION_FUNCTION(PROMICRO_RESET)

#define AC_L1 ACTION_LAYER_MOMENTARY(1)
#define AC_TM ACTION_MODS_KEY(MOD_LCTL | MOD_LALT,KC_DEL) // CTRL ALT DEL 
#define AC_RWIN ACTION_MODS_KEY(MOD_LGUI | MOD_LCTL, KC_RIGHT) 
#define AC_LWIN ACTION_MODS_KEY(MOD_LGUI | MOD_LCTL, KC_LEFT) 

#define AC_FN0 ACTION_LAYER_MOMENTARY(1)

#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif    
    //Physical
    // [0] = UNIMAP_OMNIKEY(
    // F11,F12,  ESC,                                                           PSCR,SLCK,PAUS,
    // F1, F2,   GRV,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,MINS,EQL,BSPC,     INS, HOME,PGUP,   NLCK,PSLS,PAST,PMNS,
    // F3, F4,   TAB,  Q,  W,  E,  R,  T,  Y,  U,  I,  O,  P,LBRC,RBRC,         DEL,  END,PGDN,   P7,  P8,  P9,
    // F5, F6,   CAPS, A,  S,  D,  F,  G,  H,  J,  K,  L,SCLN,QUOT,    ENT,                       P4,  P5,  P6,  PPLS,
    // F7, F8,   LSFT, Z,  X,  C,  V,  B,  N,  M,COMM, DOT, SLSH,RSFT,BSLS,            UP,        P1,  P2,  P3,  
    // F9,F10,   LCTL,     LALT,         SPC,               RALT,     RCTL,     LEFT,DOWN,RGHT,   P0,     PDOT,  PENT
    // ),      

    //Layer 0 (Base)
    [0] = UNIMAP_OMNIKEY(
    F11,F12,  ESC,                                                           PSCR,SLCK,PAUS,
    F1, F2,   GRV,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,MINS,EQL,BSPC,     INS, HOME,PGUP,   NLCK,PSLS,PAST,PMNS,
    F3, F4,   TAB,  Q,  W,  E,  R,  T,  Y,  U,  I,  O,  P,LBRC,RBRC,         DEL,  END,PGDN,   P7,  P8,  P9,
    F5, F6,   CAPS, A,  S,  D,  F,  G,  H,  J,  K,  L,SCLN,QUOT,    ENT,                       P4,  P5,  P6,  PPLS,
    F7, F8,   LSFT, Z,  X,  C,  V,  B,  N,  M,COMM, DOT, SLSH,RSFT,BSLS,            UP,        P1,  P2,  P3,  
    F9,F10,   LCTL,     LALT,         SPC,               L1,     RCTL,     LEFT,DOWN,RGHT,   P0,     PDOT,  PENT
    ),

    //Layer 1 (BFN0)
    [1] = UNIMAP_OMNIKEY(
    F11,F12,  ESC,                                                           PSCR,PROMICRO_RESET,PROMICRO_PROGRAM,
    F1, F2,   GRV,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,MINS,EQL,BSPC,     INS, HOME,PGUP,   NLCK,PSLS,PAST,PMNS,
    F3, F4,   TAB,  Q,  W,  E,  R,  T,  Y,  U,  I,  O,  P,LBRC,RBRC,         DEL,  END,PGDN,   P7,  P8,  P9,
    F5, F6,   CAPS, A,  S,  D,  F,  G,  H,  J,  K,  L,SCLN,QUOT,    ENT,                       P4,  P5,  P6,  PPLS,
    F7, F8,   LSFT, Z,  X,  C,  V,  B,  N,  M,COMM, DOT, SLSH,RSFT,BSLS,            UP,        P1,  P2,  P3,  
    F9,F10,   LCTL,     LALT,         SPC,               TRNS,     RCTL,     LEFT,DOWN,RGHT,   P0,     PDOT,  PENT
    ),    
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case PROMICRO_RESET:
            promicro_bootloader_jmp(false);
            break;
        case PROMICRO_PROGRAM:
            promicro_bootloader_jmp(true);
            break;
        default:
            break;
    }
}

const action_t PROGMEM fn_actions[] = {
    ACTION_LAYER_MOMENTARY(1), //FN0
};
