#include "comms/server.h"
#include "command_processor.h"

int main(int argc, char const* argv[]){
  CommandProcessor commandProcessor;
  Server server(&commandProcessor);
  server.listenToClient();
  return 0;
}
