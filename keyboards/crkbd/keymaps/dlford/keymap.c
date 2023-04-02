/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 @dlford

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

static uint16_t default_animation      = RGB_MATRIX_CYCLE_SPIRAL;
static int      default_speed          = 50;
static uint16_t secondary_animation    = RGB_MATRIX_HUE_WAVE;
static int      secondary_speed        = 150;
static bool     is_macro_recording     = false;
static bool     is_caps_word_active    = false;
bool            is_alt_tab_active      = false;
uint16_t        alt_tab_timer          = 0;
bool            is_mouse_jiggle_active = false;
bool            mouse_jiggle_direction = false;
uint16_t        mouse_jiggle_frequency = 15000;
uint16_t        mouse_jiggle_timer     = 0;
bool            is_scsm_active         = false;
// password generator
int  rand_size        = 32;
char rand_numbers[10] = "0123456789";
char rand_letters[26] = "abcdefghijklmnoqprstuvwyzx";
char rand_LETTERS[26] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
char rand_symbols[8]  = "!@#$^&*?";
char rand_password[32];

// Layers
enum layers {
    _QWERTY = 0,
    _COLEMAK,
    _NAVIGATION,
    _SPECIAL,
    _MOUSE,
};

// Macros
enum macro_events {
    M_KEYMAP = SAFE_RANGE,
    M_EXIT,
    M_COMM,
    M_DOT,
    M_ALT_TAB,
    M_SCSM,
    M_RAND,
};

// Quantum keys / Abbreviations
enum custom_keycodes {
    VVV        = KC_TRNS,
    XXX        = KC_NO,
    CSA_Q      = MEH_T(KC_Q),
    CSA_F1     = MEH_T(KC_F1),
    CSA_1      = MEH_T(KC_1),
    CA_W       = LCA_T(KC_W),
    CA_F2      = LCA_T(KC_F2),
    CA_2       = LCA_T(KC_2),
    CS_E       = C_S_T(KC_E),
    CS_F       = C_S_T(KC_F),
    CS_I       = C_S_T(KC_I),
    CS_U       = C_S_T(KC_U),
    CS_F3      = C_S_T(KC_F3),
    CS_3       = C_S_T(KC_3),
    CS_F8      = C_S_T(KC_F8),
    CS_8       = C_S_T(KC_8),
    CA_O       = LCA_T(KC_O),
    CA_Y       = LCA_T(KC_Y),
    CA_F9      = LCA_T(KC_F9),
    CA_9       = LCA_T(KC_9),
    CSA_P      = MEH_T(KC_P),
    CSA_SCLN   = MEH_T(KC_SCLN),
    CSA_F10    = MEH_T(KC_F10),
    CSA_0      = MEH_T(KC_0),
    LGUI_A     = LGUI_T(KC_A),
    LGUI_FIND  = LGUI_T(KC_FIND),
    LGUI_GRV   = LGUI_T(KC_GRV),
    LALT_S     = LALT_T(KC_S),
    LALT_R     = LALT_T(KC_R),
    LALT_HOME  = LALT_T(KC_HOME),
    LCTL_D     = LCTL_T(KC_D),
    LCTL_S     = LCTL_T(KC_S),
    LCTL_PGUP  = LCTL_T(KC_PGUP),
    LCTL_LBRC  = LCTL_T(KC_LBRC),
    LSFT_F     = LSFT_T(KC_F),
    _LSFT_T    = LSFT_T(KC_T),
    LSFT_PGDN  = LSFT_T(KC_PGDN),
    LSFT_RBRC  = LSFT_T(KC_RBRC),
    RSFT_J     = RSFT_T(KC_J),
    RSFT_N     = RSFT_T(KC_N),
    RSFT_DOWN  = RSFT_T(KC_DOWN),
    RSFT_MINS  = RSFT_T(KC_MINS),
    RCTL_K     = RCTL_T(KC_K),
    RCTL_E     = RCTL_T(KC_E),
    RCTL_UP    = RCTL_T(KC_UP),
    RCTL_EQL   = RCTL_T(KC_EQL),
    RALT_L     = RALT_T(KC_L),
    RALT_I     = RALT_T(KC_I),
    RALT_RGHT  = RALT_T(KC_RGHT),
    RALT_BSLS  = RALT_T(KC_BSLS),
    RGUI_SCLN  = RGUI_T(KC_SCLN),
    RGUI_O     = RGUI_T(KC_O),
    RGUI_F11   = RGUI_T(KC_F11),
    RGUI_QUOT  = RGUI_T(KC_QUOT),
    LT3_SPC    = LT(_SPECIAL, KC_SPC),
    LT2_TAB    = LT(_NAVIGATION, KC_TAB),
    DF_QWERTY  = DF(_QWERTY),
    DF_COLEMAK = DF(_COLEMAK),
};

// Init
void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(default_animation);
    rgb_matrix_set_speed_noeeprom(default_speed);
}

// Ignore mod tap interrupt per key
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT3_SPC:
        case LT2_TAB:
            return true; // select hold action immediately
        default:
            return false; // Don't select hold action when another key is pressed
    }
}

// Tapping force hold per key
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT3_SPC:
        case LT2_TAB:
            return 0;
        default:
            return 120;
    }
}

// Tapping term per key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CS_E:
        case CS_I:
            return 215;
        default:
            return 190;
    }
}

// Combos
enum combo_events {
    CAPS_COMBO,
    QW_ESC_COMBO,
    OP_BSPC_COMBO,
    YSEMI_BSPC_COMBO,
    ZX_EXIT_COMBO,
    SA_SCSM_COMBO,
    RA_SCSM_COMBO,
    KM_KEYMAP_COMBO,
    KM_KEYMAP2_COMBO,
    PW_RAND_COMBO,
    PW_RAND2_COMBO,
    LSEMI_DEL_COMBO,
    IO_DEL_COMBO,
    DOTSLASH_JIGGLE_COMBO,
    COMBO_LENGTH,
};

// clang-format off
uint16_t               COMBO_LEN               = COMBO_LENGTH;
const uint16_t PROGMEM caps_combo[]            = {KC_V, KC_M, COMBO_END};
const uint16_t PROGMEM qw_esc_combo[]          = {CSA_Q, CA_W, COMBO_END};
const uint16_t PROGMEM op_bspc_combo[]         = {CA_O, CSA_P, COMBO_END};
const uint16_t PROGMEM ysemi_bspc_combo[]      = {CA_Y, CSA_SCLN, COMBO_END};
const uint16_t PROGMEM zx_exit_combo[]         = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM sa_scsm_combo[]         = {LGUI_A, LALT_S, COMBO_END};
const uint16_t PROGMEM ra_scsm_combo[]         = {LGUI_A, LALT_R, COMBO_END};
const uint16_t PROGMEM km_keymap_combo[]       = {RCTL_K, KC_M, COMBO_END};
const uint16_t PROGMEM km_keymap2_combo[]      = {KC_K, KC_M, COMBO_END};
const uint16_t PROGMEM pw_rand_combo[]         = {CSA_P, CA_W, COMBO_END};
const uint16_t PROGMEM pw_rand2_combo[]        = {KC_P, CA_W, COMBO_END};
const uint16_t PROGMEM lsemi_del_combo[]       = {RALT_L, RGUI_SCLN, COMBO_END};
const uint16_t PROGMEM io_del_combo[]          = {RALT_I, RGUI_O, COMBO_END};
const uint16_t PROGMEM dotslash_jiggle_combo[] = {M_DOT, KC_SLSH, COMBO_END};
combo_t                key_combos[]       = {
    [CAPS_COMBO]            = COMBO_ACTION(caps_combo),
    [QW_ESC_COMBO]          = COMBO_ACTION(qw_esc_combo),
    [OP_BSPC_COMBO]         = COMBO_ACTION(op_bspc_combo),
    [YSEMI_BSPC_COMBO]      = COMBO_ACTION(ysemi_bspc_combo),
    [ZX_EXIT_COMBO]         = COMBO_ACTION(zx_exit_combo),
    [SA_SCSM_COMBO]         = COMBO_ACTION(sa_scsm_combo),
    [RA_SCSM_COMBO]         = COMBO_ACTION(ra_scsm_combo),
    [KM_KEYMAP_COMBO]       = COMBO_ACTION(km_keymap_combo),
    [KM_KEYMAP2_COMBO]      = COMBO_ACTION(km_keymap2_combo),
    [PW_RAND_COMBO]         = COMBO_ACTION(pw_rand_combo),
    [PW_RAND2_COMBO]        = COMBO_ACTION(pw_rand2_combo),
    [LSEMI_DEL_COMBO]       = COMBO_ACTION(lsemi_del_combo),
    [IO_DEL_COMBO]          = COMBO_ACTION(io_del_combo),
    [DOTSLASH_JIGGLE_COMBO] = COMBO_ACTION(dotslash_jiggle_combo),
};
// clang-format on

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case CAPS_COMBO:
            if (pressed) {
                caps_word_on();
            }
            break;
        case QW_ESC_COMBO:
            if (pressed) {
                tap_code(KC_ESC);
            }
            break;
        case OP_BSPC_COMBO:
        case YSEMI_BSPC_COMBO:
            if (pressed) {
                tap_code(KC_BSPC);
            }
            break;
        case ZX_EXIT_COMBO:
            if (pressed) {
                SEND_STRING("exit");
                tap_code(KC_ENT);
            }
            break;
        case SA_SCSM_COMBO:
        case RA_SCSM_COMBO:
            if (pressed) {
                is_scsm_active = !is_scsm_active;
                // trigger RGB layer change
                layer_on(_MOUSE);
                layer_off(_MOUSE);
                if (!is_scsm_active && host_keyboard_led_state().caps_lock) {
                    tap_code(KC_CAPS);
                }
            }
            break;
        case KM_KEYMAP_COMBO:
        case KM_KEYMAP2_COMBO:
            if (pressed) {
                SEND_STRING("https://raw.githubusercontent.com/dlford/qmk_firmware/dlford_crkbd_rp2040/keyboards/crkbd/keymaps/dlford/legends.svg");
            }
            break;
        case PW_RAND_COMBO:
        case PW_RAND2_COMBO:
            if (pressed) {
                for (int i = 0; i < rand_size; i++) {
                    int rand_type = rand() % 4;
                    switch (rand_type) {
                        case 0:
                            rand_password[i] = rand_numbers[rand() % 10];
                            break;
                        case 1:
                            rand_password[i] = rand_letters[rand() % 26];
                            break;
                        case 2:
                            rand_password[i] = rand_LETTERS[rand() % 26];
                            break;
                        case 3:
                            rand_password[i] = rand_symbols[rand() % 8];
                            break;
                    }
                }
                SEND_STRING(rand_password);
                rand_password[0] = '\0';
            }
            break;
        case LSEMI_DEL_COMBO:
        case IO_DEL_COMBO:
            if (pressed) {
                tap_code(KC_DEL);
            }
            break;
        case DOTSLASH_JIGGLE_COMBO:
            if (pressed) {
                is_mouse_jiggle_active = !is_mouse_jiggle_active;
            }
            break;
    }
}

// RGB timeout
#define RGB_CUSTOM_TIMEOUT 5 // in minutes
static uint16_t idle_timer      = 0;
static uint8_t  halfmin_counter = 0;
static bool     led_on          = true;
void            matrix_scan_user(void) {
    if (is_keyboard_master()) {
        // idle_timer needs to be set one time
        if (idle_timer == 0) idle_timer = timer_read();
        if (mouse_jiggle_timer == 0) mouse_jiggle_timer = timer_read();

        if (led_on && timer_elapsed(idle_timer) > 30000) {
            halfmin_counter++;
            idle_timer = timer_read();
        }

        if (led_on && halfmin_counter >= RGB_CUSTOM_TIMEOUT * 2) {
            rgb_matrix_disable_noeeprom();
            led_on          = false;
            halfmin_counter = 0;
        }
    }

    // Alt tab
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 750) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }

    // Mouse jiggle
    if (is_mouse_jiggle_active) {
        if (timer_elapsed(mouse_jiggle_timer) > mouse_jiggle_frequency) {
            mouse_jiggle_timer = timer_read();
            if (mouse_jiggle_direction) {
                tap_code(KC_MS_LEFT);
                tap_code(KC_MS_LEFT);
                tap_code(KC_MS_LEFT);
            } else {
                tap_code(KC_MS_RIGHT);
                tap_code(KC_MS_RIGHT);
                tap_code(KC_MS_RIGHT);
            }
            mouse_jiggle_direction = !mouse_jiggle_direction;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Caps word
    if (!process_caps_word(keycode, record)) {
        return false;
    }

    // RGB resume
    if (is_keyboard_master()) {
        if (record->event.pressed) {
            if (led_on == false) {
                rgb_matrix_enable_noeeprom();
                led_on = true;
            }
            idle_timer      = timer_read();
            halfmin_counter = 0;
        }
    }

    // Macros
    const uint8_t  mods            = get_mods();
    static uint8_t backstepCounter = 0;
    static bool    keyDown         = false;

    if (is_scsm_active && record->event.pressed) {
        tap_code(KC_CAPS);
    }

    switch (keycode) {
        case M_ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case M_COMM:
            if (record->event.pressed) {
                if ((mods & MOD_BIT(KC_LCTL)) && (mods & MOD_BIT(KC_LSFT) && (mods & MOD_BIT(KC_LALT)))) {
                    backstepCounter = 1;
                    clear_mods();
                    SEND_STRING("<>");
                } else if ((mods & MOD_BIT(KC_LCTL)) && (mods & MOD_BIT(KC_LALT))) {
                    backstepCounter = 1;
                    clear_mods();
                    SEND_STRING("()");
                } else if ((mods & MOD_BIT(KC_LCTL)) && (mods & MOD_BIT(KC_LSFT))) {
                    backstepCounter = 2;
                    clear_mods();
                    SEND_STRING("{};");
                } else if (mods & MOD_BIT(KC_LCTL)) {
                    backstepCounter = 1;
                    clear_mods();
                    SEND_STRING("{}");
                } else if ((mods & MOD_BIT(KC_LALT)) && (mods & MOD_BIT(KC_LSFT))) {
                    backstepCounter = 2;
                    clear_mods();
                    SEND_STRING("[];");
                } else if (mods & MOD_BIT(KC_LALT)) {
                    backstepCounter = 1;
                    clear_mods();
                    SEND_STRING("[]");
                } else {
                    keyDown = true;
                    register_code(KC_COMM);
                    return true;
                }
                if (backstepCounter) {
                    while (backstepCounter > 0) {
                        tap_code(KC_LEFT);
                        backstepCounter--;
                    }
                    set_mods(mods);
                }
            } else {
                if (keyDown) {
                    unregister_code(KC_COMM);
                    keyDown = false;
                    return true;
                }
            }
            return false;
        case M_DOT:
            if (record->event.pressed) {
                if (mods & MOD_BIT(KC_LCTL)) {
                    clear_mods();
                    SEND_STRING("=>");
                } else if (mods & MOD_BIT(KC_LALT)) {
                    clear_mods();
                    SEND_STRING("->");
                } else {
                    keyDown = true;
                    register_code(KC_DOT);
                    return true;
                }
            } else {
                if (keyDown) {
                    unregister_code(KC_DOT);
                    keyDown = false;
                    return true;
                }
            }
            set_mods(mods);
            return false;
    }

    return true;
}

// OLEDs
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

void oled_render_layer_state(void) {
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
                if (is_scsm_active) {
                    oled_write_ln_P(PSTR("CoLeMaK"), false);
                } else {
                    oled_write_ln_P(PSTR("Colemak"), false);
                }
            } else {
                if (is_scsm_active) {
                    oled_write_ln_P(PSTR("QwErTy"), false);
                } else {
                    oled_write_ln_P(PSTR("Qwerty"), false);
                }
            }
    }

    if (is_mouse_jiggle_active) {
        oled_write_ln_P(PSTR("Mouse Jiggling..."), false);
    } else {
        oled_write_ln_P(PSTR(""), false);
    }
}

void dynamic_macro_record_start_user(void) {
    is_macro_recording = true;
}

void dynamic_macro_record_end_user(int8_t direction) {
    is_macro_recording = false;
}

void oled_render_dynamic_macro_status(void) {
    if (is_macro_recording) {
        oled_write_ln_P(PSTR("Macro Recording..."), false);
    } else {
        oled_write_ln_P(PSTR(""), false);
    }
}

void oled_render_caps_lock_status(void) {
    if (host_keyboard_led_state().caps_lock) {
        oled_write_ln_P(PSTR("CAPS LOCK"), false);
    } else if (is_caps_word_active) {
        oled_write_ln_P(PSTR("CAPS word"), false);
    } else {
        oled_write_ln_P(PSTR(""), false);
    }
}

static void oled_render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,   128, 224, 224, 96, 96,  96,  96,  96,  96,  128, 192, 224, 224, 240, 240, 240, 224, 224, 192, 128, 0, 0, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0,   0,   0,  0,  0,  0,   0,   0,  0,   0,   0,  0,  0,  0,   0,   0, 0,   0,   0,  0,  0,  0,   0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 240, 60, 30, 7, 1, 192, 224, 224, 240, 240, 240, 0,  255, 255, 255, 255, 249, 241, 241, 7, 7, 55, 247, 192, 0, 0, 0, 0, 224, 224, 224, 224, 224, 192, 192, 192, 0, 192, 224, 224, 224, 0, 0, 0, 0, 224, 224, 96, 96, 96, 96, 0, 192, 224, 96, 96, 96, 224, 192, 192, 192, 224, 96, 96, 96, 224, 192, 0, 224, 224, 96, 96, 96, 224, 192, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 15, 60, 240, 224, 134, 31,  63, 127, 255, 249, 248, 248, 127, 127, 63,  31,  0,   0,   128, 224, 248, 60,  15,  3, 1, 0, 0, 0, 127, 127, 127, 127, 113, 127, 127, 63, 31, 31, 63, 127, 127, 112, 112, 112, 112, 127, 127, 6, 6, 6, 6, 0, 127, 127, 96, 96, 96, 127, 127, 63, 127, 127, 12, 12, 60, 127, 103, 0, 127, 127, 96, 96, 96, 127, 63, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0,   0,  0,  1, 7, 14,  12,  12,  12,  12,  12,  12, 12,  12,  12,  12,  12,  14,  7,   1, 0, 0,  0,   0,   0, 0, 0, 0, 0,   0,   0,   0,   0,   0,   0,   0,   0, 0,   0,   0,   0,   0, 0, 0, 0, 0,   0,   0,  0,  0,  0,  0, 0,   0,   0,  0,  0,  0,   0,   0,   0,   0,   0,  0,  0,  0,   0,   0, 0,   0,   0,  0,  0,  0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_dynamic_macro_status();
        oled_render_caps_lock_status();
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE

// RGB Layers (Enable animations in config.h)
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _SPECIAL:
            rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
            rgb_matrix_set_speed_noeeprom(secondary_speed);
            rgb_matrix_mode_noeeprom(secondary_animation);
            break;
        case _NAVIGATION:
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
            rgb_matrix_set_speed_noeeprom(secondary_speed);
            rgb_matrix_mode_noeeprom(secondary_animation);
            break;
        case _MOUSE:
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
            rgb_matrix_set_speed_noeeprom(secondary_speed);
            rgb_matrix_mode_noeeprom(secondary_animation);
            break;
        default:
            if (is_scsm_active) {
                rgb_matrix_sethsv_noeeprom(HSV_YELLOW);
                rgb_matrix_set_speed_noeeprom(default_speed);
                rgb_matrix_mode_noeeprom(RGB_MATRIX_PIXEL_FRACTAL);
            } else {
                rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
                rgb_matrix_set_speed_noeeprom(default_speed);
                rgb_matrix_mode_noeeprom(default_animation);
            }
            break;
    }
    return state;
}

void caps_word_set_user(bool active) {
    is_caps_word_active = active;
}

// Indicators
bool rgb_matrix_indicators_user() {
    if (host_keyboard_led_state().caps_lock || is_caps_word_active) {
        // Left master
        rgb_matrix_set_color(23, RGB_RED);
        rgb_matrix_set_color(22, RGB_RED);
        rgb_matrix_set_color(21, RGB_RED);
        // Right master
        rgb_matrix_set_color(50, RGB_RED);
        rgb_matrix_set_color(49, RGB_RED);
        rgb_matrix_set_color(48, RGB_RED);
    }
    if (is_macro_recording) {
        // Left master
        rgb_matrix_set_color(6, RGB_ORANGE);
        rgb_matrix_set_color(13, RGB_ORANGE);
        rgb_matrix_set_color(14, RGB_ORANGE);
        // Right master
        rgb_matrix_set_color(33, RGB_ORANGE);
        rgb_matrix_set_color(40, RGB_ORANGE);
        rgb_matrix_set_color(41, RGB_ORANGE);
    }
    if (default_layer_state - 1 == _COLEMAK) {
        // Left master
        rgb_matrix_set_color(18, RGB_GREEN);
        rgb_matrix_set_color(19, RGB_GREEN);
        rgb_matrix_set_color(20, RGB_GREEN);
        // Right master
        rgb_matrix_set_color(45, RGB_GREEN);
        rgb_matrix_set_color(46, RGB_GREEN);
        rgb_matrix_set_color(47, RGB_GREEN);
    }
    if (is_mouse_jiggle_active) {
        // Left master
        rgb_matrix_set_color(7, RGB_BLUE);
        rgb_matrix_set_color(8, RGB_BLUE);
        rgb_matrix_set_color(9, RGB_BLUE);
        // Right master
        rgb_matrix_set_color(34, RGB_BLUE);
        rgb_matrix_set_color(35, RGB_BLUE);
        rgb_matrix_set_color(36, RGB_BLUE);
    }

    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_split_3x5_3(
		//|--------------------------------------------|                    |--------------------------------------------|
			CSA_Q,   CA_W,    CS_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    CS_I,    CA_O,    CSA_P,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
			LGUI_A,  LALT_S,  LCTL_D,  LSFT_F,  KC_G,                         KC_H,    RSFT_J,  RCTL_K,  RALT_L, RGUI_SCLN,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
			KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    M_COMM,  M_DOT,  KC_SLSH,
		//|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
									   KC_ESC,  LT3_SPC, KC_BSPC,    KC_DEL, LT2_TAB,  KC_ENT
		//                           |--------+--------+--------|  |--------+--------+--------|
	),
	[_COLEMAK] = LAYOUT_split_3x5_3(
		//|--------------------------------------------|                    |--------------------------------------------|
			CSA_Q,   CA_W,    CS_F,    KC_P,    KC_G,                         KC_J,    KC_L,    CS_U,    CA_Y,    CSA_SCLN,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
			LGUI_A,  LALT_R,  LCTL_S,  _LSFT_T, KC_D,                         KC_H,    RSFT_N,  RCTL_E,  RALT_I,  RGUI_O,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
			KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M,    M_COMM,  M_DOT,  KC_SLSH,
		//|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
									   KC_ESC,  LT3_SPC, KC_BSPC,    KC_DEL, LT2_TAB,  KC_ENT
		//                           |--------+--------+--------|  |--------+--------+--------|
	),
	// right thumb >
	[_NAVIGATION] = LAYOUT_split_3x5_3(
		//|--------------------------------------------|                    |--------------------------------------------|
			CSA_F1,  CA_F2,   CS_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   CS_F8,  CA_F9,   CSA_F10,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
		 LGUI_FIND,LALT_HOME,LCTL_PGUP,LSFT_PGDN,KC_END,                     KC_LEFT,RSFT_DOWN,RCTL_UP,RALT_RGHT,RGUI_F11,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
		 DF_QWERTY,DF_COLEMAK,KC_VOLD, KC_VOLU, QK_BOOT,                     M_ALT_TAB, KC_MPLY, KC_MPRV, KC_MNXT, KC_F12,
		//|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
										VVV,  TG(_MOUSE), VVV,         VVV,    VVV,     VVV
		//                           |--------+--------+--------|  |--------+--------+--------|
	),
	// < left thumb
	[_SPECIAL] = LAYOUT_split_3x5_3(
		//|--------------------------------------------|                    |--------------------------------------------|
			CSA_1,   CA_2,    CS_3,    KC_4,    KC_5,                         KC_6,    KC_7,    CS_8,    CA_9,    CSA_0,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
		   LGUI_GRV,KC_LALT,LCTL_LBRC,LSFT_RBRC,KC_LPRN,                     KC_RPRN,RSFT_MINS,RCTL_EQL,RALT_BSLS,RGUI_QUOT,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
		   KC_TILD, KC_CAPS, KC_LCBR, KC_RCBR, M_ALT_TAB,                    QK_BOOT,  KC_UNDS, KC_PLUS, KC_PIPE, KC_DQUO,
		//|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
										VVV,     VVV,     VVV,        VVV,  TG(_MOUSE),  VVV
		//                           |--------+--------+--------|  |--------+--------+--------|
	),
	[_MOUSE] = LAYOUT_split_3x5_3(
		//|--------------------------------------------|                    |--------------------------------------------|
			KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, DM_REC1,                      KC_WSTP, KC_ACL2, KC_ACL1, KC_ACL0, KC_WFWD,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
			KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, DM_PLY1,                      KC_WREF, KC_BTN1, KC_BTN2, KC_BTN3, KC_WBAK,
		//|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
			 XXX,   KC_BTN3, KC_BTN2, KC_BTN1,  XXX,                          XXX,     XXX,     XXX,     XXX,     XXX,
		//|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
										VVV,  TG(_MOUSE),  VVV,       VVV,  TG(_MOUSE),  VVV
		//                           |--------+--------+--------|  |--------+--------+--------|
	),
};
// clang-format on
