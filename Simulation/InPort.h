#ifndef INPORT_H
#define INPOTR_H

#include <atomic>
#include <iostream>
#include <memory>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class InPort {
public:
  std::atomic<double> y_;
  std::atomic<double> z_;
  std::atomic<double> u_;

  void operator()(int argc, char *argv[]); // TCP/IP Routine goes here

  static void threadCall(std::shared_ptr<InPort> inPortObject, int argc,
                         char *argv[]) {
    (*inPortObject)(argc, argv);
  }

  ~InPort(){ //close connection
    if(sockfd_)
      close(sockfd_);
  }

private:
  int sockfd_;

};

#endif // INPORT