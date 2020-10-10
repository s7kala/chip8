/*
 * CHIP-8 Assembler/Disassembler
 * $PROJECT_ROOT/asm/main.cc
 */

#include "asm.h"
#include "dasm.h"
#include "excepts.h"
#include <iostream>
#include <fstream>
#include <sstream>

void use(const char*);
void help(const char*);

int main(int argc, char** argv) {
    int rc = 0;
    bool assemble = true;
    bool verbose = false;
    if(argc < 2) {
        use(argv[0]);
        rc = 1;
    } else {
        std::string file = argv[argc - 1];
        if(file[0] == '-') {
            if(file == "--help") help(argv[0]);
            else use(argv[0]);
            return rc;
        }
        for(int i = 1; i < argc - 1; ++i) {
            std::string option(argv[i]);
            if(option == "-d" || option == "--disassemble") {
                assemble = false;
            } else if(option == "-v" || option == "--verbose") {
                verbose = true;
            } else if (option == "-h" || option == "--help") {
                help(argv[0]);
                break;
            } else {
                std::cerr << "Unrecognized command-line option: " << option << std::endl;
            }
        }
        try {
            std::stringstream ss;
            if(assemble) {
                Assembler asmb(verbose);
                asmb.assemble(file, ss);
            }
            else {
                Disassembler dasm(verbose);
                dasm.disassemble(file, ss);
            }
            std::string word;
            while(getline(ss, word)) {
                std::cout << word << std::endl;
            }
        } catch (AsmException& e) {
            if(e.isAsm())
                std::cerr << "Assembler Exception: ";
            else std::cerr << "Disassembler Exception: ";
            std::cerr << e.what() << std::endl;
            return 1;  
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return rc;
}

void use(const char* progname) {
    std::cout << progname << " " << "[options] [filename]\n";
    std::cout << "\"" << progname << " --help\" for help\n";
}

void help(const char* progname) {
    std::cout << progname << " is a CHIP-8 Assembler/Disassembler\n";
    std::cout << "To assemble a CHIP-8 Assembly file, simply run:\n";
    std::cout << "\t" << progname << " [filename]\n";
    std::cout << "Available options:\n";
    std::cout << "\t-d or --disassemble: disassemble a CHIP-8 binary\n";
    std::cout << "\t-v or --verbose: Enable verbosity mode\n";
    std::cout << "\t-h or --help: to see this message\n";
    std::cout << "Learn more here: https://github.com/s7kala/chip8\n";
}
