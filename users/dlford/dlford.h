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

#pragma once

#include "layers_user.h"
#include "process_record_user.h"
#include "keyboard_post_init_user.h"
#include "matrix_scan_user.h"
#include "tap_rules.h"
#include "pwgen_user.h"
#include "mouse_jiggler_user.h"
#include "sarcasm_mode.h"
#include "alt_tab_user.h"
#include "eeprom_user.h"
#include "custom_keycodes_user.h"
#include "wrappers.h"
#include "layer_lock.h"
#ifdef OLED_ENABLE
#    include "oled_user.h"
#endif
#ifdef COMBO_ENABLE
#    include "combos_user.h"
#endif
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_timeout_user.h"
#    include "rgb_idle_mode_user.h"
#    include "rgb_matrix_user.h"
#endif
#ifdef DYNAMIC_MACRO_ENABLE
#    include "dynamic_macro_user.h"
#endif
#ifdef CAPS_WORD_ENABLE
#    include "caps_word_user.h"
#endif
