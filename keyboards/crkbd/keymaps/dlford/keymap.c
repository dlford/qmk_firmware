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
#include "features_user.h"
#include "dlford.h"

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
