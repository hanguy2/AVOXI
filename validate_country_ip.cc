#include "validate_country_ip.h"
#include "simple_logger.h"

/**
 * Constructor - initializes the validator with GeoIP database path
 * @param dbFilePath Path to the GeoIP database file
 */
CValidateCountryIP::CValidateCountryIP(const std::string& dbFilePath) : mDBFilePath(dbFilePath) {
    if (!mGeoDatabase.open(dbFilePath)) {
        CSimpleLogger::error("Failed to initialize GeoIP database from: " + dbFilePath);
    } else {
        CSimpleLogger::info("GeoIP database initialized successfully");
    }
}

/**
 * Destructor
 */
CValidateCountryIP::~CValidateCountryIP() {
    // GeoDatabase will close in its destructor
}

/**
 * Validates if an IP address is allowed based on country whitelist
 * @param jsonInput JSON string with format:
 *        {
 *          "ip": "8.8.8.8",
 *          "allowedCountries": ["US", "CA"]
 *        }
 * @return JSON response { "Access": "Allowed" } or { "Access": "Denied" }
 */
json CValidateCountryIP::validateAccess(const std::string& jsonInput) {
    std::string ipAddress;
    std::vector<std::string> countries;

    // Check if database is ready, reopen if necessary
    if (!mGeoDatabase.isReady() && !mGeoDatabase.open(mDBFilePath)) {
        CSimpleLogger::error("Failed to initialize GeoIP database from: " + mDBFilePath);
        return createResponse(false);
    }

    // Parse and validate input JSON
    if (!parseInput(jsonInput, ipAddress, countries)) {
        CSimpleLogger::error("Failed to parse input JSON");
        return createResponse(false);
    }

    // Validate IP address
    if (!CIPValidator::isValidIP(ipAddress)) {
        CSimpleLogger::warning("Invalid IP address provided: " + ipAddress);
        return createResponse(false);
    }

    CSimpleLogger::info("Validating IP: " + ipAddress);

    // Add allowed countries to the set
    // Improvement: Hash check the country list based on unique customer ID
    allowedCountries.clear();
    for (const auto& country : countries) {
        allowedCountries.addCountry(country);
    }

    // Lookup country for the IP address
    std::string foundCountry;
    if (!mGeoDatabase.lookupCountry(ipAddress, foundCountry)) {
        CSimpleLogger::warning("No country found for IP: " + ipAddress);
        return createResponse(false);
    }

    CSimpleLogger::info("Country found for IP " + ipAddress + ": " + foundCountry);

    // Check if found country is in allowed countries list
    bool isAllowed = allowedCountries.isPresent(foundCountry);

    if (isAllowed) {
        CSimpleLogger::info("Access ALLOWED for IP " + ipAddress + " (Country: " + foundCountry + ")");
    } else {
        CSimpleLogger::warning("Access DENIED for IP " + ipAddress + " (Country: " + foundCountry + " not in whitelist)");
    }

    return createResponse(isAllowed);
}

/**
 * Parses the input JSON and validates format
 * @param jsonInput JSON string to parse
 * @param ipAddress Output parameter for IP address
 * @param countries Output parameter for allowed countries list
 * @return true if parsing successful, false otherwise
 */
bool CValidateCountryIP::parseInput(const std::string& jsonInput, std::string& ipAddress, std::vector<std::string>& countries) {
    try {
        json input = json::parse(jsonInput);

        // Check if required fields exist
        if (!input.contains("ip")) {
            CSimpleLogger::error("Missing 'ip' field in JSON input");
            return false;
        }

        if (!input.contains("allowedCountries")) {
            CSimpleLogger::error("Missing 'allowedCountries' field in JSON input");
            return false;
        }

        // Extract IP address
        ipAddress = input["ip"].get<std::string>();

        // Extract allowed countries (must be an array)
        if (!input["allowedCountries"].is_array()) {
            CSimpleLogger::error("'allowedCountries' must be an array");
            return false;
        }

        for (const auto& country : input["allowedCountries"]) {
            if (!country.is_string()) {
                CSimpleLogger::error("All items in 'allowedCountries' must be strings");
                return false;
            }
            countries.push_back(country.get<std::string>());
        }

        return true;
    } catch (const json::parse_error& e) {
        CSimpleLogger::error("JSON parse error: " + std::string(e.what()));
        return false;
    } catch (const std::exception& e) {
        CSimpleLogger::error("Exception during JSON parsing: " + std::string(e.what()));
        return false;
    }
}

/**
 * Creates JSON response
 * @param allowed true for "Allowed", false for "Denied"
 * @return JSON response object
 */
json CValidateCountryIP::createResponse(bool allowed) {
    json response;
    response["Access"] = allowed ? "Allowed" : "Denied";
    return response;
}
