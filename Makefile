# Tools
CC      := i386-elf-gcc
LD      := i386-elf-ld
ASM     := nasm

# Compiler and Linker Flags
CFLAGS  := -Isrc/include -ffreestanding -O0 -nostdlib -m32 -g
ASMFLAGS:= -f elf32
LDFLAGS := -T src/linker.ld

# Directories
SRC_DIR   := src
BUILD_DIR := build

# Automatic File Detection
BOOT_SRC   := $(SRC_DIR)/boot.asm
BOOT_BIN   := $(BUILD_DIR)/boot.bin

# Dynamically find all source files
KERNEL_C_SRCS   := $(shell find $(SRC_DIR) -name "*.c")
KERNEL_ASM_SRCS := $(shell find $(SRC_DIR) -name "*.asm" ! -name "boot.asm" ! -name "kernel_entry.asm")

# Robustly convert paths
KERNEL_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(KERNEL_C_SRCS)) \
               $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(KERNEL_ASM_SRCS))

# Explicit Entry Point Handling (maintain execution order)
ENTRY_SRC   := $(SRC_DIR)/kernel_entry.asm
ENTRY_OBJ   := $(BUILD_DIR)/kernel_entry.o

# Target Outputs
KERNEL_ELF := $(BUILD_DIR)/full_kernel.elf
KERNEL_BIN := $(BUILD_DIR)/full_kernel.bin
OS_BIN     := $(BUILD_DIR)/OS.bin

# Build Rules
.PHONY: all run elf clear

all: run

# Pattern Rule for C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern Rule for Assembly files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

# Rule for the Bootloader binary
$(BOOT_BIN): $(BOOT_SRC)
	@mkdir -p $(dir $@)
	$(ASM) -f bin $< -o $@

# Link the Kernel into a raw Binary (CRITICAL: ENTRY_OBJ must be first!)
$(KERNEL_BIN): $(ENTRY_OBJ) $(KERNEL_OBJS)
	$(LD) -o $@ $(LDFLAGS) $(ENTRY_OBJ) $(KERNEL_OBJS) --oformat binary

# Link the Kernel into an ELF for debugging
$(KERNEL_ELF): $(ENTRY_OBJ) $(KERNEL_OBJS)
	$(LD) -o $@ $(LDFLAGS) $(ENTRY_OBJ) $(KERNEL_OBJS)

# Stitch the OS Image together and pad it
$(OS_BIN): $(BOOT_BIN) $(KERNEL_BIN)
	cat $^ > $@
	truncate -s 10240 $@

# Utility Targets
elf: $(KERNEL_ELF)

run: $(OS_BIN)
	qemu-system-x86_64 -drive format=raw,file=$<

clear:
	rm -rf $(BUILD_DIR)