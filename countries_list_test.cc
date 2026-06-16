#include <iostream>
#include "countries_list.h"

int main() {
    CCountriesList validator;

    std::cout << "=== Country Validator Test ===" << std::endl;
    std::cout << "Initial countries count: " << validator.size() << std::endl << std::endl;

    // Add countries to the set at runtime
    std::cout << "=== Adding Countries ===" << std::endl;
    validator.addCountry("USA");
    validator.addCountry("Canada");
    validator.addCountry("Mexico");
    validator.addCountry("France");
    validator.addCountry("Germany");
    std::cout << "Added 5 countries" << std::endl;
    std::cout << "Total countries count: " << validator.size() << std::endl << std::endl;

    // Test validation
    std::cout << "=== Testing Validation ===" << std::endl;
    std::string testCountries[] = {"USA", "Canada", "Spain", "Germany", "Japan"};

    for (const auto& country : testCountries) {
        if (validator.isPresent(country)) {
            std::cout << "✓ \"" << country << "\" is valid" << std::endl;
        } else {
            std::cout << "✗ \"" << country << "\" is NOT valid" << std::endl;
        }
    }

    // Test removing countries
    std::cout << "\n=== Removing Countries ===" << std::endl;
    if (validator.removeCountry("Mexico")) {
        std::cout << "✓ Removed \"Mexico\"" << std::endl;
    }
    std::cout << "Total countries count after removal: " << validator.size() << std::endl;
    std::cout << "Is \"Mexico\" still valid: " << (validator.isPresent("Mexico") ? "YES" : "NO") << std::endl;

    return 0;
}
