PKG_NAME=gecko_sdk
PKG_URL=https://github.com/kaibeckmann/RIOT-gecko-sdk
PKG_VERSION=80b3ec0848748d4333e5632c62b8bae583870dc0
PKG_LICENSE=Zlib

ifneq ($(CPU),efm32)
  $(error This package can only be used with EFM32 CPUs)
endif

.PHONY: all

all: git-download
	"$(MAKE)" -C $(PKG_BUILDDIR)/dist

include $(RIOTBASE)/pkg/pkg.mk
