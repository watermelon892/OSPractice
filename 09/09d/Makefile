TARGET_DIR  = target
ASM_SRC_DIR = asm_src
C_SRC_DIR   = c_src
LINKER_DIR  = linker
FONT_DIR    = font
LIB_DIR     = lib

IPL_SRC      = $(ASM_SRC_DIR)/ipl10.S
ASMHEAD_SRC  = $(ASM_SRC_DIR)/asmhead.S
ASMFUNC_SRC  = $(ASM_SRC_DIR)/asmfunc.S
IPL_LNK      = $(LINKER_DIR)/ipl10.ld
ASMHEAD_LNK  = $(LINKER_DIR)/asmhead.ld
BOOTPACK_LNK = $(LINKER_DIR)/bootpack.ld
FONT_SRC     = $(FONT_DIR)/hankaku.S
MY_CLIB_SRC  = $(LIB_DIR)/my_clib.c

IPL_BIN      = $(TARGET_DIR)/ipl10.bin
IPL_OBJ      = $(TARGET_DIR)/ipl10.o
ASMHEAD_BIN  = $(TARGET_DIR)/asmhead.bin
ASMHEAD_OBJ  = $(TARGET_DIR)/asmhead.o
ASMFUNC_OBJ  = $(TARGET_DIR)/asmfunc.o
BOOTPACK_BIN = $(TARGET_DIR)/bootpack.bin
TARGET_SYS   = $(TARGET_DIR)/helloos.sys
TARGET_IMG   = $(TARGET_DIR)/helloos.img
IPL_LST      = $(TARGET_DIR)/ipl10.lst
ASMHEAD_LST  = $(TARGET_DIR)/asmhead.lst
ASMFUNC_LST  = $(TARGET_DIR)/asmfunc.lst
FONT_BIN     = $(TARGET_DIR)/hankaku.bin
MY_CLIB_OBJ  = $(TARGET_DIR)/my_clib.o

C_OBJS  = $(TARGET_DIR)/bootpack.o
C_OBJS += $(TARGET_DIR)/dsctbl.o
C_OBJS += $(TARGET_DIR)/graphic.o
C_OBJS += $(TARGET_DIR)/int.o
C_OBJS += $(TARGET_DIR)/fifo.o
C_OBJS += $(TARGET_DIR)/keyboard.o
C_OBJS += $(TARGET_DIR)/mouse.o

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

$(TARGET_DIR)/%.o: $(C_SRC_DIR)/%.c
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -fno-pie -nostdlib -m32 -c $< -o $@

$(TARGET_DIR)/%.o: $(LIB_DIR)/%.c
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) -fno-pie -nostdlib -m32 -c $< -o $@

$(BOOTPACK_BIN): $(C_OBJS) $(ASMFUNC_OBJ) $(FONT_BIN) $(MY_CLIB_OBJ)
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
	$(QEMU) -m 32 -fda $(TARGET_IMG)

clean:
	rm -rf $(TARGET_DIR)
