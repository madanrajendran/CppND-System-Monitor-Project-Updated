#include <string>

#include "format.h"

using std::string;

string ConvertToTimeString(int val)
{
    string twoDigits = "";

    if(val < 10)
    {
        twoDigits = "0" + std::to_string(val);
    }
    else
    {
        twoDigits = std::to_string(val);
    }

    return twoDigits;
}

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
    string timeFormatted = "00:00:00";

    if(seconds > 0)
    {
        //hours
        int hours = seconds/3600;
        timeFormatted = ConvertToTimeString(hours) + ":";
        int remainingSec = seconds%3600;

        //mins
        int mins = remainingSec/60;
        timeFormatted = timeFormatted + ConvertToTimeString(mins) + ":";
        remainingSec = remainingSec%60;

        //seconds
        timeFormatted = timeFormatted + ConvertToTimeString(remainingSec);

    }

    return timeFormatted; 
}

