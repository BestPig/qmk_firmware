/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#ifdef KC_BLUETOOTH_ENABLE
#    include "transport.h"
#    include "lpm.h"
#endif

#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
#endif

#include "keymap.h"
#include "features/autocorrection.h"
#include "features/mouse_turbo_click.h"
#include "features/flip_mode.h"


// clang-format off
enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    MOUSE_PAD,
};

#define KC_TASK LGUI(KC_TAB)        // Task viewer
#define KC_FLXP LGUI(KC_E)          // Windows file explorer
#define KC_CORT LGUI(KC_C)          // Windows Cortana voice prompt
#define KC_SNIP LGUI(LSFT(KC_S))    // Windows snip tool
#define KC_W_FN MO(WIN_FN)          // Windows Fn

#define KC_MSSN LGUI(KC_F3)         // Mission Control
#define KC_FIND LALT(LGUI(KC_SPC))  // Finder
#define KC_MSCR LSFT(LGUI(KC_3))    // Mac screenshot
#define KC_MSNP LSFT(LGUI(KC_4))    // Mac snip tool
#define KC_SIRI LGUI(KC_SPC)        // Mac Siri voice prompt
#define KC_M_FN MO(MAC_FN)          // Mac Fn

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_108_ansi(
        KC_ESC,             KC_BRID,  KC_BRIU,  KC_MICT,  KC_LAPA,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU, KC_SNAP,  KC_SIRI,  RGB_MOD, KC_F13,  KC_F14,  KC_F15,  KC_F16,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, KC_INS,   KC_HOME,  KC_PGUP, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_DEL,   KC_END,   KC_PGDN, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,                               KC_P4,   KC_P5,   KC_P6,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,           KC_UP,             KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, KC_ROPTN,MO(MAC_FN),KC_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT, KC_P0,            KC_PDOT),

    [MAC_FN] = LAYOUT_108_ansi(
        QK_BOOT,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,  _______,  _______,  RGB_TOG, TOG_BT,  _______, _______, REPEAT,
        QK_RBT,   BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,  _______,  _______, _______, _______, _______, _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,  _______,  _______, _______, _______, _______, _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,                              _______, _______, _______,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,           _______,           _______, _______, _______, _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______, _______,  _______,  _______, _______,          _______),

    [WIN_BASE] = LAYOUT_108_ansi(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,  KC_PSCR,  KC_CTANA, RGB_MOD, _______, _______, _______, REPEAT,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, KC_INS,   KC_HOME,  KC_PGUP, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_DEL,   KC_END,   KC_PGDN, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,                               KC_P4,   KC_P5,   KC_P6,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,           KC_UP,             KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN, MO(WIN_FN),KC_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT, KC_P0,            KC_PDOT),

    [WIN_FN] = LAYOUT_108_ansi(
        QK_BOOT,            KC_BRID,  KC_BRIU,  KC_TASK,    KC_FILE,          RGB_VAD,  RGB_VAI,  KC_MPRV,       KC_MPLY,  KC_MNXT,           KC_MUTE,    KC_VOLD,  KC_VOLU, KC_SNIP,  KC_CORT,  RGB_TOG, TOG_BT,  _______, _______, _______,
        QK_RBT,   BT_HST1,  BT_HST2,  BT_HST3,  _______,    _______,          _______,  _______,  _______,       _______,  _______,           _______,    _______,  _______, _______,  RGB_M_P,  RGB_SPI, _______, _______, _______, _______,
        EE_CLR,   UC_LINX,  UC_WINC,  UC_MAC,   _______,    TURBO,            _______,  _______,  K_ANTI_IDLE,   _______,  _______,           _______,    _______,  _______, _______,  _______,  RGB_SPD, _______, _______, _______, _______,
        _______,  _______,  K_RFLPTB, K_DFLPTB, K_FLPTB,    K_GAME_MODE,      _______,  _______,  _______,       _______,  _______,           _______,              _______,                              _______, _______, _______,
        _______,            _______,  _______,  K_PBFLPTB,  K_FLIP_MODE,      BAT_LVL,  NK_TOGG,  TG(MOUSE_PAD), _______,  _______,           _______,              _______,           RGB_SAI,           _______, _______, _______, _______,
        _______,  _______,  _______,                                          _______,                                     K_AUT_COR_ACCENT,  K_AUT_COR,  _______,  _______, RGB_HUD,  RGB_SAD,  RGB_HUI, _______,          _______),

    [MOUSE_PAD] = LAYOUT_108_ansi(
        TG(MOUSE_PAD),          _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______, _______,  _______,        _______, _______,     _______,     _______,      _______, _______, _______, _______,
        _______,       KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______,  _______,  _______,  _______,  _______, _______,  _______,        _______, _______,     _______,     KC_WH_U,      _______, _______, _______, _______,
        _______,       _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______, _______,  _______,        _______, KC_WH_L,     KC_WH_R,     KC_WH_D,      _______, _______, _______, _______,
        _______,       _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,  _______, _______,                  _______,                                         _______, _______, _______,
        _______,                KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5,  KC_BTN6,  KC_BTN7,  KC_BTN8,  _______, _______,                  _______,              KC_MS_UP,                  _______, _______, _______, _______,
        _______,       _______, _______,                            _______,                                _______, _______,  TG(MOUSE_PAD),  _______, KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_RIGHT,  _______,          _______),
};

static bool changed = 0;
static uint8_t last_mode  = 0;
static uint32_t idle_timer;

bool autocorrect_enabled  = 1;
bool autocorrect_enabled_accent  = 1;
bool anti_idle_enabled  = 0;
bool game_mode_enabled = 0;
bool prog_key_enabled = 0;
bool flip_mode_enabled = 0;
uint8_t flip_char_counter  = 0;

#ifdef REPEAT_LAST_KEY
uint8_t last_keymod;
uint16_t last_keycode;
bool repeat_key_enabled = 0;
#endif

#ifdef OS_DETECTION_ENABLE
void set_unicode_mode(os_variant_t os) {
    switch (os) {
        case OS_WINDOWS:
            set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
            break;
        case OS_LINUX:
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
        case OS_MACOS:
            set_unicode_input_mode(UNICODE_MODE_MACOS);
            break;
        default:
            set_unicode_input_mode(UNICODE_MODE_BSD);
            break;
    }
}

uint32_t set_unicode_callback(uint32_t trigger_time, void *cb_arg) {
    os_variant_t os = detected_host_os();
    set_unicode_mode(os);
    return 0;
}
#endif

extern uint8_t mk_delay;

void move_mouse(void) {
    uint8_t mk_delay_bckp = mk_delay;

    mk_delay = 0;
    tap_code_delay(KC_MS_LEFT, 0);
    tap_code_delay(KC_MS_RIGHT, 0);
    tap_code_delay(KC_MS_UP, 0);
    tap_code_delay(KC_MS_DOWN, 0);
    mk_delay = mk_delay_bckp;
}

uint32_t do_anti_idle_routine(uint32_t trigger_time, void *cb_arg) {
    if (timer_elapsed32(idle_timer) >= 40000) {
        idle_timer = timer_read32();
        if (game_mode_enabled == 0 && anti_idle_enabled) {
            move_mouse();
        }
    }
    return 46000;
}

#ifdef REPEAT_LAST_KEY
uint32_t do_repeat_key(uint32_t trigger_time, void *cb_arg) {
    if (!repeat_key_enabled) {
        return 0;
    }
    uint8_t current_mods = get_mods();
    set_mods(last_keymod);
    tap_code(last_keycode);
    set_mods(current_mods);
    return 100;
}
#endif

void keyboard_post_init_user(void) {
    idle_timer = timer_read32();
    // Customise these values to desired behaviour
    // debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse = true;

    #ifdef OS_DETECTION_ENABLE
    defer_exec(1500, set_unicode_callback, NULL);
    #endif
    defer_exec(46000, do_anti_idle_routine, NULL);

  // Enable num lock
    led_t led_state = host_keyboard_led_state();
    bool b = led_state.num_lock;

    if (!b) {
        tap_code(KC_NUM_LOCK);
    }
}

void restore_previous_mode(void) {
    if (changed) {
        rgb_matrix_mode_noeeprom(last_mode);
        changed = 0;
    }
}

void enable_configured_effect(void) {
    if (!changed) {
        last_mode = rgb_matrix_get_mode();
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_only_configured_effect);
        changed = 1;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t new_layer = get_highest_layer(state);

    if (new_layer == WIN_BASE || new_layer == MAC_BASE) {
        restore_previous_mode();
    }
    else {
        enable_configured_effect();
    };
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (flip_mode_enabled) { return handle_flip_mode(keycode, record); }
    if (game_mode_enabled == 0 && autocorrect_enabled && !process_autocorrection(keycode, record)) { return false; }
    if (!process_mouse_turbo_click(keycode, record, TURBO)) { return false; }

    if (record->event.pressed) {
        idle_timer = timer_read32();
        const uint8_t current_mods = get_mods() | get_oneshot_mods();

        #ifdef REPEAT_LAST_KEY
        if (keycode != REPEAT) {
            last_keymod = current_mods;
            last_keycode = keycode;
        }
        #endif

        switch (keycode) {
            case RGB_TOG:
            case RGB_MODE_FORWARD:
            case RGB_MODE_REVERSE:
            case RGB_HUI:
            case RGB_HUD:
            case RGB_SAI:
            case RGB_SAD:
            case RGB_VAI:
            case RGB_VAD:
            case RGB_SPI:
            case RGB_SPD:
                restore_previous_mode();
                break;
            case K_AUT_COR:
                autocorrect_enabled = !autocorrect_enabled;
                dprintf("Autocorrect is now -> %d\n", autocorrect_enabled);
                break;
            case K_AUT_COR_ACCENT:
                autocorrect_enabled_accent = !autocorrect_enabled_accent;
                break;
            case K_ANTI_IDLE:
                anti_idle_enabled = !anti_idle_enabled;
                break;
            case K_GAME_MODE:
                game_mode_enabled = !game_mode_enabled;
                break;
            case K_FLPTB:
                if (!prog_key_enabled || get_unicode_input_mode() != UNICODE_MODE_LINUX)
                send_unicode_string("(╯°□°)╯︵ ┻━┻");
                else
                tap_code16(S(C(A(KC_1))));
                break;
            case K_RFLPTB:
                if (!prog_key_enabled || get_unicode_input_mode() != UNICODE_MODE_LINUX)
                send_unicode_string("┻━┻ ︵╰(°□°╰)");
                else
                tap_code16(S(C(A(KC_2))));
                break;
            case K_DFLPTB:
                if (!prog_key_enabled || get_unicode_input_mode() != UNICODE_MODE_LINUX)
                send_unicode_string("┻━┻︵ ╰(°□°)╯ ︵ ┻━┻");
                else
                tap_code16(S(C(A(KC_3))));
                break;
            case K_PBFLPTB:
                if (!prog_key_enabled || get_unicode_input_mode() != UNICODE_MODE_LINUX)
                send_unicode_string("┬─┬ ノ( ゜-゜ノ)");
                else
                tap_code16(S(C(A(KC_4))));
                break;
            case K_OS:
                dprintf("Maybe Linux: %d\n", maybe_linux);
                dprintf("Maybe Win: %d\n", maybe_win);
                dprintf("Not Mac: %d\n", not_mac);
                dprintf("Not Linux: %d\n", not_linux);

                dprintf("Current OS: %d\n", get_current_os());
                // set_unicode_callback(0, NULL);
                dprintf("Moving mouse ;)\n");
                move_mouse();
                break;
            case UC_LINX:
                if (get_unicode_input_mode() == UNICODE_MODE_LINUX)
                prog_key_enabled = !prog_key_enabled;
                break;
            case UC_WINC:
                if (get_unicode_input_mode() == UNICODE_MODE_WINCOMPOSE)
                prog_key_enabled = !prog_key_enabled;
                break;
            case UC_MAC:
                if (get_unicode_input_mode() == UNICODE_MODE_MACOS)
                prog_key_enabled = !prog_key_enabled;
                break;
            case K_FLIP_MODE:
                if (flip_mode_enabled) {
                flip_mode_enabled = 0;
                }
                else {
                if (!prog_key_enabled || get_unicode_input_mode() != UNICODE_MODE_LINUX)
                    send_unicode_string("(╯°□°)╯︵ ");
                else {
                    tap_code16(S(C(A(KC_5))));
                }
                flip_mode_enabled = 1;
                flip_char_counter = 0;
                }
                break;
            case KC_S:
                // Simulate print screen key on Linux when CTRL+WIN+S is pressed
                if (get_unicode_input_mode() == UNICODE_MODE_LINUX && current_mods & MOD_MASK_GUI && current_mods & MOD_MASK_SHIFT) {
                clear_mods();
                tap_code(KC_PSCR);
                set_mods(current_mods);
                return false;
                }
                break;
            case KC_CORT:
                if (game_mode_enabled) {
                tap_code16(S(C(KC_F9)));
                return false;
                }
                break;
            #ifdef KC_BLUETOOTH_ENABLE
            case TOG_BT:
                // Play a tone when enter is pressed
                if (get_transport() == TRANSPORT_BLUETOOTH && usb_power_connected()) {
                    set_transport(TRANSPORT_USB);
                }
                else if (get_transport() == TRANSPORT_USB) {
                    set_transport(TRANSPORT_BLUETOOTH);
                }
                return false; // Let QMK send the enter press/release events
            #endif
            #ifdef REPEAT_LAST_KEY
            case REPEAT:
                if (repeat_key_enabled == 0) {
                    defer_exec(100, do_repeat_key, NULL);
                }
                repeat_key_enabled = !repeat_key_enabled;
                return false;
            #endif
            default:
                return true; // Process all other keycodes normally
        }
    }

    return true;
}
