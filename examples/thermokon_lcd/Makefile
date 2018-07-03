# name of your application
APPLICATION = Thermokon_Example

# If no BOARD is found in the environment, use this default:
#BOARD ?= slstk3401a
BOARD ?= TK-MPRS06-LCD-A

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Required features:
FEATURES_REQUIRED = periph_adc
FEATURES_REQUIRED = periph_gpio
FEATURES_REQUIRED = periph_rtt

# required packages:
USEPKG += u8g2

# Required modules:
USEMODULE += printf_float
USEMODULE += sht35
USEMODULE += xtimer

USEMODULE += periph
USEMODULE += periph_spi

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP -DDEBUG_EFM

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
