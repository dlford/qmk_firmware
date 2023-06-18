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
#include <stdlib.h>
#include <time.h>

const char rand_numbers[] PROGMEM = "0123456789";
const char rand_letters[] PROGMEM = "abcdefghijklmnoqprstuvwyzx";
const char rand_LETTERS[] PROGMEM = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
const char rand_symbols[] PROGMEM = "!@#$%^&*";

void gen_random_password(int length) {
    // Seed the random-number generator
    // with current time so that the
    // numbers will be different every time
    srand(timer_read());

    char random_password[length];

    for (int i = 0; i < length; i++) {
        int rand_type = rand() % 4;

        switch (rand_type) {
            case 0:
                random_password[i] = rand_numbers[rand() % 10];
                break;
            case 1:
                random_password[i] = rand_letters[rand() % 26];
                break;
            case 2:
                random_password[i] = rand_LETTERS[rand() % 26];
                break;
            case 3:
                random_password[i] = rand_symbols[rand() % 8];
                break;
        }
    }

    send_string(random_password);
}
