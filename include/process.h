#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
 int processId_;
 std::string user_;
 std::string command_;
 float cpuUsage_;
 std::string ram_;
 long uptime_;

 void FindUserForProcess();
 void FindCommandForProcess();
 void CalcCpuUsageForProcess();
 void CalcRamUsageForProcess();
 void CalcUptimeForProcess();

   // CPU values of a process
  enum ProcessCPUStates {
    kUtime_ = 0,
    kStime_,
    kCutime_,
    kCstime_,
    kStarttime_
  };

};

#endif