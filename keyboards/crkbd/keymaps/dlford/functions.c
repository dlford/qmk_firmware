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

#include QMK_KEYBOARD_H

// Layers
#define _QWERTY 0
#define _COLEMAK 1
#define _NAVIGATION 2
#define _SPECIAL 3
#define _MOUSE 4

// Macros
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
    if (host_keyboard_led_state().caps_lock) {
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
