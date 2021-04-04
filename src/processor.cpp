#include "processor.h"
#include "linux_parser.h"
#include <unistd.h>
#include <vector>
#include <iostream>

using namespace std;

vector<long> CalculateUtilization(const vector<string>& cpuValues)
{
    long userCurr = stol(cpuValues[0]);
    long niceCurr = stol(cpuValues[1]);
    long systemCurr = stol(cpuValues[2]);
    long idleCurr = stol(cpuValues[3]);
    long iowaitCurr = stol(cpuValues[4]);
    long irqCurr = stol(cpuValues[5]);
    long softirqCurr = stol(cpuValues[6]);
    long stealCurr = stol(cpuValues[7]);

    long idleTime = idleCurr + iowaitCurr;
    long nonIdleTime = userCurr + niceCurr + systemCurr + irqCurr + softirqCurr + stealCurr;
    long totalTime = idleTime + nonIdleTime;

    vector<long> cpuUtilization{idleTime, nonIdleTime, totalTime};

    return cpuUtilization;
}


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{ 
    vector<string> cpuValues{};
    static long prevIdle{0}, prevTotal{0}, currIdle{0}, currTotal{0};
    
    cpuValues = LinuxParser::CpuUtilization();

    vector<long> cpuUtil = CalculateUtilization(cpuValues);
    currTotal = cpuUtil[2];
    currIdle = cpuUtil[0];

    float diffIdleTime = (float)(currIdle- prevIdle);
    float diffTotalTime = (float)(currTotal - prevTotal);

    //std::cout << diffIdleTime << std::endl;

    float cpuPercentage = (diffTotalTime - diffIdleTime) / diffTotalTime;

    prevTotal = currTotal;
    prevIdle = currIdle;

    return cpuPercentage; 
}