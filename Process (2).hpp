#include <sys/types.h>
#include <string>

class Process{
private: 
    pid_t pid; // this will create the private variables 
    int childStatus;
    bool has_forked;

public: 
    Process();
    void fork_process();
    bool isParent() const; // will return true if pid > 0
    bool isChild() const; // returns true if pid == 0 
    pid_t getPID() const; // returns the pid of the process after determininging whether its a parent or child
    void exec(const std::string& command, char* const* argv); // this is for CHILD process will clal execvp with command and args willl check for failure
    void wait_for_child(); // for PARENT process will call isParent and otherwise it will call std::runtime error calls wairPIS and checks for failure
    int getExitStatus() const; // returns the CHILDS exit status using WEXITSTAUTS otherwise return -1
    bool terminatedNormally() const; // will return true if child exists and terminated normally

};
