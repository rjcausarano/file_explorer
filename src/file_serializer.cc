#include "file_serializer.h"

FileSerializer::FileSerializer(const File& file) : file_{file} {}

void FileSerializer::nestedList(File parentFile, Entity& parentEntity) const{
  if(!parentFile.isDir()){
    return;
  }
  for(File childFile : parentFile.children()){
    Entity childEntity;
    childEntity.set_name(childFile.getName());
    if(childFile.isDir()){
      childEntity.set_type(Entity::DIRECTORY);
      *(parentEntity.add_entities()) = childEntity;
      nestedList(childFile, childEntity);
    } else{
      childEntity.set_type(Entity::FILE);
      *(parentEntity.add_entities()) = childEntity;
    }
  }
}

std::string FileSerializer::serialize() const {
  Entity parent;
  parent.set_name(file_.getName());
  parent.set_type(file_.isDir() ? Entity::DIRECTORY : Entity::FILE);
  nestedList(file_, parent);
  std::string serialized;
  parent.SerializeToString(&serialized);
  return serialized;
}
