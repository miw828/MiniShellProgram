#include "Process.hpp"
#include "wrappedFuncs.hpp"
#include <stdexcept>
#include <iostream>

Process::Process() : pid(-1), childStatus(-1), has_forked(false) {}

void Process::fork_process(){
    if(has_forked){
        throw std::runtime_error("Cannot fork more than once per Process instance.");
    }
    pid = Fork();
    has_forked = true; 
    }

   
    bool Process::isParent() const {
        return pid > 0; 
    } // will return true if pid > 0
    bool Process::isChild() const {
        return pid == 0; 
    }
        // returns true if pid == 0 
    pid_t Process::getPID() const {
        return pid; 

    } // returns the pid of the process after determininging whether its a parent or child
    void Process::exec(const std::string& command, char* const* argv){
        if(!isChild()) throw std::runtime_error("exec() must be called form child process.");
        Execvp(command.c_str(), argv);
    } // this is for CHILD process will clal execvp with command and args willl check for failure
    void Process::wait_for_child(){
        if(!isParent()) throw std::runtime_error("wait_for_child() must be called from parent process. ");
        Waitpid(pid, &childStatus, 0);
    }// for PARENT process will call isParent and otherwise it will call std:runtime error calls wairPIS and checks for failure
    int Process::getExitStatus() const{
        if(terminatedNormally()){
            return WEXITSTATUS(childStatus);
        }
        return -1; 
    } // returns the CHILDS exit status using WEXITSTAUTS otherwise return -1
    bool Process::terminatedNormally() const{
        return has_forked && WIFEXITED(childStatus);
    }// will return true if child exists and terminated normally
