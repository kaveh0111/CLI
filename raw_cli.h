#include <iostream>
#include <stdexcept>
#include <termios.h>
#include <unistd.h>
#include <csignal>
#include <cerrno>
#include <cstring>
#include <string>


class CliAutoComplete;
class CommandHistory;

class RawModeGuard {
public:
    RawModeGuard() {
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

    ~RawModeGuard() {
        tcsetattr(STDIN_FILENO, TCSANOW, &orig_);
    }

    RawModeGuard(const RawModeGuard&) = delete;
    RawModeGuard& operator=(const RawModeGuard&) = delete;

private:
    struct termios orig_{};
    struct termios raw_{};
};

static inline bool isPrintable(unsigned char c) {
    return c >= 0x20 && c <= 0x7E;
}
