TARGET         = helloos
IPL            = ipl
OS             = haribote
IPL_SRC        = $(IPL).S
OS_SRC         = $(OS).S
IPL_LINKER_SCR = $(IPL).ld
OS_LINKER_SCR  = $(OS).ld
IPL_LINKER_OPT = -nostdlib -T $(IPL_LINKER_SCR)
OS_LINKER_OPT  = -nostdlib -T $(OS_LINKER_SCR)
TARGET_IPL     = $(IPL).bin
TARGET_OS      = $(OS).sys
TARGET_IMG     = $(TARGET).img
GCC            = gcc
# Install Qemu
QEMU           = qemu-system-x86_64
# Install mtools
MFORMAT        = mformat
MCOPY          = mcopy

all:
	$(GCC) $(IPL_LINKER_OPT) $(IPL_SRC) -o $(TARGET_IPL)
	$(GCC) $(OS_LINKER_OPT) $(OS_SRC) -o $(TARGET_OS)
    # Create image, place IPL in boot sector
	$(MFORMAT) -f 1440 -B $(TARGET_IPL) -C -i $(TARGET_IMG) ::
    # Copy OS program to image
	$(MCOPY) $(TARGET_OS) -i $(TARGET_IMG) ::

qemu:
	$(QEMU) -fda $(TARGET_IMG)

clean:
	rm $(TARGET_IMG) $(TARGET_IPL) $(TARGET_OS)
