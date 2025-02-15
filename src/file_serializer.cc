#include "file_serializer.h"

FileSerializer::FileSerializer(const File& file) : file_{file} {}

void FileSerializer::nestedList(File parentFile, Entity* parentEntity) const{
  // std::cout << "processing file: " << parentFile.getName() << std::endl;
  for(File childFile : parentFile.children()){
    // std::cout << "iterating child file: " << childFile.getName() << std::endl;
    Entity* childEntity = parentEntity->add_entities();
    childEntity->set_name(childFile.getName());
    if(childFile.isDir()){
      childEntity->set_type(Entity::DIRECTORY);
    } else{
      childEntity->set_type(Entity::FILE);
    }
    nestedList(childFile, childEntity);
  }
  // std::cout << "Only now return" << std::endl;
  return;
}

std::string FileSerializer::serialize() const {
  Entity parent;
  parent.set_name(file_.getName());
  parent.set_type(file_.isDir() ? Entity::DIRECTORY : Entity::FILE);
  nestedList(file_, &parent);
  std::string serialized;
  parent.SerializeToString(&serialized);
  return serialized;
}
