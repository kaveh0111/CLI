// raw_mode_linux.cpp
// Compile: g++ -std=c++17 -O2 -Wall raw_mode_linux.cpp -o raw_mode
// Run:     ./raw_mode

#include "raw_cli.h"

//give name to each keypress so that it is easier to consider the switch case
enum class KeyPress  {};

//add arrow keys for history
// make it a class so that CliAutoComplete can be a dependency and also history class
// adding state for blocking new input
//waiting for loading background threads
//clossing

void loopFunction()
{
    std::string input_buffer{};
    while (true) {
            
            unsigned char input_char_sequence[3];
            ssize_t r = ::read(STDIN_FILENO, &input_char_sequence, 3);
            //ssize_t r = ::read(STDIN_FILENO, &ch, 1);
            
            
            if (r == 0) {
                std::cout << "\n[eof]\n";
                break;
            }
            if (r < 0) {
                //retry reading in the case of interuption
                if (errno == EINTR) continue;
                std::perror("read");
                break;
            }
             if (r == 3) {
                std::cout << "you pushed an arrow key";   
                if (input_char_sequence[0] != 0x1B && input_char_sequence[0] != 0x5B)
                {
                    std::cout << input_char_sequence[1] << "anddddddddddddddddddd" << input_char_sequence[2];
                    std::perror("invalid input");
                    break;
                }
                
             }
            const unsigned char ch = input_char_sequence[0];
            //std::cout << "I am getchar";
            
            switch(ch)
            {
            case 0x1B:
            {
                std::cout << " \n[exit]\n";
                return;
            }
            case 0x9:
            {
                std::cout << "hit autocompletion";
                break;
            }
            case 0x7F:
            {
                std::cout << "hit backspace";
            }
            case 0xA:
            {
                std::cout << "hit enter, execute the command, then erase string buffer";
                input_buffer.erase();
                break;
            }
            default:
            {
                input_buffer += ch;
                std::cout << input_buffer;
            
            /*if (ch == 0x1B) { // ESC byte
                std::cout << "\n[exit]\n";
                break;
            }
*/
            std::cout << "0x" << std::hex << std::uppercase << (int)ch << std::dec
                      << (isPrintable(ch) ? std::string(" '") + (char)ch + "'" : " (ctrl)")
                      << "\n";
            //std::cout << ch ;//static_cast<int>(ch);
            }
        }
}
}

int main() {
    try {
        std::setvbuf(stdout, nullptr, _IONBF, 0);
        RawModeGuard guard;

        std::cout << "Raw mode ON. Press ESC or Ctrl-C to exit.\n";
        std::cout << "Type anything; bytes will be shown in hex and (if printable) as chars.\n";
        
        
        loopFunction();
        std::cout << "Raw mode OFF. Bye!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
