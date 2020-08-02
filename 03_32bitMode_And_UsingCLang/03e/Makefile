TARGET     = helloos
IPL        = ipl
OS         = haribote

IPL_SRC    = $(IPL).S
OS_SRC     = $(OS).S
LINKER_SCR = linker.ld

LINKER_OPT = -nostdlib -T $(LINKER_SCR)

TARGET_IPL = $(IPL).bin
TARGET_OS  = $(OS).sys
TARGET_IMG = $(TARGET).img

GCC        = gcc

# Install Qemu
QEMU       = qemu-system-x86_64

# Install mtools
MFORMAT    = mformat
MCOPY      = mcopy

all:
	$(GCC) $(LINKER_OPT) $(IPL_SRC) -o $(TARGET_IPL)
	$(GCC) $(LINKER_OPT) $(OS_SRC) -o $(TARGET_OS)
    # Create image, place IPL in boot sector
	$(MFORMAT) -f 1440 -B $(TARGET_IPL) -C -i $(TARGET_IMG) ::
    # Copy OS program to image
	$(MCOPY) $(TARGET_OS) -i $(TARGET_IMG) ::

qemu:
	$(QEMU) -fda $(TARGET_IMG)

clean:
	rm $(TARGET_IMG) $(TARGET_IPL) $(TARGET_OS)
