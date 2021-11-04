#include QMK_KEYBOARD_H

// TODO: Macros (macro keymaps legends?)
// TODO: Change breathing settings when macro recording - https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_backlight
// TODO: Fix layer change when entering/leaving macro recording mode
// TODO: Fix only one half breathing in macro recording mode
// TODO: Flash red when using top row keys on base layer to deter use
// TODO: Make colemak persistent when active

#define _QWERTY 0
#define _COLEMAK 1
#define _SPECIAL 2
#define _MACRO 3
#define _MOUSE 4

/*
// Macros
enum custom_keycodes {
  M_TEST = SAFE_RANGE,
};
*/

// Keymap -
// Upload `qmk_configurator.json` to https://config.qmk.fm to edit,
// use `qmk json2c qmk_configurator.json` to dump this code to CLI,
// copy/paste here.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, LALT_T(KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, RALT_T(KC_BSLS), LSFT_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, RSFT_T(KC_QUOT), KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, TG(1), DM_REC1, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RCTL, KC_ENT, LGUI_T(KC_SPC), MO(2), MO(3), RGUI_T(KC_SPC), KC_ENT),
	[1] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_TRNS, KC_TRNS, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_TRNS, KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_TRNS, KC_TRNS, KC_K, KC_M, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, KC_GRV, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_EQL, KC_TRNS, KC_TRNS, KC_TILD, KC_LPRN, KC_LBRC, KC_LCBR, KC_LT, KC_TRNS, KC_TRNS, KC_GT, KC_RCBR, KC_RBRC, KC_RPRN, KC_PLUS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(4), KC_UNDS, KC_TRNS),
	[3] = LAYOUT(KC_TRNS, DM_PLY1, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, RALT_T(KC_PIPE), KC_TRNS, KC_WSCH, KC_WBAK, KC_WSTP, KC_WREF, KC_WFWD, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, KC_MUTE, KC_TRNS, KC_TRNS, BL_INC, BL_DEC, BL_TOGG, BL_ON, BL_OFF, KC_TRNS, KC_MPLY, KC_CALC, KC_UNDO, KC_AGIN, KC_BRID, KC_BRIU, KC_TRNS, KC_TRNS, KC_MINS, TG(4), KC_TRNS, KC_TRNS, KC_TRNS),
	[4] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_WBAK, KC_WFWD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_BTN3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ACL2, KC_ACL1, KC_ACL0, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(4), TG(4), KC_TRNS, KC_TRNS)
};

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
