#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sstream>
#include <vector>
#include "Parser/Parser.hpp"
#include "Store/KeyValueStore.hpp"
#include "CommandHandler/CommandFactory.hpp"


#define DEFAULT_BUFFER_DELIMITER "\r\n"
#define DEFAULT_BUFFER_SIZE 128

std::string getRawString(const std::string input) {
  std::ostringstream oss;
  for (char ch : input) {
    switch (ch) {
      case '\r':
        oss << "\\r";
        break;
      case '\n':
        oss << "\\n";
        break;
      default:
        oss << ch;
    }
  }
  return oss.str();
}

void*  commandHandler(void* arg){
  int fd = *((int*)arg);
  char buffer[DEFAULT_BUFFER_SIZE];

  bzero(&buffer,sizeof(buffer));
  int byteReceived ;
  while(1){
    memset(&buffer,'\0',sizeof(buffer));
    byteReceived = recv(fd, buffer, sizeof(buffer), 0);
    if(byteReceived==0){
      std::cout << "Info: Connection closed at the client end " << std::endl;
      break;
    }
    if(byteReceived==-1){
      std::cout << "error: Cannot read from buffer " << std::endl;
      break;
    }

    Parser parser;
    CommandFactory factory;

    std::vector<std::string> decodedCommands = parser.decode(std::string(buffer, byteReceived));
    std::cout << "****Printing decoded commands : *****" << std::endl;
    for(const auto& command_str: decodedCommands){
      std::cout << command_str << std::endl;
    }
    
    if(decodedCommands.size()<1){
      std::cout << "Invalid command to server" << std::endl;
    }

    std::cout << "*****Printing commands : *****" << std::endl;
    std::cout << "decodedCommands " << decodedCommands[0] << std::endl;
    ICommand* command = factory.getCommand(decodedCommands[0]);
    std::cout << command << std::endl;
    // send(fd, "+PONG\r\n", 7, 0);
    // continue;

    std::cout << "*****Printing response  : *****" << std::endl;
    std::vector<std::string> response = command->execute(decodedCommands);
    for(const auto& response_str: response){
      std::cout << response_str << std::endl;
    }

    std::cout << "*****Printing encodedResponse  : *****" << std::endl;
    std::string encodedResponse = parser.encode(response);
    std::cout << getRawString(encodedResponse) << std::endl;

    send(fd, encodedResponse.c_str(), encodedResponse.size(), 0);

    
  }
  return nullptr;
}

int main(int argc, char **argv) {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // You can use print statements as follows for debugging, they'll be visible when running tests.
  std::cout << "Logs from your program will appear here!\n";

  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
   std::cerr << "Failed to create server socket\n";
   return 1;
  }
  
  // // setting SO_REUSEADDR ensures that we don't run into 'Address already in use' errors
  int reuse = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
    std::cerr << "setsockopt failed\n";
    return 1;
  }
  
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(6379);
  
  if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
    std::cerr << "Failed to bind to port 6379\n";
    return 1;
  }
  
  int connection_backlog = 5;
  if (listen(server_fd, connection_backlog) != 0) {
    std::cerr << "listen failed\n";
    return 1;
  }
  
  struct sockaddr_in client_addr;
  int client_addr_len = sizeof(client_addr);
  
  std::cout << "Waiting for a client to connect...\n";
  
  int client_fd;
  while (true) {
    if ((client_fd = accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_len)) < 0) {
        std::cerr << "accept\n";
        continue;
    }

    // Creates a detached thread for each client
    pthread_t thread_id;
    int* new_sock = (int*)malloc(sizeof(int));
    *new_sock = client_fd;
    pthread_create(&thread_id, NULL, commandHandler, (void*)new_sock);
  }

  return 0;
}
