#include <iostream>
#include "geo_ip_database.h"

int main() {
    CGeoIPDatabase geoDb;

    std::cout << "=== GeoIP Database Test ===" << std::endl;
    std::cout << "Database open before opening: " << (geoDb.isOpen() ? "YES" : "NO") << std::endl;
    std::cout << "Database ready before opening: " << (geoDb.isReady() ? "YES" : "NO") << std::endl;

    // Open the database
    std::cout << "\n=== Opening Database ===" << std::endl;
    if (geoDb.open("./GeoLite2-Country.mmdb")) {
        std::cout << "✓ Database opened successfully" << std::endl;
    } else {
        std::cerr << "✗ Failed to open database" << std::endl;
        return 1;
    }

    std::cout << "Database open after opening: " << (geoDb.isOpen() ? "YES" : "NO") << std::endl;
    std::cout << "Database ready after opening: " << (geoDb.isReady() ? "YES" : "NO") << std::endl;

    // Test country lookup with IP addresses
    std::cout << "\n=== Testing Country Lookup ===" << std::endl;
    std::string testIPs[] = {
        "216.58.216.163",   // Google DNS
        "8.8.8.8",          // Google DNS
        "1.1.1.1",          // Cloudflare DNS
        "208.67.222.222"    // OpenDNS
    };

    for (const auto& ip : testIPs) {
        std::string country;
        if (geoDb.lookupCountry(ip, country)) {
            std::cout << "✓ IP " << ip << " -> Country: " << country << std::endl;
        } else {
            std::cout << "✗ IP " << ip << " -> No country found" << std::endl;
        }
    }

    // Test simplified lookup (returns only true/false)
    std::cout << "\n=== Testing Simplified Lookup ===" << std::endl;
    if (geoDb.lookupCountry("216.58.216.163")) {
        std::cout << "✓ Country data found for 216.58.216.163" << std::endl;
    } else {
        std::cout << "✗ No country data for 216.58.216.163" << std::endl;
    }

    // Database will be closed automatically in destructor
    std::cout << "\n=== End of Test ===" << std::endl;
    std::cout << "Database will be closed automatically by destructor" << std::endl;

    return 0;
}
