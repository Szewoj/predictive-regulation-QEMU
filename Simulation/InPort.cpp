#include "InPort.h"

void InPort::operator()() { // TODO TCP/IP communication
  double buf;
  for (;;) {
    std::cin >> buf;
    std::cout << "Received: " << buf << '\n';

    u_ = buf;
  }
}