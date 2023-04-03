SRC += tap_rules.c
SRC += custom_random_password.c
SRC += mouse_jiggler.c
SRC += sarcasm_mode.c
SRC += alt_tab.c
ifdef OLED_ENABLE
	SRC += oled.c
endif
ifdef COMBO_ENABLE
	SRC += custom_combos.c
endif
ifdef RGB_MATRIX_ENABLE
	SRC += rgb_timeout.c
	SRC += custom_rgb_matrix.c
	SRC += custom_eeprom.c
endif
