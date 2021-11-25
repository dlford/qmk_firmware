/*
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
#include "3x5_3.h"

#ifdef RGB_MATRIX_ENABLE

// LED Layout
// Columns
// 0   1   2   3   4   5   6   7   8   9   10  11
// Physical (Center: 133)
// 20  41  61  81  102 122 143 163 183 204 224 244
//                                                  Rows  Physical (Center: 54)
// 18  13  12  07  06          24  25  30  31  36   0     21
// 17  14  11  08  05          23  26  29  32  35   1     43
// 16  15  10  09  04          22  27  28  33  34   2     64
//             03  02  01  19  20  21               3     85

led_config_t g_led_config = { {
    // Key matrix to LED index
    // Left 1-18
            {18, 13, 12,  7,  6},
            {17, 14, 11,  8,  5},
            {16, 15, 10,  9,  4},
    {NO_LED, NO_LED,  3,  2,  1},
                                    // Right 1-18
                                    {24, 25, 30, 31, 36},
                                    {23, 26, 29, 32, 35},
                                    {22, 27, 28, 33, 34},
                                    {19, 20, 21, NO_LED, NO_LED},
}, {
    // LED index to physical position
    // Left 1-18
    {122,85},{102,85},{81,85},{102,64},{102,43},{102,21},
    {81,21},{81,43},{81,64},{61,64},{61,43},{61,21},
    {41,21},{41,43},{41,64},{20,64},{20,43},{20,21},
    // Right 1-18
    {143,85},{163,85},{183,85},{163,64},{163,43},{163,21},
    {183,21},{183,43},{183,64},{204,64},{204,43},{204,21},
    {224,21},{224,43},{224,64},{244,64},{244,43},{244,21}
}, {
    // LED index to flag
    // Left 1-18
    4,4,4,4,4,4,
    4,4,4,4,4,4,
    4,4,4,4,4,4,
    // Right 1-18
    4,4,4,4,4,4,
    4,4,4,4,4,4,
    4,4,4,4,4,4
} };

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
