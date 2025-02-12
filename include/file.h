#pragma once

#include <string>
#include <vector>
#include <dirent.h>

typedef std::vector<std::string> stringvec;

class File {
public:
    File(const std::string& path);
    ~File();
    std::string getName();
    stringvec list();
    bool isDir();
    bool isEmptyDir();
    void del();
private:
    void assert_existance(const std::string& path);
    bool exists(const std::string& path);

    std::string path_;
    std::string name_;
};