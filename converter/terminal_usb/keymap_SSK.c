/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"
#include "report.h"
#include "print.h"





/* 
 * IBM Terminal keyboard 6110345(122keys)/1392595(102keys)
 * http://geekhack.org/showthread.php?10737-What-Can-I-Do-With-a-Terminal-Model-M
 * http://www.seasip.info/VintagePC/ibm_1391406.html
 *
 * Keymap array:
 *     8 bytes
 *   +---------+
 *  0|         |
 *  :|         | 0x00-0x87
 *  ;|         |
 * 17|         |
 *   +---------+
 */
/*
 * IBM Terminal keyboard 1399625, 101-key
 */

#define KEYMAP_SSK( \
    K08,    K07,K0F,K17,K1F,K27,K2F,K37,K3F,K47,K4F,K56,K5E,  K57,K5F,K62,	\
                                                                          	\
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66,  K67,K6E,K6F,	\
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,K5C,  K64,K65,K6D,	\
    K14,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K5A,				\
    K12,    K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,    K59,      K63,		\
    K11,    K19,            K29,                K39,    K58,  K61,K60,K6A	\
) { \
    { KC_NO,    KC_NO   , KC_NO,    KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_##K07 }, \
    { KC_##K08, KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_NO   , KC_##K11, KC_##K12, KC_NO   , KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_NO   , KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, \
    { KC_NO   , KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_NO   , KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_NO   , KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_NO   , KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_NO   , KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47 }, \
    { KC_NO   , KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F }, \
    { KC_NO   , KC_NO   , KC_##K52, KC_NO   , KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_NO   , KC_##K5E, KC_##K5F }, \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
    { KC_NO   , KC_NO, KC_##K6A, KC_NO, KC_NO, KC_##K6D, KC_##K6E, KC_##K6F }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO   , KC_NO, KC_NO, KC_NO   , KC_NO, KC_NO, KC_NO, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO   , KC_NO, KC_NO,    KC_NO,    KC_NO,   }, \
}


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* 101-key keymaps
 */
    /* 0: default
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
     * `---'   `---------------' `---------------' `---------------' `-----------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa| |Ins|Hom|PgU| |NmL|  /|  *|  -|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|   |
     * |-----------------------------------------------------------| `-----------' |-----------|  +|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |               |  4|  5|  6|   |
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Ctrl|    |Alt |          Space              |Alt |    |Ctrl| |Lef|Dow|Rig| |      0|  .|   |
     * `----'    `---------------------------------------'    `----' `-----------' `---------------'
     */

    // Default 
    KEYMAP_SSK(
     ESC,       F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12,     PSCR,SLCK, BRK,

     GRV,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS, EQL,BSPC,      INS,HOME,PGUP,
     TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,LBRC,RBRC,BSLS,      DEL, END,PGDN,
    CAPS,   A,   S,   D,   F,   G,   H,   J,   K,   L,SCLN,QUOT,      ENT,                    
    LSFT,        Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH,     RSFT,            UP,     
    LCTL,     LALT,                SPC,                    FN0,     RCTL,     LEFT,DOWN,RGHT
    ),

    // Momentary
    KEYMAP_SSK(
     ESC,       F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12,     FN1,FN2,FN3,

     GRV,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS, EQL,BSPC,      INS,HOME,PGUP,
     TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,LBRC,RBRC,BSLS,      DEL, END,PGDN,
    CAPS,   A,   S,   D,   F,   G,   H,   J,   K,   L,SCLN,QUOT,      ENT,                    
    LSFT,        Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH,     RSFT,            UP,     
    LCTL,     LALT,                A,                    TRNS,     RCTL,     LEFT,DOWN,RGHT
    ),    

};

/* id for user defined functions */
enum function_id {
    PROMICRO_RESET,
    PROMICRO_PROGRAM,   
    TEST, 
};

// const action_t PROGMEM fn_actions[] = {    
//     // [0] = ACTION_LAYER_MOMENTARY(1),    
//     [1] = ACTION_FUNCTION(PROMICRO_RESET), 
//     [2] = ACTION_FUNCTION_TAP(PROMICRO_PROGRAM),
//     [3] = ACTION_FUNCTION_TAP(TEST),

// };

const uint8_t PROGMEM fn_layer[] = {
    1,
};


#define PROMICRO_RESET promicro_bootloader_jmp(false)
const uint8_t PROGMEM fn_keycode[] = {
    KC_NO,                  // FN0 
    PROMICRO_PROGRAM,       // FN1 
    PROMICRO_RESET,         // FN2 
    TEST,                   // FN3 
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
        case TEST:
          return (record->event.pressed ?
              MACRO( T(T),T(E),T(S),T(T), END ) :
              MACRO_NONE);
        default:
            break;
    }
}



