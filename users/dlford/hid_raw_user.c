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

bool is_notification_on  = false;
bool is_hidraw_connected = false;

void raw_hid_receive(uint8_t *data, uint8_t length) {
    is_hidraw_connected = true;

    // uint8_t send_data[32] = {1};
    // raw_hid_send(send_data, sizeof(send_data));
    raw_hid_send(data, length);

    /*
    char *str = (char *)data;
    if (strcmp(str, "toggle_notification") == 0) {
        is_notification_on = !is_notification_on;
    }

    if (is_notification_on) {
        send_string("notified!");
    } else {
        send_string("not notified!");
    }
    */
}
