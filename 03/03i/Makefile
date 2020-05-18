TARGET   = helloos
IPL      = ipl10
ASMHEAD  = asmhead
BOOTPACK = bootpack

IPL_SRC      = $(IPL).S
ASMHEAD_SRC  = $(ASMHEAD).S
BOOTPACK_SRC = $(BOOTPACK).c

IPL_LINKER      = $(IPL).ld
ASMHEAD_LINKER  = $(ASMHEAD).ld
BOOTPACK_LINKER = $(BOOTPACK).ld

IPL_LINKER_OPT      = -nostdlib -T $(IPL_LINKER)
ASMHEAD_LINKER_OPT  = -nostdlib -T $(ASMHEAD_LINKER)
BOOTPACK_LINKER_OPT = -fno-pie -nostdlib -m32 -T $(BOOTPACK_LINKER)

TARGET_IPL       = $(IPL).bin
TARGET_ASMHEAD   = $(ASMHEAD).bin
TARGET_BOOTPACK  = $(BOOTPACK).bin
TARGET_SYS       = $(TARGET).sys
TARGET_IMG       = $(TARGET).img

GCC            = gcc
CAT            = cat
# Install Qemu
QEMU           = qemu-system-x86_64
# Install mtools
MFORMAT        = mformat
MCOPY          = mcopy

all:
	$(GCC) $(IPL_LINKER_OPT) -o $(TARGET_IPL) $(IPL_SRC)
	$(GCC) $(ASMHEAD_LINKER_OPT) -o $(TARGET_ASMHEAD) $(ASMHEAD_SRC)
	$(GCC) $(BOOTPACK_SRC) $(BOOTPACK_LINKER_OPT) -o $(TARGET_BOOTPACK)
	$(CAT) $(TARGET_ASMHEAD) $(TARGET_ASMHEAD) > $(TARGET_SYS)
    # Create image, place IPL in boot sector
	$(MFORMAT) -f 1440 -B $(TARGET_IPL) -C -i $(TARGET_IMG) ::
    # Copy OS program to image
	$(MCOPY) $(TARGET_SYS) -i $(TARGET_IMG) ::

qemu:
	$(QEMU) -fda $(TARGET_IMG)

clean:
	rm $(TARGET_IPL) $(TARGET_ASMHEAD) $(TARGET_BOOTPACK) $(TARGET_SYS) $(TARGET_IMG)
