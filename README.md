## Run
### Install prerequisites
Ubuntu (WSL)
```
chmod +x ./setup-gcc-ubuntu-wsl.sh
./setup-gcc-ubuntu-wsl.sh
```
Then run
```
make all
```
If you want to debug with GDB and VS Code, make sure you have gdb installed and run
```
make elf
```
and start debugging session from VS Code

## TODO
  - [ ] Init IDT and PIT
  - [ ] Write PS/2 Keyboard driver
    - [ ] Fix Keyboard ISR - only prints character 'D' once and never works after
      - Check interrupt masking. Kernel keeps rebooting if IRQ's after 1 are unmasked.
      - Check PIC Slave cascade identity
  - [ ] Write ATA I/O driver
  - [ ] Write simple cyclic coop schedular and later a task switching one
  - [ ] Implement user space programs and syscall
  - [ ] Write a minimal filesystem (TarFS/RAMFS/FatFS/custom)
  - [ ] Implement ELF Parser
  - [ ] First user space application : a terminal shell
