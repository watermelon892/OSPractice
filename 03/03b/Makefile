TARGET     = ipl
ASM_SRC    = $(TARGET).S
LINKER_SCR = $(TARGET).ld
TARGET_IMG = $(TARGET).img
LINKER_OPT = -nostdlib -T
GCC        = gcc
QEMU       = qemu-system-x86_64

all:
	$(GCC) $(LINKER_OPT) $(LINKER_SCR) $(ASM_SRC) -o $(TARGET_IMG)

qemu:
	$(QEMU) -fda $(TARGET_IMG)

clean:
	rm $(TARGET_IMG)
