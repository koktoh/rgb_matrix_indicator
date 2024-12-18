// Copyright 2024 koktoh
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "eeconfig.h" // for EECONFIG_SIZE
#include "rgb_matrix.h"
#include "quantum_keycodes.h"
#include "color.h"
#include "action.h"
#include "led.h"

#ifdef VIA_ENABLE
#    include "via.h" // for VIA_EEPROM_CONFIG_END
#endif

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

#define RGB_INDICATOR_EEPROM_CONFIG_SIZE ((uint8_t)sizeof(rgb_indicator_config_t))
#define RGB_INDICATOR_EEPROM_CONFIG_END (RGB_INDICATOR_EEPROM_CONFIG_ADDR + RGB_INDICATOR_EEPROM_CONFIG_SIZE)

#ifndef LAYER_INDICATOR_BASE_COLOR
#    define LAYER_INDICATOR_BASE_COLOR HSV_RED
#endif

#ifndef LAYER_INDICATOR_STEP
#    define LAYER_INDICATOR_STEP 25
#endif

#ifndef INDICATOR_HUE_STEP
#    define INDICATOR_HUE_STEP 8
#endif

#ifndef INDICATOR_SAT_STEP
#    define INDICATOR_SAT_STEP 17
#endif

#ifndef INDICATOR_VAL_STEP
#    define INDICATOR_VAL_STEP 17
#endif

#ifndef INDICATOR_LIMIT_VAL
#    define INDICATOR_LIMIT_VAL 255
#endif

enum rgb_matrix_indicator_keycodes {
    RGB_INDICATOR_HUE_UP = SAFE_RANGE,
    RGB_INDICATOR_HUE_DOWN,
    RGB_INDICATOR_SATURATION_UP,
    RGB_INDICATOR_SATURATION_DOWN,
    RGB_INDICATOR_VALUE_UP,
    RGB_INDICATOR_VALUE_DOWN,
    RGB_INDICATOR_SAFE_RANGE,

    // Alias
    RGB_IHI = RGB_INDICATOR_HUE_UP,
    RGB_IHD = RGB_INDICATOR_HUE_DOWN,
    RGB_ISI = RGB_INDICATOR_SATURATION_UP,
    RGB_ISD = RGB_INDICATOR_SATURATION_DOWN,
    RGB_IVI = RGB_INDICATOR_VALUE_UP,
    RGB_IVD = RGB_INDICATOR_VALUE_DOWN,
};

typedef union {
    uint32_t raw;
    struct PACKED {
        bool is_effect_enabled : 1;
        HSV  indicator_color;
    };
} rgb_indicator_config_t;

void rgb_matrix_indicator_init(void);
void eeconfig_init_rgb_matrix_indicator(void);

void disable_rgb_effect(void);
bool process_record_rgb_matirx_indicator(uint16_t keycode, keyrecord_t *record);
void update_layer_indicator(uint8_t layer_state);
void update_indicators(led_t led_state);
void layer_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val);
void numlock_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val);
void numlock_indicator_off(void);
void capslock_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val);
void capslock_indicator_off(void);
void scrolllock_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val);
void scrolllock_indicator_off(void);
void compose_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val);
void compose_indicator_off(void);
void kana_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val);
void kana_indicator_off(void);
