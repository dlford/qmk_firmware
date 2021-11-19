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
#include <stdio.h>

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

uint16_t default_animation = RGB_MATRIX_CYCLE_SPIRAL;

// Init
void keyboard_post_init_user(void) {
  rgb_matrix_mode_noeeprom(default_animation);
  rgb_matrix_set_speed(50);
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

// TODO: Import
// TODO: Caps Lock/Colemak/Rec keys

// OLEDs
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
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

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_layer_state();
        oled_render_keylog();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
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

#endif // OLED_ENABLE

// RGB Layers (Enable animations in config.h)
// ----------
// RGB Modes
// 1 = Static (use with rgblight_sethsv)
// 2-5 = Breathing
// 6-8 = Rainbow
// 9-14 = Swirl
// 15-20 = Snake
// 21-24 = Nightrider
// 25 = Christmas
// 26-30 = Static Gradient
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _SPECIAL:
      rgblight_mode(1);
      rgblight_sethsv(HSV_PURPLE);
      break;
    case _NAVIGATION:
      rgblight_mode(1);
      rgblight_sethsv(HSV_BLUE);
      break;
    case _MOUSE:
      rgblight_mode(1);
      rgblight_sethsv(HSV_GREEN);
      break;
    default:
      if (default_layer_state - 1 == _COLEMAK) {
        rgblight_mode(3);
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
          rgblight_sethsv(HSV_YELLOW);
        } else {
          rgblight_sethsv(HSV_WHITE);
        }
      } else {
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
          rgblight_mode(1);
          rgblight_sethsv(HSV_YELLOW);
        } else {
          rgb_matrix_mode_noeeprom(default_animation);
        }
      }
      break;
  }
  return state;
}

