// raw_mode_linux.cpp
// Compile: g++ -std=c++17 -O2 -Wall raw_mode_linux.cpp -o raw_mode
// Run:     ./raw_mode


#include "cliimp.h"
#include <string>
#include <exception>
#include <iostream>
#include <memory>

int main() {
    try {
            //std::unique_ptr<CLI> cli = std::make_unique<CLIImpl>();
            CLIImpl cli{};
            cli.startCLI();
            return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
