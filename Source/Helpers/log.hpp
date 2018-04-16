//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief A small header declaring some general functions to record information 
 * in a log.
 * 
 * @file log.hpp
 * @author Camilo Talero
 * @date 2018-04-14
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//
// ────────────────────────────────────────────────────────────────── I ──────────
//   :::::: I N C L U D E   F I L E S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//
#pragma once

//IO libraries
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <libgen.h>
#include <string>

//Time handling liibraries
#include <chrono>
#include <ctime>

#include "Nyx.hpp"
// ────────────────────────────────────────────────────────────────────────────────

//
// ────────────────────────────────────────────────────────────────── I ──────────
//   :::::: G L O B A L   V A L U E S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────
//
/**
 * @def LOG_FILE
 * @brief Name of file use to record information (the log file)
*/
extern std::string LOG_FILE;
extern bool first_call;
// ────────────────────────────────────────────────────────────────────────────────

//
// ──────────────────────────────────────────────────────────────────── I ──────────
//   :::::: L O G     F U N C T I O N S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────
//
namespace Log{
/**
 * @brief Set the log file string
 * 
*/
void inline set_log_file(std::string log_path)
{
    LOG_FILE = log_path;
}

/**
 * @brief Delete the log file
 * 
*/
void inline wipe_log()
{
    std::string LOG_DIR = LOG_FILE.substr(0,LOG_FILE.find_last_of('/'));
    mkdir(LOG_DIR.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);

    std::ofstream file_stream;
    
    file_stream.open(LOG_FILE, std::ofstream::out | std::ofstream::trunc);
    file_stream.close();
}

/**
 * @brief Append a message a the end of the log file
 * 
 * @param message The message to recerod in the log
*/
void inline record_log(std::string message)
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

/**
 * @brief Record a message followed by the time and date at which this function was
 * called
 * 
 * @param message 
*/
void inline record_log_time(std::string message)
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
}
// ────────────────────────────────────────────────────────────────────────────────
