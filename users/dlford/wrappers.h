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

#include "custom_keycodes_user.h"
#include "layers_user.h"
#include "tap_dance_user.h"

// clang-format off

//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___QWERTY_L1___          CSA_Q,   CA_W,    CS_E,    KC_R,    KC_T
#define ___QWERTY_R1___                                                                            KC_Y,    KC_U,    CS_I,    CA_O,    CSA_P
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___QWERTY_L2___          LGUI_A,  LALT_S,  LCTL_D,  LSFT_F,  KC_G
#define ___QWERTY_R2___                                                                           KC_H,    RSFT_J,  RCTL_K,  RALT_L, RGUI_SCLN
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
// #define ___QWERTY_L3___          KC_Z,    KC_X,   TD_C_LDR,  KC_V,    KC_B
#define ___QWERTY_L3___          KC_Z,    KC_X,     KC_C,    KC_V,    KC_B
#define ___QWERTY_R3___                                                                            KC_N,    KC_M,   KC_COMM,  KC_DOT,  KC_SLSH
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___QWERTY_L4___                                    SH_ESC,  LT3_SPC, KC_BSPC
#define ___QWERTY_R4___                                                                  KC_DEL,  LT2_TAB,  SH_ENT
//                                                        |--------+--------+--------|  |--------+--------+--------|

//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___COLEMAK_L1___         CSA_Q,   CA_W,    CS_F,    KC_P,    KC_G
#define ___COLEMAK_R1___                                                                           KC_J,    KC_L,    CS_U,    CA_Y,   CSA_SCLN
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___COLEMAK_L2___         LGUI_A,  LALT_R,  LCTL_S,  _LSFT_T, KC_D
#define ___COLEMAK_R2___                                                                           KC_H,    RSFT_N,  RCTL_E,  RALT_I,  RGUI_O
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
// #define ___COLEMAK_L3___         KC_Z,    KC_X,   TD_C_LDR,  KC_V,    KC_B
#define ___COLEMAK_L3___         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B
#define ___COLEMAK_R3___                                                                           KC_K,    KC_M,   KC_COMM,  KC_DOT,  KC_SLSH
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___COLEMAK_L4___                                         ___QWERTY_L4___
#define ___COLEMAK_R4___                                                                       ___QWERTY_R4___
//                                                        |--------+--------+--------|  |--------+--------+--------|

// left thumb
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___SPECIAL_L1___         CSA_1,   CA_2,    CS_3,    KC_4,    KC_5
#define ___SPECIAL_R1___                                                                           KC_6,    KC_7,    CS_8,    CA_9,    CSA_0
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___SPECIAL_L2___         LGUI_GRV,KC_LALT,LCTL_LBRC,LSFT_RBRC,KC_LPRN
#define ___SPECIAL_R2___                                                                           KC_RPRN,RSFT_MINS,RCTL_EQL,RALT_BSLS,RGUI_QUOT
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___SPECIAL_L3___         KC_TILD, KC_CAPS, KC_LCBR, KC_RCBR,  XXX
#define ___SPECIAL_R3___                                                                         M_QK_BOOT, KC_UNDS, KC_PLUS, KC_PIPE, KC_DQUO
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___SPECIAL_L4___                                     VVV,     VVV,     VVV
#define ___SPECIAL_R4___                                                                M_LLOCK,TG(_MOUSE),TG(_NUMPAD)
//                                                        |--------+--------+--------|  |--------+--------+--------|

// right thumb
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___NAVIGATION_L1___      CSA_F1,  CA_F2,   CS_F3,   KC_F4,   KC_F5
#define ___NAVIGATION_R1___                                                                        KC_F6,   KC_F7,   CS_F8,  CA_F9,   CSA_F10
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___NAVIGATION_L2___   LGUI_FIND,LALT_HOME,LCTL_PGUP,LSFT_PGDN,KC_END
#define ___NAVIGATION_R2___                                                                       KC_LEFT,RSFT_DOWN,RCTL_UP,RALT_RGHT,RGUI_F11
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___NAVIGATION_L3___    M_RGB_SPD,M_RGB_HUE, KC_VOLD, KC_VOLU,M_RGB_STP
#define ___NAVIGATION_R3___                                                                       KC_MPLY,  M_VDSL,  M_VDSR,  M_MNXT,  KC_F12
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___NAVIGATION_L4___                             TG(_NUMPAD),TG(_MOUSE),M_LLOCK
#define ___NAVIGATION_R4___                                                                 VVV,    VVV,     VVV
//                                                        |--------+--------+--------|  |--------+--------+--------|

//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___MOUSE_L1___          KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, DM_REC1
#define ___MOUSE_R1___                                                                            KC_WSTP, KC_ACL2, KC_ACL1, KC_ACL0, KC_WFWD
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___MOUSE_L2___          KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, DM_PLY1
#define ___MOUSE_R2___                                                                            KC_WREF, KC_BTN1, KC_BTN2, KC_BTN3, KC_WBAK
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___MOUSE_L3___            XXX,   KC_BTN3, KC_BTN2, KC_BTN1,  XXX
#define ___MOUSE_R3___                                                                              XXX,     XXX,     XXX,     XXX,     XXX
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___MOUSE_L4___                                      VVV,  TG(_MOUSE),  VVV
#define ___MOUSE_R4___                                                                    VVV,  TG(_MOUSE),  VVV
//                                                        |--------+--------+--------|  |--------+--------+--------|

//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___NUMPAD_L1___           XXX,    KC_PGDN, KC_UP,  KC_PGUP,  KC_ASTR
#define ___NUMPAD_R1___                                                                           KC_HOME,  KC_7,    CS_8,    CA_9,    KC_0
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___NUMPAD_L2___           XXX,   KC_LEFT, KC_DOWN, KC_RGHT, KC_MINS
#define ___NUMPAD_R2___                                                                           KC_PLUS,  KC_4,    KC_5,    KC_6,    KC_COMM
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___NUMPAD_L3___           XXX,     XXX,    KC_TAB,  KC_SPC, KC_SLSH
#define ___NUMPAD_R3___                                                                           KC_END,   KC_1,    KC_2,    KC_3,    KC_DOT
//                             |--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
#define ___NUMPAD_L4___                                      VVV, TG(_NUMPAD), VVV
#define ___NUMPAD_R4___                                                                    VVV, TG(_NUMPAD), VVV
//                                                        |--------+--------+--------|  |--------+--------+--------|

// clang-format on
