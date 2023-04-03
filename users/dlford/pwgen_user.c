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

#include <stdlib.h>
#include <time.h>

char random_password[32];
char rand_numbers[] = "0123456789";
char rand_letters[] = "abcdefghijklmnoqprstuvwyzx";
char rand_LETTERS[] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
char rand_symbols[] = "!@#$^&*?";

void gen_random_password(void) {
    // Seed the random-number generator
    // with current time so that the
    // numbers will be different every time
    srand((unsigned int)(time(NULL)));

    for (int i = 0; i < 32; i++) {
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
}
