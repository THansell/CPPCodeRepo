#ifndef ARGV_HPP
#define ARGV_HPP

#include <string>

class Argv {
  private:
    std::string command_line;
  public:
    // Constructor
    Argv();
    Argv(int argc, char* argv[]);
    // 
    int size();
    void erase(int n);
    void clear();
    void process(int argc, char* argv[]);
    std::string operator[] (int n);
    void replace(int n, std::string str);
    void push_back(std::string str);
};

#endif // ARGV_HPP
