#ifndef INPORT_H
#define INPOTR_H

#include <atomic>
#include <iostream>
#include <memory>

class InPort {
public:
  std::atomic<double> y_;
  std::atomic<double> z_;
  std::atomic<double> u_;

  void operator()(); // TCP/IP Routine goes here

  static void threadCall(std::shared_ptr<InPort> inPortObject) { (*inPortObject)(); }
};

#endif // INPORT