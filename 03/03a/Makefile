TARGET          = helloos
SRC             = ipl.S
LINKER_SCR      = linker.ld
LINKER_OPT      = -nostdlib -T $(LINKER_SCR)
TARGET_OBJ      = ipl.bin
TARGET_IMG      = $(TARGET).img
TARGET_IMG_SIZE = 1474560
GCC             = gcc
DD              = dd
QEMU            = qemu-system-x86_64

all:
	$(GCC) $(LINKER_OPT) $(SRC) -o $(TARGET_OBJ)
	$(DD) if=$(TARGET_OBJ) of=$(TARGET_IMG)
	$(DD) if=/dev/zero of=$(TARGET_IMG) bs=1 count=0 seek=$(TARGET_IMG_SIZE)

qemu:
	$(QEMU) -fda $(TARGET_IMG)

clean:
	rm $(TARGET_IMG) $(TARGET_OBJ)
