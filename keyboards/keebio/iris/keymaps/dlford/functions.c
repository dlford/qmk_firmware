#include QMK_KEYBOARD_H

// TODO: Macros (keymaps legends?)
// TODO: Fix only one half breathing in macro recording mode

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

// Init
void keyboard_post_init_user(void) {
  rgblight_mode(14);
  rgblight_sethsv(HSV_PURPLE);
  breathing_disable();
  backlight_enable();
  backlight_level(3);
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

// Backlight / RGB timeout
#define BACKLIGHT_TIMEOUT 5 // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool led_on = true;
void matrix_scan_user(void) {
  // idle_timer needs to be set one time
  if (idle_timer == 0) idle_timer = sync_timer_read();

  #ifdef BACKLIGHT_ENABLE
    if (led_on && timer_elapsed(idle_timer) > 30000) {
      halfmin_counter++;
      idle_timer = sync_timer_read();
    }

    if (led_on && halfmin_counter >= BACKLIGHT_TIMEOUT * 2) {
      backlight_disable();
      rgblight_disable();
      led_on = false;
      halfmin_counter = 0;
    }
  #endif
}

// Backlight / RGB suspend
void suspend_power_down_user(void) {
  backlight_disable();
  rgblight_disable();
}
void suspend_wakeup_init_user(void) {
  backlight_enable();
  rgblight_enable();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Backlight / RGB resume
  if (record->event.pressed) {
    #ifdef BACKLIGHT_ENABLE
    if (led_on == false) {
      backlight_enable();
      rgblight_enable();
      led_on = true;
    }
    #endif
    idle_timer = sync_timer_read();
    halfmin_counter = 0;
  }

  switch (keycode) {
    // Macros
    case _M0:
      if (record->event.pressed) {
        SEND_STRING("Macro Test!");
      }
      return false;
  }

  return true;
}

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
        rgblight_sethsv(HSV_WHITE);
      } else {
        rgblight_mode(14);
        rgblight_sethsv(HSV_PURPLE);
      }
      break;
  }
  return state;
}

// Dynamic Macro Recording Backlight
void dynamic_macro_record_start_user(void) {
  breathing_enable();
}

void dynamic_macro_record_end_user(int8_t direction) {
  breathing_disable();
}
