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
TARGET_MAP   = $(TARGET_DIR)/helloos.map
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
C_OBJS += $(TARGET_DIR)/memory.o
C_OBJS += $(TARGET_DIR)/sheet.o
C_OBJS += $(TARGET_DIR)/timer.o
C_OBJS += $(TARGET_DIR)/mtask.o
C_OBJS += $(TARGET_DIR)/window.o
C_OBJS += $(TARGET_DIR)/console.o
C_OBJS += $(TARGET_DIR)/file.o

APP_DIR        = app
APP_TARGET_DIR = app_target
APP_LNK        = $(APP_DIR)/linker/app.ld
APP_LIB_SRC    = $(APP_DIR)/lib/applib.S
A_SRC          = $(APP_DIR)/a/a.c
HELLO_SRC      = $(APP_DIR)/hello/hello.S
HELLO2_SRC     = $(APP_DIR)/hello2/hello2.S
HELLO3_SRC     = $(APP_DIR)/hello3/hello3.c
CRACK1_SRC     = $(APP_DIR)/crack1/crack1.c
CRACK2_SRC     = $(APP_DIR)/crack2/crack2.S
APP_LIB_OBJ    = $(APP_TARGET_DIR)/applib.o
A_OBJ          = $(APP_TARGET_DIR)/a.o
HELLO_OBJ      = $(APP_TARGET_DIR)/hello.o
HELLO2_OBJ     = $(APP_TARGET_DIR)/hello2.o
HELLO3_OBJ     = $(APP_TARGET_DIR)/hello3.o
CRACK1_OBJ     = $(APP_TARGET_DIR)/crack1.o
CRACK2_OBJ     = $(APP_TARGET_DIR)/crack2.o
A_APP          = $(APP_TARGET_DIR)/a.hrb
HELLO_APP      = $(APP_TARGET_DIR)/hello.hrb
HELLO2_APP     = $(APP_TARGET_DIR)/hello2.hrb
HELLO3_APP     = $(APP_TARGET_DIR)/hello3.hrb
CRACK1_APP     = $(APP_TARGET_DIR)/crack1.hrb
CRACK2_APP     = $(APP_TARGET_DIR)/crack2.hrb

CAT     = cat
MKDIR   = mkdir
# Install Gcc
GCC     = gcc
LD      = ld
OBJCOPY = objcopy
# Install Qemu
QEMU    = qemu-system-x86_64
# Install mtools
MFORMAT = mformat
MCOPY   = mcopy

LFLAGS    = -m elf_i386
CFLAGS    = -fno-pie -nostdlib -m32 -O0
OS_FLAGS  = --oformat=binary -e HariMain
APP_FLAGS = --oformat=binary -e __start

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
	$(GCC) $(CFLAGS) -c $< -o $@

$(APP_TARGET_DIR)/%.o: $(APP_DIR)/%.c
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

## Application ##

### Applib
$(APP_LIB_OBJ): $(APP_LIB_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) -c -nostdlib -m32 $< -o $@

### A App
$(A_OBJ): $(A_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(A_APP): $(APP_LIB_OBJ) $(A_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Hello App
$(HELLO_OBJ): $(HELLO_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) -c -nostdlib -m32 $< -o $@

$(HELLO_APP): $(HELLO_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(OBJCOPY) -O binary $< $@

### Hello2 App
$(HELLO2_OBJ): $(HELLO2_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) -c -nostdlib -m32 $< -o $@

$(HELLO2_APP): $(HELLO2_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(OBJCOPY) -O binary $< $@

### Hello3 App
$(HELLO3_OBJ): $(HELLO3_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(HELLO3_APP): $(APP_LIB_OBJ) $(HELLO3_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Crack1 App
$(CRACK1_OBJ): $(CRACK1_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(CRACK1_APP): $(APP_LIB_OBJ) $(CRACK1_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Crack2 App
$(CRACK2_OBJ): $(CRACK2_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) -c -nostdlib -m32 $< -o $@

$(CRACK2_APP): $(CRACK2_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(OBJCOPY) -O binary $< $@

## Application ##

$(TARGET_DIR)/%.o: $(LIB_DIR)/%.c
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(BOOTPACK_BIN): $(C_OBJS) $(ASMFUNC_OBJ) $(FONT_BIN) $(MY_CLIB_OBJ)
	$(MKDIR) -p $(TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ -T $(BOOTPACK_LNK) $(OS_FLAGS) -Map=$(TARGET_MAP) $^

$(TARGET_SYS): $(ASMHEAD_BIN) $(BOOTPACK_BIN)
	$(CAT) $^ > $@

$(TARGET_IMG): $(IPL_BIN) $(TARGET_SYS) $(HELLO_APP) $(HELLO2_APP) $(A_APP) $(HELLO3_APP) $(CRACK1_APP) $(CRACK2_APP)
    # Create image, place IPL in boot sector
	$(MFORMAT) -f 1440 -B $(IPL_BIN) -C -i $@ ::
    # Copy OS program to image
	$(MCOPY) $(TARGET_SYS) -i $@ ::
    # Import testfile.txt
	$(MCOPY) testfile.txt  -i $(TARGET_IMG) ::
	$(MCOPY) $(HELLO_APP)  -i $(TARGET_IMG) ::
	$(MCOPY) $(HELLO2_APP) -i $(TARGET_IMG) ::
	$(MCOPY) $(HELLO3_APP) -i $(TARGET_IMG) ::
	$(MCOPY) $(A_APP)      -i $(TARGET_IMG) ::
	$(MCOPY) $(CRACK1_APP) -i $(TARGET_IMG) ::
	$(MCOPY) $(CRACK2_APP) -i $(TARGET_IMG) ::

qemu:
	$(QEMU) -m 32 -fda $(TARGET_IMG)

clean:
	rm -rf $(TARGET_DIR) $(APP_TARGET_DIR)
