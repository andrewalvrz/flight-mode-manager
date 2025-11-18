#include "CommandHandler.h"
void CommandHandler::push(const std::string& cmd) {
    std::lock_guard<std::mutex> lk(m_);
    q_.push(cmd);
}


bool CommandHandler::hasPending() {
    std::lock_guard<std::mutex> lk(m_);
    return !q_.empty();
}


std::string CommandHandler::pop() {
    std::lock_guard<std::mutex> lk(m_);
    if (q_.empty()) return std::string();
    std::string c = q_.front(); q_.pop();
    return c;
}
