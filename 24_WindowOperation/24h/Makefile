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
HELLO4_SRC     = $(APP_DIR)/hello4/hello4.c
HELLO5_SRC     = $(APP_DIR)/hello5/hello5.S
WIN_HELLO_SRC  = $(APP_DIR)/winhelo/winhelo.c
WIN_HELLO2_SRC = $(APP_DIR)/winhelo2/winhelo2.c
WIN_HELLO3_SRC = $(APP_DIR)/winhelo3/winhelo3.c
STAR1_SRC      = $(APP_DIR)/star1/star1.c
STARS_SRC      = $(APP_DIR)/stars/stars.c
STARS2_SRC     = $(APP_DIR)/stars2/stars2.c
LINES_SRC      = $(APP_DIR)/lines/lines.c
WALK_SRC       = $(APP_DIR)/walk/walk.c
NOODLE_SRC     = $(APP_DIR)/noodle/noodle.c
APP_LIB_OBJ    = $(APP_TARGET_DIR)/applib.o
A_OBJ          = $(APP_TARGET_DIR)/a.o
HELLO_OBJ      = $(APP_TARGET_DIR)/hello.o
HELLO2_OBJ     = $(APP_TARGET_DIR)/hello2.o
HELLO3_OBJ     = $(APP_TARGET_DIR)/hello3.o
HELLO4_OBJ     = $(APP_TARGET_DIR)/hello4.o
HELLO5_OBJ     = $(APP_TARGET_DIR)/hello5.o
WIN_HELLO_OBJ  = $(APP_TARGET_DIR)/winhelo.o
WIN_HELLO2_OBJ = $(APP_TARGET_DIR)/winhelo2.o
WIN_HELLO3_OBJ = $(APP_TARGET_DIR)/winhelo3.o
STAR1_OBJ      = $(APP_TARGET_DIR)/star1.o
STARS_OBJ      = $(APP_TARGET_DIR)/stars.o
STARS2_OBJ     = $(APP_TARGET_DIR)/stars2.o
LINES_OBJ      = $(APP_TARGET_DIR)/lines.o
WALK_OBJ       = $(APP_TARGET_DIR)/walk.o
NOODLE_OBJ     = $(APP_TARGET_DIR)/noodle.o
A_APP          = $(APP_TARGET_DIR)/a.hrb
HELLO_APP      = $(APP_TARGET_DIR)/hello.hrb
HELLO2_APP     = $(APP_TARGET_DIR)/hello2.hrb
HELLO3_APP     = $(APP_TARGET_DIR)/hello3.hrb
HELLO4_APP     = $(APP_TARGET_DIR)/hello4.hrb
HELLO5_APP     = $(APP_TARGET_DIR)/hello5.hrb
WIN_HELLO_APP  = $(APP_TARGET_DIR)/winhelo.hrb
WIN_HELLO2_APP = $(APP_TARGET_DIR)/winhelo2.hrb
WIN_HELLO3_APP = $(APP_TARGET_DIR)/winhelo3.hrb
STAR1_APP      = $(APP_TARGET_DIR)/star1.hrb
STARS_APP      = $(APP_TARGET_DIR)/stars.hrb
STARS2_APP     = $(APP_TARGET_DIR)/stars2.hrb
LINES_APP      = $(APP_TARGET_DIR)/lines.hrb
WALK_APP       = $(APP_TARGET_DIR)/walk.hrb
NOODLE_APP     = $(APP_TARGET_DIR)/noodle.hrb
APPS           = $(A_APP)
APPS          += $(HELLO_APP)
APPS          += $(HELLO2_APP)
APPS          += $(HELLO3_APP)
APPS          += $(HELLO4_APP)
APPS          += $(HELLO5_APP)
APPS          += $(WIN_HELLO_APP)
APPS          += $(WIN_HELLO2_APP)
APPS          += $(WIN_HELLO3_APP)
APPS          += $(STAR1_APP)
APPS          += $(STARS_APP)
APPS          += $(STARS2_APP)
APPS          += $(LINES_APP)
APPS          += $(WALK_APP)
APPS          += $(NOODLE_APP)

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

$(TARGET_DIR)/%.o: $(LIB_DIR)/%.c
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

## ===== [Start] Application ===== ##

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
$(HELLO_OBJ): $(HELLO5_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) -c -nostdlib -m32 $< -o $@

$(HELLO_APP): $(HELLO_OBJ) $(APP_LIB_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(OBJCOPY) -O binary $< $@
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

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

### Hello4 App
$(HELLO4_OBJ): $(HELLO4_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(HELLO4_APP): $(APP_LIB_OBJ) $(HELLO4_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Hello5 App
$(HELLO5_OBJ): $(HELLO5_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) -c -nostdlib -m32 $< -o $@

$(HELLO5_APP): $(HELLO5_OBJ) $(APP_LIB_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(OBJCOPY) -O binary $< $@
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Win hello App
$(WIN_HELLO_OBJ): $(WIN_HELLO_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(WIN_HELLO_APP): $(APP_LIB_OBJ) $(WIN_HELLO_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Win hello 2 App
$(WIN_HELLO2_OBJ): $(WIN_HELLO2_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(WIN_HELLO2_APP): $(APP_LIB_OBJ) $(WIN_HELLO2_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Win hello 3 App
$(WIN_HELLO3_OBJ): $(WIN_HELLO3_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(WIN_HELLO3_APP): $(APP_LIB_OBJ) $(WIN_HELLO3_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Star 3 App
$(STAR1_OBJ): $(STAR1_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(STAR1_APP): $(APP_LIB_OBJ) $(STAR1_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Stars App
$(STARS_OBJ): $(STARS_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(STARS_APP): $(APP_LIB_OBJ) $(STARS_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Stars2 App
$(STARS2_OBJ): $(STARS2_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(STARS2_APP): $(APP_LIB_OBJ) $(STARS2_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Lines App
$(LINES_OBJ): $(LINES_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(LINES_APP): $(APP_LIB_OBJ) $(LINES_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Walk App
$(WALK_OBJ): $(WALK_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(WALK_APP): $(APP_LIB_OBJ) $(WALK_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

### Noodle App
$(NOODLE_OBJ): $(NOODLE_SRC)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(GCC) $(CFLAGS) -c $< -o $@

$(NOODLE_APP): $(APP_LIB_OBJ) $(NOODLE_OBJ) $(MY_CLIB_OBJ)
	$(MKDIR) -p $(APP_TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ $(APP_FLAGS) -T $(APP_LNK) $^

## ===== [End] Application ===== ##

$(BOOTPACK_BIN): $(C_OBJS) $(ASMFUNC_OBJ) $(FONT_BIN) $(MY_CLIB_OBJ)
	$(MKDIR) -p $(TARGET_DIR)
	$(LD) $(LFLAGS) -o $@ -T $(BOOTPACK_LNK) $(OS_FLAGS) -Map=$(TARGET_MAP) $^

$(TARGET_SYS): $(ASMHEAD_BIN) $(BOOTPACK_BIN)
	$(CAT) $^ > $@

$(TARGET_IMG): $(IPL_BIN) $(TARGET_SYS) $(APPS)
    # Create image, place IPL in boot sector
	$(MFORMAT) -f 1440 -B $(IPL_BIN) -C -i $@ ::
    # Copy OS program to image
	$(MCOPY) $(TARGET_SYS) -i $@ ::
    # Import App
	$(MCOPY) $(A_APP)          -i $(TARGET_IMG) ::
	$(MCOPY) $(HELLO_APP)      -i $(TARGET_IMG) ::
	$(MCOPY) $(HELLO2_APP)     -i $(TARGET_IMG) ::
	$(MCOPY) $(HELLO3_APP)     -i $(TARGET_IMG) ::
	$(MCOPY) $(HELLO4_APP)     -i $(TARGET_IMG) ::
	$(MCOPY) $(HELLO5_APP)     -i $(TARGET_IMG) ::
	$(MCOPY) $(WIN_HELLO_APP)  -i $(TARGET_IMG) ::
	$(MCOPY) $(WIN_HELLO2_APP) -i $(TARGET_IMG) ::
	$(MCOPY) $(WIN_HELLO3_APP) -i $(TARGET_IMG) ::
	$(MCOPY) $(STAR1_APP)      -i $(TARGET_IMG) ::
	$(MCOPY) $(STARS_APP)      -i $(TARGET_IMG) ::
	$(MCOPY) $(STARS2_APP)     -i $(TARGET_IMG) ::
	$(MCOPY) $(LINES_APP)      -i $(TARGET_IMG) ::
	$(MCOPY) $(WALK_APP)       -i $(TARGET_IMG) ::
	$(MCOPY) $(NOODLE_APP)     -i $(TARGET_IMG) ::

qemu:
	$(QEMU) -m 32 -fda $(TARGET_IMG)

clean:
	rm -rf $(TARGET_DIR) $(APP_TARGET_DIR)
