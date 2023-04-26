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

bool is_leader_mode_active = false;

void leader_start_user(void) {
    is_leader_mode_active = true;
}

void leader_end_user(void) {
    is_leader_mode_active = false;

    // leader_sequence_one_key - leader_sequence_five_keys

    if (leader_sequence_three_keys(TD_C_LDR, KC_C, KC_W)) {
        caps_word_on();
    }
}
