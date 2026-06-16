#include "simple_logger.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

// Static member initialization
bool CSimpleLogger::showTimestamp = true;
bool CSimpleLogger::showLevel = true;

/**
 * Logs a message with the given log level
 * @param level The log level
 * @param message The message to log
 */
void CSimpleLogger::log(LogLevel level, const std::string& message) {
    std::ostringstream oss;

    // Add timestamp if enabled
    if (showTimestamp) {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        oss << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] ";
    }

    // Add log level if enabled
    if (showLevel) {
        oss << "[" << getLevelString(level) << "] ";
    }

    // Add the message
    oss << message;

    // Output to appropriate stream based on level
    if (level == LogLevel::ERROR || level == LogLevel::CRITICAL) {
        std::cerr << oss.str() << std::endl;
    } else {
        std::cout << oss.str() << std::endl;
    }
}

/**
 * Logs a debug message
 * @param message The message to log
 */
void CSimpleLogger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

/**
 * Logs an info message
 * @param message The message to log
 */
void CSimpleLogger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

/**
 * Logs a warning message
 * @param message The message to log
 */
void CSimpleLogger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

/**
 * Logs an error message
 * @param message The message to log
 */
void CSimpleLogger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

/**
 * Logs a critical message
 * @param message The message to log
 */
void CSimpleLogger::critical(const std::string& message) {
    log(LogLevel::CRITICAL, message);
}

/**
 * Enables or disables timestamp in log output
 * @param enable true to show timestamp, false to hide
 */
void CSimpleLogger::setShowTimestamp(bool enable) {
    showTimestamp = enable;
}

/**
 * Enables or disables log level in log output
 * @param enable true to show level, false to hide
 */
void CSimpleLogger::setShowLevel(bool enable) {
    showLevel = enable;
}

/**
 * Converts LogLevel enum to string
 * @param level The log level
 * @return String representation of the log level
 */
std::string CSimpleLogger::getLevelString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::CRITICAL:
            return "CRIT";
        default:
            return "UNKNOWN";
    }
}
