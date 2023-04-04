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
#include "custom_keycodes_user.h"
#include "layers_user.h"
#include "alt_tab_user.h"
#include "sarcasm_mode.h"
#include "rgb_timeout_user.h"
#include "eeprom_user.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGB_MATRIX_ENABLE
    process_record_rgb_timeout(record);
#endif
    process_record_sarcasm_mode(record);

    switch (keycode) {
        case M_ALT_TAB:
            start_alt_tab(record);
            break;
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
    }

    return process_record_keymap(keycode, record);
}
