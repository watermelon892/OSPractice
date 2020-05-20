TARGET   = helloos
IPL      = ipl10
ASMHEAD  = asmhead
BOOTPACK = bootpack
ASMFUNC  = asmfunc

IPL_SRC      = $(IPL).S
ASMHEAD_SRC  = $(ASMHEAD).S
BOOTPACK_SRC = $(BOOTPACK).c
ASMFUNC_SRC  = $(ASMFUNC).S

IPL_LINKER      = $(IPL).ld
ASMHEAD_LINKER  = $(ASMHEAD).ld
BOOTPACK_LINKER = $(BOOTPACK).ld

IPL_LINKER_OPT      = -nostdlib -T $(IPL_LINKER)
ASMHEAD_LINKER_OPT  = -nostdlib -T $(ASMHEAD_LINKER)
BOOTPACK_LINKER_OPT = -T $(BOOTPACK_LINKER)
LD_OPT              = -m elf_i386

BOOTPACK_OBJ = $(BOOTPACK).o
ASMFUNC_OBJ  = $(ASMFUNC).o
OBJ_LINK_OPT = --oformat=binary -shared $(BOOTPACK_OBJ) $(ASMFUNC_OBJ)

TARGET_IPL       = $(IPL).bin
TARGET_ASMHEAD   = $(ASMHEAD).bin
TARGET_BOOTPACK  = $(BOOTPACK).bin
TARGET_SYS       = $(TARGET).sys
TARGET_IMG       = $(TARGET).img

MKDIR          = mkdir
GCC            = gcc
LD             = ld
CAT            = cat
# Install Qemu
QEMU           = qemu-system-x86_64
# Install mtools
MFORMAT        = mformat
MCOPY          = mcopy

all:
	$(GCC) $(IPL_LINKER_OPT) -o $(TARGET_IPL) $(IPL_SRC)
	$(GCC) $(ASMHEAD_LINKER_OPT) -o $(TARGET_ASMHEAD) $(ASMHEAD_SRC)
	$(GCC) -m32 -c -o $(ASMFUNC_OBJ) $(ASMFUNC_SRC)
	$(GCC) -fno-pie -nostdlib -m32 -c -o $(BOOTPACK_OBJ) $(BOOTPACK_SRC)
	$(LD) $(LD_OPT) -o $(TARGET_BOOTPACK) $(BOOTPACK_LINKER_OPT) $(OBJ_LINK_OPT)
	$(CAT) $(TARGET_ASMHEAD) $(TARGET_ASMHEAD) > $(TARGET_SYS)
    # Create image, place IPL in boot sector
	$(MFORMAT) -f 1440 -B $(TARGET_IPL) -C -i $(TARGET_IMG) ::
    # Copy OS program to image
	$(MCOPY) $(TARGET_SYS) -i $(TARGET_IMG) ::

qemu:
	$(QEMU) -fda $(TARGET_IMG)

clean:
	rm $(TARGET_IPL) $(TARGET_ASMHEAD) $(TARGET_BOOTPACK) $(TARGET_SYS) $(TARGET_IMG) $(BOOTPACK_OBJ) $(ASMFUNC_OBJ)
