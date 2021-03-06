TARGET     = helloos
IPL        = ipl10
ASMHEAD    = asmhead
BOOTPACK   = bootpack
ASMFUNC    = asmfunc
TARGET_DIR = target
FONT       = hankaku

IPL_SRC      = $(IPL).S
ASMHEAD_SRC  = $(ASMHEAD).S
BOOTPACK_SRC = $(BOOTPACK).c
IPL_LNK      = $(IPL).ld
ASMHEAD_LNK  = $(ASMHEAD).ld
BOOTPACK_LNK = $(BOOTPACK).ld
ASMFUNC_SRC  = $(ASMFUNC).S
FONT_SRC     = $(FONT).S

IPL_BIN      = $(TARGET_DIR)/$(IPL).bin
IPL_OBJ      = $(TARGET_DIR)/$(IPL).o
ASMHEAD_BIN  = $(TARGET_DIR)/$(ASMHEAD).bin
ASMHEAD_OBJ  = $(TARGET_DIR)/$(ASMHEAD).o
ASMFUNC_OBJ  = $(TARGET_DIR)/$(ASMFUNC).o
BOOTPACK_OBJ = $(TARGET_DIR)/$(BOOTPACK).o
BOOTPACK_BIN = $(TARGET_DIR)/$(BOOTPACK).bin
TARGET_SYS   = $(TARGET_DIR)/$(TARGET).sys
TARGET_IMG   = $(TARGET_DIR)/$(TARGET).img
IPL_LST      = $(TARGET_DIR)/$(IPL).lst
ASMHEAD_LST  = $(TARGET_DIR)/$(ASMHEAD).lst
ASMFUNC_LST  = $(TARGET_DIR)/$(ASMFUNC).lst
FONT_BIN     = $(TARGET_DIR)/$(FONT).bin

CAT     = cat
MKDIR   = mkdir
# Install Gcc
GCC     = gcc
LD      = ld
# Install Qemu
QEMU    = qemu-system-x86_64
# Install mtools
MFORMAT = mformat
MCOPY   = mcopy

all: $(TARGET_IMG)

$(IPL_BIN): $(IPL_LNK) $(IPL_SRC)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -nostdlib -T $^ -o $@
	$(GCC) -T $(IPL_LNK) -c -g -Wa,-a,-ad $(IPL_SRC) -o $(IPL_OBJ) > $(IPL_LST)

$(ASMHEAD_BIN): $(ASMHEAD_LNK) $(ASMHEAD_SRC)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -nostdlib -T $^ -o $@
	$(GCC) -T $(ASMHEAD_LNK) -c -g -Wa,-a,-ad $(ASMHEAD_SRC) -o $(ASMHEAD_OBJ) > $(ASMHEAD_LST)

$(ASMFUNC_OBJ): $(ASMFUNC_SRC)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -m32 -c -g -Wa,-a,-ad $< -o $@ > $(ASMFUNC_LST)

$(FONT_BIN): $(FONT_SRC)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -m32 -T .data -c $< -o $@

$(BOOTPACK_OBJ): $(BOOTPACK_SRC)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -fno-pie -nostdlib -m32 -c $< -o $@

$(BOOTPACK_BIN): $(BOOTPACK_OBJ) $(ASMFUNC_OBJ) $(FONT_BIN)
	$(MKDIR) -p $(TARGET_DIR)
	$(LD) -m elf_i386 -o $@ -T $(BOOTPACK_LNK) --oformat=binary -shared $^

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
