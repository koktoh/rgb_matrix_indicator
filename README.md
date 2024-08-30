# rgb_matrix_indicator

Control the indicators in the QMK RGB MATRIX.

## Contents

### src/rgb_matrix_indicator directory

Source code.

Copy the `rgb_matrix_indicator` directory under the `<keyboard>` directory to use it.

### example_xxxx files

Usage examples.

It is written with a specific code example.

## Keycodes

### Overridden keycodes

| Key                          | Default operation             | Overridden operation                                         |
|:-----------------------------|:------------------------------|:-------------------------------------------------------------|
| `RGB_TOG`                    | Toggle RGB lighting on or off | Toggle RGB lighting without affecting the indicator lighting |
| from `RGB_MOD` to `RGB_M_SW` | Default operation             | No change if only the indicators are lit                     |

### Custom keycodes

| Key                             | Alies     | Description                                           |
|:--------------------------------|:----------|:------------------------------------------------------|
| `RGB_INDICATOR_HUE_UP`          | `RGB_IHI` | Increase hue of the indicator lighting                |
| `RGB_INDICATOR_HUE_DOWN`        | `RGB_IHD` | Decrease hue of the indicator lighting                |
| `RGB_INDICATOR_SATURATION_UP`   | `RGB_ISI` | Increase saturation of the indicator lighting         |
| `RGB_INDICATOR_SATURATION_DOWN` | `RGB_ISD` | Decrease saturation of the indicator lighting         |
| `RGB_INDICATOR_VALUE_UP`        | `RGB_IVI` | Increase value (brightness) of the indicator lighting |
| `RGB_INDICATOR_VALUE_DOWN`      | `RGB_IVD` | Derease value (brightness) of the indicator lighting  |

## Configurations

| Define                             | Default       | Description                                                                                                                 |
|:-----------------------------------|:--------------|:----------------------------------------------------------------------------------------------------------------------------|
| `RGB_INDICATOR_EEPROM_CONFIG_ADDR` | _Not defined_ | The EEPROM address of rgb matrix indicator configuration. You must define this                                              |
| `LAYER_INDICATOR_LED_INDEX`        | _Not defined_ | The number of the LED index for using the Layer indicator. Mutually exclusive with `LAYER_INDICATOR_LED_INDEXES`            |
| `NUMLOCK_INDICATOR_LED_INDEX`      | _Not defined_ | The number of the LED index for using the Num Lock indicator. Mutually exclusive with `NUMLOCK_INDICATOR_LED_INDEXES`       |
| `CAPSLOCK_INDICATOR_LED_INDEX`     | _Not defined_ | The number of the LED index for using the Caps Lock indicator. Mutually exclusive with `CAPSLOCK_INDICATOR_LED_INDEXES`     |
| `SCROLLLOCK_INDICATOR_LED_INDEX`   | _Not defined_ | The number of the LED index for using the Scroll Lock indicator. Mutually exclusive with `SCROLLLOCK_INDICATOR_LED_INDEXES` |
| `COMPOSE_INDICATOR_LED_INDEX`      | _Not defined_ | The number of the LED index for using the Compose indicator. Mutually exclusive with `COMPOSE_INDICATOR_LED_INDEXES`        |
| `KANA_INDICATOR_LED_INDEX`         | _Not defined_ | The number of the LED index for using the Kana indicator. Mutually exclusive with `KANA_INDICATOR_LED_INDEXES`              |
| `LAYER_INDICATOR_LED_INDEXES`      | _Not defined_ | The number of the LED indexes for using the Layer indicator. Mutually exclusive with `LAYER_INDICATOR_LED_INDEX`            |
| `NUMLOCK_INDICATOR_LED_INDEXES`    | _Not defined_ | The number of the LED indexes for using the Num Lock indicator. Mutually exclusive with `NUMLOCK_INDICATOR_LED_INDEX`       |
| `CAPSLOCK_INDICATOR_LED_INDEXES`   | _Not defined_ | The number of the LED indexes for using the Caps Lock indicator. Mutually exclusive with `CAPSLOCK_INDICATOR_LED_INDEX`     |
| `SCROLLLOCK_INDICATOR_LED_INDEXES` | _Not defined_ | The number of the LED indexes for using the Scroll Lock indicator. Mutually exclusive with `SCROLLLOCK_INDICATOR_LED_INDEX` |
| `COMPOSE_INDICATOR_LED_INDEXES`    | _Not defined_ | The number of the LED indexes for using the Compose indicator. Mutually exclusive with `COMPOSE_INDICATOR_LED_INDEX`        |
| `KANA_INDICATOR_LED_INDEXES`       | _Not defined_ | The number of the LED indexes for using the Kana indicator. Mutually exclusive with `KANA_INDICATOR_LED_INDEX`              |
| `LAYER_INDICATOR_BASE_COLOR`       | `HSV_RED`     | The color of default (layer 0) color for the Layer indicator by                                                             |
| `LAYER_INDICATOR_STEP`             | `25`          | The number of steps to cycle through the hue for the Layer indicator by                                                     |
| `INDICATOR_HUE_STEP`               | `8`           | The number of steps to cycle through the hue for the indicator by                                                           |
| `INDICATOR_SAT_STEP`               | `17`          | The number of steps to increment the saturation for the indicator by                                                        |
| `INDICATOR_VAL_STEP`               | `17`          | The number of steps to increment the brightness for the indicator by                                                        |
| `INDICATOR_LIMIT_VAL`              | `255`         | The maximum brightness level for the indicator                                                                              |

## API

### void rgb_matrix_indicator_init(void)

Initialize rgb_matrix_indicator.

### void eeconfig_init_rgb_matrix_indicator(void)

Reinitializes the rgb_matrix_indicator's EEPROM (persistent memory).

### void disable_rgb_effect(void)

Turn off RGB lighting without affecting the indicator lighting.

### bool process_record_rgb_matirx_indicator(uint16_t keycode, keyrecord_t *record)

Run the behaviors for rgb_matrix_indicator_keycodes that defined in rgb_matrix_indicator.h.

#### Arguments

* `uint16_t keycode`
  Same as `process_record_*` function's argument.
* `keyrecord_t *record`
  Same as `process_record_*` function's argument.

#### Return value

Same as `process_record_*` function's return value.

### void update_layer_indicator(uint8_t layer_state)

Update the layer indicator(s).

#### Arguments

* `uint8_t layer_state`

The layer state to update the layer indicator lighting(s).

### void update_indicators(led_t led_state)

Update all indicators except the layer indicator(s). (e.g. Num Lock, Caps Lock, etc...)

#### Arguments

* `let_t led_state`
  The led state to toggle the indicator lighting(s).

### void layer_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val)

Set the color of the layer indicator(s).

Only `RGB_IVI` and `RGB_IVD` are applied.

#### Arguments

* `uint8_t hue`
  The hue to set, from 0 to 255.
* `uint8_t sat`
  The saturation to set, from 0 to 255.
* `uint8_t val`
  The value (brightness) to set, from 0 to 255.

### void numlock_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val)

Set the color of the Num Lock indicator(s).

Only `RGB_IVI` and `RGB_IVD` are applied.

#### Arguments

* `uint8_t hue`
  The hue to set, from 0 to 255.
* `uint8_t sat`
  The saturation to set, from 0 to 255.
* `uint8_t val`
  The value (brightness) to set, from 0 to 255.

### void numlock_indicator_off(void)

Turn off the Num Lock indicator(s).

### void capslock_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val)

Set the color of the Caps Lock indicator(s).

Only `RGB_IVI` and `RGB_IVD` are applied.

#### Arguments

* `uint8_t hue`
  The hue to set, from 0 to 255.
* `uint8_t sat`
  The saturation to set, from 0 to 255.
* `uint8_t val`
  The value (brightness) to set, from 0 to 255.

### void capslock_indicator_off(void)

Turn off the Caps Lock indicator(s).

### void scrolllock_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val)

Set the color of the Scroll Lock indicator(s).

Only `RGB_IVI` and `RGB_IVD` are applied.

#### Arguments

* `uint8_t hue`
  The hue to set, from 0 to 255.
* `uint8_t sat`
  The saturation to set, from 0 to 255.
* `uint8_t val`
  The value (brightness) to set, from 0 to 255.

### void scrolllock_indicator_off(void)

Turn off the Scroll Lock indicator(s).

### void compose_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val)

Set the color of the Compose indicator(s).

Only `RGB_IVI` and `RGB_IVD` are applied.

#### Arguments

* `uint8_t hue`
  The hue to set, from 0 to 255.
* `uint8_t sat`
  The saturation to set, from 0 to 255.
* `uint8_t val`
  The value (brightness) to set, from 0 to 255.

### void compose_indicator_off(void)

Turn off the Compose indicator(s).

### void kana_indicator_set_hsv(uint8_t hue, uint8_t sat, uint8_t val)

Set the color of the Kana indicator(s).

Only `RGB_IVI` and `RGB_IVD` are applied.

#### Arguments

* `uint8_t hue`
  The hue to set, from 0 to 255.
* `uint8_t sat`
  The saturation to set, from 0 to 255.
* `uint8_t val`
  The value (brightness) to set, from 0 to 255.

### void kana_indicator_off(void)

Turn off the Kana indicator(s).

## See also

[How to use rgb_matrix_indicator (Japanese)](https://koktoh.hatenablog.com/entry/2024/08/30/185017)
