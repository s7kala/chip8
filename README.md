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
### Keyboard Layout:
<pre>
  Keypad                   Keyboard
  +-+-+-+-+                +-+-+-+-+
  |1|2|3|C|                |1|2|3|4|
  +-+-+-+-+                +-+-+-+-+
  |4|5|6|D|                |Q|W|E|R|
  +-+-+-+-+       =>       +-+-+-+-+
  |7|8|9|E|                |A|S|D|F|
  +-+-+-+-+                +-+-+-+-+
  |A|0|B|F|                |Z|X|C|V|
  +-+-+-+-+                +-+-+-+-+
</pre>
### Test ROMs
##### Airplane.ch8
![alt text](https://github.com/s7kala/chip8/blob/master/docs/airplane.png?raw=true)
Blitz type bomber game. Press 'S' ('8' on the CHIP-8 keypad) to drop a bomb.
There are 5 levels and 4 lives; the objective is to drop a bomb without hitting another plane.
## CHIP-8 Assembler and Disassembler
```bash
cd ${CH8_ROOT}/asm
make
./ch8asm --help
```
