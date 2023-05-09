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
#include "dlford.h"

// clang-format off

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_wrapper(
        ___QWERTY_L1___,                   ___QWERTY_R1___,
        ___QWERTY_L2___,                   ___QWERTY_R2___,
        ___QWERTY_L3___,                   ___QWERTY_R3___,
        ___QWERTY_L4___,                   ___QWERTY_R4___
    ),
    [_COLEMAK] = LAYOUT_wrapper(
        ___COLEMAK_L1___,                  ___COLEMAK_R1___,
        ___COLEMAK_L2___,                  ___COLEMAK_R2___,
        ___COLEMAK_L3___,                  ___COLEMAK_R3___,
        ___COLEMAK_L4___,                  ___COLEMAK_R4___
    ),
    [_SPECIAL] = LAYOUT_wrapper(
        ___SPECIAL_L1___,                  ___SPECIAL_R1___,
        ___SPECIAL_L2___,                  ___SPECIAL_R2___,
        ___SPECIAL_L3___,                  ___SPECIAL_R3___,
        ___SPECIAL_L4___,                  ___SPECIAL_R4___
    ),
    [_NAVIGATION] = LAYOUT_wrapper(
        ___NAVIGATION_L1___,               ___NAVIGATION_R1___,
        ___NAVIGATION_L2___,               ___NAVIGATION_R2___,
        ___NAVIGATION_L3___,               ___NAVIGATION_R3___,
        ___NAVIGATION_L4___,               ___NAVIGATION_R4___
    ),
    [_MOUSE] = LAYOUT_wrapper(
        ___MOUSE_L1___,                    ___MOUSE_R1___,
        ___MOUSE_L2___,                    ___MOUSE_R2___,
        ___MOUSE_L3___,                    ___MOUSE_R3___,
        ___MOUSE_L4___,                    ___MOUSE_R4___
    ),
    [_NUMPAD] = LAYOUT_wrapper(
        ___NUMPAD_L1___,                   ___NUMPAD_R1___,
        ___NUMPAD_L2___,                   ___NUMPAD_R2___,
        ___NUMPAD_L3___,                   ___NUMPAD_R3___,
        ___NUMPAD_L4___,                   ___NUMPAD_R4___
    ),
};

// clang-format on
