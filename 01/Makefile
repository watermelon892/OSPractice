TARGET     = helloos
ASM_SRC    = $(TARGET).S
TMP_IMG    = tmp.img
TARGET_IMG = $(TARGET).img
AS         = as
DD         = dd
QEMU       = qemu-system-x86_64

all:
	$(AS) $(ASM_SRC) -o $(TMP_IMG)
	$(DD) if=$(TMP_IMG) of=$(TARGET_IMG) skip=64 bs=1

qemu:
	$(QEMU) -fda $(TARGET_IMG)

clean:
	rm $(TMP_IMG) $(TARGET_IMG)
