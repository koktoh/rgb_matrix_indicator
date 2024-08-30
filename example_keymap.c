// Copyright 2023 koktoh
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "rgb_matrix/rgb_matrix_indicator.h"

#define _BASE 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3

enum custom_keycodes {
    CUSTOM1 = RGB_INDICATOR_SAFE_RANGE, // Define keycode safe range
    CUSTOM2,
    CUSTOM3,
    CUSTOM4,
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_3x3(
        KC_A,    KC_B,    TO(_LAYER1),
        KC_C,    KC_D,    KC_E,
        KC_F,    KC_G,    KC_H
    ),
    [_LAYER1] = LAYOUT_ortho_3x3(
        RGB_TOG, RGB_MOD, TO(_LAYER2),
        RGB_HUI, RGB_SAI, RGB_VAI,
        RGB_HUD, RGB_SAD, RGB_VAD
    ),
    [_LAYER2] = LAYOUT_ortho_3x3(
        XXXXXXX, XXXXXXX, TO(_LAYER3),
        RGB_IHI, RGB_ISI, RGB_IVI,
        RGB_IHD, RGB_ISD, RGB_IVD
    ),
    [_LAYER3] = LAYOUT_ortho_3x3(
        XXXXXXX, XXXXXXX, TO(_BASE),
        CUSTOM1, CUSTOM2, CUSTOM3,
        CUSTOM4, XXXXXXX, XXXXXXX
    ),
};
// clang-format on

void eeconfig_init_user(void) {
    /* ---- Reset the EEPROM space for rgb_matrix_indicator when the EEPROM is reset ---- */
    eeconfig_init_rgb_matrix_indicator();
    /* ---- Reset the EEPROM spade for rgb_matrix_indicator when the EEPROM is reset ---- */
}

void keyboard_post_init_user(void) {
    /* ---- Initialize rgb_matrix_indicator ---- */
    rgb_matrix_indicator_init();
    /* ---- Initialize rgb_matrix_indicator ---- */
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* ---- Run the behaviors for rgb_matrix_indicator_keycodes that defined in rgb_matrix_indicator.h ---- */
    bool p_rgb_indicator = process_record_rgb_matirx_indicator(keycode, record);
    if (!p_rgb_indicator) {
        return false;
    }
    /* ---- Run the behaviors for rgb_matrix_indicator_keycodes that defined in rgb_matrix_indicator.h ---- */

    /*
     * If you want to define the behaviors for custom keycodes,
     * write from here.
     */
    switch (keycode) {
        case CUSTOM1:
            if (record->event.pressed) {
                // Do something when pressed
            } else {
                // Do something else when release
            }
            return false;
        case CUSTOM2:
            if (record->event.pressed) {
                // Do something when pressed
            } else {
                // Do something else when release
            }
            return false;
        case CUSTOM3:
            if (record->event.pressed) {
                // Do something when pressed
            } else {
                // Do something else when release
            }
            return false;
        case CUSTOM4:
            if (record->event.pressed) {
                // Do something when pressed
            } else {
                // Do something else when release
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    /*
     * Generally, "General usage" is sufficient.
     *
     * If you want to perform a customized action, write it as in "Custom usage".
     */

    /* ---- General usage ---- */
    update_layer_indicator(get_highest_layer(layer_state | default_layer_state));
    update_indicators(host_keyboard_led_state());
    /* ---- General usage ---- */

    /* ---- Custom usasge ---- */
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _BASE:
            layer_indicator_set_hsv(HSV_CYAN);
            break;
        case _LAYER1:
            layer_indicator_set_hsv(HSV_MAGENTA);
            break;
        case _LAYER2:
            layer_indicator_set_hsv(HSV_ORANGE);
            break;
        case _LAYER3:
            layer_indicator_set_hsv(HSV_PURPLE);
            break;
        default:
            break;
    }

    if (host_keyboard_led_state().num_lock) {
        numlock_indicator_set_hsv(HSV_AZURE);
    } else {
        numlock_indicator_off();
    }

    if (host_keyboard_led_state().caps_lock) {
        capslock_indicator_set_hsv(HSV_YELLOW);
    } else {
        capslock_indicator_off();
    }
    /* ---- Custom usage ---- */

    return false;
}
