SRC += tap_rules.c
SRC += pwgen_user.c
SRC += mouse_jiggler_user.c
SRC += sarcasm_mode.c
ifdef ALT_TAB_USER_ENABLE
SRC += alt_tab_user.c
endif
ifdef OLED_ENABLE
	SRC += oled_user.c
endif
ifdef COMBO_ENABLE
	SRC += combos_user.c
endif
ifdef RGB_MATRIX_ENABLE
	SRC += rgb_timeout_user.c
	SRC += rgb_matrix_user.c
	ifdef ALL_MATRIX_ANIMATIONS_USER_ENABLE
		SRC += eeprom_user.c
	endif
endif
