#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "quantum.h"

enum custom_keycodes {
  TURBO = QK_KB_0,
  K_AUT_COR,
  K_AUT_COR_ACCENT,
  K_ANTI_IDLE,
  K_GAME_MODE,
  K_FLPTB, // Flip Table
  K_RFLPTB, // Reverse flip table
  K_DFLPTB, // Double flip table
  K_PBFLPTB, // Push-back flip table
  K_OS,
  K_FLIP_MODE,
  TOG_BT,
  // Other custom keys...
};

enum operating_system {
  HOST_OS_WIN = 0,
  HOST_OS_LIN = 1,
  HOST_OS_MAC = 2,
  HOST_UNKNWN = 3,
};

#ifdef RAW_ENABLE
enum qmk_rc_commands_custom {
  RC_MOVE_MOUSE = 32,
  RC_TOGGLE_GAME_MODE = 33,
  RC_GET_PROG_KEY_STATUS = 34,
  RC_TOGGLE_PROG_KEY = 35,
  RC_SET_OS = 36,
  RC_PING = 37,
};
#endif

enum operating_system get_current_os(void);

#ifdef __cplusplus
}
#endif
