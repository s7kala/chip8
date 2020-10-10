# chip8
A CHIP-8 interpreter and processor emulator

```bash
CH8_ROOT=$(pwd)
```

## A VM environment to run CHIP-8 programs
```bash
cd ${CH8_ROOT}/src
```
Build with CMake:
```bash
sudo apt-get install cmake  (Ubuntu/Debian)
cmake .
make
./ch8vm --help
```
## CHIP-8 Assembler and Disassembler
```bash
cd ${CH8_ROOT}/asm
make
./ch8asm --help
```
