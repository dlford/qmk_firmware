/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
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

#define EE_HANDS // ./util/docker_build.sh crkbd:dlford:uf2-split-[left|right]

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 150U
#define USE_SERIAL_PD2

#ifdef RGB_MATRIX_ENABLE
#    define RGB_INDICATOR_CAPS_IDS \
        { 21, 22, 23, 48, 49, 50 }
#    define RGB_INDICATOR_MACRO_RECORDING_IDS \
        { 6, 13, 14, 33, 40, 41 }
#    define RGB_INDICATOR_COLEMAK_IDS \
        { 18, 19, 20, 45, 46, 47 }
#    define RGB_INDICATOR_MOUSE_JIGGLER_IDS \
        { 7, 8, 9, 34, 35, 36 }
#    define RGB_INDICATOR_RGB_IDLE_CHANGED_IDS \
        { 21, 22, 23, 48, 49, 50 }
#endif
