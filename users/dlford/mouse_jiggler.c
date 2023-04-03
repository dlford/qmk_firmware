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

bool     is_mouse_jiggle_active = false;
bool     mouse_jiggle_direction = false;
uint16_t mouse_jiggle_frequency = 15000;
uint16_t mouse_jiggle_timer     = 0;

void matrix_scan_mouse_jiggler(void) {
    if (mouse_jiggle_timer == 0) mouse_jiggle_timer = timer_read();

    if (is_mouse_jiggle_active) {
        if (timer_elapsed(mouse_jiggle_timer) > mouse_jiggle_frequency) {
            mouse_jiggle_timer = timer_read();
            if (mouse_jiggle_direction) {
                tap_code(KC_MS_LEFT);
                tap_code(KC_MS_LEFT);
                tap_code(KC_MS_LEFT);
            } else {
                tap_code(KC_MS_RIGHT);
                tap_code(KC_MS_RIGHT);
                tap_code(KC_MS_RIGHT);
            }
            mouse_jiggle_direction = !mouse_jiggle_direction;
        }
    }
}
