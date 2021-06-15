#include "InPort.h"

void InPort::operator()(int argc, char *argv[]) {
  //---INITIALIZE COMMUNICATION
  int portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];
  if (argc < 3) {
    std::cerr << "Error: usage " << argv[0] << " hostname port\n" << std::endl;
    return;
  }
  portno = atoi(argv[2]);
  sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd_ < 0){
    std::cerr << "ERROR opening socket " << strerror(errno) << std::endl;
    return;
  }
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    std::cerr << "ERROR, no such host\n" << std::endl;
    return;
  }
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd_, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
    std::cerr << "ERROR connecting " << strerror(errno) << std::endl;
    return;
  }
  
  std::cout << "Connected to Regulator";
  //---

  //--- PROCESS MESSAGES
  for(;;){
    bzero(buffer, 256);
    n = read(sockfd_, buffer, 255);
    if (n < 0){
      std::cerr << "ERROR reading from socket!" << std::endl;
    }

    if (n == 0)
      continue;

    uint8_t action = buffer[0];

    switch(action){
      case CODE_ACK:
        continue;
        break;

      case CODE_ERR:
        std::cerr << "ERROR Received communication error code!" << std::endl;
        return;
        break;

      case CODE_GETALL:
        bzero(buffer, 256);
        buffer[0] = CODE_ACK;
        buffer[1] = 16;
        memcpy(buffer+2, &y_, sizeof(double));
        memcpy(buffer+2+sizeof(double), &z_, sizeof(double));
        n = write(sockfd_, buffer, 18);
        if (n < 0)
          std::cerr << "ERROR writing to socket!" << std::endl;
        break;

      case CODE_SET:
        if(buffer[1] == 8){
          double tmp;
          memcpy(&tmp, buffer+2, sizeof(double));
          u_ = tmp;
        }
        break;

      default:
        break;

    }

  }
  //---
}
