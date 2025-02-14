#include <iostream>
#include "file.h"
#include "file_serializer.h"

void printEntity(Entity& entity, int depth = 0){
  std::string indent(depth * 2, ' ');
  std::cout << indent << entity.name() << std::endl;
  if(entity.type() == Entity::DIRECTORY){
    for(Entity child : entity.entities()){
      printEntity(child, depth + 1);
    }
  }
}

int main(){
	File file("../test/parent_dir");
	FileSerializer fileSerializer(file);
	std::string serialized_data = fileSerializer.serialize();

  // Now deserialize it and show the contents

  Entity entity;
  entity.ParseFromString(serialized_data);
  printEntity(entity);
	return 0;
}
