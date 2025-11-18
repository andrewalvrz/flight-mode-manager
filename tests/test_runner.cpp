#include <cassert>
#include <iostream>
#include "Watchdog.h"
#include "FaultDetector.h"
int main() {
// Watchdog basic
Watchdog wd(100);
wd.kick();
assert(!wd.expired());
// Fault detector sampling
FaultDetector fd;
fd.sample();
// after sample, hasFault() is either true or false, just ensure it compiles
//and runs
bool hf = fd.hasFault();
std::cout << "FaultDetector.hasFault() = " << hf << "\n";
std::cout << "All tests passed.\n";
return 0;
}