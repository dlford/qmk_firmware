#include QMK_KEYBOARD_H

// TODO: Tune Change LEDs on layers
// TODO: Test Turn off backlight on suspend
// TODO: Macros

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

// Backlight timeout feature
#define BACKLIGHT_TIMEOUT 1 // in minutes
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static uint8_t old_backlight_level = -1;
static bool led_on = true;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, LGUI(KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, RGUI(KC_BSLS), LALT_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, RALT_T(KC_QUOT), KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, TT(3), KC_BTN2, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, LCTL_T(KC_ENT), KC_SPC, TT(1), TT(2), KC_SPC, RCTL_T(KC_ENT)),
	[_LOWER] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_PGUP, KC_INS, KC_UP, KC_PAUS, KC_HOME, KC_NO, KC_P7, KC_P8, KC_P9, KC_PLUS, KC_PMNS, KC_NO, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_PSCR, KC_P4, KC_P5, KC_P6, KC_PAST, KC_PSLS, KC_NO, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_NO, KC_NO, KC_NO, KC_APP, KC_P1, KC_P2, KC_P3, KC_PDOT, KC_SPC, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_P0),
	[_RAISE] = LAYOUT(KC_EXEC, KC_MAIL, KC_CALC, KC_MYCM, KC_MSEL, KC_NO, KC_BRID, KC_BRIU, KC_NO, KC_NO, KC_NO, KC_SLEP, KC_NO, KC_NO, KC_MS_U, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MNXT, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_FIND, KC_NO, KC_NO, KC_ACL0, KC_ACL1, KC_ACL2, KC_NO, KC_NO, KC_NO, KC_NO, KC_CUT, KC_COPY, KC_PSTE, KC_NO, KC_NO, KC_MPLY, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_TRNS, KC_BTN3, KC_NO),
	[_ADJUST] = LAYOUT(RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_HUI, RGB_SAI, RGB_VAI, RGB_M_P, RGB_M_B, KC_NO, KC_NO, KC_NO, BL_STEP, BL_ON, KC_NO, KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, RGB_M_R, RGB_M_SW, KC_NO, KC_NO, KC_NO, BL_INC, BL_TOGG, KC_NO, RGB_M_T, RGB_TOG, RGB_MOD, RGB_SPI, RGB_M_SN, RGB_M_K, KC_NO, KC_NO, KC_NO, BL_DEC, BL_OFF, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, RGB_RMOD, RGB_SPD, RGB_M_X, RGB_M_G, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Backlight timeout feature
  if (record->event.pressed) {
    #ifdef BACKLIGHT_ENABLE
    if (led_on == false || old_backlight_level == -1) {
      if (old_backlight_level == -1) old_backlight_level = get_backlight_level();
      backlight_set(old_backlight_level);
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
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
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
      case _LOWER:
          rgblight_mode(1);
          rgblight_sethsv(HSV_BLUE);
          break;
      case _RAISE:
          rgblight_mode(1);
          rgblight_sethsv(HSV_PURPLE);
          break;
      case _ADJUST:
          rgblight_mode(1);
          rgblight_sethsv(HSV_RED);
          break;
      default:
          rgblight_mode(14);
          break;
    }
  return state;
}

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
