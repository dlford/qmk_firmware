/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

/* TODO:
 * cheatsheet https://jayliu50.github.io/qmk-cheatsheet/
 * tap dance number keys => symbols
 * combo arrow keys (adjacent)
 * combo toggle layers (instead of MO)
 * override alt+w => alt+tab
 * MT ctrl+win: MT(MOD_LCTL | MOD_LGUI, KC_XXX)
 * paired braces https://www.reddit.com/r/olkb/comments/8jvxkv/qmk_trick_for_paired_braces/?utm_medium=android_app&utm_source=share
 *   https://getreuer.info/posts/keyboards/macros/index.html
 * macros https://getreuer.info/posts/keyboards/macros/index.html#next-sentence-macro
 */

#include QMK_KEYBOARD_H
#include "features/caps_word.h"

// Layers
enum {
    _QWERTY = 0,
    _COLEMAK,
    _NAVIGATION,
    _SPECIAL,
    _MOUSE,
};

// Macros
// TODO: Cleanup
#define _M0 KC_F13
#define _M1 KC_F14
#define _M2 KC_F15
#define _M3 KC_F16
#define _M4 KC_F17
#define _M5 KC_F18
#define _M6 KC_F19
#define _M7 KC_F20
#define _M8 KC_F21
#define _M9 KC_F22

static uint16_t default_animation = RGB_MATRIX_CYCLE_SPIRAL;
static int default_speed = 50;
static uint16_t secondary_animation = RGB_MATRIX_HUE_WAVE;
static int secondary_speed = 150;
static bool is_macro_recording = false;

// Init
void keyboard_post_init_user(void) {
  rgb_matrix_mode_noeeprom(default_animation);
  rgb_matrix_set_speed_noeeprom(default_speed);
}

// Permissive hold per key
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(3, KC_SPC):
      return true; // Enable permissive hold
    case LT(2, KC_TAB):
      return true;
    default:
      return false; // Disable permissive hold
  }
}

// Tapping force hold per key
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT(3, KC_SPC):
      return true; // Enable force hold
    case LT(2, KC_TAB):
      return true;
    default:
      return false; // Disable force hold
  }
}

// Tapping term per key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case C_S_T(KC_E):
    case C_S_T(KC_I):
      return 215;
    default:
      return 190;
  }
}

// RGB timeout
#define RGB_CUSTOM_TIMEOUT 5 // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool led_on = true;
void matrix_scan_user(void) {
  // idle_timer needs to be set one time
  if (idle_timer == 0) idle_timer = sync_timer_read();

    if (led_on && timer_elapsed(idle_timer) > 30000) {
      halfmin_counter++;
      idle_timer = sync_timer_read();
    }

    if (led_on && halfmin_counter >= RGB_CUSTOM_TIMEOUT * 2) {
      rgb_matrix_disable_noeeprom();
      led_on = false;
      halfmin_counter = 0;
    }
}

// RGB suspend
void suspend_power_down_user(void) {
  rgb_matrix_disable_noeeprom();
}
void suspend_wakeup_init_user(void) {
  rgb_matrix_enable_noeeprom();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // RGB resume
  if (record->event.pressed) {
    if (led_on == false) {
      rgb_matrix_enable_noeeprom();
      led_on = true;
    }
    idle_timer = sync_timer_read();
    halfmin_counter = 0;
  }

  // Caps word
  if (!process_caps_word(keycode, record)) { return false; }

  switch (keycode) {
    // Macros
    case _M0: // Link to keymap legends SVG file
      if (record->event.pressed) {
        SEND_STRING("https://raw.githubusercontent.com/dlford/qmk_firmware/master/keyboards/keebio/iris/keymaps/dlford/legends.svg");
      }
      return false;
  }

  return true;
}

// OLEDs
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            oled_write_ln_P(PSTR("Colemak"), false);
            break;
        case _NAVIGATION:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case _SPECIAL:
            oled_write_ln_P(PSTR("Special"), false);
            break;
        case _MOUSE:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        default:
            if (default_layer_state - 1 == _COLEMAK) {
                oled_write_ln_P(PSTR("Colemak"), false);
            } else {
                oled_write_ln_P(PSTR("Qwerty"), false);
            }
    }
}

void dynamic_macro_record_start_user(void) {
    is_macro_recording = true;
}
void dynamic_macro_record_end_user(int8_t direction) {
    is_macro_recording = false;
}
void oled_render_dynamic_macro_status(void) {
    if (is_macro_recording) {
        oled_write_ln_P(PSTR("Macro Recording..."), false);
    } else {
        oled_write_ln_P(PSTR(""), false);
    }
}

void oled_render_caps_lock_status(void) {
    if (host_keyboard_led_state().caps_lock) {
        oled_write_ln_P(PSTR("CAPS LOCK"), false);
    } else if (caps_word_enabled) {
        oled_write_ln_P(PSTR("CAPS word"), false);
    } else {
        oled_write_ln_P(PSTR(""), false);
    }
}

// DLF Logo
static void oled_render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,248, 60, 12, 12, 12, 12, 12, 12, 12, 12,196,240,248,252,252,252,124,124,124,252,252,248,248,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,224,240,124, 31,  7,  1,  0,128,192,224,240,240,248,248,248,  0,255,255,255,255,255,254,252,248,248,  1,  3, 11, 59,251,225,128,  0,  0,  0,  0,  0,224,224,224,224,224,224,224,224,192,128,  0,  0,224,224,224,224,  0,  0,  0,  0,  0,  0,224,224, 96, 96, 96, 96, 96,  0,224,224, 96, 96, 96, 96, 96,224,224,  0,  0,224,224, 96, 96, 96, 96,224,224,  0,224,224,224, 96, 96, 96,224,224,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  7, 31, 60,248,224,128,  0, 63,127,255,255,255,241,240,240,240,255,255,255,127, 63,  0,  0,  0,  0,128,192,240,124, 31,  7,  3,  0,  0,  0,  0,  0,255,255,255,255,225,225,251,255,255,127, 63,  0,255,255,255,255,224,224,224,224,224,  0,255,255, 12, 12, 12, 12,  0,  0,255,255,128,128,128,128,128,255,255,  0,  0,255,255, 28, 28, 60,252,255,207,  0,255,255,255,128,128,128,192,255,255,127,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 30, 60, 48, 48, 49, 49, 51, 51, 51, 51, 49, 49, 48, 48, 48, 48, 48, 56, 62, 15,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  0,  0,  0,  0,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_dynamic_macro_status();
        oled_render_caps_lock_status();
    } else {
        oled_render_logo();
    }
}
#endif // OLED_ENABLE

// RGB Layers (Enable animations in config.h)
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
            rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
            rgb_matrix_set_speed_noeeprom(default_speed);
            rgb_matrix_mode_noeeprom(default_animation);
            break;
    }
    return state;
}

// Indicators
void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock || caps_word_enabled) {
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
}

// Quantum keys / Abbreviations
enum {
    VVV = KC_TRNS,
    XXX = KC_NO,
    CSA_Q = MEH_T(KC_Q),
    CA_W = LCA_T(KC_W),
    CS_E = C_S_T(KC_E),
    CS_F = C_S_T(KC_F),
    CS_I = C_S_T(KC_I),
    CS_U = C_S_T(KC_U),
    CA_O = LCA_T(KC_O),
    CA_Y = LCA_T(KC_Y),
    CSA_P = MEH_T(KC_P),
    CSA_SCLN = MEH_T(KC_SCLN),
    LGUI_A = LGUI_T(KC_A),
    LALT_S = LALT_T(KC_S),
    LALT_R = LALT_T(KC_R),
    LCTL_D = LCTL_T(KC_D),
    LCTL_S = LCTL_T(KC_S),
    LSFT_F = LSFT_T(KC_F),
    _LSFT_T = LSFT_T(KC_T),
    RSFT_J = RSFT_T(KC_J),
    RSFT_N = RSFT_T(KC_N),
    RCTL_K = RCTL_T(KC_K),
    RCTL_E = RCTL_T(KC_E),
    RALT_L = RALT_T(KC_L),
    RALT_I = RALT_T(KC_I),
    RGUI_SCLN = RGUI_T(KC_SCLN),
    RGUI_O = RGUI_T(KC_O),
    LT3_SPC = LT(3,KC_SPC),
    LT2_TAB = LT(2,KC_TAB),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x5_3(
        //|--------------------------------------------|                    |--------------------------------------------|
            CSA_Q,   CA_W,    CS_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    CS_I,    CA_O,    CSA_P,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            LGUI_A,  LALT_S,  LCTL_D,  LSFT_F,  KC_G,                         KC_H,    RSFT_J,  RCTL_K,  RALT_L,  RGUI_SCLN,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
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
            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                       KC_ESC,  LT3_SPC, KC_BSPC,    KC_DEL, LT2_TAB,  KC_ENT
        //                           |--------+--------+--------|  |--------+--------+--------|
    ),
    [_NAVIGATION] = LAYOUT_split_3x5_3(
            // TODO: Formatting
        //|--------------------------------------------|                    |--------------------------------------------|
            MEH_T(KC_F1), LCA_T(KC_F2), C_S_T(KC_F3), KC_F4, KC_F5, KC_F6, KC_F7, C_S_T(KC_F8), LCA_T(KC_F9), MEH_T(KC_F10),
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            LGUI_T(KC_FIND), LALT_T(KC_HOME), LCTL_T(KC_PGUP), LSFT_T(KC_PGDN), KC_END, KC_LEFT, RSFT_T(KC_DOWN), RCTL_T(KC_UP), RALT_T(KC_RGHT), RGUI_T(KC_F11),
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            DF(0), DF(1), KC_VOLD, KC_VOLU, RESET, KC_MUTE, KC_MPLY, KC_MPRV, KC_MNXT, KC_F12,
        //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
            VVV, TG(4), VVV, VVV, VVV, VVV
        //                           |--------+--------+--------|  |--------+--------+--------|
    ),
    [_SPECIAL] = LAYOUT_split_3x5_3(
        //|--------------------------------------------|                    |--------------------------------------------|
            MEH_T(KC_1), LCA_T(KC_2), C_S_T(KC_3), KC_4, KC_5, KC_6, KC_7, C_S_T(KC_8), LCA_T(KC_9), MEH_T(KC_0),
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            LGUI_T(KC_GRV), KC_LALT, LCTL_T(KC_LBRC), LSFT_T(KC_RBRC), KC_LPRN, KC_RPRN, RSFT_T(KC_MINS), RCTL_T(KC_EQL), RALT_T(KC_BSLS), RGUI_T(KC_QUOT),
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            KC_TILD, KC_CAPS, KC_LCBR, KC_RCBR, EEP_RST, XXX, KC_UNDS, KC_PLUS, KC_PIPE, KC_DQUO,
        //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
            VVV, VVV, VVV, VVV, TG(4), VVV
        //                           |--------+--------+--------|  |--------+--------+--------|
    ),
    [_MOUSE] = LAYOUT_split_3x5_3(
        //|--------------------------------------------|                    |--------------------------------------------|
            KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, DM_REC1, KC_WSTP, KC_ACL2, KC_ACL1, KC_ACL0, KC_WFWD,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, DM_PLY1, KC_WREF, KC_BTN1, KC_BTN2, KC_BTN3, KC_WBAK,
        //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
            KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22,
        //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
            VVV, TG(4), VVV, VVV, TG(4), VVV
        //                           |--------+--------+--------|  |--------+--------+--------|
    ),
};
