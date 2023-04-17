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
#include "eeprom_user.h"
#include "rgb_matrix_user.h"
#include "layers_user.h"
#include "sarcasm_mode.h"

int rgb_idle_mode_user_timeout_seconds           = 1;
int rgb_idle_mode_user_toggled_indicator_seconds = 2;

uint16_t rgb_idle_mode_user_idle_timer           = 0;
uint8_t  rgb_idle_mode_user_timer_second_counter = 0;
bool     is_rgb_idle_mode_user_on                = true;

bool     rgb_idle_mode_user_toggled                = false;
uint16_t rgb_idle_mode_user_toggled_timer          = 0;
uint8_t  rgb_idle_mode_user_toggled_second_counter = 0;

void toggle_rgb_idle_mode_user(void) {
    user_config.is_rgb_idle_enabled = !user_config.is_rgb_idle_enabled;
    write_user_config();
    rgb_idle_mode_user_toggled = true;
}

// Return true to prevent idle mode
__attribute__((weak)) bool rgb_idle_user_interrupt_keymap(void) {
    return false;
}

// TODO: Check only run if default_layer is highest
bool rgb_idle_user_interrupt(void) {
    if (is_scsm_active) return true;
    if (!layer_state_is(_QWERTY) && !(layer_state_is(_COLEMAK))) return true;
    return rgb_idle_user_interrupt_keymap();
}

void matrix_scan_rgb_idle_mode(void) {
    // This is used to show an indicator of a few seconds and then turn it off
    // See rgb_matrix_user.c for the rest of the logic
    if (is_keyboard_master() && rgb_idle_mode_user_toggled) {
        if (rgb_idle_mode_user_toggled && timer_elapsed(rgb_idle_mode_user_toggled_timer) > 1000) {
            rgb_idle_mode_user_toggled_second_counter++;
            rgb_idle_mode_user_toggled_timer = timer_read();
        }

        if (rgb_idle_mode_user_toggled && rgb_idle_mode_user_toggled_second_counter >= rgb_idle_mode_user_toggled_indicator_seconds + 1) {
            rgb_idle_mode_user_toggled                = false;
            rgb_idle_mode_user_toggled_second_counter = 0;
        }
    }

    if (is_keyboard_master() && user_config.is_rgb_idle_enabled) {
        if (rgb_idle_mode_user_idle_timer == 0) rgb_idle_mode_user_idle_timer = timer_read();
        if (rgb_idle_mode_user_toggled_timer == 0) rgb_idle_mode_user_toggled_timer = timer_read();

        if (is_rgb_idle_mode_user_on && timer_elapsed(rgb_idle_mode_user_idle_timer) > 1000) {
            rgb_idle_mode_user_timer_second_counter++;
            rgb_idle_mode_user_idle_timer = timer_read();
        }

        if (is_rgb_idle_mode_user_on && rgb_idle_mode_user_timer_second_counter >= rgb_idle_mode_user_timeout_seconds && !rgb_idle_user_interrupt()) {
            rgb_matrix_set_speed_noeeprom(user_config.rgb_idle_speed);
            rgb_matrix_mode_noeeprom(user_config.rgb_idle_mode);
            rgb_matrix_sethsv_noeeprom(user_config.rgb_idle_hsv.h, user_config.rgb_idle_hsv.s, user_config.rgb_idle_hsv.v);
            is_rgb_idle_mode_user_on                = false;
            rgb_idle_mode_user_timer_second_counter = 0;
        }
    }
}

void process_record_rgb_idle_mode(keyrecord_t *record) {
    if (is_keyboard_master() && user_config.is_rgb_idle_enabled) {
        if (record->event.pressed) {
            if (!is_rgb_idle_mode_user_on) {
                rgb_matrix_reload_from_eeprom();
                rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                is_rgb_idle_mode_user_on = true;
            }
        }
        rgb_idle_mode_user_idle_timer           = timer_read();
        rgb_idle_mode_user_timer_second_counter = 0;
    }
}
