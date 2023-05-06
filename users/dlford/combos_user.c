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
#include "combos_user.h"
#include "custom_keycodes_user.h"
#include "layers_user.h"
#include "mouse_jiggler_user.h"
#include "sarcasm_mode.h"
#include "pwgen_user.h"

#ifdef AUDIO_ENABLE
__attribute__((weak)) float password_song[][2] = SONG(ZELDA_PUZZLE);
#endif

const char PROGMEM legends_url[] = "https://raw.githubusercontent.com/dlford/qmk_firmware/dlford/users/dlford/keymap_3x5_3.svg";

const uint16_t PROGMEM qw_esc_combo[]          = {CSA_Q, CA_W, COMBO_END};
const uint16_t PROGMEM op_bspc_combo[]         = {CA_O, CSA_P, COMBO_END};
const uint16_t PROGMEM ysemi_bspc_combo[]      = {CA_Y, CSA_SCLN, COMBO_END};
const uint16_t PROGMEM qx_exit_combo[]         = {CSA_Q, KC_X, COMBO_END};
const uint16_t PROGMEM sc_scsm_combo[]         = {KC_C, LALT_S, COMBO_END};
const uint16_t PROGMEM sc_scsm2_combo[]        = {KC_C, LCTL_S, COMBO_END};
const uint16_t PROGMEM km_keymap_combo[]       = {RCTL_K, KC_M, COMBO_END};
const uint16_t PROGMEM km_keymap2_combo[]      = {KC_K, KC_M, COMBO_END};
const uint16_t PROGMEM pw_rand_combo[]         = {CSA_P, CA_W, COMBO_END};
const uint16_t PROGMEM pw_rand2_combo[]        = {KC_P, CA_W, COMBO_END};
const uint16_t PROGMEM lsemi_del_combo[]       = {RALT_L, RGUI_SCLN, COMBO_END};
const uint16_t PROGMEM io_del_combo[]          = {RALT_I, RGUI_O, COMBO_END};
const uint16_t PROGMEM dotslash_jiggle_combo[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM cm_colemak_combo[]      = {KC_C, KC_M, COMBO_END};
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
#ifdef CAPS_WORD_ENABLE
const uint16_t PROGMEM caps_combo[]  = {LSFT_F, RSFT_J, COMBO_END};
const uint16_t PROGMEM caps2_combo[] = {_LSFT_T, RSFT_N, COMBO_END};
#endif // CAPS_WORD_ENABLE

uint16_t COMBO_LEN = COMBO_LENGTH;

combo_t key_combos[COMBO_LENGTH] = {
    [QW_ESC_COMBO]          = COMBO_ACTION(qw_esc_combo),
    [OP_BSPC_COMBO]         = COMBO_ACTION(op_bspc_combo),
    [YSEMI_BSPC_COMBO]      = COMBO_ACTION(ysemi_bspc_combo),
    [QX_EXIT_COMBO]         = COMBO_ACTION(qx_exit_combo),
    [SC_SCSM_COMBO]         = COMBO_ACTION(sc_scsm_combo),
    [SC_SCSM2_COMBO]        = COMBO_ACTION(sc_scsm2_combo),
    [KM_KEYMAP_COMBO]       = COMBO_ACTION(km_keymap_combo),
    [KM_KEYMAP2_COMBO]      = COMBO_ACTION(km_keymap2_combo),
    [PW_RAND_COMBO]         = COMBO_ACTION(pw_rand_combo),
    [PW_RAND2_COMBO]        = COMBO_ACTION(pw_rand2_combo),
    [LSEMI_DEL_COMBO]       = COMBO_ACTION(lsemi_del_combo),
    [IO_DEL_COMBO]          = COMBO_ACTION(io_del_combo),
    [DOTSLASH_JIGGLE_COMBO] = COMBO_ACTION(dotslash_jiggle_combo),
    [CM_COLEMAK_COMBO]      = COMBO_ACTION(cm_colemak_combo),
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
#ifdef CAPS_WORD_ENABLE
    [CAPS_COMBO]  = COMBO_ACTION(caps_combo),
    [CAPS2_COMBO] = COMBO_ACTION(caps2_combo),
#endif // CAPS_WORD_ENABLE
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
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
        case QX_EXIT_COMBO:
            if (pressed) {
                SEND_STRING("exit");
                tap_code(KC_ENT);
            }
            break;
        case SC_SCSM_COMBO:
        case SC_SCSM2_COMBO:
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
            if (pressed) {
#ifdef KEYMAP_SVG_URL
                send_string(KEYMAP_SVG_URL);
#else
                send_string(legends_url);
#endif
            }
            break;
        case PW_RAND_COMBO:
        case PW_RAND2_COMBO:
            if (pressed) {
#ifdef AUDIO_ENABLE
                PLAY_SONG(password_song);
#endif
                gen_random_password();
                send_string(random_password);
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
        case CM_COLEMAK_COMBO:
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
#ifdef CAPS_WORD_ENABLE
        case CAPS_COMBO:
        case CAPS2_COMBO:
            if (pressed) {
                caps_word_on();
            }
            break;
#endif // CAPS_WORD_ENABLE
    }
}
