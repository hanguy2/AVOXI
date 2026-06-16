#ifndef GEO_IP_DATABASE_H
#define GEO_IP_DATABASE_H

#include <string>
#include <maxminddb.h>

/**
 * Class to manage MaxMind GeoIP database operations
 */
class CGeoIPDatabase {
private:
    MMDB_s mmdb;
    bool isOpened;

public:
    /**
     * Constructor - initializes the database as closed
     */
    CGeoIPDatabase();

    /**
     * Destructor - closes the database if it's open
     */
    ~CGeoIPDatabase();

    /**
     * Opens the GeoIP database file
     * @param dbFilePath Path to the MMDB database file
     * @return true if database opened successfully, false otherwise
     */
    bool open(const std::string& dbFilePath);

    /**
     * Closes the database if it's open
     */
    void close();

    /**
     * Checks if the database is open
     * @return true if database is open, false otherwise
     */
    bool isOpen() const;

    /**
     * Checks if the database is ready for lookup
     * @return true if database is open and ready, false otherwise
     */
    bool isReady() const;

    /**
     * Looks up country information for a given IP address
     * @param ipAddress The IP address to look up (IPv4 or IPv6)
     * @param countryName Output parameter to store the country name
     * @return true if country is found, false otherwise
     */
    bool lookupCountry(const std::string& ipAddress, std::string& countryName);

    /**
     * Looks up if a country exists for given IP (simplified version)
     * @param ipAddress The IP address to look up
     * @return true if country data is found for the IP, false otherwise
     */
    bool lookupCountry(const std::string& ipAddress);

    /**
     * Gets the last error message from the library
     * @param status The status code from MMDB operation
     * @return Error message string
     */
    static std::string getErrorMessage(int status);
};

#endif // GEO_IP_DATABASE_H
