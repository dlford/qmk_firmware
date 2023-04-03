/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 @dlford

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
#include "tap_rules.h"
#include "mouse_jiggler_user.h"
#include "sarcasm_mode.h"
#ifdef ALT_TAB_USER_ENABLE
#    include "alt_tab_user.h"
#endif
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_timeout_user.h"
#endif
#ifdef OLED_ENABLE
#    include "oled_user.h"
#endif
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix_user.h"
#endif
#ifdef ALL_MATRIX_ANIMATIONS_USER_ENABLE
#    include "eeprom_user.h"
#endif

bool is_macro_recording = false;

#ifdef DYNAMIC_MACRO_ENABLE
void dynamic_macro_record_start_user(void) {
    is_macro_recording = true;
}

void dynamic_macro_record_end_user(int8_t direction) {
    is_macro_recording = false;
}
#endif

bool is_caps_word_active = false;

#ifdef CAPS_WORD_ENABLE
void caps_word_set_user(bool active) {
    is_caps_word_active = active;
}
#endif

#ifdef ALL_MATRIX_ANIMATIONS_USER_ENABLE
void eeconfig_init_user(void) {
    eeconfig_init_custom_eeprom();
}

void keyboard_post_init_user(void) {
    read_user_config();
    keyboard_post_init_rgb_matrix();
}
#endif

void matrix_scan_user(void) {
#ifdef RGB_MATRIX_ENABLE
    matrix_scan_rgb_matrix();
#endif
    matrix_scan_mouse_jiggler();
    matrix_scan_alt_tab();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGB_MATRIX_ENABLE
    process_record_rgb_timeout(record);
#endif
    process_record_sarcasm_mode(record);

    switch (keycode) {
#ifdef ALT_TAB_USER_ENABLE
        case M_ALT_TAB:
            start_alt_tab(record);
            break;
#endif
#ifdef ALL_MATRIX_ANIMATIONS_USER_ENABLE
        case M_RGB_SPD:
            if (record->event.pressed) {
                if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)) {
                    user_config.rgb_speed = (user_config.rgb_speed - 10) % 256;
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                    write_user_config();
                } else {
                    user_config.rgb_speed = (user_config.rgb_speed + 10) % 256;
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                    write_user_config();
                }
            }
            break;
        case M_RST_RGB:
            if (record->event.pressed) {
                layer_off(_MOUSE);
                rgb_matrix_mode(RGB_MATRIX_CYCLE_SPIRAL);
                rgb_matrix_sethsv(HSV_ORANGE);
                user_config.rgb_speed = 50;
                rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                write_user_config();
            }
            break;
#endif // ALL_MATRIX_ANIMATIONS_USER
    }

    return true;
}
