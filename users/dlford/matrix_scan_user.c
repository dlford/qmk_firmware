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
#include "mouse_jiggler_user.h"
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_timeout_user.h"
#    include "rgb_idle_mode_user.h"
#endif

__attribute__((weak)) void matrix_scan_keymap(void) {
    return;
}

void matrix_scan_user(void) {
#ifdef RGB_MATRIX_ENABLE
    matrix_scan_rgb_timeout();
    matrix_scan_rgb_idle_mode();
#endif
    matrix_scan_mouse_jiggler();
    matrix_scan_keymap();
}
