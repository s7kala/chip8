# chip8
<In progress!>
A CHIP-8 interpreter and processor emulator

Clone this repo:
```bash
git clone https://github.com/s7kala/chip8.git
cd chip8
CH8_ROOT=$(pwd)
```

## A VM environment to run CHIP-8 programs
```bash
cd ${CH8_ROOT}/src
```
You'll need to install SFML:
```bash
sudo apt-get install libsfml-dev (Ubuntu/Debian)
```
Build with CMake:
```bash
sudo apt-get install cmake  (Ubuntu/Debian)
cmake .
make
./ch8vm --help
```
Boot an image:
```bash
./ch8vm ${CH8_ROOT}/roms/Airplane.ch8
```
## CHIP-8 Assembler and Disassembler
```bash
cd ${CH8_ROOT}/asm
make
./ch8asm --help
```
