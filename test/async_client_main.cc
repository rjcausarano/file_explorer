#include "comms/communicator.h"
#include "comms/client.h"
#include <string>
#include <iostream>
#include <unistd.h>

class ClientSocketThread : public SocketThread{
  public:
  void operator()(const std::string& ip, SharedMessage& shared_message) override {
    Client client(ip.c_str());
    client.Connect();
    while(true){
      if(shared_message.hasMessage()){
        const std::string message = shared_message.getMessage();
        std::string response = client.Send(message.c_str());
        std::cout << response << std::endl;
      }
      sleep(1);
    }
  }
};

int main(int argc, char const* argv[])
{
  if(argc < 2){
    std::cout << "The server IP address must be passed as argument." << std::endl;
    return 1;
  }
  ClientSocketThread clientSocketThread;
  Communicator communicator((std::string(argv[1])), &clientSocketThread);
  communicator.sendTest();

  std::string tmp;
  std::cin >> tmp;

  return 0;
}
