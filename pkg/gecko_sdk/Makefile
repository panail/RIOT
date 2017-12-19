PKG_NAME=gecko_sdk
PKG_URL=https://github.com/kaibeckmann/RIOT-gecko-sdk
PKG_VERSION=d3284819d650a010b3d6492996682a4a58c7f5a9
PKG_LICENSE=Zlib

ifneq ($(CPU),efm32)
  $(error This package can only be used with EFM32 CPUs)
endif

.PHONY: all

all: git-download
	"$(MAKE)" -C $(PKG_BUILDDIR)/dist

include $(RIOTBASE)/pkg/pkg.mk
