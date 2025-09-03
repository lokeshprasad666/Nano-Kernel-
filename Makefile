# Nano Kernel Build System
ASM = nasm
CC = i686-elf-gcc
BOOTSTRAP_FILE = bootstrap.asm 
INIT_KERNEL_FILES = starter.asm
KERNEL_FILES = main.c
KERNEL_FLAGS = -Wall -c -ffreestanding -fno-asynchronous-unwind-tables -fno-pie -fcommon -DNANO_VERSION="1.0"
KERNEL_OBJECT = -o kernel.elf

build: $(BOOTSTRAP_FILE) $(KERNEL_FILE)
	@echo "Building Nano Kernel..."
	$(ASM) -f bin $(BOOTSTRAP_FILE) -o bootstrap.o
	$(ASM) -f elf32 $(INIT_KERNEL_FILES) -o starter.o 
	$(CC) $(KERNEL_FLAGS) $(KERNEL_FILES) $(KERNEL_OBJECT)
	$(CC) $(KERNEL_FLAGS) screen.c -o screen.elf
	$(CC) $(KERNEL_FLAGS) process.c -o process.elf
	$(CC) $(KERNEL_FLAGS) scheduler.c -o scheduler.elf
	@echo "Linking kernel components..."
	i686-elf-ld -Tlinker.ld starter.o kernel.elf screen.elf process.elf scheduler.elf -o nano_kernel.elf
	i686-elf-objcopy -O binary nano_kernel.elf nano_kernel.bin
	@echo "Creating bootable image..."
	dd if=bootstrap.o of=kernel.img
	dd seek=1 conv=sync if=nano_kernel.bin of=kernel.img bs=512 count=8
	dd seek=9 conv=sync if=/dev/zero of=kernel.img bs=512 count=2046
	@echo "Starting QEMU emulator..."
	qemu-system-x86_64 -s kernel.img

clean:
	rm -rf *.o
	rm -rf *.bin
	rm -rf *.img
	rm -rf *.elf
