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
#include "tap_dance_user.h"

void dance_leader(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 3) {
        leader_start();
        reset_tap_dance(state);
    } else {
        tap_code(KC_C);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_C_LDR] = ACTION_TAP_DANCE_FN(dance_leader),
};
