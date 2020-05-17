TARGET     = helloos
SRC        = ipl.S
LINKER_SCR = linker.ld
LINKER_OPT = -nostdlib -T $(LINKER_SCR)
TARGET_OBJ = ipl.bin
TARGET_IMG = $(TARGET).img
GCC        = gcc
DD         = dd
QEMU       = qemu-system-x86_64

all:
	$(GCC) $(LINKER_OPT) $(SRC) -o $(TARGET_OBJ)
	$(DD) if=$(TARGET_OBJ) of=$(TARGET_IMG)

qemu:
	$(QEMU) -fda $(TARGET_IMG)

clean:
	rm $(TARGET_IMG) $(TARGET_OBJ)
