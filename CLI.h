#pragma once

class CLI{
    
    public:
    CLI() = default;
    virtual ~CLI() noexcept = default;
    CLI(CLI&) = delete;
    CLI& operator==(CLI&) = delete;
    virtual void startCLI() = 0;
};
