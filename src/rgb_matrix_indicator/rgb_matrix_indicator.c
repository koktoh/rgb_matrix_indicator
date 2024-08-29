// Copyright 2024 koktoh
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_matrix_indicator.h"

#include <lib/lib8tion/lib8tion.h>

rgb_indicator_config_t indicator_config;

#ifdef LAYER_INDICATOR_LED_INDEXES
int layer_led_indexes[]    = LAYER_INDICATOR_LED_INDEXES;
int layer_led_indexes_size = ARRAY_SIZE(layer_led_indexes);
#endif

#ifdef NUMLOCK_INDICATOR_LED_INDEXES
int numlock_led_indexes[]    = NUMLOCK_INDICATOR_LED_INDEXES;
int numlock_led_indexes_size = ARRAY_SIZE(numlock_led_indexes);
#endif

#ifdef CAPSLOCK_INDICATOR_LED_INDEXES
int capslock_led_indexes[]    = CAPSLOCK_INDICATOR_LED_INDEXES;
int capslock_led_indexes_size = ARRAY_SIZE(capslock_led_indexes);
#endif

#ifdef SCROLLLOCK_INDICATOR_LED_INDEXES
int scrolllock_led_indexes[]    = SCROLLLOCK_INDICATOR_LED_INDEXES;
int scrolllock_led_indexes_size = ARRAY_SIZE(scrolllock_led_indexes);
#endif

#ifdef COMPOSE_INDICATOR_LED_INDEXES
int compose_led_indexes[]    = COMPOSE_INDICATOR_LED_INDEXES;
int compose_led_indexes_size = ARRAY_SIZE(compose_led_indexes);
#endif

#ifdef KANA_INDICATOR_LED_INDEXES
int kana_led_indexes[]    = KANA_INDICATOR_LED_INDEXES;
int kana_led_indexes_size = ARRAY_SIZE(kana_led_indexes);
#endif

uint32_t eeconfig_read_indicator(void) {
    return eeprom_read_dword((void *)RGB_INDICATOR_EEPROM_CONFIG_ADDR);
}

void eeconfig_update_indicator(uint32_t value) {
    eeprom_update_dword((void *)RGB_INDICATOR_EEPROM_CONFIG_ADDR, value);
}

void eeconfig_update_indicator_color(uint8_t hue, uint8_t sat, uint8_t val) {
    indicator_config.indicator_color.h = hue;
    indicator_config.indicator_color.s = sat;
    indicator_config.indicator_color.v = (val > INDICATOR_LIMIT_VAL) ? INDICATOR_LIMIT_VAL : val;
    eeconfig_update_indicator(indicator_config.raw);
}

void rgb_matrix_indicator_init(void) {
    indicator_config.raw = eeconfig_read_indicator();

    if (!indicator_config.is_effect_enabled) {
        disable_rgb_effect();
    }
}

void eeconfig_init_rgb_matrix_indicator(void) {
    indicator_config.raw = eeconfig_read_indicator();

    indicator_config.is_effect_enabled = true;
    indicator_config.indicator_color   = (HSV){HSV_BLUE};
    indicator_config.indicator_color.v = INDICATOR_LIMIT_VAL;
    eeconfig_update_indicator(indicator_config.raw);
}

void disable_rgb_effect(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}

bool process_record_rgb_matirx_indicator(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                indicator_config.is_effect_enabled ^= 1;         // Toggles the status
                eeconfig_update_indicator(indicator_config.raw); // Writes the new status to EEPROM
                if (indicator_config.is_effect_enabled) {
                    rgb_matrix_reload_from_eeprom();
                } else {
                    disable_rgb_effect();
                }
            }
            return false;
        case RGB_MOD ... RGB_M_SW:
            return indicator_config.is_effect_enabled;
        case RGB_IHI:
            eeconfig_update_indicator_color(indicator_config.indicator_color.h + INDICATOR_HUE_STEP, indicator_config.indicator_color.s, indicator_config.indicator_color.v);
            return false;
        case RGB_IHD:
            eeconfig_update_indicator_color(indicator_config.indicator_color.h - INDICATOR_HUE_STEP, indicator_config.indicator_color.s, indicator_config.indicator_color.v);
            return false;
        case RGB_ISI:
            eeconfig_update_indicator_color(indicator_config.indicator_color.h, qadd8(indicator_config.indicator_color.s, INDICATOR_SAT_STEP), indicator_config.indicator_color.v);
            return false;
        case RGB_ISD:
            eeconfig_update_indicator_color(indicator_config.indicator_color.h, qsub8(indicator_config.indicator_color.s, INDICATOR_SAT_STEP), indicator_config.indicator_color.v);
            return false;
        case RGB_IVI:
            eeconfig_update_indicator_color(indicator_config.indicator_color.h, indicator_config.indicator_color.s, qadd8(indicator_config.indicator_color.v, INDICATOR_VAL_STEP));
            return false;
        case RGB_IVD:
            eeconfig_update_indicator_color(indicator_config.indicator_color.h, indicator_config.indicator_color.s, qsub8(indicator_config.indicator_color.v, INDICATOR_VAL_STEP));
            return false;
        default:
            return true;
    }
}

RGB hsv_to_rgb_override_val(HSV hsv, uint8_t val) {
    hsv.v = val;
    return hsv_to_rgb(hsv);
}

void indicator_set_color(int index, uint8_t hue, uint8_t sat, uint8_t val) {
    RGB rgb = hsv_to_rgb_override_val((HSV){hue, sat, val}, indicator_config.indicator_color.v);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

void indicators_set_color(int indexes[], int size, uint8_t hue, uint8_t sat, uint8_t val) {
    RGB rgb = hsv_to_rgb_override_val((HSV){hue, sat, val}, indicator_config.indicator_color.v);
    for (int i = 0; i < size; i++) {
        rgb_matrix_set_color(indexes[i], rgb.r, rgb.g, rgb.b);
    }
}

void indicator_off(int index) {
    rgb_matrix_set_color(index, RGB_OFF);
}

void indicators_off(int indexes[], int size) {
    for (int i = 0; i < size; i++) {
        rgb_matrix_set_color(indexes[i], RGB_OFF);
    }
}

void layer_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val) {
#if defined(LAYER_INDICATOR_LED_INDEX)
    indicator_set_color(LAYER_INDICATOR_LED_INDEX, hue, sat, val);
#elif defined(LAYER_INDICATOR_LED_INDEXES)
    indicators_set_color(layer_led_indexes, layer_led_indexes_size, hue, sat, val);
#endif
}

void numlock_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val) {
#if defined(NUMLOCK_INDICATOR_LED_INDEX)
    indicator_set_color(NUMLOCK_INDICATOR_LED_INDEX, hue, sat, val);
#elif defined(NUMLOCK_INDICATOR_LED_INDEXES)
    indicators_set_color(numlock_led_indexes, numlock_led_indexes_size, hue, sat, val);
#endif
}

void numlock_indicator_off(void) {
#if defined(NUMLOCK_INDICATOR_LED_INDEX)
    indicator_off(NUMLOCK_INDICATOR_LED_INDEX);
#elif defined(NUMLOCK_INDICATOR_LED_INDEXES)
    indicators_off(numlock_led_indexes, numlock_led_indexes_size);
#endif
}

void capslock_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val) {
#if defined(CAPSLOCK_INDICATOR_LED_INDEX)
    indicator_set_color(CAPSLOCK_INDICATOR_LED_INDEX, hue, sat, val);
#elif defined(CAPSLOCK_INDICATOR_LED_INDEXES)
    indicators_set_color(capsock_led_indexes, capslock_led_indexes_size, hue, sat, val);
#endif
}

void capslock_indicator_off(void) {
#if defined(CAPSLOCK_INDICATOR_LED_INDEX)
    indicator_off(CAPSLOCK_INDICATOR_LED_INDEX);
#elif defined(CAPSLOCK_INDICATOR_LED_INDEXES)
    indicators_off(capslock_led_indexes, capslock_led_indexes_size);
#endif
}

void scrolllock_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val) {
#if defined(SCROLLLOCK_INDICATOR_LED_INDEX)
    indicator_set_color(SCROLLLOCK_INDICATOR_LED_INDEX, hue, sat, val);
#elif defined(SCROLLLOCK_INDICATOR_LED_INDEXES)
    indicators_set_color(scrolllock_led_indexes, scrolllock_led_indexes_size, hue, sat, val);
#endif
}

void scrolllock_indicator_off(void) {
#if defined(SCROLLLOCK_INDICATOR_LED_INDEX)
    indicator_off(SCROLLLOCK_INDICATOR_LED_INDEX);
#elif defined(SCROLLLOCK_INDICATOR_LED_INDEXES)
    indicators_off(scrolllock_led_indexes, scrolllock_led_indexes_size);
#endif
}

void compose_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val) {
#if defined(COMPOSE_INDICATOR_LED_INDEX)
    indicator_set_color(COMPOSE_INDICATOR_LED_INDEX, hue, sat, val);
#elif defined(COMPOSE_INDICATOR_LED_INDEXES)
    indicators_set_color(compose_led_indexes, compose_led_indexes_size, hue, sat, val);
#endif
}

void compose_indicator_off(void) {
#if defined(COMPOSE_INDICATOR_LED_INDEX)
    indicator_off(KANA_INDICATOR_LED_INDEX);
#elif defined(COMPOSE_INDICATOR_LED_INDEXES)
    indicators_off(compose_led_indexes, compose_led_indexes_size);
#endif
}

void kana_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val) {
#if defined(KANA_INDICATOR_LED_INDEX)
    indicator_set_color(KANA_INDICATOR_LED_INDEX, hue, sat, val);
#elif defined(KANA_INDICATOR_LED_INDEXES)
    indicators_set_color(kana_led_indexes, kana_led_indexes_size, hue, sat, val);
#endif
}

void kana_indicator_off(void) {
#if defined(KANA_INDICATOR_LED_INDEX)
    indicator_off(KANA_INDICATOR_LED_INDEX);
#elif defined(KANA_INDICATOR_LED_INDEXES)
    indicators_off(kana_led_indexes, kana_led_indexes_size);
#endif
}

void update_layer_indicator(uint8_t layer_state) {
    HSV hsv = (HSV){LAYER_INDICATOR_BASE_COLOR};

    hsv.h += layer_state * LAYER_INDICATOR_STEP;

    layer_indicator_set_hsv(hsv.h, hsv.s, hsv.v);
}

void update_indicators(led_t led_state) {
    if (led_state.num_lock) {
        numlock_indicator_set_hsv(indicator_config.indicator_color.h, indicator_config.indicator_color.s, indicator_config.indicator_color.v);
    } else {
        numlock_indicator_off();
    }

    if (led_state.caps_lock) {
        capslock_indicator_set_hsv(indicator_config.indicator_color.h, indicator_config.indicator_color.s, indicator_config.indicator_color.v);
    } else {
        capslock_indicator_off();
    }

    if (led_state.scroll_lock) {
        scrolllock_indicator_set_hsv(indicator_config.indicator_color.h, indicator_config.indicator_color.s, indicator_config.indicator_color.v);
    } else {
        scrolllock_indicator_off();
    }

    if (led_state.compose) {
        compose_indicator_set_hsv(indicator_config.indicator_color.h, indicator_config.indicator_color.s, indicator_config.indicator_color.v);
    } else {
        compose_indicator_off();
    }

    if (led_state.kana) {
        kana_indicator_set_hsv(indicator_config.indicator_color.h, indicator_config.indicator_color.s, indicator_config.indicator_color.v);
    } else {
        kana_indicator_off();
    }
}
