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
#include "eeprom_user.h"
#include "eeconfig.h"
#include "eeprom.h"
#include "progmem.h"

user_config_t user_config;

void eeconfig_init_user(void) {
    user_config.raw                 = 0;
    user_config.rgb_speed           = 50;
    user_config.is_rgb_idle_enabled = true;
    eeconfig_update_user(user_config.raw);
}

void read_user_config(void) {
    user_config.raw = eeconfig_read_user();
}

void write_user_config(void) {
    eeconfig_update_user(user_config.raw);
}
