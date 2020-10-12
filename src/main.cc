#include "mcomp.h"
#include <iostream>
#include <vector>
#include "ch8excepts.h"

void use(const char* progname) {
    std::cout << progname << " " << "[options] [filename]\n";
    std::cout << "\"" << progname << " --help\" for help\n";
}

void help(const char* progname) {
    std::cout << progname << " " << "[options] [filename]\n";
    std::cout << progname << " is a CHIP-8 interpreter and processor emulator.\n";
    std::cout << "It provides a virtual machine environment to run CHIP-8 programs.\n";
    std::cout << "Available options:\n";
    std::cout << "\t-E or --ETI660: Input program is for the ETI 660 computer\n";
    std::cout << "\t-g or --graphics: Run in external graphics mode (default ASCII graphics on terminal)\n";
    std::cout << "\t-v or --verbose: Enable verbosity mode\n";
    std::cout << "\t-h or --help: Print this message\n";
    std::cout << "Learn more here: https://github.com/s7kala/chip8\n";
}

int main(int argc, char** argv) {
    int rc = 0;
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
            if(option == "-E" || option == "--ETI660") {

            } else if(option == "-g" || option == "--graphics") {

            } else if(option == "-v" || option == "--verbose") {

            } else if (option == "-h" || option == "--help") {
                help(argv[0]);
                break;
            } else {
                    std::cerr << "Unrecognized command-line option: " << option << std::endl;
            }
        }
        // TO-DO impl options
        try {
            Mcomp emulator;
#ifdef DEBUG
            // step through each instance of fetch-execute cycle
            char ch;
            emulator.boot(file);
            while(emulator.emulate(file) && std::cin.get(ch)) {
            }
#else
            emulator.run(file);
#endif
        } catch (ProcessorException& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return rc;
}
