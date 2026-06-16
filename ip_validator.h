#ifndef IP_VALIDATOR_H
#define IP_VALIDATOR_H

#include <string>
#include <regex>
#include <arpa/inet.h>
#include <cstring>

class CIPValidator {
public:
    /**
     * Validates if a string is a valid IPv4 address
     * @param ip The IP address string to validate
     * @return true if valid IPv4, false otherwise
     */
    static bool isValidIPv4(const std::string& ip) {
        struct in_addr addr;
        return inet_pton(AF_INET, ip.c_str(), &addr) == 1;
    }

    /**
     * Validates if a string is a valid IPv6 address
     * @param ip The IP address string to validate
     * @return true if valid IPv6, false otherwise
     */
    static bool isValidIPv6(const std::string& ip) {
        struct in6_addr addr;
        return inet_pton(AF_INET6, ip.c_str(), &addr) == 1;
    }

    /**
     * Validates if a string is a valid IPv4 or IPv6 address
     * @param ip The IP address string to validate
     * @return true if valid IPv4 or IPv6, false otherwise
     */
    static bool isValidIP(const std::string& ip) {
        return isValidIPv4(ip) || isValidIPv6(ip);
    }

    /**
     * Determines the type of IP address
     * @param ip The IP address string to check
     * @return "IPv4", "IPv6", or "Invalid"
     */
    static std::string getIPType(const std::string& ip) {
        if (isValidIPv4(ip)) {
            return "IPv4";
        } else if (isValidIPv6(ip)) {
            return "IPv6";
        }
        return "Invalid";
    }

    /**
     * Validates if an IPv4 address is in a private range
     * @param ip The IPv4 address string to check
     * @return true if in private range, false otherwise
     */
    static bool isPrivateIPv4(const std::string& ip) {
        if (!isValidIPv4(ip)) {
            return false;
        }

        struct in_addr addr;
        inet_pton(AF_INET, ip.c_str(), &addr);
        unsigned long host_addr = ntohl(addr.s_addr);

        // 10.0.0.0/8
        if ((host_addr >= 0x0A000000) && (host_addr <= 0x0AFFFFFF)) {
            return true;
        }
        // 172.16.0.0/12
        if ((host_addr >= 0xAC100000) && (host_addr <= 0xAC1FFFFF)) {
            return true;
        }
        // 192.168.0.0/16
        if ((host_addr >= 0xC0A80000) && (host_addr <= 0xC0A8FFFF)) {
            return true;
        }
        // 127.0.0.0/8 (loopback)
        if ((host_addr >= 0x7F000000) && (host_addr <= 0x7FFFFFFF)) {
            return true;
        }

        return false;
    }
};

#endif // IP_VALIDATOR_H
