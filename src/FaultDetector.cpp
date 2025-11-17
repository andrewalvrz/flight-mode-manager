#include "FaultDetector.h"
#include <cstdlib>
FaultDetector::FaultDetector(): st_(), counter_(0) {}
void FaultDetector::sample() {
// Simulated sampling logic for demo purposes.
++counter_;
// Introduce a temporary IMU fault occasionally
st_.imuFault = (rand() % 200) == 0; // rare
st_.gpsFault = (rand() % 500) == 0;
// simulated thermal rises for demo
st_.thermalFault = (counter_ % 1000) == 0;
// simulated power fault
st_.powerFault = (rand() % 1000) == 0;
}
bool FaultDetector::hasFault() const {
return st_.imuFault || st_.gpsFault || st_.thermalFault || st_.powerFault;
}
bool FaultDetector::hasCriticalFault() const {
// For demo: power fault is critical
return st_.powerFault;
}
