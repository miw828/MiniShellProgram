#include <string>
#include <vector>
#include <memory>

class Command {
public: 
    std::string program; //  will store the program name for a command
    std::vector<std::string> args; // will store the arguments for the command 

    Command(); // the constructor 
    bool parse(const std::string& line); // will parse input, all tokens stored in args vector, should return true if input text contains at least one token else return false
    std::vector<char*> argvConverter(); // input: array of pointers where each pointer refers to null-terminated character array, shohuld convert vector<string> into vector, returns array/vector of char* pointers (use .reserve)

};