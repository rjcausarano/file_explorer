#pragma once

#include "file.h"
#include "../proto/dir_descriptor.pb.h"
#include <string>

class FileSerializer{
	public:
	FileSerializer(const File& file);
	std::string serialize() const;
	
	private:
  void nestedList(File parentFile, Entity& parentEntity) const;
	File file_;
};
