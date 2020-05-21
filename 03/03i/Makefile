TARGET     = helloos
IPL        = ipl10
ASMHEAD    = asmhead
BOOTPACK   = bootpack
TARGET_DIR = target

IPL_SRC      = $(IPL).S
ASMHEAD_SRC  = $(ASMHEAD).S
BOOTPACK_SRC = $(BOOTPACK).c
IPL_LNK      = $(IPL).ld
ASMHEAD_LNK  = $(ASMHEAD).ld
BOOTPACK_LNK = $(BOOTPACK).ld

IPL_BIN      = $(TARGET_DIR)/$(IPL).bin
ASMHEAD_BIN  = $(TARGET_DIR)/$(ASMHEAD).bin
BOOTPACK_BIN = $(TARGET_DIR)/$(BOOTPACK).bin
TARGET_SYS   = $(TARGET_DIR)/$(TARGET).sys
TARGET_IMG   = $(TARGET_DIR)/$(TARGET).img

CAT     = cat
MKDIR   = mkdir
# Install Gcc
GCC     = gcc
# Install Qemu
QEMU    = qemu-system-x86_64
# Install mtools
MFORMAT = mformat
MCOPY   = mcopy

all: $(TARGET_IMG)

$(IPL_BIN): $(IPL_LNK) $(IPL_SRC)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -nostdlib -T $^ -o $@

$(ASMHEAD_BIN): $(ASMHEAD_LNK) $(ASMHEAD_SRC)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -nostdlib -T $^ -o $@

$(BOOTPACK_BIN): $(BOOTPACK_LNK) $(BOOTPACK_SRC)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -fno-pie -nostdlib -m32 -T $^ -o $@

$(TARGET_SYS): $(ASMHEAD_BIN) $(BOOTPACK_BIN)
	$(CAT) $^ > $@

$(TARGET_IMG): $(IPL_BIN) $(TARGET_SYS)
    # Create image, place IPL in boot sector
	$(MFORMAT) -f 1440 -B $(IPL_BIN) -C -i $@ ::
    # Copy OS program to image
	$(MCOPY) $(TARGET_SYS) -i $@ ::

qemu:
	$(QEMU) -fda $(TARGET_IMG)

clean:
	rm -rf $(TARGET_DIR)
