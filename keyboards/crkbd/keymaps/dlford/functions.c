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

static uint16_t default_animation = RGB_MATRIX_CYCLE_SPIRAL;
static int default_speed = 50;
static uint16_t secondary_animation = RGB_MATRIX_HUE_WAVE;
static int secondary_speed = 150;

// Init
void keyboard_post_init_user(void) {
  rgb_matrix_mode_noeeprom(default_animation);
  rgb_matrix_set_speed(default_speed);
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
// TODO: OLEDs
// TODO: EE_HANDS
// TODO: Macro rec oled indicator

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

// WPM
int timer = 0;
char wpm_text[5];
int x = 31;
int currwpm = 0;
int vert_count = 0; 
//=============  USER CONFIG PARAMS  ===============
float max_wpm = 110.0f; //WPM value at the top of the graph window
int graph_refresh_interval = 80; //in milliseconds
int graph_area_fill_interval = 3; //determines how dense the horizontal lines under the graph line are; lower = more dense
int vert_interval = 3; //determines frequency of vertical lines under the graph line
bool vert_line = false; //determines whether to draw vertical lines
int graph_line_thickness = 3; //determines thickness of graph line in pixels
void oled_render_wpm(void) {
  //get current WPM value
  currwpm = get_current_wpm();
  //check if it's been long enough before refreshing graph
  if(timer_elapsed(timer) > graph_refresh_interval){
    // main calculation to plot graph line
    x = 32 - ((currwpm / max_wpm) * 32);
    //first draw actual value line
    for(int i = 0; i <= graph_line_thickness - 1; i++){
      oled_write_pixel(1, x + i, true);
    }
    //then fill in area below the value line
    if(vert_line){
      if(vert_count == vert_interval){
        vert_count = 0;
        while(x <= 32){
          oled_write_pixel(1, x, true);
          x++;
        }
      } else {
        for(int i = 32; i > x; i--){
          if(i % graph_area_fill_interval == 0){
            oled_write_pixel(1, i, true);
          }
        }
        vert_count++;
      }
    } else {
      for(int i = 32; i > x; i--){
        if(i % graph_area_fill_interval == 0){
          oled_write_pixel(1, i, true);
        }
      }
    }
    //then move the entire graph one pixel to the right
    oled_pan(false); 
    //refresh the timer for the next iteration
    timer = timer_read();
  }
  //format current WPM value into a printable string
  sprintf(wpm_text,"%i", currwpm);
  //formatting for triple digit WPM vs double digits, then print WPM readout
  if(currwpm >= 100){
    oled_set_cursor(14, 3);
    oled_write("WPM: ", false);
    oled_set_cursor(18, 3);
    oled_write(wpm_text, false);
  } else if (currwpm >= 10){
    oled_set_cursor(15, 3);
    oled_write("WPM: ", false);
    oled_set_cursor(19, 3);
    oled_write(wpm_text, false);
  } else if (currwpm > 0) {
    oled_set_cursor(16, 3);
    oled_write("WPM: ", false);
    oled_set_cursor(20, 3);
    oled_write(wpm_text, false);		
  }
}
// WPM

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_wpm();
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
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _SPECIAL:
      rgb_matrix_sethsv(HSV_ORANGE);
      rgb_matrix_set_speed_noeeprom(secondary_speed);
      rgb_matrix_mode_noeeprom(secondary_animation);
      break;
    case _NAVIGATION:
      rgb_matrix_sethsv(HSV_BLUE);
      rgb_matrix_set_speed_noeeprom(secondary_speed);
      rgb_matrix_mode_noeeprom(secondary_animation);
      break;
    case _MOUSE:
      rgb_matrix_sethsv(HSV_GREEN);
      rgb_matrix_set_speed_noeeprom(secondary_speed);
      rgb_matrix_mode_noeeprom(secondary_animation);
      break;
    default:
      if (default_layer_state - 1 == _COLEMAK) {
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
          rgb_matrix_sethsv(HSV_TURQUOISE);
          rgb_matrix_set_speed_noeeprom(secondary_speed);
          rgb_matrix_mode_noeeprom(secondary_animation);
        } else {
          rgb_matrix_sethsv(HSV_CYAN);
          rgb_matrix_set_speed_noeeprom(secondary_speed);
          rgb_matrix_mode_noeeprom(secondary_animation);
        }
      } else {
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
          rgb_matrix_sethsv(HSV_RED);
          rgb_matrix_set_speed_noeeprom(secondary_speed);
          rgb_matrix_mode_noeeprom(secondary_animation);
        } else {
          rgb_matrix_sethsv(HSV_ORANGE);
          rgb_matrix_set_speed_noeeprom(default_speed);
          rgb_matrix_mode_noeeprom(default_animation);
        }
      }
      break;
  }
  return state;
}
