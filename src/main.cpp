#include "FlightModeManager.h"
#include <iostream>
#include <string>
#include <thread>

int main(int argc, char** argv) {
    bool simulate = false;
    for (int i = 1; i < argc; ++i) {
        std::string a(argv[i]);
        if (a == "--simulate") simulate = true;
    }

    // seed RNG for demo faults
    std::srand((unsigned)time(nullptr));

    FlightModeManager fm;

    // Start runtime loop in a background thread
    std::thread fmthread([&fm, simulate]() {
        fm.start(simulate);
    });

    std::cout << "[MAIN] Interactive console. Type commands (NOMINAL/SAFE/DEGRADED/PAYLOAD/BOOT/SHUTDOWN/KICK). Type EXIT to stop.\n";

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        // normalize
        std::string tmp = line;
        for (auto &c : tmp) c = (char)std::toupper(c);
        if (tmp == "EXIT") {
            // request graceful shutdown
            fm.handleCommand("SHUTDOWN");
            break;
        }

        fm.handleCommand(line); // deliver user's string - FM uppercases internally
        std::cout << "[MAIN] Command delivered to FlightModeManager: " << line << "\n";
    }

    // wait for FM to finish
    if (fmthread.joinable()) fmthread.join();
    std::cout << "[MAIN] Exiting.\n";
    return 0;
}
