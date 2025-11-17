#pragma once

#include <queue>
#include <string>
#include <mutex>


class CommandHandler {
public:
    void push(const std::string& cmd);
    bool hasPending();
    std::string pop();
private:
    std::queue<std::string> q_;
    std::mutex m_;
};
