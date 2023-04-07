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

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_keymap_caps(void) {
    // Left master
    rgb_matrix_set_color(23, RGB_RED);
    rgb_matrix_set_color(22, RGB_RED);
    rgb_matrix_set_color(21, RGB_RED);
    // Right master
    rgb_matrix_set_color(50, RGB_RED);
    rgb_matrix_set_color(49, RGB_RED);
    rgb_matrix_set_color(48, RGB_RED);
}

void rgb_matrix_indicators_keymap_colemak(void) {
    // Left master
    rgb_matrix_set_color(18, RGB_GREEN);
    rgb_matrix_set_color(19, RGB_GREEN);
    rgb_matrix_set_color(20, RGB_GREEN);
    // Right master
    rgb_matrix_set_color(45, RGB_GREEN);
    rgb_matrix_set_color(46, RGB_GREEN);
    rgb_matrix_set_color(47, RGB_GREEN);
}

void rgb_matrix_indicators_keymap_dynamic_macro_recording(void) {
    // Left master
    rgb_matrix_set_color(6, RGB_ORANGE);
    rgb_matrix_set_color(13, RGB_ORANGE);
    rgb_matrix_set_color(14, RGB_ORANGE);
    // Right master
    rgb_matrix_set_color(33, RGB_ORANGE);
    rgb_matrix_set_color(40, RGB_ORANGE);
    rgb_matrix_set_color(41, RGB_ORANGE);
}

void rgb_matrix_indicators_keymap_mouse_jiggling(void) {
    // Left master
    rgb_matrix_set_color(7, RGB_BLUE);
    rgb_matrix_set_color(8, RGB_BLUE);
    rgb_matrix_set_color(9, RGB_BLUE);
    // Right master
    rgb_matrix_set_color(34, RGB_BLUE);
    rgb_matrix_set_color(35, RGB_BLUE);
    rgb_matrix_set_color(36, RGB_BLUE);
}
#endif // RGB_MATRIX_ENABLE

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
