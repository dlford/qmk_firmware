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
#include "layer_lock.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool custom_keycodes_result       = true;
bool process_record_keymap_result = true;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_layer_lock(keycode, record, M_LLOCK)) {
        return false;
    }

#ifdef RGB_MATRIX_ENABLE
    process_record_rgb_timeout(record);
#endif

    process_record_sarcasm_mode(record);
    custom_keycodes_result       = process_record_custom_keycodes_user(keycode, record);
    process_record_keymap_result = process_record_keymap(keycode, record);

    if (custom_keycodes_result && process_record_keymap_result) {
        return true;
    } else {
        return false;
    }
}
