#include "Command.hpp"
#include <sstream>
#include <string>

Command::Command() : program(""), args() {} // the constructor 

bool Command::parse(const std::string& line){ // parse be pu
    std::istringstream iss(line);  // this creates the token
    std::string token; //this stores the token 
    args.clear(); // will clear the previous state before parsing new line 

    while(iss >> token){ // this will get the tokens and store them in args 
        args.push_back(token);
    }
    if(!args.empty()){ // set to the first token 
        program = args[0];
    } else {
        program.clear(); 
    }
    return !args.empty();
}
// input: array of pointers where each pointer refers to null-terminated character array, shohuld convert vector<string> into vector, returns array/vector of char* pointers (use .reserve)
std::vector<char*> Command::argvConverter(){
    std::vector<char*> argv;
    argv.reserve(argv.size() + 1); // reserve space for args 
    for(auto& arg : args){ // for each std::string in args , push a pointer 
        argv.push_back(const_cast<char*>(arg.c_str()));

    }
    argv.push_back(nullptr); // the array needs to be terminated by a null pointer
    return argv;
}