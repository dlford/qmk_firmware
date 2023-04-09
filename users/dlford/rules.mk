SRC += process_record_user.c
SRC += keyboard_post_init_user.c
SRC += matrix_scan_user.c
SRC += tap_rules.c
SRC += pwgen_user.c
SRC += mouse_jiggler_user.c
SRC += sarcasm_mode.c
SRC += eeprom_user.c
SRC += custom_keycodes_user.c
SRC += layer_lock.c
ifdef OLED_ENABLE
	SRC += oled_user.c
endif
ifdef COMBO_ENABLE
	SRC += combos_user.c
endif
ifdef RGB_MATRIX_ENABLE
	SRC += rgb_timeout_user.c
	SRC += rgb_idle_mode_user.c
	SRC += rgb_matrix_user.c
endif
ifdef DYNAMIC_MACRO_ENABLE
	SRC += dynamic_macro_user.c
endif
ifdef CAPS_WORD_ENABLE
	SRC += caps_word_user.c
endif
