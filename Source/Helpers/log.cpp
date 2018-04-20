//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief Implementation of the log helper header
 * 
 * @file log.cpp
 * @author Camilo Talero
 * @date 2018-04-15
*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                     Global Values                                    *
 *                                                                                      */
//========================================================================================
#include "log.hpp"

bool first_call = true;
std::string LOG_FILE = "log/.log";

//########################################################################################

//========================================================================================
/*                                                                                      *
 *                               Function Implementations                               *
 *                                                                                      */
//========================================================================================

namespace Log {

//Set log file we will write to
void set_log_file(std::string log_path)
{
    LOG_FILE = log_path;
}

//Delete previous log if existing
void wipe_log()
{
    std::string LOG_DIR = LOG_FILE.substr(0,LOG_FILE.find_last_of('/'));
    mkdir(LOG_DIR.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);

    std::ofstream file_stream;

    file_stream.open(LOG_FILE, std::ofstream::out | std::ofstream::trunc);
    file_stream.close();
}

//Record a message
void record_log(std::string message)
{
    if(first_call)
        wipe_log();

    first_call = false;

    std::string LOG_DIR = LOG_FILE.substr(0,LOG_FILE.find_last_of('/'));
    mkdir(LOG_DIR.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);

    std::ofstream file_stream;
    file_stream.open(LOG_FILE, std::ios_base::app);
    file_stream << message << std::endl;
    file_stream.close();
}
void record_log(std::string message, std::string end, int alignment)
{
    if(first_call)
        wipe_log();

    first_call = false;

    std::string LOG_DIR = LOG_FILE.substr(0,LOG_FILE.find_last_of('/'));
    mkdir(LOG_DIR.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);

    std::istringstream stream(message);
    std::string last_line;
    for (std::string line; std::getline(stream, line); )
    {
        last_line = line;
    }

    int gap = alignment - last_line.length();
    if(gap > 0)
        end = std::string(gap,' ') + end;

    std::ofstream file_stream;
    file_stream.open(LOG_FILE, std::ios_base::app);
    file_stream << message + end << std::endl;
    file_stream.close();
}
void record_log(std::string message, std::string end, int alignment, char fill)
{
    if(first_call)
        wipe_log();

    first_call = false;

    std::string LOG_DIR = LOG_FILE.substr(0,LOG_FILE.find_last_of('/'));
    mkdir(LOG_DIR.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);

    std::istringstream stream(message);
    std::string last_line;
    for (std::string line; std::getline(stream, line); )
    {
        last_line = line;
    }

    int gap = alignment - last_line.length();
    if(gap > 0)
        end = std::string(gap,fill) + end;

    std::ofstream file_stream;
    file_stream.open(LOG_FILE, std::ios_base::app);
    file_stream << message + end << std::endl;
    file_stream.close();
}

//Record a message and the time of the message
void record_log_time(std::string message)
{
    if(first_call)
        wipe_log();

    first_call = false;

    auto execution_start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(execution_start);

    std::ofstream file_stream;
    file_stream.open(LOG_FILE, std::ios_base::app);
    file_stream << message + std::ctime(&start_time);
    file_stream.close();
}

//Wrap text by maximum alignment
std::string wrap_text(std::string text, int maximum)
{
    std::string result = "";

    std::istringstream stream(text);
    std::string word;
    std::string line = "";
    while (stream >> word)
    {
        if((line.length() + word.length()) > maximum)
        {
            result+=line + "\n";
            line = word + " ";
        }
        else
            line += word + " ";
    }
    return result + line + "\n";
}
}//Closing bracket of Log namespace
//########################################################################################
