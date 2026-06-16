#include <iostream>
#include "ip_validator.h"

int main() {
    // Test IPv4 addresses
    std::cout << "=== IPv4 Validation ===" << std::endl;
    std::string ipv4_valid = "192.168.1.1";
    std::string ipv4_invalid = "256.1.1.1";
    
    std::cout << ipv4_valid << " is valid: " << (CIPValidator::isValidIPv4(ipv4_valid) ? "YES" : "NO") << std::endl;
    std::cout << ipv4_invalid << " is valid: " << (CIPValidator::isValidIPv4(ipv4_invalid) ? "YES" : "NO") << std::endl;

    // Test IPv6 addresses
    std::cout << "\n=== IPv6 Validation ===" << std::endl;
    std::string ipv6_valid = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";
    std::string ipv6_invalid = "gggg::1";
    
    std::cout << ipv6_valid << " is valid: " << (CIPValidator::isValidIPv6(ipv6_valid) ? "YES" : "NO") << std::endl;
    std::cout << ipv6_invalid << " is valid: " << (CIPValidator::isValidIPv6(ipv6_invalid) ? "YES" : "NO") << std::endl;

    // Test generic IP validation
    std::cout << "\n=== Generic IP Validation ===" << std::endl;
    std::string ips[] = {"192.168.1.1", "::1", "invalid", "10.0.0.1", "fe80::1"};
    for (const auto& ip : ips) {
        std::cout << ip << " -> " << CIPValidator::getIPType(ip) << std::endl;
    }

    // Test private IP detection
    std::cout << "\n=== Private IP Detection ===" << std::endl;
    std::string test_ips[] = {"192.168.1.1", "10.0.0.1", "172.16.5.5", "127.0.0.1", "8.8.8.8"};
    for (const auto& ip : test_ips) {
        std::cout << ip << " is private: " << (CIPValidator::isPrivateIPv4(ip) ? "YES" : "NO") << std::endl;
    }

    return 0;
}
