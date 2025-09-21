#pragma once

#include "CLI.h"

static inline bool isPrintable(unsigned char c) {
    return c >= 0x20 && c <= 0x7E;
}


class CLIImpl : public CLI{
    
    public:
    CLIImpl() = default;
    ~CLIImpl() noexcept = default;
    CLIImpl(const CLIImpl&) = delete;
    CLIImpl& operator=(const CLIImpl&) = delete;
    CLIImpl(CLIImpl&&) = default;
    CLIImpl& operator=(CLIImpl&&) = default;
    virtual void startCLI() override;
    
    private:
    
    
};



void loopFunction();
