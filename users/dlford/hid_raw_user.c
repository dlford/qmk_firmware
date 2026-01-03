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
#include "raw_hid.h"
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

bool is_hidraw_user_notification_on = false;
bool is_hidraw_user_connected       = false;
char hidraw_user_string_value[32];
int  hidraw_user_cpu_usage;

enum hid_raw_user_indices {
    NOTIFICATION = 1,
    CPU_USAGE,
    STRING_VALUE,
};

void raw_hid_receive(uint8_t *data, uint8_t length) {
    is_hidraw_user_connected = true;
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif

    uint8_t res[32] = {data[0], 1};
    switch (data[0]) {
        case NOTIFICATION:
            is_hidraw_user_notification_on = data[1] == 1;
            break;
        case CPU_USAGE:
            hidraw_user_cpu_usage = data[1];
#ifdef CONSOLE_ENABLE
            uprintf("CPU usage: %d\n", hidraw_user_cpu_usage);
#endif
            /*
            char snum[5];
            itoa(hidraw_user_cpu_usage, snum, 10);
            send_string(snum);
            */
            break;
        case STRING_VALUE:
            memcpy(hidraw_user_string_value, (char *)&data[1], sizeof(hidraw_user_string_value));
#ifdef CONSOLE_ENABLE
            uprintf("String value: %s\n", hidraw_user_string_value);
#endif
            // send_string(hidraw_user_string_value);
            break;
        default:
            res[1] = 0;
    }

    raw_hid_send(res, sizeof(res));
}
