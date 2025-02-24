#include "command_processor.h"
#include "comms/socket_common.h"
#include "comms/entity.pb.h"
#include "entity_processor.h"
#include "comms/header_factory.h"

CommandProcessor::CommandProcessor() : HeaderProcessor() {}

Header CommandProcessor::process(std::string type, std::string data) const {
  Header responseHeader;
  if(type == common::getClassName<EntityRequest>()){
    EntityRequest req;
    req.ParseFromString(data);
    EntityProcessor processor(File(req.path()));
    Entity entity = processor.getEntity();
    responseHeader = HeaderFactory::createHeader(entity);
  }
  return responseHeader;
}
