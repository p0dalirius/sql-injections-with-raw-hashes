.PHONY: all compile configure

CC := gcc
CFLAGS := -g -lpthread -lcrypto -D_GNU_SOURCE

DIR_SRC := ./src/
DIR_BIN := ./bin/

$(eval NCORES := $(shell lscpu | grep "^CPU(s):" | awk '{split($$0,a," "); print a[2]}'))
$(eval LIBSSL_DEV_VERSION := $(shell ldconfig -v 2>/dev/null | grep libssl | grep '1.' | head -n1 | awk '{split($$0,a," "); print a[1]}'))
$(eval LIBSSL_AU := above)
ifeq ($(shell echo "$(LIBSSL_DEV_VERSION)" | grep "1.0" | wc -l),1)
	$(eval LIBSSL_AU := under)
endif

all : configure compile

configure :
	@echo "[CONFIGURE] Detected ${NCORES} CPU. Compiling for ${NCORES} threads."
	@echo "[CONFIGURE] Detected openssl version    : $(shell openssl version)"
	@echo "[CONFIGURE] Detected libssl-dev version : $(LIBSSL_DEV_VERSION)"
	@#
	@sed -i "s/^#define _NUM_THREADS.*/#define _NUM_THREADS ${NCORES}/g" "$(DIR_SRC)/main.c"
	@sed -i "s/^#include \".\/includes\/hashes\/hashes_libssl_.*\.h\".*/#include \".\/includes\/hashes\/hashes_libssl_$(LIBSSL_AU)_1.1.0.h\"/g" "$(DIR_SRC)/main.c"
	@#
	@if [ ! -d $(DIR_BIN) ]; then mkdir -p $(DIR_BIN); fi

compile : configure
	$(CC) \
		$(DIR_SRC)includes/hashes/hashes_libssl_$(LIBSSL_AU)_1.1.0.c \
		$(DIR_SRC)main.c \
		-I $(DIR_SRC)includes/ \
		$(CFLAGS) \
		-o $(DIR_BIN)hashsqli
