#include <stdio.h>
#include <maxminddb.h>

int main() {
    // 1. Path to your local GeoLite2-City.mmdb database file
    const char *db_filename = "./GeoLite2-Country.mmdb";
    // The target IP address to look up
    const char *ip_address = "216.58.216.163"; 

    MMDB_s mmdb;
    int status = MMDB_open(db_filename, MMDB_MODE_MMAP, &mmdb);

    if (MMDB_SUCCESS != status) {
        fprintf(stderr, "Cannot open maxmind db: %s\n", MMDB_strerror(status));
        return 1;
    }

    int gai_error, mmdb_error;
    MMDB_lookup_result_s result = MMDB_lookup_string(&mmdb, ip_address, &gai_error, &mmdb_error);

    if (0 != gai_error) {
        fprintf(stderr, "Getaddrinfo error: %s\n", gai_strerror(gai_error));
        MMDB_close(&mmdb);
        return 1;
    }

    if (0 != mmdb_error) {
        fprintf(stderr, "MMDB error: %s\n", MMDB_strerror(mmdb_error));
        MMDB_close(&mmdb);
        return 1;
    }

    if (result.found_entry) {
        MMDB_entry_data_s entry_data;
        
        // --- Look up Country Name (English) ---
        int status_country = MMDB_get_value(&result.entry, &entry_data, 
            "country", "names", "en", NULL);
        if (status_country == MMDB_SUCCESS && entry_data.has_data) {
            printf("Country: %.*s\n", entry_data.data_size, entry_data.utf8_string);
        }

        // --- Look up City Name (English) ---
        int status_city = MMDB_get_value(&result.entry, &entry_data, 
            "city", "names", "en", NULL);
        if (status_city == MMDB_SUCCESS && entry_data.has_data) {
            printf("City: %.*s\n", entry_data.data_size, entry_data.utf8_string);
        }

        // --- Look up Latitude ---
        int status_lat = MMDB_get_value(&result.entry, &entry_data, 
            "location", "latitude", NULL);
        if (status_lat == MMDB_SUCCESS && entry_data.has_data) {
            printf("Latitude: %f\n", entry_data.double_value);
        }

        // --- Look up Longitude ---
        int status_long = MMDB_get_value(&result.entry, &entry_data, 
            "location", "longitude", NULL);
        if (status_long == MMDB_SUCCESS && entry_data.has_data) {
            printf("Longitude: %f\n", entry_data.double_value);
        }
    } else {
        printf("No entry found for IP: %s\n", ip_address);
    }

    MMDB_close(&mmdb);
    return 0;
}

