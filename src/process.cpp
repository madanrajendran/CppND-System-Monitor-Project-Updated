#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;


Process::Process(int pid):processId_(pid)
{
    FindUserForProcess();
    FindCommandForProcess();
    CalcCpuUsageForProcess();
    CalcRamUsageForProcess();
    CalcUptimeForProcess();
}


// TODO: Return this process's ID
int Process::Pid() 
{ 
    return processId_; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() 
{ 
    return cpuUsage_; 
}

// TODO: Return the command that generated this process
string Process::Command() 
{ 
    return command_; 
}

// TODO: Return this process's memory utilization
string Process::Ram() 
{ 
    return ram_; 
}

// TODO: Return the user (name) that generated this process
string Process::User() 
{ 
    return user_; 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() 
{ 
    return uptime_; 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

void Process::FindUserForProcess()
{
    user_ = LinuxParser::User(Pid());
}

void Process::FindCommandForProcess()
{
    command_ = LinuxParser::Command(Pid());
}

void Process::CalcCpuUsageForProcess()
{
    // read values from filesystem
    long uptime = LinuxParser::UpTime();
    
    vector<float> val = LinuxParser::CpuUtilization(Pid());

    // only if the values could be read sucessfully
    if (val.size() == 5) 
    {
        // add utime, stime, cutime, cstime (they are in seconds)
        float totaltime = val[kUtime_] + val[kStime_] + val[kCutime_] + val[kCstime_];
        float seconds = uptime - val[kStarttime_];
        
        // calculate the processes CPU usage
        cpuUsage_ = totaltime / seconds;
    } 
    else
    {
        cpuUsage_ = 0;
    }
}

void Process::CalcRamUsageForProcess()
{
    // read kB value from file
    std::string val = LinuxParser::Ram(Pid());

    // convert into MB
    long conv = std::stol(val)/1000;
    ram_ = std::to_string(conv);
}

void Process::CalcUptimeForProcess()
{
    uptime_ = LinuxParser::UpTime(Pid());
}