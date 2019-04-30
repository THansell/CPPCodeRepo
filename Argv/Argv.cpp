#include "Argv.hpp"

Argv::Argv() {
}

Argv::Argv(int argc, char* argv[]) {
    this->process(argc, argv);
}


int Argv::size() {
    return this->command_line.size() ;
}

void Argv::erase(int n) {
    this->command_line.erase(n);
}

void Argv::clear() {
    this->command_line.clear();
}

void Argv::process(int argc, char* argv[]) {
    this->command_line.
    for(int i = 0; i < argc; i++) {
    
}

std::string Argv::operator[] (int n) {
    if (this->command_line.size() > 0 && n < this->command_line.size()) {
        return(this->command_line[n]
    }
    return "" ;
}

void Argv::replace(int n, std::string str) {
    this->command_line[n] = str;
}

void Argv::push_back(std::string str) {
    this->command_line.push_back(str);
}
