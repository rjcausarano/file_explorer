#pragma once

#include "file.h"
#include "comms/entity.pb.h"
#include <string>

class EntityProcessor{
	public:
	EntityProcessor(const File& file);
  EntityProcessor(const Entity& entity);
  EntityProcessor(const std::string serialized_data);
	std::string serialize() const;
  Entity getEntity() const;
  void printDescription() const;
	
	private:
  void createNestedEntity(File parentFile, Entity* parentEntity) const;
  void printNestedEntity(const Entity& entity, int depth = 0) const;
  Entity entity_;
};
