//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @brief A small header declaring some general functions to record information 
 * in a log.
 * 
 * @file log.hpp
 * @author Camilo Talero
 * @date 2018-04-14
*/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//========================================================================================
/*                                                                                      *
 *                                     Include Files                                    *
 *                                                                                      */
//========================================================================================
#pragma once

//IO libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <libgen.h>
#include <string>

//Time handling libraries
#include <chrono>
#include <ctime>
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                     Global Values                                    *
 *                                                                                      */
//========================================================================================
/**
 * @def LOG_FILE
 * @brief Name of file use to record information (the log file)
*/
extern std::string LOG_FILE;
extern bool first_call;
//########################################################################################

//========================================================================================
/*                                                                                      *
 *                                     Log Functions                                    *
 *                                                                                      */
//========================================================================================

namespace Log{
/**
 * @brief Set the log file string
 * 
*/
void set_log_file(std::string log_path);

/**
 * @brief Delete the log file
 * 
*/
void wipe_log();

/**
 * @brief Append a message a the end of the log file
 * 
 * @param message The message to record in the log
*/
void record_log(std::string message);

/**
 * @brief A function to print log messages with a specially aligned formatting
 * 
 * The function records the first message plus some alignment plus the second message. 
 * Space is added between the first and the second message such that the second message 
 * always starts at the same character position. 
 * 
 * @param message The first part of the message
 * @param end The second part of the message
 * @param alignment The character position where the second part of the message should be.
*/
void record_log(std::string message, std::string end, int alignment);

/**
 * @brief Similar to {@link void record_log(std::string message)}
 *
 * @param message The first part of the message
 * @param end The second part of the message
 * @param alignment The character position where the second part of the message should be.
 * @param fill the character that will be used to fill the aligned space
*/
void record_log(std::string message, std::string end, int alignment, char fill);
/**
 * @brief Record a message followed by the time and date at which this function was
 * called
 * 
 * @param message 
*/
void record_log_time(std::string message);
/**
 * @brief Wrap the text to so that no line exceeds the maximum
 *
 * @param text The text to modify
 * @param maximum The maximum line length
 * @return std::string The modified text
*/
std::string wrap_text(std::string text, int maximum);
}//Closing bracket of Log namespace
//########################################################################################
