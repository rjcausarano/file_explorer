#include "file.h"
#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include <cstring>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>

File::File(const std::string path) {
    path_ = std::string(realpath(path.c_str(), nullptr));
    if(!exists()){
        throw std::runtime_error("Directory does not exist: " + path);
    }
    if(isDir()){
        dir_ = opendir(path_.c_str());
    }
    char c_path[256];
    strcpy(c_path, path_.c_str());
    name_ = basename(c_path);
}

File::~File(){
    if(dir_ != nullptr){
        closedir(dir_);
    }
}

std::string File::getName(){
    return name_;
}

stringvec File::list(){
    std::vector<std::string> items;
    if(dir_ == nullptr){
        return items;
    }
    dirent* ent;
    while( (ent = readdir(dir_)) != nullptr ){
        items.emplace_back(ent->d_name);
        std::cout << ent->d_name << std::endl;
    }
    rewinddir(dir_);
    return items;
}

bool File::isDir(){
    struct stat info;
    stat(path_.c_str(), &info);
    return S_ISDIR(info.st_mode);
}

void File::del(){
    if(isDir()){
        stringvec to_remove = list();
        to_remove.erase(std::remove(to_remove.begin(), to_remove.end(), "."), to_remove.end());
        to_remove.erase(std::remove(to_remove.begin(), to_remove.end(), ".."), to_remove.end());
        for(std::string filename : to_remove){
            std::cout << "Removing " << (path_ + "/" + filename).c_str() << std::endl;
            remove((path_ + "/" + filename).c_str());
        }
        closedir(dir_);
        dir_ = nullptr;
        rmdir(path_.c_str());
    } else {
        remove(path_.c_str());
    }
}

bool File::exists(){
    return access(path_.c_str(), F_OK) == 0;
}