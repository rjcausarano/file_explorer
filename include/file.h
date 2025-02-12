#pragma once

#include <string>
#include <vector>
#include <dirent.h>

typedef std::vector<std::string> stringvec;

class File {
public:
    File(const std::string path);
    ~File();
    std::string getName();
    stringvec list();
    bool isDir();
    void del();
private:
    bool exists();

    std::string path_;
    std::string name_;
    DIR* dir_{nullptr};
};