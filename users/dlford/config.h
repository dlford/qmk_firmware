/*
This is the c configuration file for the keymap
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

#define TAPPING_TOGGLE 2
#define TAPPING_TERM_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define QUICK_TAP_TERM_PER_KEY

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250

#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(TERMINAL_SOUND)
// #    define GOODBYE_SONG SONG(TERMINAL_SOUND)
// #    define AUDIO_CLICKY
// #    define AUDIO_CLICKY_DELAY_DURATION 0
// #    define AUDIO_CLICKY_FREQ_DEFAULT 100.0f
// #    define AUDIO_CLICKY_FREQ_MIN 61.0f
// #    define AUDIO_CLICKY_FREQ_RANDOMNESS 0.2f
// #    define AUDIO_CLICKY_FREQ_FACTOR 1.61803f
// #    define STARTUP_SONG SONG(GUITAR_SOUND)
#endif

#ifdef COMBO_ENABLE
#    define COMBO_TERM 30
#    define COMBO_STRICT_TIMER
#    define EXTRA_EXTRA_LONG_COMBOS
#endif // COMBO_ENABLE

#ifdef SPLIT_KEYBOARD
#    define SPLIT_LAYER_STATE_ENABLE
#    define SPLIT_LED_STATE_ENABLE
#    define SPLIT_MODS_ENABLE
#    ifdef WPM_ENABLE
#        define SPLIT_WPM_ENABLE
#    endif
#    define SPLIT_USB_DETECT
#    define SPLIT_USB_TIMEOUT 2500
#    define SPLIT_WATCHDOG_ENABLE
#    ifdef OLED_ENABLE
#        define SPLIT_OLED_ENABLE
#    endif
#endif // SPLIT_KEYBOARD

#ifdef MOUSEKEY_ENABLE
#    define MK_KINETIC_SPEED
#    ifdef MOUSEKEY_DELAY
#        undef MOUSEKEY_DELAY
#    endif
#    define MOUSEKEY_DELAY 100
#    ifdef MOUSEKEY_INTERVAL
#        undef MOUSEKEY_INTERVAL
#    endif
#    define MOUSEKEY_INTERVAL 35
#    define MOUSEKEY_MOVE_DELTA 5
#    define MOUSEKEY_INITIAL_SPEED 1
#    define MOUSEKEY_DECELERATED_SPEED 10
#    define MOUSEKEY_BASE_SPEED 1200
#    define MOUSEKEY_ACCELERATED_SPEED 4800
#endif // MOUSEKEY_ENABLE

#ifdef OLED_ENABLE
#    define SPLIT_OLED_ENABLE
#    define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
// #    define RGB_MATRIX_TIMEOUT 300000
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_KEYPRESSES
#    define SPLIT_TRANSPORT_MIRROR
#    define RGB_TRIGGER_ON_KEYDOWN
#    define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE
#    define ENABLE_RGB_MATRIX_SOLID_COLOR            // Static single hue, no speed support
#    define ENABLE_RGB_MATRIX_ALPHAS_MODS            // Static dual hue, speed is hue for secondary hue
#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN       // Static gradient top to bottom, speed controls how much gradient changes
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT    // Static gradient left to right, speed controls how much gradient changes
#    define ENABLE_RGB_MATRIX_BREATHING              // Single hue brightness cycling animation
#    define ENABLE_RGB_MATRIX_BAND_SAT               // Single hue band fading saturation scrolling left to right
#    define ENABLE_RGB_MATRIX_BAND_VAL               // Single hue band fading brightness scrolling left to right
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT      // Single hue 3 blade spinning pinwheel fades saturation
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL      // Single hue 3 blade spinning pinwheel fades brightness
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT        // Single hue spinning spiral fades saturation
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL        // Single hue spinning spiral fades brightness
#    define ENABLE_RGB_MATRIX_CYCLE_ALL              // Full keyboard solid hue cycling through full gradient
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT       // Full gradient scrolling left to right
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN          // Full gradient scrolling top to bottom
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN           // Full gradient scrolling out to in
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL      // Full dual gradients scrolling out to in
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON // Full gradient Chevron shapped scrolling left to right
#    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL         // Full gradient spinning pinwheel around center of keyboard
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL           // Full gradient spinning spiral around center of keyboard
#    define ENABLE_RGB_MATRIX_DUAL_BEACON            // Full gradient spinning around center of keyboard
#    define ENABLE_RGB_MATRIX_RAINBOW_BEACON         // Full tighter gradient spinning around center of keyboard
#    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS      // Full dual gradients spinning two halfs of keyboard
#    define ENABLE_RGB_MATRIX_RAINDROPS              // Randomly changes a single key's hue
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS    // Randomly changes a single key's hue and saturation
#    define ENABLE_RGB_MATRIX_HUE_BREATHING          // Hue shifts up a slight ammount at the same time, then shifts back
#    define ENABLE_RGB_MATRIX_HUE_PENDULUM           // Hue shifts up a slight ammount in a wave to the right, then back to the left
#    define ENABLE_RGB_MATRIX_HUE_WAVE               // Hue shifts up a slight ammount and then back down in a wave to the right
#    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL          // Single hue fractal filled keys pulsing horizontally out to edges
#    define ENABLE_RGB_MATRIX_PIXEL_FLOW             // Pulsing RGB flow along LED wiring with random hues
#    define ENABLE_RGB_MATRIX_PIXEL_RAIN             // Randomly light keys with random hues
#    ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS
#        define ENABLE_RGB_MATRIX_TYPING_HEATMAP // How hot is your WPM!
#        define ENABLE_RGB_MATRIX_DIGITAL_RAIN   // That famous computer simulation
#    endif
#    if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE     // Pulses keys hit to hue & value then fades value out
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE            // Static single hue, pulses keys hit to shifted hue then fades to current hue
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
#        define ENABLE_RGB_MATRIX_SPLASH                    // Full gradient & value pulse away from a single key hit then fades value out
#        define ENABLE_RGB_MATRIX_MULTISPLASH               // Full gradient & value pulse away from multiple key hits then fades value out
#        define ENABLE_RGB_MATRIX_SOLID_SPLASH              // Hue & value pulse away from a single key hit then fades value out
#        define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH         // Hue & value pulse away from multiple key hits then fades value out
#    endif
#endif
