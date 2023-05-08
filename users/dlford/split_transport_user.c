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

#include "transactions.h"
#include "split_transport_user.h"
#include "caps_word_user.h"
#include "dynamic_macro_user.h"
#include "mouse_jiggler_user.h"
#include "eeprom_user.h"
#include "rgb_idle_mode_user.h"

rgb_sync_states_t rgb_sync_states;

void user_sync_rgb_states_slave_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(rgb_sync_states)) {
        memcpy(&rgb_sync_states, initiator2target_buffer, initiator2target_buffer_size);
    }
}

void keyboard_post_init_split_transport_user(void) {
    transaction_register_rpc(USER_SYNC_RGB_STATES, user_sync_rgb_states_slave_handler);
}

void user_transport_update(void) {
    rgb_sync_states.is_caps_word_active        = is_caps_word_active;
    rgb_sync_states.is_macro_recording         = is_macro_recording;
    rgb_sync_states.is_mouse_jiggle_active     = is_mouse_jiggle_active;
    rgb_sync_states.rgb_idle_mode_user_toggled = rgb_idle_mode_user_toggled;
    rgb_sync_states.is_rgb_idle_enabled        = user_config.is_rgb_idle_enabled; // TODO: always true???
}

bool user_transport_sync(void) {
    bool res = false;
    res      = transaction_rpc_send(USER_SYNC_RGB_STATES, sizeof(rgb_sync_states), &rgb_sync_states);
    return res;
}

void housekeeping_task_split_transport_user(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            user_transport_update();
            if (user_transport_sync()) {
                last_sync = timer_read32();
            }
        }
    }
}
