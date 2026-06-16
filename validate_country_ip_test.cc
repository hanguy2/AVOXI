#include <iostream>
#include "validate_country_ip.h"

int main() {
    std::cout << "=== Country IP Validator Test ===" << std::endl << std::endl;

    // Initialize validator with GeoIP database
    CValidateCountryIP validator("./geodata/GeoLite2-Country.mmdb");

    // Test cases
    std::vector<std::string> testCases = {
        // US IP with US allowed
        R"({
            "ip": "8.8.8.8",
            "allowedCountries": ["US", "CA"]
        })",
        
        // Google DNS with specific countries
        R"({
            "ip": "216.58.216.163",
            "allowedCountries": ["US"]
        })",
        
        // Invalid IP
        R"({
            "ip": "999.999.999.999",
            "allowedCountries": ["US", "CA"]
        })",
        
        // IP with empty allowed list
        R"({
            "ip": "8.8.8.8",
            "allowedCountries": []
        })",
        
        // Different country not in whitelist
        R"({
            "ip": "216.58.216.163",
            "allowedCountries": ["GB", "FR"]
        })"
    };

    std::cout << "Testing various IP validation scenarios:" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;

    for (size_t i = 0; i < testCases.size(); ++i) {
        std::cout << "Test " << (i + 1) << ":" << std::endl;
        std::cout << "Input: " << testCases[i] << std::endl;
        
        json response = validator.validateAccess(testCases[i]);
        std::cout << "Response: " << response.dump() << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
