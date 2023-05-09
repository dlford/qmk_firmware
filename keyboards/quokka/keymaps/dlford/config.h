/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
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

#pragma once

#define EE_HANDS

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 150U

#ifdef RGB_MATRIX_ENABLE
#    define RGB_INDICATOR_CAPS_IDS \
        { 13 }
#    define RGB_INDICATOR_MACRO_RECORDING_IDS \
        { 5 }
#    define RGB_INDICATOR_COLEMAK_IDS \
        { 9, 26 }
#    define RGB_INDICATOR_MOUSE_JIGGLER_IDS \
        { 33 }
#    define RGB_INDICATOR_RGB_IDLE_CHANGED_IDS \
        { 3 }
#endif
