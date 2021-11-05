#include QMK_KEYBOARD_H

// TODO: Macros (alt tab, etc, keymaps legends?)
// TODO: Change breathing settings when macro recording - https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_backlight
// TODO: Fix layer change when entering/leaving macro recording mode
// TODO: Fix only one half breathing in macro recording mode
// TODO: Make colemak persistent when active

#define _QWERTY 0
#define _COLEMAK 1
#define _SPECIAL 2
#define _MACRO 3
#define _MOUSE 4

/*
// Macros
enum custom_keycodes {
  M_ALT_TAB = SAFE_RANGE,
};
*/

// Backlight timeout
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

// Backlight suspend
void suspend_power_down_user(void) {
  backlight_disable();
  rgblight_disable();
}
void suspend_wakeup_init_user(void) {
  backlight_enable();
  rgblight_enable();
}

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Backlight resume
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

  mod_state = get_mods();
  switch (keycode) {
    // Alt+Escape = Alt+Tab
    case KC_ESC:
        if ((mod_state & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
            if (record->event.pressed) {
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false; // Stop processing keycodes
        }
        return true; // Continue processing keycodes

    // Shift+Backspace = Delete
    case KC_BSPC:
        {
            static bool delkey_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    delkey_registered = true;
                    set_mods(mod_state);
                    return false;
                } else {
                    if (delkey_registered) {
                        unregister_code(KC_DEL);
                        delkey_registered = false;
                        return true;
                    }
                }
            }
            return true;
        }

      // Macros
      /*
      case M_TEST:
        if (record->event.pressed) {
          SEND_STRING("Macro Test!");
        }
        return false;
      */
  }

  return true;
}

// RGB Layers
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
      case _MACRO:
          rgblight_mode(1);
          rgblight_sethsv(HSV_PURPLE);
          break;
      case _SPECIAL:
          rgblight_mode(1);
          rgblight_sethsv(HSV_BLUE);
          break;
      case _MOUSE:
          rgblight_mode(1);
          rgblight_sethsv(HSV_GREEN);
          break;
      case _COLEMAK:
          rgblight_mode(3);
          rgblight_sethsv(HSV_WHITE);
          break;
      default:
          rgblight_mode(14);
          rgblight_sethsv(HSV_PURPLE);
          break;
    }
  return state;
}

void keyboard_post_init_user(void) {
    breathing_disable();
}

void dynamic_macro_record_start_user(void) {
    breathing_enable();
}

void dynamic_macro_record_end_user(int8_t direction) {
    breathing_disable();
}

// Encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(biton32(layer_state)){
         case 3:
            if (clockwise){
                tap_code(KC_VOLU);
            } else{
                tap_code(KC_VOLD);
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_WH_D);
            } else {
                tap_code(KC_WH_U);
            }
            break;
    }
    return true;
}
