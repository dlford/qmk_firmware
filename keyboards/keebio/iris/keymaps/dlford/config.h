/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

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

// #define USE_I2C
#define EE_HANDS
#define TAPPING_TOGGLE 2 // number of taps to toggle TT
#define TAPPING_TERM 180 // milliseconds from tap to hold for mod tap
#define IGNORE_MOD_TAP_INTERRUPT // ignore hold mod if another tap occurs within tapping term
#define PERMISSIVE_HOLD_PER_KEY // activate mod top hold earlier if another key is pressed AND released per key
#define TAPPING_FORCE_HOLD_PER_KEY // disable double tap hold key repeat per key
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 3
// Animations I want
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// Animations I don't want, remove to save space
#undef RGBLIGHT_ANIMATIONS
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE
// Features I don't want, remove to save space
#define NO_ACTION_ONESHOT
#define NO_ACTION_FUNCTION
#define NO_ACTION_MACRO
