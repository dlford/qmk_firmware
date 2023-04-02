/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 @dlford

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
#include "keycodes.h"
#include "features/tap_rules.h"
#include "features/mouse_jiggler.h"
#include "features/sarcasm_mode.h"
#include "features/rgb_timeout.h"
#include "features/alt_tab.h"
#include "features/oled.h"
#include "features/rgb_matrix.h"
#include "features/custom_eeprom.h"

bool is_macro_recording  = false;
bool is_caps_word_active = false;

void caps_word_set_user(bool active) {
    is_caps_word_active = active;
}

void dynamic_macro_record_start_user(void) {
    is_macro_recording = true;
}

void dynamic_macro_record_end_user(int8_t direction) {
    is_macro_recording = false;
}

void eeconfig_init_user(void) {
    eeconfig_init_custom_eeprom();
}

void keyboard_post_init_user(void) {
    read_user_config();
    keyboard_post_init_rgb_matrix();
}

void matrix_scan_user(void) {
    matrix_scan_rgb_timeout();
    matrix_scan_mouse_jiggler();
    matrix_scan_alt_tab();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_record_rgb_timeout(record);
    process_record_sarcasm_mode(record);

    switch (keycode) {
        case M_ALT_TAB:
            start_alt_tab(record);
            break;
        case M_RGB_SPD:
            if (record->event.pressed) {
                if (keyboard_report->mods & MOD_BIT(KC_LSFT) || keyboard_report->mods & MOD_BIT(KC_RSFT)) {
                    user_config.rgb_speed = (user_config.rgb_speed - 10) % 256;
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                    write_user_config();
                } else {
                    user_config.rgb_speed = (user_config.rgb_speed + 10) % 256;
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                    write_user_config();
                }
            }
            break;
        case M_RST_RGB:
            if (record->event.pressed) {
                layer_off(_MOUSE);
                rgb_matrix_mode(RGB_MATRIX_CYCLE_SPIRAL);
                rgb_matrix_sethsv(HSV_ORANGE);
                user_config.rgb_speed = 50;
                rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                write_user_config();
            }
            break;
    }

    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_split_3x5_3(
		//|--------------------------------------------|                    |--------------------------------------------|
			CSA_Q,   CA_W,    CS_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    CS_I,    CA_O,    CSA_P,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
			LGUI_A,  LALT_S,  LCTL_D,  LSFT_F,  KC_G,                         KC_H,    RSFT_J,  RCTL_K,  RALT_L, RGUI_SCLN,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
			KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,   KC_COMM,  KC_DOT,  KC_SLSH,
		//|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
									   KC_ESC,  LT3_SPC, KC_BSPC,    KC_DEL, LT2_TAB,  KC_ENT
		//                           |--------+--------+--------|  |--------+--------+--------|
	),
	[_COLEMAK] = LAYOUT_split_3x5_3(
		//|--------------------------------------------|                    |--------------------------------------------|
			CSA_Q,   CA_W,    CS_F,    KC_P,    KC_G,                         KC_J,    KC_L,    CS_U,    CA_Y,    CSA_SCLN,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
			LGUI_A,  LALT_R,  LCTL_S,  _LSFT_T, KC_D,                         KC_H,    RSFT_N,  RCTL_E,  RALT_I,  RGUI_O,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
			KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M,   KC_COMM,  KC_DOT,  KC_SLSH,
		//|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
									   KC_ESC,  LT3_SPC, KC_BSPC,    KC_DEL, LT2_TAB,  KC_ENT
		//                           |--------+--------+--------|  |--------+--------+--------|
	),
	// left thumb
	[_SPECIAL] = LAYOUT_split_3x5_3(
		//|--------------------------------------------|                    |--------------------------------------------|
			CSA_1,   CA_2,    CS_3,    KC_4,    KC_5,                         KC_6,    KC_7,    CS_8,    CA_9,    CSA_0,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
		   LGUI_GRV,KC_LALT,LCTL_LBRC,LSFT_RBRC,KC_LPRN,                     KC_RPRN,RSFT_MINS,RCTL_EQL,RALT_BSLS,RGUI_QUOT,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
		   KC_TILD, KC_CAPS, KC_LCBR, KC_RCBR, M_ALT_TAB,                    QK_BOOT,  KC_UNDS, KC_PLUS, KC_PIPE, KC_DQUO,
		//|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
										VVV,     VVV,     VVV,        VVV,  TG(_MOUSE),  VVV
		//                           |--------+--------+--------|  |--------+--------+--------|
	),
	// right thumb
	[_NAVIGATION] = LAYOUT_split_3x5_3(
		//|--------------------------------------------|                    |--------------------------------------------|
			CSA_F1,  CA_F2,   CS_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   CS_F8,  CA_F9,   CSA_F10,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
		 LGUI_FIND,LALT_HOME,LCTL_PGUP,LSFT_PGDN,KC_END,                     KC_LEFT,RSFT_DOWN,RCTL_UP,RALT_RGHT,RGUI_F11,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
	     M_RGB_SPD, RGB_HUI, KC_VOLD, KC_VOLU,  RGB_MOD,                     M_ALT_TAB, KC_MPLY, KC_MPRV, KC_MNXT, KC_F12,
		//|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
										VVV,  TG(_MOUSE), VVV,         VVV,    VVV,     VVV
		//                           |--------+--------+--------|  |--------+--------+--------|
	),
	[_MOUSE] = LAYOUT_split_3x5_3(
		//|--------------------------------------------|                    |--------------------------------------------|
			KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, DM_REC1,                      KC_WSTP, KC_ACL2, KC_ACL1, KC_ACL0, KC_WFWD,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
			KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, DM_PLY1,                      KC_WREF, KC_BTN1, KC_BTN2, KC_BTN3, KC_WBAK,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
		    XXX,    KC_BTN3, KC_BTN2, KC_BTN1, M_RST_RGB,                     XXX,     XXX,     XXX,     XXX,     XXX,
		//|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
										VVV,  TG(_MOUSE),  VVV,       VVV,  TG(_MOUSE),  VVV
		//                           |--------+--------+--------|  |--------+--------+--------|
	),
};
// clang-format on
