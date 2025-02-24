#include <string>
#include <iostream>
#include <unistd.h>
#include "file.h"
#include "entity_processor.h"
#include "comms/communicator.h"

int main(int argc, char const* argv[])
{
  if(argc < 2){
    std::cout << "The server IP address must be passed as argument." << std::endl;
    return 1;
  }

  Communicator communicator((std::string(argv[1])));
  Entity entity = communicator.getDirTree("/Users/rodric/Downloads");
  EntityProcessor processor(entity);
  processor.printDescription();
  std::string tmp;
  std::cin >> tmp;

  return 0;
}
