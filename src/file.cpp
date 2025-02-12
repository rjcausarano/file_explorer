#include "file.h"
#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include <cstring>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>

File::File(const std::string& path) {
    assert_existance(path);
    path_ = std::string(realpath(path.c_str(), nullptr));
    char c_path[256];
    strcpy(c_path, path_.c_str());
    name_ = basename(c_path);
}

File::~File(){}

std::string File::getName(){
    assert_existance(path_);
    return name_;
}

stringvec File::list(){
    assert_existance(path_);
    std::vector<std::string> items;
    DIR* dir = opendir(path_.c_str());
    if(dir == nullptr){
        return items;
    }
    dirent* ent;
    while( (ent = readdir(dir)) != nullptr ){
        items.emplace_back(ent->d_name);
        std::cout << ent->d_name << std::endl;
    }
    closedir(dir);
    return items;
}

bool File::isDir(){
    assert_existance(path_);
    struct stat info;
    stat(path_.c_str(), &info);
    return S_ISDIR(info.st_mode);
}

bool File::isEmptyDir(){
    assert_existance(path_);
    return ( isDir() && list().empty() );
}

void File::del(){
    assert_existance(path_);
    if(isDir()){
        stringvec to_remove = list();
        to_remove.erase(std::remove(to_remove.begin(), to_remove.end(), "."), to_remove.end());
        to_remove.erase(std::remove(to_remove.begin(), to_remove.end(), ".."), to_remove.end());
        for(std::string filename : to_remove){
            const std::string filepath(path_ + "/" + filename);
            File file(filepath);
            if(file.isDir()){
                if(!file.isEmptyDir()){
                    file.del();
                }
            } else {  
                file.del();
            }
        }
        std::cout << "Removing dir: " << path_.c_str() << std::endl;
        rmdir(path_.c_str());
    } else {
        std::cout << "Removing file: " << path_.c_str() << std::endl;
        remove(path_.c_str());
    }
}

void File::assert_existance(const std::string& path){
    if(!exists(path)){
        throw std::runtime_error("Directory does not exist: " + path);
    }
}

bool File::exists(const std::string& path){
    return access(path.c_str(), F_OK) == 0;
}