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

#pragma once

bool process_record_custom_keycodes_user(uint16_t keycode, keyrecord_t *record);

enum custom_keycodes {
    M_KEYMAP = SAFE_RANGE,
    M_EXIT,
    M_ALT_TAB,
    M_RST_RGB,
    M_RGB_SPD,
    M_LLOCK,
};

#define VVV KC_TRNS
#define XXX KC_NO
#define CSA_Q MEH_T(KC_Q)
#define CSA_F1 MEH_T(KC_F1)
#define CSA_1 MEH_T(KC_1)
#define CA_W LCA_T(KC_W)
#define CA_F2 LCA_T(KC_F2)
#define CA_2 LCA_T(KC_2)
#define CS_E C_S_T(KC_E)
#define CS_F C_S_T(KC_F)
#define CS_I C_S_T(KC_I)
#define CS_U C_S_T(KC_U)
#define CS_F3 C_S_T(KC_F3)
#define CS_3 C_S_T(KC_3)
#define CS_F8 C_S_T(KC_F8)
#define CS_8 C_S_T(KC_8)
#define CA_O LCA_T(KC_O)
#define CA_Y LCA_T(KC_Y)
#define CA_F9 LCA_T(KC_F9)
#define CA_9 LCA_T(KC_9)
#define CSA_P MEH_T(KC_P)
#define CSA_SCLN MEH_T(KC_SCLN)
#define CSA_F10 MEH_T(KC_F10)
#define CSA_0 MEH_T(KC_0)
#define LGUI_A LGUI_T(KC_A)
#define LGUI_FIND LGUI_T(KC_FIND)
#define LGUI_GRV LGUI_T(KC_GRV)
#define LALT_S LALT_T(KC_S)
#define LALT_R LALT_T(KC_R)
#define LALT_HOME LALT_T(KC_HOME)
#define LCTL_D LCTL_T(KC_D)
#define LCTL_S LCTL_T(KC_S)
#define LCTL_PGUP LCTL_T(KC_PGUP)
#define LCTL_LBRC LCTL_T(KC_LBRC)
#define LSFT_F LSFT_T(KC_F)
#define _LSFT_T LSFT_T(KC_T)
#define LSFT_PGDN LSFT_T(KC_PGDN)
#define LSFT_RBRC LSFT_T(KC_RBRC)
#define RSFT_J RSFT_T(KC_J)
#define RSFT_N RSFT_T(KC_N)
#define RSFT_DOWN RSFT_T(KC_DOWN)
#define RSFT_MINS RSFT_T(KC_MINS)
#define RCTL_K RCTL_T(KC_K)
#define RCTL_E RCTL_T(KC_E)
#define RCTL_UP RCTL_T(KC_UP)
#define RCTL_EQL RCTL_T(KC_EQL)
#define RALT_L RALT_T(KC_L)
#define RALT_I RALT_T(KC_I)
#define RALT_RGHT RALT_T(KC_RGHT)
#define RALT_BSLS RALT_T(KC_BSLS)
#define RGUI_SCLN RGUI_T(KC_SCLN)
#define RGUI_O RGUI_T(KC_O)
#define RGUI_F11 RGUI_T(KC_F11)
#define RGUI_QUOT RGUI_T(KC_QUOT)
#define LT3_SPC LT(_SPECIAL, KC_SPC)
#define LT2_TAB LT(_NAVIGATION, KC_TAB)
