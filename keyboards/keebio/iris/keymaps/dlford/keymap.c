#include QMK_KEYBOARD_H

// TODO: Fix Turn off backlight on suspend
// TODO: Macros

#define _QWERTY 0
#define _COLEMAK 1
#define _LOWER 2
#define _RAISE 3

// Backlight timeout feature
#define BACKLIGHT_TIMEOUT 1 // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static uint8_t old_backlight_level = -1;
static bool led_on = true;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
};

// Keymap -
// Upload `qmk_configurator.json` to https://config.qmk.fm to edit,
// use `qmk json2c qmk_configurator.json` to dump this code to CLI,
// copy/paste here.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, LGUI_T(KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, RGUI_T(KC_BSLS), LALT_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, RALT_T(KC_QUOT), KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, TG(1), KC_BTN3, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, LCTL_T(KC_SPC), KC_ENT, TT(2), TT(3), KC_ENT, RCTL_T(KC_SPC)),
	[1] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_TRNS, KC_TRNS, KC_A, KC_R, KC_S, KC_F, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_TRNS, KC_TRNS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_TRNS, KC_TRNS, KC_K, KC_M, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_PGUP, KC_INS, KC_UP, KC_PAUS, KC_HOME, KC_TRNS, KC_P7, KC_P8, KC_P9, KC_PLUS, KC_PMNS, TG(2), KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_PSCR, KC_P4, KC_P5, KC_P6, KC_PAST, KC_PSLS, KC_TRNS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_P1, KC_P2, KC_P3, KC_PDOT, KC_ENT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[3] = LAYOUT(RESET, KC_EXEC, KC_MAIL, KC_CALC, KC_MYCM, KC_MSEL, KC_BRID, KC_BRIU, KC_TRNS, KC_TRNS, KC_TRNS, KC_SLEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, BL_ON, BL_STEP, TG(3), KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_BTN3, BL_TOGG, BL_INC, KC_TRNS, KC_TRNS, KC_CUT, KC_COPY, KC_PSTE, KC_FIND, KC_TRNS, KC_MPLY, KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2, BL_OFF, BL_DEC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Backlight timeout feature
  if (record->event.pressed) {
    #ifdef BACKLIGHT_ENABLE
    if (led_on == false || old_backlight_level == -1) {
      if (old_backlight_level == -1) old_backlight_level = get_backlight_level();
      backlight_set(old_backlight_level);
      rgblight_enable();
      led_on = true;
    }
    #endif
    idle_timer = sync_timer_read();
    halfmin_counter = 0;
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        layer_on(_COLEMAK);
      } else {
        layer_off(_COLEMAK);
      }
      return false;
      break;
  }
  return true;
}

// Backlight timeout feature
void matrix_scan_user(void) {
  // idle_timer needs to be set one time
  if (idle_timer == 0) idle_timer = sync_timer_read();

  #ifdef BACKLIGHT_ENABLE
    if ( led_on && timer_elapsed(idle_timer) > 30000) {
      halfmin_counter++;
      idle_timer = sync_timer_read();
    }

    if ( led_on && halfmin_counter >= BACKLIGHT_TIMEOUT * 2) {
      old_backlight_level = get_backlight_level();
      backlight_set(0);
      rgblight_disable();
      led_on = false;
      halfmin_counter = 0;
    }
  #endif
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
      case _RAISE:
          rgblight_mode(1);
          rgblight_sethsv(HSV_PURPLE);
          break;
      case _LOWER:
          rgblight_mode(1);
          rgblight_sethsv(HSV_BLUE);
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

// Encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(biton32(layer_state)){
         case 2:
            if (clockwise){
                tap_code(KC_VOLU);
            } else{
                tap_code(KC_VOLD);
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
            break;
    }
    return true;
}
