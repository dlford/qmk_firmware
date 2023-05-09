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
#include "os_detection.h"
#include "custom_keycodes_user.h"
#include "layers_user.h"
#include "layer_lock.h"
#include "rgb_matrix_user.h"
#include "rgb_timeout_user.h"
#include "eeprom_user.h"
#include "split_util.h"
#include "rgb_idle_mode_user.h"
#ifdef AUDIO_ENABLE
#    include "audio.h"
#    ifdef AUDIO_CLICKY
#        include "process_clicky.h"
#    endif
#    ifndef CLICKY_ON_SONG
#        define CLICKY_ON_SONG SONG(ZELDA_TREASURE)
#    endif
#    ifndef CLICKY_OFF_SONG
#        define CLICKY_OFF_SONG SONG(PLOVER_GOODBYE_SOUND)
#    endif
#    ifndef RESET_EEPROM_SONG
#        define RESET_EEPROM_SONG SONG(PLOVER_SOUND)
#    endif
#    ifndef RESET_RGB_SONG
#        define RESET_RGB_SONG SONG(PLANCK_SOUND)
#    endif
#    ifndef CAPS_ON_SONG
#        define CAPS_ON_SONG SONG(CAPS_LOCK_ON_SOUND)
#    endif
#    ifndef CAPS_OFF_SONG
#        define CAPS_OFF_SONG SONG(CAPS_LOCK_OFF_SOUND)
#    endif
float clicky_on_song[][2]    = CLICKY_ON_SONG;
float clicky_off_song[][2]   = CLICKY_OFF_SONG;
float reset_eeprom_song[][2] = RESET_EEPROM_SONG;
float reset_rgb_song[][2]    = RESET_RGB_SONG;
float caps_on_song[][2]      = CAPS_ON_SONG;
float caps_off_song[][2]     = CAPS_OFF_SONG;
#endif

bool is_left_hand;

bool should_cancel_mouse_layer = false;

bool process_record_custom_keycodes_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods = get_mods();
    uint8_t osm  = get_oneshot_mods();
    switch (keycode) {
        case LT3_SPC:
        case LT2_TAB:
        case TG(_MOUSE):
            if (record->event.pressed) {
                if (is_layer_locked(_SPECIAL) || is_layer_locked(_NAVIGATION)) {
                    layer_lock_all_off();
                    should_cancel_mouse_layer = true;
                    return false;
                }
            } else {
                if (should_cancel_mouse_layer) {
                    layer_off(_MOUSE);
                    should_cancel_mouse_layer = false;
                    return false;
                }
            }
            break;
        case M_AU:
#ifdef AUDIO_ENABLE
            if (record->event.pressed) {
                if ((mods | osm) & MOD_MASK_ALT) {
#    ifdef AUDIO_CLICKY
                    if (audio_is_on()) {
                        if (is_clicky_on()) {
                            clicky_off();
                            PLAY_SONG(clicky_off_song);
                        } else {
                            clicky_on();
                            PLAY_SONG(clicky_on_song);
                        }
                    }
#    endif
                } else {
                    if (audio_is_on()) {
                        audio_off();
                    } else {
                        audio_on();
                    }
                }
            }
            break;
#endif
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
#ifdef AUDIO_ENABLE
                    audio_on();
#    ifdef AUDIO_CLICKY
                    clicky_on();
#    endif
#endif
#ifdef AUDIO_ENABLE
                    PLAY_SONG(reset_eeprom_song);
#endif
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
#ifdef AUDIO_ENABLE
                    PLAY_SONG(reset_rgb_song);
#endif
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
                if (detected_host_os() == OS_WINDOWS) {
                    register_code(KC_LGUI);
                    register_code(KC_LCTL);
                    tap_code(KC_LEFT);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LCTL);
                } else {
                    register_code(KC_LGUI);
                    tap_code(KC_LBRC);
                    unregister_code(KC_LGUI);
                }
                set_mods(mods);
                return false;
            }
        case M_VDSR:
            if (record->event.pressed) {
                clear_mods();
                clear_oneshot_mods();
                if (detected_host_os() == OS_WINDOWS) {
                    register_code(KC_LGUI);
                    register_code(KC_LCTL);
                    tap_code(KC_RIGHT);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LCTL);
                } else {
                    register_code(KC_LGUI);
                    tap_code(KC_RBRC);
                    unregister_code(KC_LGUI);
                }
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
        case KC_CAPS:
#ifdef AUDIO_ENABLE
            if (record->event.pressed) {
                if (host_keyboard_led_state().caps_lock) {
                    PLAY_SONG(caps_on_song);
                } else {
                    PLAY_SONG(caps_off_song);
                }
            }
#endif
            break;
    }

    return true;
}
