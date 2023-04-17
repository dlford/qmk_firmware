/*
Copyright 2023 @dlford
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
#include "version.h"
#include "custom_keycodes_user.h"
#include "layers_user.h"
#include "rgb_matrix_user.h"
#include "rgb_timeout_user.h"
#include "eeprom_user.h"
#include "split_util.h"
#include "rgb_idle_mode_user.h"

bool is_left_hand;

bool process_record_custom_keycodes_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
    uint8_t osm  = get_oneshot_mods();
    switch (keycode) {
        case M_QK_BOOT:
            if (record->event.pressed) {
                if ((mods | osm) & MOD_MASK_ALT && (mods | osm) & MOD_MASK_CTRL) {
                    is_left_hand = isLeftHand;
                    eeconfig_init();
                    eeconfig_update_handedness(is_left_hand);
                    eeconfig_init_user();
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                    rgb_matrix_mode(RGB_MATRIX_SPLASH);
                    rgb_matrix_sethsv(HSV_BLUE);
                } else if ((mods | osm) & MOD_MASK_SHIFT) {
                    clear_mods();
                    clear_oneshot_mods();
                    send_string("qmk generate-version-h -q -o quantum/version.h && make -j$(nproc) --output-sync " QMK_KEYBOARD ":" QMK_KEYMAP ":flash");
                    set_mods(mods);
                } else if ((mods | osm) & MOD_MASK_ALT) {
                    clear_mods();
                    clear_oneshot_mods();
                    send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
                    set_mods(mods);
                } else {
                    reset_keyboard();
                }
            }
            break;
        case M_RGB_SPD:
            if (record->event.pressed) {
                if ((mods | osm) & MOD_MASK_ALT) {
                    rgb_matrix_mode_noeeprom(user_config.rgb_idle_mode);
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_idle_speed);
                    rgb_matrix_sethsv_noeeprom(user_config.rgb_idle_hsv.h, user_config.rgb_idle_hsv.s, user_config.rgb_idle_hsv.v);
                    if ((mods | osm) & MOD_MASK_SHIFT) {
                        rgb_matrix_decrease_speed_noeeprom();
                    } else {
                        rgb_matrix_increase_speed_noeeprom();
                    }
                    user_config.rgb_idle_speed = rgb_matrix_get_speed();
                    write_user_config();
                } else if ((mods | osm) & MOD_MASK_SHIFT) {
                    rgb_matrix_reload_from_eeprom();
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                    rgb_matrix_decrease_speed_noeeprom();
                    user_config.rgb_speed = rgb_matrix_get_speed();
                    write_user_config();
                } else {
                    rgb_matrix_reload_from_eeprom();
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                    rgb_matrix_increase_speed_noeeprom();
                    user_config.rgb_speed = rgb_matrix_get_speed();
                    write_user_config();
                }
                return false;
            }
            break;
        case M_RGB_HUE:
            if (record->event.pressed) {
                rgb_matrix_reload_from_eeprom();
                rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                if ((mods | osm) & MOD_MASK_ALT) {
                    rgb_matrix_mode_noeeprom(user_config.rgb_idle_mode);
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_idle_speed);
                    rgb_matrix_sethsv_noeeprom(user_config.rgb_idle_hsv.h, user_config.rgb_idle_hsv.s, user_config.rgb_idle_hsv.v);
                    if ((mods | osm) & MOD_MASK_SHIFT) {
                        rgb_matrix_decrease_hue_noeeprom();
                    } else {
                        rgb_matrix_increase_hue_noeeprom();
                    }
                    user_config.rgb_idle_hsv = rgb_matrix_get_hsv();
                    write_user_config();
                } else if ((mods | osm) & MOD_MASK_SHIFT) {
                    rgb_matrix_decrease_hue();
                } else {
                    rgb_matrix_increase_hue();
                }
                return false;
            }
            break;
        case M_RGB_STP:
            if (record->event.pressed) {
                rgb_matrix_reload_from_eeprom();
                rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                if ((mods | osm) & MOD_MASK_CTRL && (mods | osm) & MOD_MASK_ALT) {
                    user_config.rgb_speed           = 150;
                    user_config.is_rgb_idle_enabled = true;
                    user_config.rgb_idle_speed      = 50;
                    user_config.rgb_idle_mode       = RGB_MATRIX_DIGITAL_RAIN;
                    user_config.rgb_idle_hsv.h      = 85;
                    user_config.rgb_idle_hsv.s      = 255;
                    user_config.rgb_idle_hsv.v      = 255;
                    write_user_config();
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_speed);
                    rgb_matrix_mode(RGB_MATRIX_SPLASH);
                    rgb_matrix_sethsv(HSV_BLUE);
                } else if ((mods | osm) & MOD_MASK_ALT) {
                    rgb_matrix_mode_noeeprom(user_config.rgb_idle_mode);
                    rgb_matrix_set_speed_noeeprom(user_config.rgb_idle_speed);
                    rgb_matrix_sethsv_noeeprom(user_config.rgb_idle_hsv.h, user_config.rgb_idle_hsv.s, user_config.rgb_idle_hsv.v);
                    if ((mods | osm) & MOD_MASK_SHIFT) {
                        rgb_matrix_step_reverse_noeeprom();
                    } else {
                        rgb_matrix_step_noeeprom();
                    }
                    user_config.rgb_idle_mode = rgb_matrix_get_mode();
                    write_user_config();
                } else if ((mods | osm) & MOD_MASK_SHIFT) {
                    rgb_matrix_step_reverse();
                } else if ((mods | osm) & MOD_MASK_CTRL) {
                    toggle_rgb_idle_mode_user();
                } else {
                    rgb_matrix_step();
                }
                return false;
            }
            break;
        case M_VDSL:
            if (record->event.pressed) {
                clear_mods();
                clear_oneshot_mods();
                register_code(KC_LGUI);
                register_code(KC_LCTL);
                tap_code(KC_LEFT);
                unregister_code(KC_LGUI);
                unregister_code(KC_LCTL);
                set_mods(mods);
                return false;
            }
        case M_VDSR:
            if (record->event.pressed) {
                clear_mods();
                clear_oneshot_mods();
                register_code(KC_LGUI);
                register_code(KC_LCTL);
                tap_code(KC_RIGHT);
                unregister_code(KC_LGUI);
                unregister_code(KC_LCTL);
                set_mods(mods);
                return false;
            }
        case M_MNXT:
            if (record->event.pressed) {
                if ((mods | osm) & MOD_MASK_SHIFT) {
                    tap_code(KC_MPRV);
                } else {
                    tap_code(KC_MNXT);
                }
                return false;
            }
        case M_SKN_ARW:
            if (record->event.pressed) {
                send_string("->");
            }
            break;
        case M_FAT_ARW:
            if (record->event.pressed) {
                send_string("=>");
            }
            break;
        case KC_ESC:
            if (record->event.pressed && ((mods | osm) & (MOD_BIT(KC_LALT) | MOD_BIT(KC_LGUI)))) {
                tap_code(KC_TAB);
                return false;
            }
            break;
        case KC_ENT:
            if (record->event.pressed && ((mods | osm) & (MOD_BIT(KC_RALT) | MOD_BIT(KC_RGUI)))) {
                tap_code(KC_TAB);
                return false;
            }
            break;
    }

    return true;
}
