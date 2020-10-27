#include "mcomp.h"
#include <iostream>
#include <vector>
#include "ch8excepts.h"

#define PROGNAME "ch8vm"

void use() {
    std::cout << PROGNAME << " " << "[options] [filename]\n";
    std::cout << "\"" << PROGNAME << " --help\" for help\n";
}

void help() {
    std::cout << PROGNAME << " " << "[options] [filename]\n";
    std::cout << PROGNAME << " is a CHIP-8 interpreter and processor emulator.\n";
    std::cout << "It provides a virtual machine environment to run CHIP-8 programs.\n";
    std::cout << "Available options:\n";
    std::cout << "\t-E or --ETI660: Input program is for the ETI 660 computer\n";
    std::cout << "\t-a or --text: Run in ASCII graphics mode for debugging (deprecated, default SFML graphics)\n";
    std::cout << "\t-v or --verbose: Enable verbosity mode\n";
    std::cout << "\t-h or --help: Print this message\n";
    std::cout << "Learn more here: https://github.com/s7kala/chip8\n";
}

int main(int argc, char** argv) {
    int rc = 0;
    bool graphics = true;
    if(argc < 2) {
        use();
        rc = 1;
    } else {
        std::string file = argv[argc - 1];
        if(file[0] == '-') {
            if(file == "--help") help();
            else use();
            return rc;
        }
        for(int i = 1; i < argc - 1; ++i) {
            std::string option(argv[i]);
            if(option == "-E" || option == "--ETI660") {
#define ETI660
            } else if(option == "-a" || option == "--text") {
                graphics = false;
            } else if(option == "-v" || option == "--verbose") {

            } else if (option == "-h" || option == "--help") {
                help();
                break;
            } else {
                    std::cerr << "Unrecognized command-line option: " << option << std::endl;
            }
        }
        // TO-DO impl options
        try {
            Mcomp emulator(graphics);
#ifdef DEBUG
            std::cout << "============= DEBUG MODE =============\n";
            std::cout << "WARNING! Debug mode is a lot slower and uses more memory than normal mode!\n";
            std::cout << "Press enter to step through the program.\n";
            std::cout << "======================================\n";
            // step through each instance of fetch-execute cycle
            char ch;
            emulator.boot(file);
            while(emulator.emulate(file) && std::cin.get(ch));
#else
            emulator.run(file);
#endif
        } catch (ProcessorException& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        } catch (DisplayException& e) {
            std::cerr << e.what() << std::endl;
            return 0;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return rc;
}
