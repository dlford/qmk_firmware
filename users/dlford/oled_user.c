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
#include "layers_user.h"
#include "mouse_jiggler_user.h"
#include "sarcasm_mode.h"
#include "layer_lock.h"
#include "split_util.h"
#include "split_transport_user.h"
#ifdef CAPS_WORD_ENABLE
#    include "caps_word_user.h"
#endif
#ifdef DYNAMIC_MACRO_ENABLE
#    include "dynamic_macro_user.h"
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#ifdef OLED_DISPLAY_128X64
    return OLED_ROTATION_180;
#else
    if (!isLeftHand) {
        return OLED_ROTATION_180;
    }
#endif
    return rotation;
}

void oled_render_layer_state(void) {
    int highest_layer = get_highest_layer(layer_state);

#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR("Layer: "), false);
#endif

    switch (highest_layer) {
        case _COLEMAK:
            oled_write_ln_P(PSTR("Colemak"), false);
            break;
        case _SPECIAL:
            oled_write_ln_P(PSTR("Special"), false);
            break;
        case _NAVIGATION:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case _MOUSE:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case _GAMING:
            oled_write_ln_P(PSTR("Gaming"), false);
            break;
        default:
            if (default_layer_state - 1 == _COLEMAK) {
                if (is_scsm_active || info_sync_states.is_scsm_active) {
                    oled_write_ln_P(PSTR("CoLeMaK"), false);
                } else {
                    oled_write_ln_P(PSTR("Colemak"), false);
                }
            } else {
                if (is_scsm_active || info_sync_states.is_scsm_active) {
                    oled_write_ln_P(PSTR("QwErTy"), false);
                } else {
                    oled_write_ln_P(PSTR("Qwerty"), false);
                }
            }
    }

    if (is_mouse_jiggle_active || info_sync_states.is_mouse_jiggle_active) {
        oled_write_ln_P(PSTR("Mouse Jiggling..."), false);
    } else {
        oled_write_ln_P(PSTR(""), false);
    }
}

#ifdef DYNAMIC_MACRO_ENABLE
void oled_render_dynamic_macro_status(void) {
    if (is_macro_recording || info_sync_states.is_macro_recording) {
        oled_write_ln_P(PSTR("Macro Recording..."), false);
    } else {
        oled_write_ln_P(PSTR(""), false);
    }
}
#endif

void oled_render_caps_lock_status(void) {
    if (host_keyboard_led_state().caps_lock) {
        oled_write_ln_P(PSTR("CAPS LOCK"), false);
#ifdef CAPS_WORD_ENABLE
    } else if (is_caps_word_active || info_sync_states.is_caps_word_active) {
        oled_write_ln_P(PSTR("CAPS word"), false);
#endif
    } else {
        oled_write_ln_P(PSTR(""), false);
    }
}

#ifndef WPM_ENABLE
static void oled_render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,   128, 224, 224, 96, 96,  96,  96,  96,  96,  128, 192, 224, 224, 240, 240, 240, 224, 224, 192, 128, 0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0,   0,   0,  0,  0,  0,   0,   0,  0,   0,   0,  0,  0,  0,   0,   0, 0,   0,   0,  0,  0,  0,   0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 240, 60, 30, 7, 1, 192, 224, 224, 240, 240, 240, 0,  255, 255, 255, 255, 249, 241, 241, 7, 7, 55, 247, 192, 0, 0, 0, 0, 224, 224, 224, 224, 224, 192, 192, 192, 0, 192, 224, 224, 224, 0, 0, 0, 0, 224, 224, 96, 96, 96, 96, 0, 192, 224, 96, 96, 96, 224, 192, 192, 192, 224, 96, 96, 96, 224, 192, 0, 224, 224, 96, 96, 96, 224, 192, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 15, 60, 240, 224, 134, 31,  63, 127, 255, 249, 248, 248, 127, 127, 63,  31,  0,   0,   128, 224, 248, 60,  15,  3, 1, 0, 0, 0, 127, 127, 127, 127, 113, 127, 127, 63, 31, 31, 63, 127, 127, 112, 112, 112, 112, 127, 127, 6, 6, 6, 6, 0, 127, 127, 96, 96, 96, 127, 127, 63, 127, 127, 12, 12, 60, 127, 103, 0, 127, 127, 96, 96, 96, 127, 63, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,  0,  1, 7, 14,  12,  12,  12,  12,  12,  12, 12,  12,  12,  12,  12,  14,  7,   1, 0, 0,  0,   0,   0, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0,   0,   0, 0,   0,   0,   0,   0, 0, 0, 0, 0,   0,   0,  0,  0,  0,  0, 0,   0,   0,  0,  0,  0,   0,   0,   0,   0,   0,  0,  0,  0,   0,   0, 0,   0,   0,  0,  0,  0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}
#endif

bool oled_task_user(void) {
    if (isLeftHand) {
#ifdef WPM_ENABLE
        oled_write_P(PSTR("WPM: "), false);
        oled_write_ln_P(get_u8_str(get_current_wpm(), '0'), false);
#else
        oled_render_logo();
#endif
    } else {
        oled_render_layer_state();
        oled_render_dynamic_macro_status();
        oled_render_caps_lock_status();
    }
    return false;
}
