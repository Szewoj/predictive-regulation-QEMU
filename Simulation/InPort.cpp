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
  bzero(buffer, 256);
  //---

  //--- PROCESS MESSAGES
  for(;;){
    
    /* czytanie i pisanie:
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
      error("ERROR writing to socket");
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
      error("ERROR reading from socket");
    printf("%s\n", buffer);
     */
  }
  //---
}
