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

bool is_macro_recording = false;

__attribute__((weak)) void dynamic_macro_record_start_keymap(void) {
    return;
}

void dynamic_macro_record_start_user(void) {
    is_macro_recording = true;
    dynamic_macro_record_start_keymap();
}

__attribute__((weak)) void dynamic_macro_record_end_keymap(int8_t direction) {
    return;
}

void dynamic_macro_record_end_user(int8_t direction) {
    is_macro_recording = false;
    dynamic_macro_record_end_keymap(direction);
}
