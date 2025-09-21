#include <stdexcept>
#include <iostream>
#include <csignal>
#include <cerrno>
#include <cstring>
#include <string>

#include "cli_raw_mode_guard.h"

RawModeGuard::RawModeGuard(){
        if (!isatty(STDIN_FILENO))
            throw std::runtime_error("stdin is not a TTY");

        if (tcgetattr(STDIN_FILENO, &orig_) == -1)
            throw std::runtime_error(std::string("tcgetattr failed: ") + strerror(errno));

        raw_ = orig_;
        cfmakeraw(&raw_);

        // Optional: keep Ctrl-C generating SIGINT. Comment out if you want pure raw.
        raw_.c_lflag |= ISIG;

        if (tcsetattr(STDIN_FILENO, TCSANOW, &raw_) == -1)
            throw std::runtime_error(std::string("tcsetattr failed: ") + strerror(errno));
    }
    
RawModeGuard::~RawModeGuard() {
        tcsetattr(STDIN_FILENO, TCSANOW, &orig_);
    }
    
    
