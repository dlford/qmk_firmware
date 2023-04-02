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
#include "../keycodes.h"
#include "sarcasm_mode.h"
#include "mouse_jiggler.h"

uint16_t default_animation   = RGB_MATRIX_CYCLE_SPIRAL;
int      default_speed       = 50;
uint16_t secondary_animation = RGB_MATRIX_HUE_WAVE;
int      secondary_speed     = 150;
uint16_t tertiary_animation  = RGB_MATRIX_PIXEL_FRACTAL;
int      tertiary_speed      = 250;

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(default_animation);
    rgb_matrix_set_speed_noeeprom(default_speed);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _SPECIAL:
            rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
            rgb_matrix_set_speed_noeeprom(secondary_speed);
            rgb_matrix_mode_noeeprom(secondary_animation);
            break;
        case _NAVIGATION:
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            rgb_matrix_set_speed_noeeprom(secondary_speed);
            rgb_matrix_mode_noeeprom(secondary_animation);
            break;
        case _MOUSE:
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            rgb_matrix_set_speed_noeeprom(secondary_speed);
            rgb_matrix_mode_noeeprom(secondary_animation);
            break;
        default:
            if (is_scsm_active) {
                rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
                rgb_matrix_set_speed_noeeprom(tertiary_speed);
                rgb_matrix_mode_noeeprom(tertiary_animation);
            } else {
                rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
                rgb_matrix_set_speed_noeeprom(default_speed);
                rgb_matrix_mode_noeeprom(default_animation);
            }
            break;
    }
    return state;
}

bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock || is_caps_word_active) {
        // Left master
        rgb_matrix_set_color(23, RGB_RED);
        rgb_matrix_set_color(22, RGB_RED);
        rgb_matrix_set_color(21, RGB_RED);
        // Right master
        rgb_matrix_set_color(50, RGB_RED);
        rgb_matrix_set_color(49, RGB_RED);
        rgb_matrix_set_color(48, RGB_RED);
    }
    if (is_macro_recording) {
        // Left master
        rgb_matrix_set_color(6, RGB_ORANGE);
        rgb_matrix_set_color(13, RGB_ORANGE);
        rgb_matrix_set_color(14, RGB_ORANGE);
        // Right master
        rgb_matrix_set_color(33, RGB_ORANGE);
        rgb_matrix_set_color(40, RGB_ORANGE);
        rgb_matrix_set_color(41, RGB_ORANGE);
    }
    if (default_layer_state - 1 == _COLEMAK) {
        // Left master
        rgb_matrix_set_color(18, RGB_GREEN);
        rgb_matrix_set_color(19, RGB_GREEN);
        rgb_matrix_set_color(20, RGB_GREEN);
        // Right master
        rgb_matrix_set_color(45, RGB_GREEN);
        rgb_matrix_set_color(46, RGB_GREEN);
        rgb_matrix_set_color(47, RGB_GREEN);
    }
    if (is_mouse_jiggle_active) {
        // Left master
        rgb_matrix_set_color(7, RGB_BLUE);
        rgb_matrix_set_color(8, RGB_BLUE);
        rgb_matrix_set_color(9, RGB_BLUE);
        // Right master
        rgb_matrix_set_color(34, RGB_BLUE);
        rgb_matrix_set_color(35, RGB_BLUE);
        rgb_matrix_set_color(36, RGB_BLUE);
    }

    return true;
}
