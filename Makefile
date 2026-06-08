boot.bin : src/boot.asm
	nasm -f bin src/boot.asm -o build/boot.bin
kernel.o : src/kernel.c
	i386-elf-gcc -Isrc/include -ffreestanding -O0 -nostdlib -m32 -g -c "src/kernel.c" -o "build/kernel.o"
kernel_entry.o : src/kernel_entry.asm
	nasm "src/kernel_entry.asm" -f elf32 -o "build/kernel_entry.o"
idt.o : src/drivers/interrupt/idt.asm
	nasm "src/drivers/interrupt/idt.asm" -f elf32 -o "build/idt.o"
interrupt.o : src/drivers/interrupt/interrupt.c
	i386-elf-gcc -Isrc/include -ffreestanding -O0 -nostdlib -m32 -g -c "src/drivers/interrupt/interrupt.c" -o "build/interrupt.o"
pic8259.o : src/drivers/pic8259/pic8259.c
	i386-elf-gcc -Isrc/include -ffreestanding -O0 -nostdlib -m32 -g -c "src/drivers/pic8259/pic8259.c" -o "build/pic8259.o"
inlineasm.o : src/inlineasm.c
	i386-elf-gcc -Isrc/include -ffreestanding -O0 -nostdlib -m32 -g -c "src/inlineasm.c" -o "build/inlineasm.o"
vga.o : src/drivers/video/vga.c
	i386-elf-gcc -Isrc/include -ffreestanding -O0 -nostdlib -m32 -g -c "src/drivers/video/vga.c" -o "build/vga.o"
full_kernel.elf : kernel.o kernel_entry.o vga.o interrupt.o idt.o pic8259.o
	i386-elf-ld -o "build/full_kernel.elf" -T src/linker.ld "build/kernel_entry.o" "build/kernel.o" "build/vga.o" "build/idt.o" "build/interrupt.o"
full_kernel.bin : kernel.o kernel_entry.o vga.o idt.o interrupt.o pic8259.o
	i386-elf-ld -o "build/full_kernel.bin" -T src/linker.ld "build/kernel_entry.o" "build/kernel.o" "build/vga.o" "build/idt.o" "build/interrupt.o" "build/pic8259.o" --oformat binary
OS.bin : boot.bin full_kernel.bin
	cat "build/boot.bin" "build/full_kernel.bin" > "build/OS.bin"
extend : OS.bin
	truncate -s 10240 build/OS.bin
run : extend
	qemu-system-x86_64 -drive format=raw,file="build/OS.bin"

elf : full_kernel.elf
all : run

clear:
	rm -rf build/*.bin build/*.o build/*.elf