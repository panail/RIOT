PKG_NAME=gecko_sdk
PKG_URL=https://github.com/kaibeckmann/RIOT-gecko-sdk
PKG_VERSION=d76b98633e64d1026cffacd6780949db4f6ef9ab
PKG_LICENSE=Zlib

ifneq ($(CPU),efm32)
  $(error This package can only be used with EFM32 CPUs)
endif

.PHONY: all

all: git-download
	"$(MAKE)" -C $(PKG_BUILDDIR)/dist

include $(RIOTBASE)/pkg/pkg.mk
