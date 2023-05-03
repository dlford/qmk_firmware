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
#include "eeprom_user.h"
#include "rgb_matrix_user.h"
#include "rgb_timeout_user.h"

__attribute__((weak)) void keyboard_post_init_keymap(void) {
    return;
}

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif

    read_user_config();
    keyboard_post_init_rgb_matrix();
    keyboard_post_init_keymap();
}
