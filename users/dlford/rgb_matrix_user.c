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
#ifdef ALL_MATRIX_ANIMATIONS_USER_ENABLE
#    include "eeconfig.h"
#    include "eeprom.h"
#    include "progmem.h"
#    include "eeprom_user.h"
#endif
#include "dlford.h"
#include "sarcasm_mode.h"
#include "mouse_jiggler_user.h"

#ifdef ALL_MATRIX_ANIMATIONS_USER_ENABLE
rgb_config_t  rgb_matrix_config;
user_config_t user_config;

void matrix_init_user(void) {
    rgb_matrix_config.raw = eeprom_read_dword(EECONFIG_RGB_MATRIX);
}

void keyboard_post_init_rgb_matrix(void) {
    if (rgb_matrix_config.mode == 0) {
        rgb_matrix_mode(RGB_MATRIX_CYCLE_SPIRAL);
        rgb_matrix_sethsv(HSV_ORANGE);
        user_config.rgb_speed = 50;
        rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
        write_user_config();
    } else {
        rgb_matrix_mode(rgb_matrix_config.mode);
        rgb_matrix_set_speed(user_config.rgb_speed);
        rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
    }
}
#else
void keyboard_post_init_rgb_matrix(void) {
    rgb_matrix_mode(RGB_MATRIX_CYCLE_SPIRAL);
    rgb_matrix_set_speed(50);
    rgb_matrix_sethsv(HSV_ORANGE);
}
#endif // ALL_MATRIX_ANIMATIONS_USER

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _SPECIAL:
            rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
            rgb_matrix_set_speed_noeeprom(150);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_HUE_WAVE);
            break;
        case _NAVIGATION:
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            rgb_matrix_set_speed_noeeprom(150);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_HUE_WAVE);
            break;
        case _MOUSE:
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            rgb_matrix_set_speed_noeeprom(150);
            rgb_matrix_mode_noeeprom(RGB_MATRIX_HUE_WAVE);
            break;
        default:
            if (is_scsm_active) {
                rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
                rgb_matrix_set_speed_noeeprom(250);
                rgb_matrix_mode_noeeprom(RGB_MATRIX_PIXEL_FRACTAL);

            } else {
#ifdef ALL_MATRIX_ANIMATIONS_USER_ENABLE
                rgb_matrix_config.raw = eeprom_read_dword(EECONFIG_RGB_MATRIX);
                rgb_matrix_mode(rgb_matrix_config.mode);
                rgb_matrix_set_speed(user_config.rgb_speed);
                rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
#else
                rgb_matrix_mode(RGB_MATRIX_CYCLE_SPIRAL);
                rgb_matrix_set_speed(50);
                rgb_matrix_sethsv(HSV_ORANGE);
#endif
            }
            break;
    }
    return state;
}

__attribute__((weak)) void rgb_matrix_indicators_keymap_caps(void) {
    return;
}

__attribute__((weak)) void rgb_matrix_indicators_keymap_colemak(void) {
    return;
}

__attribute__((weak)) void rgb_matrix_indicators_keymap_dynamic_macro_recording(void) {
    return;
}

__attribute__((weak)) void rgb_matrix_indicators_keymap_mouse_jiggling(void) {
    return;
}

__attribute__((weak)) bool rgb_matrix_indicators_keymap_custom(void) {
    return true;
}

bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock
#ifdef CAPS_WORD_ENABLE
        || is_caps_word_active
#endif
    ) {
        rgb_matrix_indicators_keymap_caps();
    }
    if (is_macro_recording) {
        rgb_matrix_indicators_keymap_dynamic_macro_recording();
    }
    if (default_layer_state - 1 == _COLEMAK) {
        rgb_matrix_indicators_keymap_colemak();
    }
    if (is_mouse_jiggle_active) {
        rgb_matrix_indicators_keymap_mouse_jiggling();
    }

    return rgb_matrix_indicators_keymap_custom();
}
