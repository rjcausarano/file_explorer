#pragma once

#include "header.pb.h"
#include <string>

class HeaderFactory {
    public:
    static Header createHeader(Header::Type type, std::string data);
    private:
    HeaderFactory(){}
};