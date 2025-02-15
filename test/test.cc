#include <iostream>
#include "file.h"
#include "entity_processor.h"

int main(){
	File file("../test/parent_dir");
	EntityProcessor entityProcessor(file);
	std::string serialized_data = entityProcessor.serialize();

  // Now deserialize it and show the contents

  EntityProcessor newEntityProcessor(serialized_data);
  newEntityProcessor.printDescription();
	return 0;
}
