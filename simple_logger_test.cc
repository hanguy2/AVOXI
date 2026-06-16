#include <iostream>
#include "simple_logger.h"

int main() {
    std::cout << "=== Simple Logger Test ===" << std::endl << std::endl;

    // Test basic logging with different levels
    std::cout << "--- Log messages with timestamp and level ---" << std::endl;
    CSimpleLogger::debug("This is a debug message");
    CSimpleLogger::info("Application started successfully");
    CSimpleLogger::warning("This is a warning message");
    CSimpleLogger::error("An error occurred");
    CSimpleLogger::critical("Critical system failure");

    // Test custom log function with LogLevel parameter
    std::cout << "\n--- Using log() with LogLevel parameter ---" << std::endl;
    CSimpleLogger::log(LogLevel::INFO, "Direct log with INFO level");
    CSimpleLogger::log(LogLevel::DEBUG, "Direct log with DEBUG level");
    CSimpleLogger::log(LogLevel::ERROR, "Direct log with ERROR level");

    // Test disabling timestamp
    std::cout << "\n--- Log messages without timestamp ---" << std::endl;
    CSimpleLogger::setShowTimestamp(false);
    CSimpleLogger::info("Message without timestamp");
    CSimpleLogger::warning("Warning without timestamp");
    CSimpleLogger::error("Error without timestamp");

    // Test disabling level
    std::cout << "\n--- Log messages without level ---" << std::endl;
    CSimpleLogger::setShowLevel(false);
    CSimpleLogger::info("Message without level");
    CSimpleLogger::warning("Warning without level");

    // Enable both again
    std::cout << "\n--- Log messages with both timestamp and level enabled ---" << std::endl;
    CSimpleLogger::setShowTimestamp(true);
    CSimpleLogger::setShowLevel(true);
    CSimpleLogger::info("Final info message");
    CSimpleLogger::error("Final error message");

    return 0;
}
