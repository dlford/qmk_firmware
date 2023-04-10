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
#include "rgb_timeout_user.h"
#include "eeprom_user.h"

int      RGB_CUSTOM_TIMEOUT          = 5;
uint16_t rgb_timeout_user_idle_timer = 0;
uint8_t  halfmin_counter             = 0;
bool     is_rgb_timeout_user_on      = true;

void matrix_scan_rgb_timeout(void) {
    if (is_keyboard_master() && !user_config.is_rgb_idle_enabled) {
        if (rgb_timeout_user_idle_timer == 0) rgb_timeout_user_idle_timer = timer_read();

        if (is_rgb_timeout_user_on && timer_elapsed(rgb_timeout_user_idle_timer) > 30000) {
            halfmin_counter++;
            rgb_timeout_user_idle_timer = timer_read();
        }

        if (is_rgb_timeout_user_on && halfmin_counter >= RGB_CUSTOM_TIMEOUT * 2) {
            rgb_matrix_disable_noeeprom();
            is_rgb_timeout_user_on = false;
            halfmin_counter        = 0;
        }
    }
}

void process_record_rgb_timeout(keyrecord_t *record) {
    if (is_keyboard_master() && !user_config.is_rgb_idle_enabled) {
        if (record->event.pressed) {
            if (is_rgb_timeout_user_on == false) {
                rgb_matrix_enable_noeeprom();
                is_rgb_timeout_user_on = true;
            }
            rgb_timeout_user_idle_timer = timer_read();
            halfmin_counter             = 0;
        }
    }
}
