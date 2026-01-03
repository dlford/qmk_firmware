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
#include "custom_keycodes_user.h"

/*
#ifdef AUDIO_ENABLE
#    include "audio.h"
#    ifdef AUDIO_CLICKY
#        include "process_clicky.h"
#        ifndef CLICKY_ON_SONG
#            define CLICKY_ON_SONG SONG(ZELDA_TREASURE)
#        endif
#        ifndef CLICKY_OFF_SONG
#            define CLICKY_OFF_SONG SONG(PLOVER_GOODBYE_SOUND)
#        endif
#    endif

#    ifdef AUDIO_CLICKY
    float clicky_on_song[][2]  = CLICKY_ON_SONG;
float     clicky_off_song[][2] = CLICKY_OFF_SONG;
#    endif
#endif
*/

bool is_leader_mode_active = false;

void leader_start_user(void) {
    is_leader_mode_active = true;
}

void leader_end_user(void) {
    is_leader_mode_active = false;

    // leader_sequence_one_key - leader_sequence_five_keys

    /*
    if (leader_sequence_two_keys(KC_C, KC_W)) {
        caps_word_on();
    } else
#ifdef AUDIO_ENABLE
    if (leader_sequence_three_keys(KC_A, KC_U, KC_T)) {
        if (audio_is_on()) {
            audio_off();
        } else {
            audio_on();
        }
    }
#    ifdef AUDIO_CLICKY
    else if (audio_is_on()) {
        if (leader_sequence_three_keys(KC_A, KC_C, KC_T)) {
            if (is_clicky_on()) {
                clicky_off();
                PLAY_SONG(clicky_off_song);
            } else {
                clicky_on();
                PLAY_SONG(clicky_on_song);
            }
        }
    }
#    endif // AUDIO_CLICKY
#endif     // AUDIO_ENABLE
    */
}
