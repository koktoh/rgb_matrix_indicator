// Copyright 2024 koktoh
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Define the RGB_INDICATOR_EEPROM_CONFIG_ADDR
 *
 * You should define the RGB_INDICATOR_EEPROM_CONFIG_ADDR in config.h.
 * Feel free to copy and use it.
 */
#ifdef DYNAMIC_KEYMAP_ENABLE
#    ifdef VIA_ENABLE
#        define DYNAMIC_KEYMAP_EEPROM_ADDR (VIA_EEPROM_CONFIG_END)
#    else // VIA_ANABLE
#        define DYNAMIC_KEYMAP_EEPROM_ADDR (EECONFIG_SIZE)
#    endif // VIA_ENABLE

#    define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR (TOTAL_EEPROM_BYTE_COUNT - 1)
#    define DYNAMIC_KEYMAP_LAYER_COUNT 4
#    define DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR (DYNAMIC_KEYMAP_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2))

#    ifdef ENCODER_MAP_ENABLE
#        define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * NUM_ENCODERS * 2 * 2))
#    else // ENCODER_MAP_ENABLE
#        define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR)
#    endif // ENCODER_MAP_ENABLE

#    define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE (DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 1)

#    define RGB_INDICATOR_EEPROM_CONFIG_ADDR (DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE)
#else // DYNAMIC_KEYMAP_ENABLE
#    define RGB_INDICATOR_EEPROM_CONFIG_ADDR (EECONFIG_SIZE)
#endif // DYNAMIC_KEYMAP_ENABLE
/* END Define the RGB_INDICATOR_EEPROM_CONFIG_ADDR */

/*
 * Define the LED index
 *
 * You can define either XXXX_INDICATOR_LED_INDEX or XXXX_INDICATOR_LED_INDEXES.
 * If neither XXXX_INDICATOR_LED_INDEX nor XXXX_INDICATOR_LED_INDEXES is defined, the LED is not defined as the indicator.
 *
 * XXXX_INDICATOR_LED_INDEX:   Single LED is defined as the indicator for each state.
 *
 * XXXX_INDICATOR_LED_INDEXES: Multiple LEDs are defined as the indicator for each state.
 *                             Multiple indicator LEDs light same color.
 *                             You can define any number of the LED index.
 */

/* ---- Single LED ---- */
#define LAYER_INDICATOR_LED_INDEX 0

#define NUMLOCK_INDICATOR_LED_INDEX 1
#define CAPSLOCK_INDICATOR_LED_INDEX 2
#define SCROLLLOCK_INDICATOR_LED_INDEX 3
#define COMPOSE_INDICATOR_LED_INDEX 4
#define KANA_INDICATOR_LED_INDEX 5
/* ---- Single LED ---- */

/* ---- Multiple LEDs ---- */
#define LAYER_INDICATOR_LED_INDEXES { 0, 1 }

#define NUMLOCK_INDICATOR_LED_INDEXES { 2, 3 }
#define CAPSLOCK_INDICATOR_LED_INDEXES { 4, 5, 6 }
#define SCROLLLOCK_INDICATOR_LED_INDEXES { 7, 8, 9, 10 }
#define COMPOSE_INDICATOR_LED_INDEXES { 11, 12 }
#define KANA_INDICATOR_LED_INDEXES { 13, 14 }
/* ---- Multiple LEDs ---- */

/* END Define the LED index */

/*
 * Additional configurations
 *
 * If not defined, the default value will be used.
 */
#define LAYER_INDICATOR_BASE_COLOR HSV_CYAN // Default is HSV_RED
#define LAYER_INDICATOR_STEP 17             // Default is 25
#define INDICATOR_HUE_STEP 4                // Default is 8
#define INDICATOR_SAT_STEP 8                // Default is 17
#define INDICATOR_VAL_STEP 8                // Default is 17
#define INDICATOR_LIMIT_VAL 127             // Default is 255
