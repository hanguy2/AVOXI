#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H

#include <string>

/**
 * Enum for log levels
 */
enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

/**
 * Simple logger class that prints messages with log levels
 */
class CSimpleLogger {
private:
    static bool showTimestamp;
    static bool showLevel;

public:
    /**
     * Logs a message with the given log level
     * @param level The log level
     * @param message The message to log
     */
    static void log(LogLevel level, const std::string& message);

    /**
     * Logs a debug message
     * @param message The message to log
     */
    static void debug(const std::string& message);

    /**
     * Logs an info message
     * @param message The message to log
     */
    static void info(const std::string& message);

    /**
     * Logs a warning message
     * @param message The message to log
     */
    static void warning(const std::string& message);

    /**
     * Logs an error message
     * @param message The message to log
     */
    static void error(const std::string& message);

    /**
     * Logs a critical message
     * @param message The message to log
     */
    static void critical(const std::string& message);

    /**
     * Enables or disables timestamp in log output
     * @param enable true to show timestamp, false to hide
     */
    static void setShowTimestamp(bool enable);

    /**
     * Enables or disables log level in log output
     * @param enable true to show level, false to hide
     */
    static void setShowLevel(bool enable);

private:
    /**
     * Converts LogLevel enum to string
     * @param level The log level
     * @return String representation of the log level
     */
    static std::string getLevelString(LogLevel level);
};

#endif // SIMPLE_LOGGER_H
