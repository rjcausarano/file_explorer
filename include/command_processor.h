#pragma once

#include "comms/header_processor.h"
#include <string>

class CommandProcessor : public HeaderProcessor{
  public:
  CommandProcessor();
  Header process(std::string type, std::string data) const override;
};