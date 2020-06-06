TARGET     = helloos
IPL        = ipl10
ASMHEAD    = asmhead
BOOTPACK   = bootpack
DSCTBL     = dsctbl
GRAPHIC    = graphic
ASMFUNC    = asmfunc
FONT       = hankaku
MY_CLIB    = my_clib

TARGET_DIR  = target
ASM_SRC_DIR = asm_src
C_SRC_DIR   = c_src
LINKER_DIR  = linker
FONT_DIR    = font
LIB_DIR     = lib

IPL_SRC      = $(ASM_SRC_DIR)/$(IPL).S
ASMHEAD_SRC  = $(ASM_SRC_DIR)/$(ASMHEAD).S
ASMFUNC_SRC  = $(ASM_SRC_DIR)/$(ASMFUNC).S
BOOTPACK_SRC = $(C_SRC_DIR)/$(BOOTPACK).c
DSCTBL_SRC   = $(C_SRC_DIR)/$(DSCTBL).c
GRAPHIC_SRC  = $(C_SRC_DIR)/$(GRAPHIC).c
IPL_LNK      = $(LINKER_DIR)/$(IPL).ld
ASMHEAD_LNK  = $(LINKER_DIR)/$(ASMHEAD).ld
BOOTPACK_LNK = $(LINKER_DIR)/$(BOOTPACK).ld
FONT_SRC     = $(FONT_DIR)/$(FONT).S
MY_CLIB_SRC  = $(LIB_DIR)/$(MY_CLIB).c

IPL_BIN      = $(TARGET_DIR)/$(IPL).bin
IPL_OBJ      = $(TARGET_DIR)/$(IPL).o
ASMHEAD_BIN  = $(TARGET_DIR)/$(ASMHEAD).bin
ASMHEAD_OBJ  = $(TARGET_DIR)/$(ASMHEAD).o
ASMFUNC_OBJ  = $(TARGET_DIR)/$(ASMFUNC).o
BOOTPACK_OBJ = $(TARGET_DIR)/$(BOOTPACK).o
DSCTBL_OBJ   = $(TARGET_DIR)/$(DSCTBL).o
GRAPHIC_OBJ  = $(TARGET_DIR)/$(GRAPHIC).o
BOOTPACK_BIN = $(TARGET_DIR)/$(BOOTPACK).bin
TARGET_SYS   = $(TARGET_DIR)/$(TARGET).sys
TARGET_IMG   = $(TARGET_DIR)/$(TARGET).img
IPL_LST      = $(TARGET_DIR)/$(IPL).lst
ASMHEAD_LST  = $(TARGET_DIR)/$(ASMHEAD).lst
ASMFUNC_LST  = $(TARGET_DIR)/$(ASMFUNC).lst
FONT_BIN     = $(TARGET_DIR)/$(FONT).bin
MY_CLIB_OBJ  = $(TARGET_DIR)/$(MY_CLIB).o

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

$(DSCTBL_OBJ): $(DSCTBL_SRC)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -fno-pie -nostdlib -m32 -c $< -o $@

$(GRAPHIC_OBJ): $(GRAPHIC_SRC)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -fno-pie -nostdlib -m32 -c $< -o $@

$(MY_CLIB_OBJ): $(MY_CLIB_SRC)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -fno-pie -nostdlib -m32 -c $< -o $@

$(BOOTPACK_BIN): $(BOOTPACK_OBJ) $(DSCTBL_OBJ) $(GRAPHIC_OBJ) $(ASMFUNC_OBJ) $(FONT_BIN) $(MY_CLIB_OBJ)
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
