#include "entity_processor.h"
#include <iostream>

EntityProcessor::EntityProcessor(const File& file) {
  entity_.set_name(file.getName());
  entity_.set_type(file.isDir() ? Entity::DIRECTORY : Entity::FILE);
  createNestedEntity(file, &entity_);
}

EntityProcessor::EntityProcessor(const Entity& entity) : entity_{entity} {}

EntityProcessor::EntityProcessor(const std::string serialized_data){
  entity_.ParseFromString(serialized_data);
}

Entity EntityProcessor::getEntity() const{
  return entity_;
}

void EntityProcessor::createNestedEntity(File parentFile, Entity* parentEntity) const{
  for(File childFile : parentFile.children()){
    Entity* childEntity = parentEntity->add_entities();
    childEntity->set_name(childFile.getName());
    if(childFile.isDir()){
      childEntity->set_type(Entity::DIRECTORY);
    } else{
      childEntity->set_type(Entity::FILE);
    }
    createNestedEntity(childFile, childEntity);
  }
  return;
}

std::string EntityProcessor::serialize() const {
  std::string serialized;
  entity_.SerializeToString(&serialized);
  return serialized;
}

void EntityProcessor::printNestedEntity(const Entity& entity, int depth) const{
  std::string indent(depth * 2, ' ');
  std::cout << indent << entity.name() << std::endl;
  if(entity.type() == Entity::DIRECTORY){
    for(Entity child : entity.entities()){
      printNestedEntity(child, depth + 1);
    }
  }
}

void EntityProcessor::printDescription() const{
  printNestedEntity(entity_);
}
