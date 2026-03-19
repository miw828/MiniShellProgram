#include "Process.hpp"
#include "Command.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>     // needed for getpid()

int main(){
    std::cout << "Simple Shell (PID: " << getpid() << ")\n";
    std::cout << "Type 'exit' to quit; Type 'last' to re-run the last command. \n";

    std::shared_ptr<Command> lastCommand;
    std::string line;

    while(true) {
        std::cout << "myshell> ";
        if(!std::getline(std::cin, line)) break;

        if(line == "exit") {
            std::cout << "Exiting shell. " << "\n";
            break;
        }
        if(line == "last"){
            if(!lastCommand || lastCommand->program.empty()){
                std::cout << "No previous command." << "\n";
                continue;
            }
            std::cout << "Re-running: ";
            for(const auto& s: lastCommand->args){
                std::cout << s << " ";
            }
            std::cout << "\n";
        }

        std::shared_ptr<Command> com = std::make_shared<Command>();
        if(line != "last") {
            if(!com->parse(line)){
                continue;
            }
            if(com->program == "exit"){
                std::cout << "Exiting shell." << "\n";
                break; 
            }
            if(com->program == "last"){
                std::cout << "No previous command.\n";
                continue;
            }
            lastCommand = com; // store command for last 
        } else {
            com = lastCommand; // this will re-run last 
        }

        std::unique_ptr<Process> pro = std::make_unique<Process>(); // creates vector 
        try {
            pro->fork_process();
            if(pro->isChild()){
                pro->exec(com->program, com->argvConverter().data());
            } else {
                pro->wait_for_child();
            }
        }
        catch(std::runtime_error& e){
            continue; 
        }
    }
    return 0; 
}