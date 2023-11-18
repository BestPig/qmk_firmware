VIA_ENABLE = yes
MOUSEKEY_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes
# LTO_ENABLE = no
# CONSOLE_ENABLE = no
UNICODE_ENABLE = yes
# EXTRAKEY_ENABLE = no

# PROGRAMMABLE_BUTTON_ENABLE = yes

# OS_DETECTION_ENABLE = yes

# Free space :)
# SPACE_CADET_ENABLE = no
# GRAVE_ESC_ENABLE = no
# AVR_USE_MINIMAL_PRINTF = yes

SRC += features/autocorrection.c
SRC += features/mouse_turbo_click.c
SRC += features/flip_mode.c
# SRC += qmk_rc.c

# BOOTMAGIC_ENABLE = yes
#SRC += bootmagic_lite.c

# EXTRAFLAGS += -O3
