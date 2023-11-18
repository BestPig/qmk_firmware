#include "quantum.h"


extern bool flip_mode_enabled;
extern uint8_t flip_char_counter;


void send_upsidedown_key(const char *str) {
    const uint8_t current_mods = get_mods() | get_oneshot_mods();

    send_unicode_string(str);
    flip_char_counter++;
    clear_mods();
    tap_code(KC_LEFT);
    set_mods(current_mods);
}

/*
reverse = {
    'a': 'ɐ',
    'b': 'q',
    'c': 'ɔ',
    'd': 'p',
    'e': 'ǝ',
    'f': 'ɟ',
    'g': 'ɓ',
    'h': 'ɥ',
    'i': 'ᴉ',
    'j': 'ɾ',
    'k': 'ʞ',
    'l': 'ʅ',
    'm': 'ɯ',
    'n': 'u',
    'o': 'o',
    'p': 'd',
    'q': 'b',
    'r': 'ɹ',
    's': 's',
    't': 'ʇ',
    'u': 'n',
    'v': 'ʌ',
    'w': 'ʍ',
    'x': 'x',
    'y': 'ʎ',
    'z': 'z',
    'A': 'Ɐ',
    'B': 'q',
    'C': 'Ɔ',
    'D': 'p',
    'E': 'Ǝ',
    'F': 'Ⅎ',
    'G': 'פ',
    'H': 'H',
    'I': 'I',
    'J': 'ſ',
    'K': 'ʞ',
    'L': '˥',
    'M': 'W',
    'N': 'N',
    'O': 'O',
    'P': 'Ԁ',
    'Q': 'Ὸ',
    'R': 'ꓤ',
    'S': 'S',
    'T': 'ꓕ',
    'U': '∩',
    'V': 'Λ',
    'W': 'M',
    'X': 'X',
    'Y': '⅄',
    'Z': 'Z',
    '!': '¡',
    '?': '¿',
    '.': '·',
    ',': 'ʻ',
    '&': '⅋',
    '-': '-',
    '_': '‾',
    '|': '|',
    '(': ')',
    ')': '(',
    '{': '}',
    '}': '{',
    '[': ']',
    ']': '[',
    ' ': ' ',
    '/': '/',
    '\\': '\\',
    '\'': ',',
    '·': '·'}
*/

char *get_unicode_upsidedown_key(uint16_t keycode) {
    const uint8_t current_mods = get_mods() | get_oneshot_mods();

    if (current_mods & MOD_MASK_SHIFT) {
        switch (keycode) {
            case KC_A:
                return "Ɐ";
            case KC_B:
                return "ꓭ";
            case KC_C:
                return "ꓛ";
            case KC_D:
                return "ꓷ";
            case KC_E:
                return "Ǝ";
            case KC_F:
                return "ꓞ";
            case KC_G:
                return "ꓨ";
            case KC_H:
                return "H";
            case KC_I:
                return "I";
            case KC_J:
                return "ſ";
            case KC_K:
                return "ꓘ";
            case KC_L:
                return "ꓶ";
            case KC_M:
                return "W";
            case KC_N:
                return "N";
            case KC_O:
                return "O";
            case KC_P:
                return "ꓒ";
            case KC_Q:
                return "Ὸ";
            case KC_R:
                return "ꓤ";
            case KC_S:
                return "S";
            case KC_T:
                return "ꓕ";
            case KC_U:
                return "ꓵ";
            case KC_V:
                return "ꓥ";
            case KC_W:
                return "M";
            case KC_X:
                return "X";
            case KC_Y:
                return "⅄";
            case KC_Z:
                return "Z";
        }
    }
    else {
        switch (keycode) {
            case KC_A:
                return "ɐ";
            case KC_B:
                return "q";
            case KC_C:
                return "ɔ";
            case KC_D:
                return "p";
            case KC_E:
                return "ǝ";
            case KC_F:
                return "ɟ";
            case KC_G:
                return "ɓ";
            case KC_H:
                return "ɥ";
            case KC_I:
                return "ᴉ";
            case KC_J:
                return "ꓩ";
            case KC_K:
                return "ʞ";
            case KC_L:
                return "ʅ";
            case KC_M:
                return "ɯ";
            case KC_N:
                return "u";
            case KC_O:
                return "o";
            case KC_P:
                return "d";
            case KC_Q:
                return "b";
            case KC_R:
                return "ɹ";
            case KC_S:
                return "s";
            case KC_T:
                return "ʇ";
            case KC_U:
                return "n";
            case KC_V:
                return "ʌ";
            case KC_W:
                return "ʍ";
            case KC_X:
                return "x";
            case KC_Y:
                return "ʎ";
            case KC_Z:
                return "z";
        }
    }
    return NULL;
}

bool handle_flip_mode(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        const uint8_t current_mods = get_mods() | get_oneshot_mods();
        char *tmp_str;

        switch (keycode) {
            case KC_A...KC_Z:
                tmp_str = get_unicode_upsidedown_key(keycode);
                if (tmp_str) {
                    send_upsidedown_key(tmp_str);
                }
                break;
            case KC_ENTER:
            case KC_ESCAPE:
                flip_mode_enabled = 0;
                while (flip_char_counter > 0) {
                    tap_code(KC_RIGHT);
                    flip_char_counter--;
                }
                break;
            case KC_1...KC_0:
            case KC_TAB...KC_NONUS_BACKSLASH:
                flip_char_counter++;
                tap_code(keycode);
                clear_mods();
                tap_code(KC_LEFT);
                set_mods(current_mods);
                return false;
            case KC_BACKSPACE:
                if (flip_char_counter > 0) {
                    tap_code(KC_DELETE);
                    flip_char_counter--;
                }
                break;
            default:
                return true;
        }
        return false;
    }
    return true;
}