# chip8
A CHIP-8 interpreter and processor emulator

#### CH8_ROOT=$(pwd)

## A VM environment to run CHIP-8 programs
cd ${CH8_ROOT}/src
Build with CMake:
sudo apt-get install cmake  (Ubuntu/Debian)
cmake .
make
./ch8vm

## CHIP-8 Assembler and Disassembler
cd ${CH8_ROOT}/asm
make
./ch8asm --help
