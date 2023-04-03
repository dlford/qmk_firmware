SRC += features/tap_rules.c
SRC += features/random_password.c
SRC += features/mouse_jiggler.c
SRC += features/sarcasm_mode.c
SRC += features/alt_tab.c
ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += features/oled.c
endif
ifeq ($(strip $(COMBO_ENABLE)), yes)
	SRC += features/combos.c
endif
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC += features/rgb_timeout.c
	SRC += features/rgb_matrix.c
	SRC += features/custom_eeprom.c
endif
