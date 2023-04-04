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

enum combo_events {
    QW_ESC_COMBO = 0,
    OP_BSPC_COMBO,
    YSEMI_BSPC_COMBO,
    ZX_EXIT_COMBO,
    SA_SCSM_COMBO,
    RA_SCSM_COMBO,
    KM_KEYMAP_COMBO,
    KM_KEYMAP2_COMBO,
    PW_RAND_COMBO,
    PW_RAND2_COMBO,
    LSEMI_DEL_COMBO,
    IO_DEL_COMBO,
    DOTSLASH_JIGGLE_COMBO,
    CX_COLEMAK_COMBO,
    BR_WRAP_COMBO,
    BR_WRAP_SEMI_COMBO,
    CBR_WRAP_COMBO,
    CBR_WRAP_SEMI_COMBO,
    PRN_WRAP_COMBO,
    PRN_WRAP_SEMI_COMBO,
    ANG_WRAP_COMBO,
    ANG_WRAP_SEMI_COMBO,
    FAT_ARROW_COMBO,
    FAT_ARROW2_COMBO,
    SKINNY_ARROW_COMBO,
    SKINNY_ARROW2_COMBO,
#ifdef CAPS_WORD_ENABLE
    CAPS_COMBO,
    CAPS2_COMBO,
#endif // CAPS_WORD_ENABLE
    COMBO_LENGTH,
};

uint16_t COMBO_LEN;
combo_t  key_combos[COMBO_LENGTH];
void     process_combo_event(uint16_t combo_index, bool pressed);
