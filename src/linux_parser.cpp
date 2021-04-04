#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ 
  string line{};
  string strMemoryType{}, strMemorySize{};
  std::ifstream memoryFileStream(kProcDirectory + kMeminfoFilename);
  long lngTotalMemorySize{0}, lngFreeMemory{0};

  if(memoryFileStream.is_open())
  {
    while(getline(memoryFileStream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');

      std::stringstream lineStream(line);
      lineStream >> strMemoryType >> strMemorySize;

      if(strMemoryType == "MemTotal")
      {
        lngTotalMemorySize = std::stol(strMemorySize);
      }
      else if(strMemoryType == "MemFree")
      {
        lngFreeMemory = std::stol(strMemorySize);
      }
    }

  }

  float memoryUsage = ((float)lngTotalMemorySize - (float)lngFreeMemory)/(float)lngTotalMemorySize;

  return memoryUsage; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{ 
  std::ifstream uptimeFileStream(kProcDirectory + kUptimeFilename);
  string line{}, strUptime{"0"};

  if(uptimeFileStream.is_open())
  {
    getline(uptimeFileStream, line);
    std::stringstream uptimeStringStream(line);
    uptimeStringStream >> strUptime;
  }
  return std::stol(strUptime); 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{ 
  std::ifstream cpuFileStream;
  vector<string> cpuValues(9, "");
  string lineString = "";
  string cpuString;

  cpuFileStream.open(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);

  if(cpuFileStream.is_open())
  {
    //std::cout << "open\n";
    getline(cpuFileStream, lineString);
    std::stringstream lineStringStream(lineString);

    lineStringStream >> cpuString >> cpuValues[0] >> cpuValues[1] >> cpuValues[2] >> cpuValues[3] >> 
    cpuValues[4] >> cpuValues[5] >> cpuValues[6] >> cpuValues[7] >> cpuValues[8];

    //std::cout << lineString << std::endl;
  }
  
  return cpuValues; 

}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{ 
  std::ifstream statFileStream(kProcDirectory+kStatFilename);
  string line{}, key{}, value{"0"};
  bool keyFound = false;

  if(statFileStream.is_open())
  {
    while(std::getline(statFileStream, line) && keyFound == false)
    {
      std::stringstream statLineStringStream(line);
      statLineStringStream >> key >> value;
      if(key == "processes")
      {
        keyFound = true;
      }
    }
  }

  return std::stoi(value); 
} 

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{ 
  std::ifstream statFileStream(kProcDirectory+kStatFilename);
  string line{}, key{}, value{"0"};
  bool keyFound = false;

  if(statFileStream.is_open())
  {
    while(std::getline(statFileStream, line) && keyFound == false)
    {
      std::stringstream statLineStringStream(line);
      statLineStringStream >> key >> value;
      if(key == "procs_running")
      {
        keyFound = true;
      }
    }
  }
  return std::stoi(value); 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
