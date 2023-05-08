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

typedef struct _master_to_slave_t {
    bool is_caps_word_active;
    bool is_macro_recording;
    bool is_mouse_jiggle_active;
    bool rgb_idle_mode_user_toggled;
    bool is_rgb_idle_enabled;
} rgb_sync_states_t;

rgb_sync_states_t rgb_sync_states;

void keyboard_post_init_split_transport_user(void);
void housekeeping_task_split_transport_user(void);
