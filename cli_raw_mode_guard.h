#pragma once
#include <termios.h>


class CliAutoComplete;
class CommandHistory;

class RawModeGuard {
public:
    RawModeGuard(); 

    ~RawModeGuard();

    RawModeGuard(const RawModeGuard&) = delete;
    RawModeGuard& operator=(const RawModeGuard&) = delete;

private:
    struct termios orig_{};
    struct termios raw_{};
};

