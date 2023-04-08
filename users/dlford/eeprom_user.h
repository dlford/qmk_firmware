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

#define EECONFIG_CUSTOM_USER_QWORD (uint16_t *)36

typedef union {
    uint64_t raw;
    struct {
        uint8_t rgb_speed : 8;
        bool    is_rgb_idle_enabled : 1;
    };
} user_config_t;

user_config_t user_config;

void eeconfig_init_user(void);
void read_user_config(void);
void write_user_config(void);
