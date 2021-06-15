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

#define CODE_ACK 1
#define CODE_ERR 2
#define CODE_GET 3
#define CODE_GETALL 4
#define CODE_SET 5
#define CODE_SETALL 6


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