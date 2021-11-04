#include QMK_KEYBOARD_H

// TODO: Macros (macro keymaps legends?)

#define _QWERTY 0
#define _COLEMAK 1
#define _SPECIAL 2
#define _MACRO 3
#define _MOUSE 4

// RGB states
static bool isColemak = false;
static bool isMouse = false;
static bool isMacroRecording = false;

// Backlight timeout feature
#define BACKLIGHT_TIMEOUT 5 // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool led_on = true;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  SPECIAL,
  MACRO,
  MOUSE,
  // Macros
  /*
  M_TEST,
  */
};

// Keymap -
// Upload `qmk_configurator.json` to https://config.qmk.fm to edit,
// use `qmk json2c qmk_configurator.json` to dump this code to CLI,
// copy/paste here.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, LALT_T(KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, RALT_T(KC_BSLS), LSFT_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, RSFT_T(KC_QUOT), KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, TG(1), DM_REC1, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RCTL, KC_ENT, LGUI_T(KC_SPC), TT(2), TT(3), RGUI_T(KC_SPC), KC_ENT),
	[1] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_TRNS, KC_TRNS, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_TRNS, KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_TRNS, KC_TRNS, KC_K, KC_M, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TT(2), TT(3), KC_TRNS, KC_TRNS),
	[2] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, KC_GRV, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_EQL, KC_TRNS, KC_TRNS, KC_TILD, KC_LPRN, KC_LBRC, KC_LCBR, KC_LT, KC_TRNS, KC_TRNS, KC_GT, KC_RCBR, KC_RBRC, KC_RPRN, KC_PLUS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(4), KC_UNDS, KC_TRNS),
	[3] = LAYOUT(KC_TRNS, DM_PLY1, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, RALT_T(KC_BSLS), KC_TRNS, KC_WSCH, KC_WBAK, KC_WSTP, KC_WREF, KC_WFWD, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, KC_MUTE, KC_TRNS, KC_TRNS, BL_INC, BL_DEC, BL_TOGG, BL_ON, BL_OFF, KC_TRNS, KC_MPLY, KC_CALC, KC_UNDO, KC_AGIN, KC_BRID, KC_BRIU, KC_TRNS, KC_TRNS, KC_MINS, TG(4), KC_TRNS, KC_TRNS, KC_TRNS),
	[4] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_BTN3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ACL2, KC_ACL1, KC_ACL0, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(4), TG(4), KC_TRNS, KC_TRNS)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Backlight timeout feature
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

  // Layers
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (isColemak) {
        layer_off(_COLEMAK);
        isColemak = false;
      } else {
        layer_on(_COLEMAK);
        isColemak = true;
      }
      return false;
      break;
    case SPECIAL:
      if (record->event.pressed) {
        layer_on(_SPECIAL);
      } else {
        layer_off(_SPECIAL);
      }
      return false;
      break;
    case MACRO:
      if (record->event.pressed) {
        layer_on(_MACRO);
      } else {
        layer_off(_MACRO);
      }
      return false;
      break;
    case MOUSE:
      if (record->event.pressed) {
        layer_on(_MOUSE);
        isMouse = true;
      } else {
        layer_off(_MOUSE);
        isMouse = false;
      }
      return false;
      break;
  }

  // Macros
  /*
  switch (keycode) {
    case M_TEST:
      if (record->event.pressed) {
        SEND_STRING("Macro Test!");
      }
      break;
  }
  */

  return true;
}

// Backlight timeout feature
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
          if (isMacroRecording) {
            rgblight_mode(3);
          } else {
            rgblight_mode(1);
          }
          rgblight_sethsv(HSV_GREEN);
          break;
      case _COLEMAK:
          if (isMacroRecording) {
            rgblight_mode(3);
            rgblight_sethsv(HSV_RED);
          } else {
            rgblight_mode(3);
            rgblight_sethsv(HSV_WHITE);
          }
          break;
      default:
          if (isMacroRecording) {
              rgblight_mode(1);
              rgblight_sethsv(HSV_RED);
          } else {
              rgblight_mode(14);
              rgblight_sethsv(HSV_PURPLE);
          }
          break;
    }
  return state;
}

void dynamic_macro_record_start_user(void) {
    isMacroRecording = true;
}

void dynamic_macro_record_end_user(int8_t direction) {
    isMacroRecording = false;
    if (isColemak) {
        rgblight_mode(3);
        rgblight_sethsv(HSV_WHITE);
    } else if (isMouse) {
        rgblight_mode(1);
        rgblight_sethsv(HSV_ORANGE);
    } else {
        rgblight_mode(14);
        rgblight_sethsv(HSV_PURPLE);
    }
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
