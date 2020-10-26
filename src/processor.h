#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "memory.h"
#include "subject.h"
#include "keyboard.h"
#include <vector>
#include <stack>
#include <cstdint>
#include <random>

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#define GPR_NO 16
/*
 * Add later (for now, call stack is environment-dependent)
#define STACK_SIZE 16
*/

class Processor : public Subject {
    public:
        explicit Processor(Memory* pMem, Keyboard* kb);
        /*
         * Init proc (push retAddr to callStack)
         */
        void init(uint16_t retAddr);
        /*
         * Set PC to addr
         */
        void jump(uint16_t addr);
        /*
         * Fetch and execute opcodes
         * Returns true for a successful run of the emulation cycle,
         * false otherwise
         */
        bool run();
        Info getInfo() const override;
        ~Processor() noexcept override;
    private:
        std::vector<uint8_t> registers;
        uint8_t delay;
        uint8_t sound;
        sf::Time delayTimer;
        sf::Time soundTimer;
        sf::Clock clock;
        sf::SoundBuffer src;
        sf::Sound beep;
        uint16_t I;
        uint16_t PC;
        std::stack<uint16_t> callStack;
        Memory* pMem;
        Keyboard* pkb;
        std::random_device dev;
        std::mt19937 engine;
        std::uniform_int_distribution<uint8_t> dist;
        Info displayInstruction;
        void executeInstruction(uint16_t opcode);
        bool compareVxkk(uint16_t opcode);
        bool compareVxVy(uint16_t opcode);
        template<typename T>
        void setVxVy(int Vx, int Vy, T op);
};

#endif
