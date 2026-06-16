#ifndef VALIDATE_COUNTRY_IP_H
#define VALIDATE_COUNTRY_IP_H

#include <string>
#include "json/json.hpp"
#include "ip_validator.h"
#include "countries_list.h"
#include "geo_ip_database.h"

using json = nlohmann::json;

/**
 * Class to validate if an IP address belongs to allowed countries
 */
class CValidateCountryIP {
private:
    CGeoIPDatabase mGeoDatabase;
    CCountriesList allowedCountries;
    std::string mDBFilePath;
public:
    /**
     * Constructor - initializes the validator with GeoIP database path
     * @param dbFilePath Path to the GeoIP database file
     */
    explicit CValidateCountryIP(const std::string& dbFilePath);

    /**
     * Destructor
     */
    ~CValidateCountryIP();

    /**
     * Validates if an IP address is allowed based on country whitelist
     * @param jsonInput JSON string with format:
     *        {
     *          "ip": "8.8.8.8",
     *          "allowedCountries": ["US", "CA"]
     *        }
     * @return JSON response { "Access": "Allowed" } or { "Access": "Denied" }
     */
    json validateAccess(const std::string& jsonInput);

private:
    /**
     * Parses the input JSON and validates format
     * @param jsonInput JSON string to parse
     * @param ipAddress Output parameter for IP address
     * @param countries Output parameter for allowed countries list
     * @return true if parsing successful, false otherwise
     */
    bool parseInput(const std::string& jsonInput, std::string& ipAddress, std::vector<std::string>& countries);

    /**
     * Creates JSON response
     * @param allowed true for "Allowed", false for "Denied"
     * @return JSON response object
     */
    json createResponse(bool allowed);
};

#endif // VALIDATE_COUNTRY_IP_H
