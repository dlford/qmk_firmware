/*
Copyright 2023 @dlford

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

#include QMK_KEYBOARD_H
#include "dlford.h"
#include "mouse_jiggler.h"
#include "sarcasm_mode.h"
#include "custom_random_password.h"

enum combo_events {
#ifdef CAPS_WORD_ENABLE
    CAPS_COMBO,
    CAPS2_COMBO,
#endif // CAPS_WORD_ENABLE
    QW_ESC_COMBO,
    OP_BSPC_COMBO,
    YSEMI_BSPC_COMBO,
    ZX_EXIT_COMBO,
    SA_SCSM_COMBO,
    RA_SCSM_COMBO,
    KM_KEYMAP_COMBO,
    KM_KEYMAP2_COMBO,
    PW_RAND_COMBO,
    PW_RAND2_COMBO,
    LSEMI_DEL_COMBO,
    IO_DEL_COMBO,
    DOTSLASH_JIGGLE_COMBO,
    CX_COLEMAK_COMBO,
    BR_WRAP_COMBO,
    BR_WRAP_SEMI_COMBO,
    CBR_WRAP_COMBO,
    CBR_WRAP_SEMI_COMBO,
    PRN_WRAP_COMBO,
    PRN_WRAP_SEMI_COMBO,
    ANG_WRAP_COMBO,
    ANG_WRAP_SEMI_COMBO,
    FAT_ARROW_COMBO,
    FAT_ARROW2_COMBO,
    SKINNY_ARROW_COMBO,
    SKINNY_ARROW2_COMBO,
    COMBO_LENGTH,
};

uint16_t COMBO_LEN = COMBO_LENGTH;

#ifdef CAPS_WORD_ENABLE
const uint16_t PROGMEM caps_combo[]  = {LSFT_F, RSFT_J, COMBO_END};
const uint16_t PROGMEM caps2_combo[] = {_LSFT_T, RSFT_N, COMBO_END};
#endif // CAPS_WORD_ENABLE
const uint16_t PROGMEM qw_esc_combo[]          = {CSA_Q, CA_W, COMBO_END};
const uint16_t PROGMEM op_bspc_combo[]         = {CA_O, CSA_P, COMBO_END};
const uint16_t PROGMEM ysemi_bspc_combo[]      = {CA_Y, CSA_SCLN, COMBO_END};
const uint16_t PROGMEM zx_exit_combo[]         = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM sa_scsm_combo[]         = {LGUI_A, LALT_S, COMBO_END};
const uint16_t PROGMEM ra_scsm_combo[]         = {LGUI_A, LALT_R, COMBO_END};
const uint16_t PROGMEM km_keymap_combo[]       = {RCTL_K, KC_M, COMBO_END};
const uint16_t PROGMEM km_keymap2_combo[]      = {KC_K, KC_M, COMBO_END};
const uint16_t PROGMEM pw_rand_combo[]         = {CSA_P, CA_W, COMBO_END};
const uint16_t PROGMEM pw_rand2_combo[]        = {KC_P, CA_W, COMBO_END};
const uint16_t PROGMEM lsemi_del_combo[]       = {RALT_L, RGUI_SCLN, COMBO_END};
const uint16_t PROGMEM io_del_combo[]          = {RALT_I, RGUI_O, COMBO_END};
const uint16_t PROGMEM dotslash_jiggle_combo[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM cx_colemak_combo[]      = {KC_C, KC_X, COMBO_END};
const uint16_t PROGMEM br_wrap_combo[]         = {LCTL_LBRC, LSFT_RBRC, COMBO_END};
const uint16_t PROGMEM br_wrap_semi_combo[]    = {LCTL_LBRC, LSFT_RBRC, RGUI_QUOT, COMBO_END};
const uint16_t PROGMEM cbr_wrap_combo[]        = {KC_LCBR, KC_RCBR, COMBO_END};
const uint16_t PROGMEM cbr_wrap_semi_combo[]   = {KC_LCBR, KC_RCBR, RGUI_QUOT, COMBO_END};
const uint16_t PROGMEM prn_wrap_combo[]        = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM prn_wrap_semi_combo[]   = {KC_LPRN, KC_RPRN, RGUI_QUOT, COMBO_END};
const uint16_t PROGMEM ang_wrap_combo[]        = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM ang_wrap_semi_combo[]   = {KC_COMM, KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM fat_arrow_combo[]       = {RCTL_K, KC_DOT, COMBO_END};
const uint16_t PROGMEM fat_arrow2_combo[]      = {RCTL_E, KC_DOT, COMBO_END};
const uint16_t PROGMEM skinny_arrow_combo[]    = {RSFT_J, KC_DOT, COMBO_END};
const uint16_t PROGMEM skinny_arrow2_combo[]   = {RSFT_N, KC_DOT, COMBO_END};

combo_t key_combos[] = {
#ifdef CAPS_WORD_ENABLE
    [CAPS_COMBO]  = COMBO_ACTION(caps_combo),
    [CAPS2_COMBO] = COMBO_ACTION(caps2_combo),
#endif // CAPS_WORD_ENABLE
    [QW_ESC_COMBO]          = COMBO_ACTION(qw_esc_combo),
    [OP_BSPC_COMBO]         = COMBO_ACTION(op_bspc_combo),
    [YSEMI_BSPC_COMBO]      = COMBO_ACTION(ysemi_bspc_combo),
    [ZX_EXIT_COMBO]         = COMBO_ACTION(zx_exit_combo),
    [SA_SCSM_COMBO]         = COMBO_ACTION(sa_scsm_combo),
    [RA_SCSM_COMBO]         = COMBO_ACTION(ra_scsm_combo),
    [KM_KEYMAP_COMBO]       = COMBO_ACTION(km_keymap_combo),
    [KM_KEYMAP2_COMBO]      = COMBO_ACTION(km_keymap2_combo),
    [PW_RAND_COMBO]         = COMBO_ACTION(pw_rand_combo),
    [PW_RAND2_COMBO]        = COMBO_ACTION(pw_rand2_combo),
    [LSEMI_DEL_COMBO]       = COMBO_ACTION(lsemi_del_combo),
    [IO_DEL_COMBO]          = COMBO_ACTION(io_del_combo),
    [DOTSLASH_JIGGLE_COMBO] = COMBO_ACTION(dotslash_jiggle_combo),
    [CX_COLEMAK_COMBO]      = COMBO_ACTION(cx_colemak_combo),
    [BR_WRAP_COMBO]         = COMBO_ACTION(br_wrap_combo),
    [BR_WRAP_SEMI_COMBO]    = COMBO_ACTION(br_wrap_semi_combo),
    [CBR_WRAP_COMBO]        = COMBO_ACTION(cbr_wrap_combo),
    [CBR_WRAP_SEMI_COMBO]   = COMBO_ACTION(cbr_wrap_semi_combo),
    [PRN_WRAP_COMBO]        = COMBO_ACTION(prn_wrap_combo),
    [PRN_WRAP_SEMI_COMBO]   = COMBO_ACTION(prn_wrap_semi_combo),
    [ANG_WRAP_COMBO]        = COMBO_ACTION(ang_wrap_combo),
    [ANG_WRAP_SEMI_COMBO]   = COMBO_ACTION(ang_wrap_semi_combo),
    [FAT_ARROW_COMBO]       = COMBO_ACTION(fat_arrow_combo),
    [FAT_ARROW2_COMBO]      = COMBO_ACTION(fat_arrow2_combo),
    [SKINNY_ARROW_COMBO]    = COMBO_ACTION(skinny_arrow_combo),
    [SKINNY_ARROW2_COMBO]   = COMBO_ACTION(skinny_arrow2_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
#ifdef CAPS_WORD_ENABLE
        case CAPS_COMBO:
        case CAPS2_COMBO:
            if (pressed) {
                caps_word_on();
            }
            break;
#endif // CAPS_WORD_ENABLE
        case QW_ESC_COMBO:
            if (pressed) {
                tap_code(KC_ESC);
            }
            break;
        case OP_BSPC_COMBO:
        case YSEMI_BSPC_COMBO:
            if (pressed) {
                tap_code(KC_BSPC);
            }
            break;
        case ZX_EXIT_COMBO:
            if (pressed) {
                SEND_STRING("exit");
                tap_code(KC_ENT);
            }
            break;
        case SA_SCSM_COMBO:
        case RA_SCSM_COMBO:
            if (pressed) {
                is_scsm_active = !is_scsm_active;
#ifdef RGB_MATRIX_ENABLE
                // trigger RGB layer change
                layer_on(_MOUSE);
                layer_off(_MOUSE);
#endif // RGB_MATRIX_ENABLE
                if (!is_scsm_active && host_keyboard_led_state().caps_lock) {
                    tap_code(KC_CAPS);
                }
            }
            break;
        case KM_KEYMAP_COMBO:
        case KM_KEYMAP2_COMBO:
            // TODO: Make this adjustable?
            if (pressed) {
                SEND_STRING("https://raw.githubusercontent.com/dlford/qmk_firmware/dlford/keyboards/crkbd/keymaps/dlford/legends.svg");
            }
            break;
        case PW_RAND_COMBO:
        case PW_RAND2_COMBO:
            if (pressed) {
                gen_random_password();
                SEND_STRING(random_password);
            }
            break;
        case LSEMI_DEL_COMBO:
        case IO_DEL_COMBO:
            if (pressed) {
                tap_code(KC_DEL);
            }
            break;
        case DOTSLASH_JIGGLE_COMBO:
            if (pressed) {
                is_mouse_jiggle_active = !is_mouse_jiggle_active;
            }
            break;
        case CX_COLEMAK_COMBO:
            if (pressed) {
                if (default_layer_state - 1 == _COLEMAK) {
                    set_single_persistent_default_layer(_QWERTY);
                } else {
                    set_single_persistent_default_layer(_COLEMAK);
                }
            }
            break;
        case BR_WRAP_COMBO:
            if (pressed) {
                SEND_STRING("[]");
                tap_code(KC_LEFT);
            }
            break;
        case BR_WRAP_SEMI_COMBO:
            if (pressed) {
                SEND_STRING("[];");
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
            }
            break;
        case CBR_WRAP_COMBO:
            if (pressed) {
                SEND_STRING("{}");
                tap_code(KC_LEFT);
            }
            break;
        case CBR_WRAP_SEMI_COMBO:
            if (pressed) {
                SEND_STRING("{};");
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
            }
            break;
        case PRN_WRAP_COMBO:
            if (pressed) {
                SEND_STRING("()");
                tap_code(KC_LEFT);
            }
            break;
        case PRN_WRAP_SEMI_COMBO:
            if (pressed) {
                SEND_STRING("();");
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
            }
            break;
        case ANG_WRAP_COMBO:
            if (pressed) {
                SEND_STRING("<>");
                tap_code(KC_LEFT);
            }
            break;
        case ANG_WRAP_SEMI_COMBO:
            if (pressed) {
                SEND_STRING("<>;");
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
            }
            break;
        case FAT_ARROW_COMBO:
        case FAT_ARROW2_COMBO:
            if (pressed) {
                SEND_STRING("=>");
            }
            break;
        case SKINNY_ARROW_COMBO:
        case SKINNY_ARROW2_COMBO:
            if (pressed) {
                SEND_STRING("->");
            }
            break;
    }
}
