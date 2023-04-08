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
#include "rgb_matrix_user.h"
#include "rgb_timeout_user.h"
#include "alt_tab_user.h"
#include "eeprom_user.h"

bool process_record_custom_keycodes_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_ALT_TAB:
            start_alt_tab(record);
            break;
        case M_RGB_SPD:
            if (record->event.pressed) {
                rgb_matrix_reload_from_eeprom();
                rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                if (keyboard_report->mods & MOD_MASK_SHIFT) {
                    if (user_config.rgb_speed <= 5) {
                        user_config.rgb_speed = 0;
                    } else {
                        user_config.rgb_speed -= 5;
                    }
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                    write_user_config();
                } else {
                    if (user_config.rgb_speed >= 250) {
                        user_config.rgb_speed = 255;
                    } else {
                        user_config.rgb_speed += 5;
                    }
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                    write_user_config();
                }
                return false;
            }
            break;
        case M_RGB_HUE:
            if (record->event.pressed) {
                rgb_matrix_reload_from_eeprom();
                rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                if (keyboard_report->mods & MOD_MASK_SHIFT) {
                    rgb_matrix_decrease_hue();
                } else {
                    rgb_matrix_increase_hue();
                }
                return false;
            }
            break;
        case M_RGB_STP:
            if (record->event.pressed) {
                rgb_matrix_reload_from_eeprom();
                rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                if (keyboard_report->mods & MOD_MASK_SHIFT) {
                    rgb_matrix_step_reverse();
                } else if (keyboard_report->mods & MOD_MASK_CTRL) {
                    user_config.is_rgb_idle_enabled = !user_config.is_rgb_idle_enabled;
                    write_user_config();
                } else {
                    rgb_matrix_step();
                }
                return false;
            }
            break;
        case M_RGB_RST:
            if (record->event.pressed) {
                layer_off(_MOUSE);
                rgb_matrix_mode(RGB_MATRIX_SPLASH);
                rgb_matrix_sethsv(HSV_BLUE);
                user_config.is_rgb_idle_enabled = true;
                user_config.rgb_speed           = 150;
                rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                write_user_config();
                return false;
            }
            break;
        case M_SKN_ARW:
            if (record->event.pressed) {
                send_string("->");
            }
            break;
        case M_FAT_ARW:
            if (record->event.pressed) {
                send_string("=>");
            }
            break;
    }

    return true;
}
