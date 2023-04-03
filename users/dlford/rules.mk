SRC += tap_rules.c
SRC += pwgen_user.c
SRC += mouse_jiggler_user.c
SRC += sarcasm_mode.c
SRC += alt_tab_user.c
ifdef OLED_ENABLE
	SRC += oled_user.c
endif
ifdef COMBO_ENABLE
	SRC += combos_user.c
endif
ifdef RGB_MATRIX_ENABLE
	SRC += rgb_timeout_user.c
	SRC += rgb_matrix_user.c
	SRC += eeprom_user.c
endif
