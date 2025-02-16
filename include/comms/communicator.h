#pragma once

#include <thread>
#include <mutex>
#include <stack>
#include <string>

class SharedMessage{
  public:
  void setMessage(const std::string& message){
    mtx.lock();
    messages_.push(message);
    mtx.unlock();
  }

  const std::string getMessage(){
    std::string return_value;
    mtx.lock();
    return_value = messages_.top();
    messages_.pop();
    mtx.unlock();
    return return_value;
  }

  bool hasMessage(){
    bool isEmpty;
    mtx.lock();
    isEmpty = messages_.empty();
    mtx.unlock();
    return !isEmpty;
  }

  private:
  std::stack<std::string> messages_;
  std::mutex mtx;
};

class Communicator{
  public:
  Communicator(const std::string& ip);
  void sendTest();
  private:
  std::thread coms_thread_;
  SharedMessage shared_message_;
};