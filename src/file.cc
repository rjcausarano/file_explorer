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

std::string File::getName() const{
  assert_existance(path_);
  return name_;
}

stringvec File::list() const{
  assert_existance(path_);
  std::vector<std::string> items;
  DIR* dir = opendir(path_.c_str());
  if(dir == nullptr){
    return items;
  }
  dirent* ent;
  while( (ent = readdir(dir)) != nullptr ){
    if((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0)){
      items.emplace_back(ent->d_name);
    }
  }
  closedir(dir);
  return items;
}

filevec File::children() const{
  assert_existance(path_);
  filevec children;
  for(std::string filename : list()){
    children.emplace_back(File(path_ + "/" + filename));
  }
  return children;
}

bool File::isDir() const{
  assert_existance(path_);
  struct stat info;
  stat(path_.c_str(), &info);
  return S_ISDIR(info.st_mode);
}

bool File::isEmptyDir() const{
  assert_existance(path_);
  return ( isDir() && list().empty() );
}

void File::del(){
  assert_existance(path_);
  if(isDir()){
    for(std::string filename : list()){
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
    rmdir(path_.c_str());
  } else {
    remove(path_.c_str());
  }
}

void File::assert_existance(const std::string& path) const{
  if(!exists(path)){
    throw std::runtime_error("Directory does not exist: " + path);
  }
}

bool File::exists(const std::string& path) const{
  return access(path.c_str(), F_OK) == 0;
}