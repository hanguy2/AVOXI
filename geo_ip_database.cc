#include "geo_ip_database.h"
#include "simple_logger.h"
#include <cstring>

/**
 * Constructor - initializes the database as closed
 */
CGeoIPDatabase::CGeoIPDatabase() : isOpened(false) {
    memset(&mmdb, 0, sizeof(MMDB_s));
}

/**
 * Destructor - closes the database if it's open
 */
CGeoIPDatabase::~CGeoIPDatabase() {
    close();
}

/**
 * Opens the GeoIP database file
 * @param dbFilePath Path to the MMDB database file
 * @return true if database opened successfully, false otherwise
 */
bool CGeoIPDatabase::open(const std::string& dbFilePath) {
    if (isOpened) {
        close();
    }

    int status = MMDB_open(dbFilePath.c_str(), MMDB_MODE_MMAP, &mmdb);
    
    if (status != MMDB_SUCCESS) {
        std::string errorMsg = "Failed to open MMDB database: " + std::string(MMDB_strerror(status));
        CSimpleLogger::error(errorMsg);
        isOpened = false;
        return false;
    }
    
    isOpened = true;
    return true;
}

/**
 * Closes the database if it's open
 */
void CGeoIPDatabase::close() {
    if (isOpened) {
        MMDB_close(&mmdb);
        isOpened = false;
        memset(&mmdb, 0, sizeof(MMDB_s));
    }
}

/**
 * Checks if the database is open
 * @return true if database is open, false otherwise
 */
bool CGeoIPDatabase::isOpen() const {
    return isOpened;
}

/**
 * Checks if the database is ready for lookup
 * @return true if database is open and ready, false otherwise
 */
bool CGeoIPDatabase::isReady() const {
    return isOpened;
}

/**
 * Looks up country information for a given IP address
 * @param ipAddress The IP address to look up (IPv4 or IPv6)
 * @param countryName Output parameter to store the country name
 * @return true if country is found, false otherwise
 */
bool CGeoIPDatabase::lookupCountry(const std::string& ipAddress, std::string& countryName) {
    if (!isReady()) {
        return false;
    }

    int gai_error, mmdb_error;
    MMDB_lookup_result_s result = MMDB_lookup_string(&mmdb, ipAddress.c_str(), 
                                                     &gai_error, &mmdb_error);

    if (gai_error != 0) {
        std::string errorMsg = "GAI error during country lookup for IP " + ipAddress + ": " + gai_strerror(gai_error);
        CSimpleLogger::error(errorMsg);
        return false;
    }

    if (mmdb_error != MMDB_SUCCESS) {
        std::string errorMsg = "MMDB error during country lookup for IP " + ipAddress + ": " + MMDB_strerror(mmdb_error);
        CSimpleLogger::error(errorMsg);
        return false;
    }

    if (!result.found_entry) {
        return false;
    }

    MMDB_entry_data_s entry_data;
    int status = MMDB_get_value(&result.entry, &entry_data, 
                                "country", "names", "en", NULL);

    if (status == MMDB_SUCCESS && entry_data.has_data) {
        countryName.assign(entry_data.utf8_string, entry_data.data_size);
        return true;
    }

    if (status != MMDB_SUCCESS) {
        std::string errorMsg = "Failed to get country value for IP " + ipAddress + ": " + MMDB_strerror(status);
        CSimpleLogger::error(errorMsg);
    }

    return false;
}

/**
 * Looks up if a country exists for given IP (simplified version)
 * @param ipAddress The IP address to look up
 * @return true if country data is found for the IP, false otherwise
 */
bool CGeoIPDatabase::lookupCountry(const std::string& ipAddress) {
    if (!isReady()) {
        return false;
    }

    int gai_error, mmdb_error;
    MMDB_lookup_result_s result = MMDB_lookup_string(&mmdb, ipAddress.c_str(), 
                                                     &gai_error, &mmdb_error);

    if (gai_error != 0) {
        std::string errorMsg = "GAI error during country lookup for IP " + ipAddress + ": " + gai_strerror(gai_error);
        CSimpleLogger::error(errorMsg);
        return false;
    }

    if (mmdb_error != MMDB_SUCCESS) {
        std::string errorMsg = "MMDB error during country lookup for IP " + ipAddress + ": " + MMDB_strerror(mmdb_error);
        CSimpleLogger::error(errorMsg);
        return false;
    }

    if (!result.found_entry) {
        return false;
    }

    MMDB_entry_data_s entry_data;
    int status = MMDB_get_value(&result.entry, &entry_data, 
                                "country", "names", "en", NULL);

    if (status != MMDB_SUCCESS) {
        std::string errorMsg = "Failed to get country value for IP " + ipAddress + ": " + MMDB_strerror(status);
        CSimpleLogger::error(errorMsg);
        return false;
    }

    return entry_data.has_data;
}

/**
 * Gets the last error message from the library
 * @param status The status code from MMDB operation
 * @return Error message string
 */
std::string CGeoIPDatabase::getErrorMessage(int status) {
    return std::string(MMDB_strerror(status));
}
