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

int      RGB_CUSTOM_TIMEOUT = 5;
uint16_t idle_timer         = 0;
uint8_t  halfmin_counter    = 0;
bool     led_on             = true;

void matrix_scan_rgb_timeout(void) {
    if (is_keyboard_master()) {
        if (idle_timer == 0) idle_timer = timer_read();

        if (led_on && timer_elapsed(idle_timer) > 30000) {
            halfmin_counter++;
            idle_timer = timer_read();
        }

        if (led_on && halfmin_counter >= RGB_CUSTOM_TIMEOUT * 2) {
            rgb_matrix_disable_noeeprom();
            led_on          = false;
            halfmin_counter = 0;
        }
    }
}

void process_record_rgb_timeout(keyrecord_t *record) {
    if (is_keyboard_master()) {
        if (record->event.pressed) {
            if (led_on == false) {
                rgb_matrix_enable_noeeprom();
                led_on = true;
            }
            idle_timer      = timer_read();
            halfmin_counter = 0;
        }
    }
}
